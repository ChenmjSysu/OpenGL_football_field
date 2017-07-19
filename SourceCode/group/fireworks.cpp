#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include "base.h"
#include <gl/glaux.h>// header file for the glaux library
#include "fps.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "winmm.lib")

FPS m_fps;

bool g_brainbow = true; // rainbow mode on / off
bool g_sbpressed;       // spacebar pressed
bool g_rtpressed;       // return key pressed

float g_speed = 60.0f;  // particles move speed, 60 fps
float g_xspeed, g_yspeed, g_zoom = -40.0f;
GLuint g_currentcolor = 0;
GLuint g_delay;   // delay of rainbow effect
GLuint g_texnames[2];   // storage for two texture

const int MAX_FIRES = 1;       // 最多5个烟花
const int MAX_PARTICLES = 32; // 每个烟花升空散开的小烟花个数
const int MAX_TAILS = 4;      // 烟花尾迹


float v_foot[MAX_PARTICLES] = {2.5, 2.4, 2.4, 2.3, 2.3, 2.2, 2.1, 2,
								 2, 2.1, 2.2, 2.5, 3, 3.6, 4.7, 5,
								 5, 4.5, 4, 3.5, 3.0, 2.1, 1.8, 1.5,
                                 1.6, 2.1, 2.2, 2.3, 2.3, 2.4, 2.4, 2.5};
 
float v_circle[MAX_PARTICLES] = {2, 2, 2, 2, 2, 2, 2, 2,
								 2, 2, 2, 2, 2, 2, 2, 2,
							     2, 2, 2, 2, 2, 2, 2, 2,
                                 2, 2, 2, 2, 2, 2, 2, 2,};

float v_star[MAX_PARTICLES] = {2, 3, 4, 5, 4, 3, 2, 3,
							   4, 4.5, 5, 4, 3, 2, 3, 4,
							   5, 4, 3, 2, 3, 4, 5, 4,
                               3, 3.5, 2, 3, 4, 5, 4, 3,};

float v_spiral[MAX_PARTICLES] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7,
							     1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5,
							     2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3,
                                 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1};

float* v_shape;
int shape_type = 0;


typedef struct {
   float r, g, b;      /* color */
   float x, y, z;      /* position  */
   float xs, ys, zs;   /* speed  */
   float xg, yg, zg;   /* gravity  */
   bool up;         /* up or down */
} Particle;

typedef struct {
   Particle particle[MAX_PARTICLES][MAX_TAILS]; // 烟花系统数组
   float life, fade, rad; // 生命，衰减速度，x-z平面上的运动速度
} Fire;

Fire g_fires[MAX_FIRES];

