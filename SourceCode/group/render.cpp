#include "render.h"

extern CVector3 Vector(CVector3 vPoint1, CVector3 vPoint2);
extern CVector3 AddVector(CVector3 vPoint1, CVector3 vPoint2);
extern CVector3 Normalize(CVector3 vNormal);
extern CVector3 DivideVectorByScaler(CVector3 vVector1, float Scaler);
extern CVector3 Cross(CVector3 vVector1, CVector3 vVector2);
extern int shape_type;

SkyBox m_skybox;
Court football_court;
Terrain terrain;

bool show_fireworks = false;
bool show_help = false;
bool lighting = true;
int update_return = 0;

extern bool Initialize();
extern bool Update();
extern bool Draw();
extern FPS m_fps;

CVector3 eye_point = CVector3(0, 2, 10);
CVector3 center_point = CVector3(-2, 2, 0);
CVector3 up_point = CVector3(0, 1, 0);

//CVector3 eye_point = CVector3(-1.9, 59.8, 38.9);
//CVector3 center_point = CVector3(-1.2, 56.3, 29.4);
//CVector3 up_point = CVector3(0, 1, 0);

float y_rotate = 0.0f;
float x_rotate = 0.0f;
float y_rotate_step = 2;
float x_rotate_step = 2;
float move_step = 2;

//��������ϵ
void draw_axes() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(50, 0, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 50, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 50);
	glEnd();
	glPopMatrix();
}