static GLfloat colors[12][3] = { // Rainbow Of Colors
   {1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
   {0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
   {0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

// loads a bitmap image
AUX_RGBImageRec* LoadBMP(char* filename) {
   if (filename == NULL) {
      return NULL;
   }

   FILE* file = NULL;
   if (fopen_s(&file, filename, "r") == 0) {
      fclose(file);
      return auxDIBImageLoadA(filename);
   }
   return NULL;
}

 //load bitmap and convert to textures
 //The image height and width MUST be a power of 2. The width and height must be 
 //at least 64 pixels, and for compatability reasons, shouldn't be more than 256 
 //pixels. If the image you want to use is not 64, 128 or 256 pixels on the width 
 //or height, resize it in an art program. There are ways around this limitation, 
 //but for now we'll just stick to standard texture sizes.
int LoadGLTexture() {
   AUX_RGBImageRec* teximage[1]; // create storage space for the texture
   memset(teximage, 0, sizeof(void*)); // set the pointer to NULL

   if (!(teximage[0] = LoadBMP("resource/fireworks/particle.bmp"))) {
      return FALSE;
   }

   glGenTextures(1, g_texnames);// provide unused texture names
   for (int i = 0; i < 1; i++) {
     glBindTexture(GL_TEXTURE_2D, g_texnames[i]); // create a new texture object and assigned name
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexImage2D(GL_TEXTURE_2D, 0, 3, teximage[i]->sizeX, // define the texture
       teximage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, teximage[i]->data);

     if (teximage[i]) {
       if (teximage[i]->data) {
         free(teximage[i]->data);
       }
       free(teximage[i]);
     }
   }
   return TRUE;
}

void ResetFire(int loop) {
   // init position
   float xtemp = rand()%22 - 11.f;
   float ytemp = -1*rand()%4 - 8.f;
   float ztemp = -1.0f*(rand()%5) - 10.f;
   float speed = (rand()%20 + 100.f) / 480.0f * 1.7;

   g_fires[loop].life = 1.5f;
   g_fires[loop].fade = (float) ((rand()%100)/20000 + 0.002);
   g_fires[loop].rad  = (rand()%12 + 24.0f) / 480.0f;

   for (int loop1 = 0; loop1 < MAX_PARTICLES; loop1++) {
      Particle* pat = &g_fires[loop].particle[loop1][0];
      //初始颜色
      pat->r = 1.0f; pat->g = 1.0f; pat->b = 1.0f;
      //初始位置
      pat->x = xtemp; pat->y = ytemp; pat->z = ztemp;
      //初始速度
      pat->xs = 0.0f; pat->ys = speed; pat->zs = 0.0f;
      //初始加速度
      pat->xg = 0.0f; pat->yg = -0.5f/480.0f; pat->zg = 0.0f;
      pat->up = true;

      //尾部初始化
      for(int loop2 = 1; loop2 < MAX_TAILS; loop2++) {
         pat = &g_fires[loop].particle[loop1][loop2];
         pat->x = g_fires[loop].particle[loop1][0].x;
         pat->y = g_fires[loop].particle[loop1][0].y;
         pat->z = g_fires[loop].particle[loop1][0].z;
      } //for loop2 end
   }//for loop1 end
   switch(shape_type) {
   case 0:
	   v_shape = v_circle;
	   break;
   case 1:
	   v_shape = v_foot;
	   break;
   case 2:
	   v_shape = v_star;
	   break;
   case 3:
	   v_shape = v_spiral;
	   break;
   }
}

bool Initialize() {
  m_fps.fixFps(60);
  if (!LoadGLTexture()) {
    return false;
  }

  glEnable(GL_TEXTURE_2D);
  //glShadeModel(GL_SMOOTH);   // enables smooth shading
  //glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // black background
  //glClearDepth(1.0f);     // depth buffer setup
  //glEnable(GL_DEPTH_TEST);// enables depth testing
  //glDepthFunc(GL_LEQUAL); // the type of depth test to do
  //glDisable(GL_DEPTH_TEST);
  //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // really nice perspective calculations
  //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  for(int loop = 0; loop < MAX_FIRES; loop++) {
    ResetFire(loop);
  }

  glDisable(GL_TEXTURE_2D);
  return true;
}

void Deinitialize() {
  glDeleteTextures(2, g_texnames);
}

void Selection() {
  return;
}

bool Update() {
  DWORD dt = m_fps.difftime();

  g_delay++;
  return true;
}

bool Draw() {
  
  float dt = m_fps.difftime() * 0.001f;
  float factor = dt * g_speed;

  // 背景颜色随烟花颜色变化
  //float rgb_max_value = 0.0f;
  //for(int loop = 0; loop < MAX_FIRES; loop++) {
  //  Particle& p = g_fires[loop].particle[0][0];
  //  float rgb_value = p.r + p.g + p.b;
  //  if (rgb_value > rgb_max_value) {
  //    rgb_max_value = rgb_value;
  //    glColor4f(p.r, p.g, p.b, 1.0f);
  //  }
  //}
  //glColor4f(1, 1, 1, 0.5f);
  glBindTexture(GL_TEXTURE_2D, g_texnames[0]);
  for(int loop = 0; loop < MAX_FIRES; loop++) {
    int color = rand()%12;
    for (int loop1 = 0; loop1 < MAX_PARTICLES; loop1++) {
      for(int loop2 = 0; loop2 < MAX_TAILS; loop2++) {
        float x = g_fires[loop].particle[loop1][loop2].x;
        float y = g_fires[loop].particle[loop1][loop2].y;
        float z = g_fires[loop].particle[loop1][loop2].z + g_zoom;
        float dt = 1 - (float)loop2/MAX_TAILS;
		//设置颜色
        glColor4f(g_fires[loop].particle[loop1][0].r, 
          g_fires[loop].particle[loop1][0].g, 
          g_fires[loop].particle[loop1][0].b, 
          g_fires[loop].life * dt);


		glPushMatrix();
        glScalef(1, 1, 1);
		glTranslatef(x, y, z);
        float size = 1.0f * dt;

		glBegin(GL_QUADS);
			glTexCoord2d(0,0); glVertex3f(-size, -size, 0); // Bottom Left				
			glTexCoord2d(1,0); glVertex3f(size, -size, 0); // Bottom Right			
			glTexCoord2d(1,1); glVertex3f(size, size, 0); // Top Right
			glTexCoord2d(0,1); glVertex3f(-size, size, 0); // Top Left			
		glEnd();
		glPopMatrix();
      }

      // update position（尾巴）
      for(int loop2 = MAX_TAILS-1; loop2 > 0; loop2--) {
        g_fires[loop].particle[loop1][loop2].x = g_fires[loop].particle[loop1][loop2-1].x;
        g_fires[loop].particle[loop1][loop2].y = g_fires[loop].particle[loop1][loop2-1].y;
        g_fires[loop].particle[loop1][loop2].z = g_fires[loop].particle[loop1][loop2-1].z;
      } //for loop2 end

	  //更新粒子的位置
      g_fires[loop].particle[loop1][0].x += g_fires[loop].particle[loop1][0].xs * factor;
      g_fires[loop].particle[loop1][0].y += g_fires[loop].particle[loop1][0].ys * factor;
      g_fires[loop].particle[loop1][0].z += g_fires[loop].particle[loop1][0].zs * factor;

      //更新粒子y方向的速度
      float yd = g_fires[loop].particle[loop1][0].yg * factor;
      g_fires[loop].particle[loop1][0].ys += yd;
      if (g_fires[loop].particle[loop1][0].up && g_fires[loop].particle[loop1][0].ys < -yd) {
        g_fires[loop].particle[loop1][0].up = false;
        //int color = rand()%12;
        g_fires[loop].particle[loop1][0].r = colors[color][0];
        g_fires[loop].particle[loop1][0].g = colors[color][1];
        g_fires[loop].particle[loop1][0].b = colors[color][2];
		
        // 更新x-z的速度
        //double radian = 3.14159*loop1*15.0/180.0;
        //g_fires[loop].particle[loop1][0].xs = (float)(g_fires[loop].rad*sin(radian));
        //g_fires[loop].particle[loop1][0].zs = (float)(g_fires[loop].rad*cos(radian));
		double radian = 3.14159*loop1*13.7/180.0;
		g_fires[loop].particle[loop1][0].xs = (float)(v_shape[loop1]/50*sin(radian));
        g_fires[loop].particle[loop1][0].zs = (float)(v_shape[loop1]/50*cos(radian));
      }
    }

    g_fires[loop].life -= g_fires[loop].fade;
	if (g_fires[loop].life < 0) {
      ResetFire(loop);
    }
	if((g_fires[loop].particle[0][0].y < -10 && !g_fires[loop].particle[0][0].up)) {
	    ResetFire(loop);
	}
  }
  glDisable(GL_TEXTURE_2D);  
  return true;
}