void keyAction(unsigned char key, int x, int y) {
	//printf("%d %c\n", key, key);
	double matrix[16];

	//���Ͽ�
	if(key == 'i' || key == 'I') {
		CVector3 temp = Vector(center_point, eye_point);
		x_rotate += x_rotate_step;
		float y = temp.y;
		temp.y = 0;
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		//������ת��
		glRotatef(-90, 0, 1, 0);
		glGetDoublev(GL_MODELVIEW_MATRIX, matrix);         //��ʱ����ת90�ȵõ���ת��
		CVector3 rotate_axis = transform(matrix, temp);     //������ת��

		glLoadIdentity();
		glRotatef(x_rotate_step, rotate_axis.x, rotate_axis.y, rotate_axis.z);  //����ת����ת
		glGetDoublev(GL_MODELVIEW_MATRIX, matrix);                              //��ȡ��ת����		
		temp.y = y;
		CVector3 rotated = transform(matrix, temp);          //��ת
		rotated = AddVector(rotated, eye_point);
		center_point.assign(rotated);
		glPopMatrix();
	}
	//���¿�
	if(key == 'k' || key == 'K') {
		CVector3 temp = Vector(center_point, eye_point);
		x_rotate += x_rotate_step;
		float y = temp.y;
		temp.y = 0;
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		//������ת��
		glRotatef(-90, 0, 1, 0);
		glGetDoublev(GL_MODELVIEW_MATRIX, matrix);         //��ʱ����ת90�ȵõ���ת��
		CVector3 rotate_axis = transform(matrix, temp);     //������ת��

		glLoadIdentity();
		glRotatef(-x_rotate_step, rotate_axis.x, rotate_axis.y, rotate_axis.z);  //����ת����ת
		glGetDoublev(GL_MODELVIEW_MATRIX, matrix);                              //��ȡ��ת����		
		temp.y = y;
		CVector3 rotated = transform(matrix, temp);          //��ת
		rotated = AddVector(rotated, eye_point);
		center_point.assign(rotated);
		glPopMatrix();
	}
	//����ת
	else if(key == 'd' || key == 'D') {		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();        //���浱ǰջ������
		glLoadIdentity();      //����ջ������Ϊ��λ����
		y_rotate -= y_rotate_step;       //��¼�ܵ���ת�Ƕȣ���ʱûʲô��
		glRotatef(-y_rotate_step, 0, 1, 0); //������ת����y_rotate_step��һ��������������ÿ����ת�ĽǶ� 
		glGetDoublev(GL_MODELVIEW_MATRIX, matrix);  //��ջ������ȡ����matrix��
		CVector3 temp = Vector(center_point, eye_point);//�������Ƶ�y���ϣ�Ŀ����λ��
		CVector3 rotated = transform(matrix, temp);  //�����Ŀ���λ����y����ת
		rotated = AddVector(rotated, eye_point);  //Ŀ������յ�λ��
		center_point.assign(rotated);
		glPopMatrix();
	}
	//����ת
	else if(key == 'a' || key == 'A') {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		y_rotate = y_rotate_step;
		glRotatef(y_rotate_step, 0, 1, 0);
		glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
		CVector3 temp = Vector(center_point, eye_point);
		CVector3 rotated = transform(matrix, temp);
		rotated = AddVector(rotated, eye_point);
		center_point.assign(rotated);
		glPopMatrix();
	}
	//��ǰ��
	else if(key == 'w' || key == 'W') {
		CVector3 temp = Vector(center_point, eye_point);
		temp = Normalize(temp);
		temp = DivideVectorByScaler(temp, 1 / move_step);
		center_point = AddVector(center_point, temp);
		eye_point = AddVector(eye_point, temp);		
	}
	//������
	else if(key == 's' || key == 'S') {
		CVector3 temp = Vector(eye_point, center_point);
		temp = Normalize(temp);
		temp = DivideVectorByScaler(temp, 1 / move_step);
		center_point = AddVector(center_point, temp);
		eye_point = AddVector(eye_point, temp);
	}
    //����
	else if(key == 'e' || key == 'E') {
		eye_point.y -= move_step;
		center_point.y -= move_step;
	}
	//����
	else if(key == 'q' || key == 'Q') {
		eye_point.y += move_step;
		center_point.y += move_step;
	}
	//��������Ϣ
	else if(key == 'p' || key == 'P') {
		printf("eye: %.1f, %.1f, %.1f\ncenter: %.1f, %.1f, %.1f\n",
			eye_point.x, eye_point.y, eye_point.z,
			center_point.x, center_point.y, center_point.z);
	}
    //�ƵĿ���
	else if(key == 'l' || key == 'L') {
		lighting = !lighting;
		if(lighting) {
			glEnable(GL_LIGHT0);
		}
		else {
			glDisable(GL_LIGHT0);
		}
	}
    //�̻�
	else if(key == 'f' || key == 'F') {
		show_fireworks = !show_fireworks;
		if(show_fireworks) {
		    shape_type++;
			shape_type = shape_type % 4;
		}
		Initialize();
		m_fps.reset();
	}
	else if(key == 'c' || key == 'C') {
		int s = football_court.player_a0.GetAnimation();
		football_court.player_a0.SetAnimation(++s);
	}
	//����
	else if(key == 'h' || key == 'H') {
		show_help = !show_help;		
	}

	glutPostRedisplay(); 

	if(eye_point.y < 0) eye_point.y = 0;
	if(center_point.y < 0) center_point.y = 0;
	glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
	gluLookAt(eye_point.x, eye_point.y, eye_point.z, 
		center_point.x, center_point.y, center_point.z,
		up_point.x, up_point.y, up_point.z);
}

void init() {
	set_light();
	create_bmp_text("Verdana", 17);
	terrain.init();
    m_skybox.init(600);
	m_skybox.load_texture("resource/skybox/up.tga", "resource/skybox/dn.tga", 
		"resource/skybox/ft.tga", "resource/skybox/bk.tga",
		"resource/skybox/lt.tga", "resource/skybox/rt.tga");
	football_court.init();

	glEnable(GL_DEPTH_TEST);
	football_court.player_a0.Load("resource/player/tris.md2", "resource/player/white.tga",  0.07f);
	football_court.player_a1.Load("resource/player/tris.md2", "resource/player/white.tga",  0.07f);
	football_court.player_a2.Load("resource/player/tris.md2", "resource/player/white.tga",  0.07f);
	football_court.player_a3.Load("resource/player/tris.md2", "resource/player/white.tga",  0.07f);
	football_court.player_a4.Load("resource/player/tris.md2", "resource/player/white.tga",  0.07f);

	football_court.player_b0.Load("resource/player/tris.md2", "resource/player/red.tga",  0.07f);
	football_court.player_b1.Load("resource/player/tris.md2", "resource/player/red.tga",  0.07f);
	football_court.player_b2.Load("resource/player/tris.md2", "resource/player/red.tga",  0.07f);
	football_court.player_b3.Load("resource/player/tris.md2", "resource/player/red.tga",  0.07f);
	football_court.player_b4.Load("resource/player/tris.md2", "resource/player/red.tga",  0.07f);	

	Initialize();
	m_fps.reset();
	show_fireworks = false;
}

//����
void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//��ʾ����
	if(show_help) help();
	//���õƹ�
	if(lighting) set_light();
	//����skybox
	glPushMatrix();
	glTranslatef(0, -50, 0);
	m_skybox.render(0, 0, 0);
	glPopMatrix();
	//���Ƶ���
	terrain.render();
	//������
	football_court.render();
	
	if(show_fireworks) {
		if(update_return == 0) {
			glPushAttrib(GL_CURRENT_BIT);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_COLOR_MATERIAL);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // really nice perspective calculations
			glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glColor3f(1, 1, 1);
			//Update();
			Draw();
			glPopAttrib();
			glColor3f(1, 1, 1);
			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
		else if(update_return == 1) {
		    Sleep(1);
		}
	}


	glutSwapBuffers(); //����������  
}

void set_light() {
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

	//����̫����,ƽ�й�
	GLfloat sun_direction[] = {0, 100, 0, 0};
	GLfloat sun_ambient[] = {1, 1, 1, 1};
	GLfloat sun_diffuse[] = {1, 1, 1, 1};
	GLfloat sun_specular[] = {1, 1, 1, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_specular);	
}

void Reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, width / height, 1, 2000);
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
	gluLookAt(eye_point.x, eye_point.y, eye_point.z, 
		center_point.x, center_point.y, center_point.z,
		up_point.x, up_point.y, up_point.z);
}

void idle() {
	if(show_fireworks) {
	    update_return = m_fps.update();
		update_return = 0;
	}
	float dt = 0.5;
	
	football_court.player_a0.Animate(dt);
	football_court.player_a1.Animate(dt);
	football_court.player_a2.Animate(dt);
	football_court.player_a3.Animate(dt);
	football_court.player_a4.Animate(dt);

	football_court.player_b0.Animate(dt);
	football_court.player_b1.Animate(dt);
	football_court.player_b2.Animate(dt);
	football_court.player_b3.Animate(dt);
	football_court.player_b4.Animate(dt);
	glutPostRedisplay(); 
}

//��ʾ����
void help() {
    glPushMatrix();
	glTranslatef(center_point.x, center_point.y + 1, center_point.z);
	render_bmp_text(0, 0, "Help:");
	glTranslatef(0, -0.3, 0);
	render_bmp_text(0, 0, "W(w): move forward");
	glTranslatef(0, -0.3, 0);
	render_bmp_text(0, 0, "S(s): move back");
	glTranslatef(0, -0.3, 0);
	render_bmp_text(0, 0, "A(a): turn left");
	glTranslatef(0, -0.3, 0);
	render_bmp_text(0, 0, "D(d): turn right");
	glTranslatef(0, -0.3, 0);
	render_bmp_text(0, 0, "Q(q): go up");
	glTranslatef(0, -0.3, 0);
	render_bmp_text(0, 0, "E(e): go down");
	glTranslatef(0, -0.3, 0);
	render_bmp_text(0, 0, "F(f): appear/disappear firework");
	glTranslatef(0, -0.3, 0);
	render_bmp_text(0, 0, "L(l): turn on/off lighting");

	glPopMatrix();
}