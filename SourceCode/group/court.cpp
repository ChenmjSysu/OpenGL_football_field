#include "court.h"

#include "base.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <gl\glaux.h>
#include <crtdbg.h>

//�����Ϸ������Ŀ��Ƶ�
GLfloat ctrl_points_data_up[3][3][3]= {
{{ 0.0f, GOAL_HEIGHT, GOAL_WIDTH },    
{ GOAL_LENGTH / 2, GOAL_HEIGHT - 0.5, GOAL_WIDTH },    
{ GOAL_LENGTH, GOAL_HEIGHT, GOAL_WIDTH }},

{{ 0.0f, GOAL_HEIGHT, GOAL_WIDTH / 2 },    
{ GOAL_LENGTH / 2, GOAL_HEIGHT - 2, GOAL_WIDTH / 2 },    
{ GOAL_LENGTH, GOAL_HEIGHT - 1, GOAL_WIDTH / 2 }},

{{ 0.0f, GOAL_HEIGHT, 0.0f },    
{ GOAL_LENGTH / 2, GOAL_HEIGHT - 0.5, 0.0f },    
{ GOAL_LENGTH, GOAL_HEIGHT, 0.0f }}};

//����һ������Ŀ��Ƶ�
GLfloat ctrl_points_data_side[3][3][3]= {
{{ 0.0f, GOAL_HEIGHT, 0.0f },    
{ GOAL_LENGTH / 2, GOAL_HEIGHT - 0.5, 0.0f },    
{ GOAL_LENGTH, GOAL_HEIGHT, 0.0f }},

{{ 0.0f, GOAL_HEIGHT / 2, 0.0f },    
{ GOAL_LENGTH / 2, GOAL_HEIGHT / 2 - 0.5, 0.0f },    
{ GOAL_LENGTH, GOAL_HEIGHT / 2, 0.0f }},

{{ 0.0f, 0.0f, 0.0f },    
{ GOAL_LENGTH / 2, 0.0f - 0.5, 0.0f },    
{ GOAL_LENGTH, 0.0f, 0.0f }}};

//�����������Ŀ��Ƶ�
GLfloat ctrl_points_data_back[3][3][3]= {
{{ GOAL_LENGTH, GOAL_HEIGHT, GOAL_WIDTH },    
{ GOAL_LENGTH, GOAL_HEIGHT / 2, GOAL_WIDTH },    
{ GOAL_LENGTH, 0.0f, GOAL_WIDTH }},

{{ GOAL_LENGTH, GOAL_HEIGHT - 1, GOAL_WIDTH  / 2},    
{ GOAL_LENGTH, GOAL_HEIGHT / 2, GOAL_WIDTH / 2 },    
{ GOAL_LENGTH, -0.2f, GOAL_WIDTH / 2 }},

{{ GOAL_LENGTH, GOAL_HEIGHT, 0.0f },    
{ GOAL_LENGTH, GOAL_HEIGHT / 2, 0.0f },    
{ GOAL_LENGTH, 0.0f, 0.0f }}};

//����������֧�Ÿ˵Ŀ��Ƶ�
GLfloat net_bar_ctrl_points[4][3] = {
{ GOAL_LENGTH, GOAL_HEIGHT, 0 },
{ GOAL_LENGTH * (BACK_X_SCALE * 0.8), GOAL_HEIGHT * (BACK_Y_SCALE * 0.8), -GOAL_WIDTH * 0.1f },
{ GOAL_LENGTH * (BACK_X_SCALE * 0.9), GOAL_HEIGHT * (BACK_Y_SCALE * 0.9 ) , -GOAL_WIDTH * 0.15f },
{ GOAL_LENGTH * BACK_X_SCALE, GOAL_HEIGHT * BACK_Y_SCALE, -GOAL_WIDTH * 0.2f }};

//�����油ϯ�Ϸ��İ�
GLfloat ctrl_points_bench_seat_up[3][3][3]= {
{{ 0.0f, BENCH_SEAT_HEIGHT, 0.0f },    
{ BENCH_SEAT_LENGTH * 0.7, BENCH_SEAT_HEIGHT * 1.3, 0.0f },    
{ BENCH_SEAT_LENGTH, 0.0f, 0.0f }},

{{ 0.0f, BENCH_SEAT_HEIGHT, BENCH_SEAT_WIDTH / 2 },    
{ BENCH_SEAT_LENGTH * 0.7, BENCH_SEAT_HEIGHT * 1.3, BENCH_SEAT_WIDTH / 2 },    
{ BENCH_SEAT_LENGTH, 0.0f, BENCH_SEAT_WIDTH / 2 }},

{{ 0.0f, BENCH_SEAT_HEIGHT, BENCH_SEAT_WIDTH },    
{ BENCH_SEAT_LENGTH * 0.7, BENCH_SEAT_HEIGHT * 1.3, BENCH_SEAT_WIDTH },    
{ BENCH_SEAT_LENGTH, 0.0f, BENCH_SEAT_WIDTH }}};


void Court::load_texture() {
	load_tga_texture("resource/grass.tga", grass_texture_id);
	load_tga_texture("resource/shuinidi.tga", floor_texture_id);
	load_tga_texture("resource/shuinidi2.tga", floor2_texture_id);
	load_tga_texture("resource/shuiniqiang.tga", wall_texture_id);
	load_tga_texture("resource/ad1.tga", ad1_texture_id);
	load_tga_texture("resource/ad2.tga", ad2_texture_id);
	load_tga_texture("resource/audience.tga", audience_texture_id);
	load_tga_texture("resource/football.tga", football_texture_id);
    load_tga_texture("resource/audience_seat_vertical.tga", audience_seat_vertical_texture_id);
	load_tga_texture("resource/audience_seat_horizontal.tga", audience_seat_horizontal_texture_id);

	load_tga_texture("resource/third_ad1.tga", third_ad1_texture_id);
	load_tga_texture("resource/third_ad2.tga", third_ad2_texture_id);
	load_tga_texture("resource/third_ad3.tga", third_ad3_texture_id);
	load_tga_texture("resource/third_ad4.tga", third_ad4_texture_id);

	load_tga_texture("resource/middle_wall1.tga", middle_wall1_texture_id);
	load_tga_texture("resource/middle_wall2.tga", middle_wall2_texture_id);
	load_tga_texture("resource/middle_wall3.tga", middle_wall3_texture_id);
	load_tga_texture("resource/middle_wall4.tga", middle_wall4_texture_id);

	load_tga_texture("resource/wall_outside.tga", wall_outside_texture_id);
	load_tga_texture("resource/wall_inside.tga", wall_inside_texture_id);

	load_tga_texture("resource/tv_forward.tga", tv_texture_id[0]);    //ǰ
	load_tga_texture("resource/tv_back.tga", tv_texture_id[1]);       //��
	load_tga_texture("resource/tv_left.tga", tv_texture_id[2]);       //��
	load_tga_texture("resource/tv_right.tga", tv_texture_id[3]);      //��
	load_tga_texture("resource/tv_bottom.tga", tv_texture_id[4]);     //��
	load_tga_texture("resource/tv_top.tga", tv_texture_id[5]);        //��
	

	glGenTextures(1, &env_texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, env_texture_id);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // set the texture coordinate generation mode to reflection mapping
    glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGenf(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
}

//  ���ļ��д�������
void CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID)
{
	AUX_RGBImageRec *pBitmap = NULL;
	
	if(!strFileName)									// ����޴��ļ�����ֱ�ӷ���
		return;

	pBitmap = auxDIBImageLoadA(strFileName);				// װ��λͼ������������
	
	if(pBitmap == NULL)									// ���װ��λͼʧ�ܣ����˳�
		exit(0);

	// ��������
	glGenTextures(1, &textureArray[textureID]);

	// �������ض����ʽ
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitmap->sizeX, pBitmap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitmap->data);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

	if (pBitmap)										// �ͷ�λͼռ�õ���Դ
	{
		if (pBitmap->data)						
		{
			free(pBitmap->data);				
		}

		free(pBitmap);					
	}
}

Court::Court() {
	show_audience = false;
}

void Court::load_3ds_model(char* filename, CLoad3DS& loder, t3DModel& model, unsigned int* texture) {
    loder.Import3DS(&model, filename);       //�������˵�ģ��
	// �������еĲ���
	for(int i = 0; i < model.numOfMaterials; i++) {
		glEnable(GL_TEXTURE_2D);
		// �ж��Ƿ���һ���ļ���
		if(strlen(model.pMaterials[i].strFile) > 0) {
			CTargaImage image;
			//��������
			int len = strlen(model.pMaterials[i].strFile);
			model.pMaterials[i].strFile[len - 3] = 't';
			model.pMaterials[i].strFile[len - 2] = 'g';
			model.pMaterials[i].strFile[len - 1] = 'a';
			image.Load(model.pMaterials[i].strFile);
			glGenTextures(1, &texture[i]);
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());
			image.Release();
			//  ʹ�������ļ�������װ��λͼ
			//CreateTexture(g_Texture, g_3DModel.pMaterials[i].strFile, i);			
		}
		// ���ò��ʵ�����ID
		model.pMaterials[i].texureId = i;
	}
}

void Court::init() {	
	//������ͼ
	load_texture();
	//��������ģ��
	load_3ds_model(BENCH_FILENAME, seat_Load3ds, seat_model, seat_models_texture);
	//��������ģ��
	load_3ds_model(RAILING_FILENAME, railing_Load3ds, railing_model, railing_models_texture);

	//������ʾ�б��������油ϯ����ģ��
	seat_model_index = glGenLists(1);
	if( seat_model_index != 0) {
		glNewList(seat_model_index, GL_COMPILE);
		draw_3ds_model(seat_model, seat_models_texture);
		glEndList();
	}
	//������ʾ�б�����������ģ��
	railing_model_index = glGenLists(1);
	if( railing_model_index != 0) {
		glNewList(railing_model_index, GL_COMPILE);
		draw_3ds_model(railing_model, railing_models_texture);
		glEndList();
	}

	//������ʾ�б�����������
	goal_index = glGenLists(1);
	if( goal_index != 0) {
		glNewList(goal_index, GL_COMPILE);
		draw_goal();
		glEndList();
	}

	//������ʾ�б������ƹ���
	audience_index = glGenLists(1);
	if( audience_index != 0) {
		glNewList(audience_index, GL_COMPILE);
		draw_audience();
		glEndList();
	}
}

//��Ⱦ��
void Court::render() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	
	draw_match_floor();
	draw_advertisement();
	draw_models();
	
	glCallList(audience_index);
	//draw_audience();
	//��������油ϯ
	glPushMatrix();
	glTranslatef(MATCH_HALF_WIDTH / 2, 0, COURT_HALF_HEIGHT);
	glRotatef(-90, 0, 1, 0);
	draw_bench_seat();
	glPopMatrix();

	//�����Ҳ��油ϯ
	glPushMatrix();
	glTranslatef(-MATCH_HALF_WIDTH / 2, 0, COURT_HALF_HEIGHT);
	glRotatef(-90, 0, 1, 0);
	draw_bench_seat();
	glPopMatrix();
	
    //�����Ҳ�����
	glPushMatrix();
	glTranslatef(MATCH_HALF_WIDTH + 0.1, 0, -GOAL_WIDTH / 2);
	glCallList(goal_index);
	glPopMatrix();
	
	//�����������
	glPushMatrix();
	glTranslatef(-MATCH_HALF_WIDTH - 0.1, 0, -GOAL_WIDTH / 2);
	glScalef(-1, 1, 1);
	glCallList(goal_index);
	glPopMatrix();

	//��������
	draw_football();
	//������ǽ
	draw_wall();
	//���ƴ���Ļ
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 3 + WALL_HEIGHT, -LEVEL_HORIZONTAL_DIS * 3.5 - COURT_AD_OFFSET2);
	draw_tv();
	glPopMatrix();
	glPushMatrix();
	glScalef(1, 1, -1);
	glTranslatef(0, LEVEL_VERTICAL_DIS * 3 + WALL_HEIGHT, -LEVEL_HORIZONTAL_DIS * 3.5 - COURT_AD_OFFSET2);
	draw_tv();
	glPopMatrix();
	draw_lines();
}

//�������ϵ���
void Court::draw_lines() {
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);    // ���û��
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

	glColor4f(1, 1, 1, 0.8);
	
	glLineWidth(2);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);  // Antialias the lines
	
	float half_width = MATCH_HALF_WIDTH;
	float half_height = MATCH_HALF_HEIGHT;
	float jinqu1 = 52.5;
	float jinqu2 = 20;
	float qiumen1 = 67.5f;
	float qiumen2 = 10.0f;
	float dianqiu = 60.0f;
	float point_r = 0.1f;

	glBegin(GL_LINES);
	    //�ϱ߽�
	    glVertex3f(-half_width, 0.01, -half_height);
		glVertex3f(half_width, 0.01, -half_height);
		//�±߽�
		glVertex3f(-half_width, 0.01, half_height);
		glVertex3f(half_width, 0.01, half_height);
		//��߽�
		glVertex3f(-half_width, 0.01, -half_height);
		glVertex3f(-half_width, 0.01, half_height);
		//�ұ߽�
		glVertex3f(half_width, 0.01, -half_height);
		glVertex3f(half_width, 0.01, half_height);

		//����
		glVertex3f(0, 0.01, -half_height);
		glVertex3f(0, 0.01, half_height);
	glEnd();		
	glBegin(GL_LINES);
		//����
		glVertex3f(-qiumen1, 0.01, -qiumen2);
		glVertex3f(-qiumen1, 0.01, qiumen2);
		glVertex3f(-half_width, 0.01, -qiumen2);
		glVertex3f(-qiumen1, 0.01, -qiumen2);
		glVertex3f(-half_width, 0.01, qiumen2);
		glVertex3f(-qiumen1, 0.01, qiumen2);
		//����
		glVertex3f(-jinqu1, 0.01, -jinqu2);
		glVertex3f(-jinqu1, 0.01, jinqu2);
		glVertex3f(-half_width, 0.01, -jinqu2);
		glVertex3f(-jinqu1, 0.01, -jinqu2);
		glVertex3f(-half_width, 0.01, jinqu2);
		glVertex3f(-jinqu1, 0.01, jinqu2);
	glEnd();	

	glPushMatrix();
	glScalef(-1, 1, 1);
	glBegin(GL_LINES);
		//����
		glVertex3f(-qiumen1, 0.01, -qiumen2);
		glVertex3f(-qiumen1, 0.01, qiumen2);
		glVertex3f(-half_width, 0.01, -qiumen2);
		glVertex3f(-qiumen1, 0.01, -qiumen2);
		glVertex3f(-half_width, 0.01, qiumen2);
		glVertex3f(-qiumen1, 0.01, qiumen2);
		//����
		glVertex3f(-jinqu1, 0.01, -jinqu2);
		glVertex3f(-jinqu1, 0.01, jinqu2);
		glVertex3f(-half_width, 0.01, -jinqu2);
		glVertex3f(-jinqu1, 0.01, -jinqu2);
		glVertex3f(-half_width, 0.01, jinqu2);
		glVertex3f(-jinqu1, 0.01, jinqu2);
	glEnd();	
	glPopMatrix();
	//����
	glPointSize(10);
	glPushMatrix();
	glTranslatef(-dianqiu, 0.01, -point_r);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj *point = gluNewQuadric();
	gluQuadricDrawStyle(point, GLU_FILL);
	gluDisk(point, 0, point_r, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(dianqiu, 0.01, -point_r);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(point, GLU_FILL);
	gluDisk(point, 0, point_r, 20, 20);
	gluDeleteQuadric(point);
	glPopMatrix();

	//��Ȧ
	int n = 400;
	float R = 10;
	glBegin(GL_LINE_LOOP);
    for(int i=0; i < n; ++i)
         glVertex3f(R*cos(2*3.14/n*i), 0.01, R*sin(2*3.14/n*i));
    glEnd();

	glBegin(GL_LINE_STRIP );
    for(int i=0; i < n; ++i) {
		if(R*cos(2*3.14/n*i) - dianqiu < -jinqu1 ) continue;
        glVertex3f(R*cos(2*3.14/n*i) - dianqiu, 0.01, R*sin(2*3.14/n*i));
	}
    glEnd();

	glBegin(GL_LINE_STRIP );
    for(int i=0; i < n; ++i) {
		if(R*cos(2*3.14/n*i) + dianqiu > jinqu1 ) continue;
        glVertex3f(R*cos(2*3.14/n*i) + dianqiu, 0.01, R*sin(2*3.14/n*i));
	}
    glEnd();

	//����λ��
	R = 1;
	//����
	glBegin(GL_LINE_STRIP );
    for(int i=0; i < n; ++i) {
		float x = R*cos(2*3.14/n*i) - MATCH_HALF_WIDTH;
		float z = R*sin(2*3.14/n*i) - MATCH_HALF_HEIGHT;
		if(x < -MATCH_HALF_WIDTH ||  z < -MATCH_HALF_HEIGHT) continue;
        glVertex3f(x, 0.01, z);
	}
    glEnd();
	//����
	glPushMatrix();
	glScalef(-1, 1, 1);
	glBegin(GL_LINE_STRIP );
    for(int i=0; i < n; ++i) {
		float x = R*cos(2*3.14/n*i) - MATCH_HALF_WIDTH;
		float z = R*sin(2*3.14/n*i) - MATCH_HALF_HEIGHT;
		if(x < -MATCH_HALF_WIDTH ||  z < -MATCH_HALF_HEIGHT) continue;
        glVertex3f(x, 0.01, z);
	}
    glEnd();
	glPopMatrix();

	//����
	glPushMatrix();
	glScalef(1, 1, -1);
	glBegin(GL_LINE_STRIP );
    for(int i=0; i < n; ++i) {
		float x = R*cos(2*3.14/n*i) - MATCH_HALF_WIDTH;
		float z = R*sin(2*3.14/n*i) - MATCH_HALF_HEIGHT;
		if(x < -MATCH_HALF_WIDTH ||  z < -MATCH_HALF_HEIGHT) continue;
        glVertex3f(x, 0.01, z);
	}
    glEnd();
	glPopMatrix();
	//����
	glPushMatrix();
	glScalef(-1, 1, -1);
	glBegin(GL_LINE_STRIP );
    for(int i=0; i < n; ++i) {
		float x = R*cos(2*3.14/n*i) - MATCH_HALF_WIDTH;
		float z = R*sin(2*3.14/n*i) - MATCH_HALF_HEIGHT;
		if(x < -MATCH_HALF_WIDTH ||  z < -MATCH_HALF_HEIGHT) continue;
        glVertex3f(x, 0.01, z);
	}
    glEnd();
	glPopMatrix();

	glLineWidth(1);

	glDisable(GL_BLEND);    // ���û��
	glDisable(GL_COLOR_MATERIAL);
}

//����3dģ��
void Court::draw_models() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	player_a0.Move(-10, 0, -20);
	player_a1.Move(-10, 0, -10);
	player_a2.Move(-10, 0, 0);
	player_a3.Move(-10, 0, 10);
	player_a4.Move(-10, 0, 20);
	player_a0.Render();
	player_a1.Render();
	player_a2.Render();
	player_a3.Render();
	player_a4.Render();

	player_b0.Move(10, 0, -20);
	player_b1.Move(10, 0, -10);
	player_b2.Move(10, 0, 0);
	player_b3.Move(10, 0, 10);
	player_b4.Move(10, 0, 20);
	player_b0.Rotate(180);
	player_b1.Rotate(180);
	player_b2.Rotate(180);
	player_b3.Rotate(180);
	player_b4.Rotate(180);
	player_b0.Render();
	player_b1.Render();
	player_b2.Render();
	player_b3.Render();
	player_b4.Render();

	flag0.Move(0, 0, 0);
	flag0.Render();


	////����ģ��
	//pModel = glmReadOBJ( FileName );		
	////���ɷ�����
	//glmFacetNormals( pModel );
	//// Scale the model to fit the screen
	//glmUnitize( pModel, modelCenter );
	////����
	//glmDraw( pModel, GLM_FLAT );
	
}

//���ƹ����
void Court::draw_advertisement() {
	glEnable(GL_TEXTURE_2D);
	//��
	glPushMatrix();
	glTranslatef(0, 0, -COURT_AD_OFFSET2);
	glBindTexture(GL_TEXTURE_2D, ad1_texture_id);
	glBegin(GL_QUADS);
	    glTexCoord2f(0.0f, 0.0f); glVertex3f(-COURT_AD1_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(COURT_AD1_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(COURT_AD1_HALF_WIDTH, COURT_AD1_HEIGHT, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-COURT_AD1_HALF_WIDTH, COURT_AD1_HEIGHT, 0);
	glEnd();
	glPopMatrix();

	//��
	float player_channel_half_width = 4;
	float part_width = (COURT_AD1_HALF_WIDTH - player_channel_half_width) / 2;
	float trans_x = part_width + player_channel_half_width;
	glPushMatrix();
	glTranslatef(trans_x, 0, COURT_AD_OFFSET2);
	//glScalef(1, 1, -1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-part_width, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(part_width, 0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(part_width, COURT_AD1_HEIGHT, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-part_width, COURT_AD1_HEIGHT, 0);
	glEnd();
	glTranslatef(-2 * trans_x, 0, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-part_width, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(part_width, 0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(part_width, COURT_AD1_HEIGHT, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-part_width, COURT_AD1_HEIGHT, 0);
	glEnd();
	glPopMatrix();

	//��
	glPushMatrix();
	glTranslatef(-COURT_AD_OFFSET1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, ad2_texture_id);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-COURT_AD2_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(COURT_AD2_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(COURT_AD2_HALF_WIDTH, COURT_AD2_HEIGHT, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-COURT_AD2_HALF_WIDTH, COURT_AD2_HEIGHT, 0);
	glEnd();
	glPopMatrix();
	//��
	glPushMatrix();
	glTranslatef(COURT_AD_OFFSET1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-COURT_AD2_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(COURT_AD2_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(COURT_AD2_HALF_WIDTH, COURT_AD2_HEIGHT, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-COURT_AD2_HALF_WIDTH, COURT_AD2_HEIGHT, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//���ƹ��ڵ���λ
void Court::draw_audience() {
	draw_first_level();
	draw_second_level();
	draw_middle_level();
	draw_third_level();

	//�ԳƵ���һ��
	glPushMatrix();
	glScalef(-1, 1, -1);
	draw_second_level();
	draw_middle_level();
	draw_third_level();
	glPopMatrix();
}

//���Ƶ�һ�����λ
void Court::draw_first_level() {
	float edge_step = 1.5;
	float corridor = 5;                         //���ȿ��
	float second_level_hor_dis = 60 + corridor;   //10Ϊ�ߵ����
	float gap = 2;             //��һ���߶ȱȹ���Ƶ�СС
	float base_height = COURT_AD1_HEIGHT - gap;
	float trans_x = 0, trans_y = 0, trans_z = 0;
	//��һ��
	//ǰ
	//�ֳ�5������
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	float part_width = COURT_AD1_HALF_WIDTH / 5;
	for(int n = 0; n < 5; n++) {
	    glPushMatrix();
		glTranslatef((n - 2) * part_width * 2, base_height, -COURT_AD_OFFSET2);
		if(n == 0) draw_steps(part_width, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 1.5, 0, LEVEL_STEPS);
		else if(n == 4) draw_steps(part_width, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 0, 1.5, LEVEL_STEPS);
		else draw_steps(part_width, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 0, 0, LEVEL_STEPS);
		glPopMatrix();
	}

	//��
	glPushMatrix();
	glTranslatef(-COURT_AD_OFFSET1, base_height, 0);
	glRotatef(90, 0, 1, 0);
	draw_steps(COURT_AD2_HALF_WIDTH, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 1.5, 1.5, LEVEL_STEPS);
	glPopMatrix();

	//��
	glPushMatrix();
	glScalef(-1, 1, 1);
	glTranslatef(-COURT_AD_OFFSET1, base_height, 0);
	glRotatef(90, 0, 1, 0);
	draw_steps(COURT_AD2_HALF_WIDTH, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 1.5, 1.5, LEVEL_STEPS);
	glPopMatrix();

	//��
	float  player_channel_half_width = 4;
	part_width = (COURT_AD1_HALF_WIDTH - player_channel_half_width) / 2;
	trans_x = part_width + player_channel_half_width;
	glPushMatrix();
	glTranslatef(trans_x, base_height, COURT_AD_OFFSET2);
	glScalef(1, 1, -1);
	draw_steps(part_width, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 0.0, 1.5, LEVEL_STEPS);
	glTranslatef(-2 * trans_x, 0, 0);
	draw_steps(part_width, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 1.5, 0.0, LEVEL_STEPS);
	glPopMatrix();

	//�����
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.1, 0.4, 0.5);
	glTranslatef(0, base_height + LEVEL_VERTICAL_DIS, COURT_AD_OFFSET2 + LEVEL_HORIZONTAL_DIS);
	glBegin(GL_QUADS);
		glVertex3f(-player_channel_half_width, -COURT_AD1_HEIGHT, 0);
		glVertex3f(player_channel_half_width, -COURT_AD1_HEIGHT, 0);
		glVertex3f(player_channel_half_width, 0, 0);
		glVertex3f(-player_channel_half_width, 0, 0);
	glEnd();
	glPopMatrix();
	glColor3f(1, 1, 1);
}

//���Ƶڶ������λ
void Court::draw_second_level() {
	float edge_step = 1.5;
	float corridor = 5;                         //���ȿ��
	float second_level_hor_dis = 60 + corridor;   //10Ϊ�ߵ����
	float gap = 2;             //��һ���߶ȱȹ���Ƶ�СС
	float base_height = COURT_AD1_HEIGHT - gap;
	float trans_x = 0, trans_y = 0, trans_z = 0;
	float forward_floor_half_width = LEVEL_STEPS * edge_step + COURT_AD1_HALF_WIDTH;
	float forward_floor_height = second_level_hor_dis;
	float left_floor_width = second_level_hor_dis;
	float left_floor_half_height = LEVEL_STEPS * edge_step + COURT_AD2_HALF_WIDTH;
	//�ڶ���
	//ǰ����
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floor2_texture_id);
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS + base_height, -LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET2);
	//��������
	draw_railing((LEVEL_STEPS * edge_step + COURT_AD1_HALF_WIDTH) * 2);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-forward_floor_half_width, 0, 0);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(forward_floor_half_width, 0, 0);
		glTexCoord2f(10.0f, 5.0f); glVertex3f(forward_floor_half_width, 0, -forward_floor_height);
		glTexCoord2f(0.0f, 5.0f); glVertex3f(-forward_floor_half_width, 0, -forward_floor_height);
	glEnd();
	glPopMatrix();
	
	//�����    
	glPushMatrix();
	glTranslatef(-LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET1, LEVEL_VERTICAL_DIS + base_height, 0);
	//��������
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	draw_railing((LEVEL_STEPS * edge_step + COURT_AD2_HALF_WIDTH) * 2);
	glPopMatrix();
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-left_floor_width, 0, left_floor_half_height);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(0, 0, left_floor_half_height);
		glTexCoord2f(10.0f, 10.0f); glVertex3f(0, 0, -left_floor_half_height);
		glTexCoord2f(0.0f, 10.0f); glVertex3f(-left_floor_width, 0, -left_floor_half_height);
	glEnd();
	glPopMatrix();
	//�ڶ���ǰ����Ĺսǵ���
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS + base_height, 0);
	Point p1, p2, p3, p4;	
	p1.x = -LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET1;
	p1.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	p2.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p2.z = -LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET2;
	p3.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p3.z = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET2;
	p4.x = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET1;
	p4.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(10.0f, 10.0f); glVertex3f(p3.x, p3.y, p3.z);
		glTexCoord2f(0.0f, 10.0f); glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//�����
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0.1, 0.4, 0.5);
	glBegin(GL_QUADS);
		glVertex3f(p1.x, p1.y - COURT_AD1_HEIGHT, p1.z);
		glVertex3f(p2.x, p2.y - COURT_AD1_HEIGHT, p2.z);
		glVertex3f(p2.x, p2.y + 2.5, p2.z);
		glVertex3f(p1.x, p1.y + 2.5, p1.z);
	glEnd();
	glPopMatrix();
	glPopAttrib();

	//�ڶ���ǰ����Ĺսǵ���(��һ��)
	glPushMatrix();
	glScalef(-1, 1, 1);
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS + base_height, 0);
	p1.x = -LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET1;
	p1.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	p2.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p2.z = -LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET2;
	p3.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p3.z = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET2;
	p4.x = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET1;
	p4.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floor2_texture_id);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(10.0f, 10.0f); glVertex3f(p3.x, p3.y, p3.z);
		glTexCoord2f(0.0f, 10.0f); glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//�����
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0.1, 0.4, 0.5);
	glBegin(GL_QUADS);
		glVertex3f(p1.x, p1.y - COURT_AD1_HEIGHT, p1.z);
		glVertex3f(p2.x, p2.y - COURT_AD1_HEIGHT, p2.z);
		glVertex3f(p2.x, p2.y + 2.5, p2.z);
		glVertex3f(p1.x, p1.y + 2.5, p1.z);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopAttrib();
	
	//ǰ
	float part_width = COURT_AD1_HALF_WIDTH / 7.0;
	float offset = COURT_AD1_HALF_WIDTH / 2.8;
	for(int i = 0; i < 7; i++) {
		trans_x = (i - 3) * offset;
		trans_y = LEVEL_VERTICAL_DIS + base_height + 0.1;
		trans_z = - LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET2 - corridor;
	    glPushMatrix();
		glTranslatef(trans_x, trans_y, trans_z);
		if(i == 0 || i == 6) {
		    draw_steps(part_width, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 0, 0, LEVEL_STEPS);
		} 
		else {
			draw_steps(part_width, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 0, 0, LEVEL_STEPS);
		}
		glPopMatrix();
	}
	for(int i = 0; i < 6; i++) {
		trans_x = (i - 3) * offset + (offset - 2 *  part_width) / 2 + part_width;
		trans_y = LEVEL_VERTICAL_DIS * 1.5 + base_height + 0.1 - LEVEL_VERTICAL_DIS / (LEVEL_STEPS) / 2;
		trans_z = - LEVEL_HORIZONTAL_DIS * 1.5 - COURT_AD_OFFSET2 - corridor + LEVEL_HORIZONTAL_DIS / LEVEL_STEPS / 2;
	    glPushMatrix();
		glTranslatef(trans_x, trans_y, trans_z);
		draw_steps((offset - 2.0 * part_width) / 2.0, LEVEL_VERTICAL_DIS / 2.0, LEVEL_HORIZONTAL_DIS / 2.0, 0, 0, LEVEL_STEPS / 2.0,
			true);
		glPopMatrix();
	}

	//��
	glPushMatrix();
	glTranslatef(-COURT_AD_OFFSET1 - LEVEL_HORIZONTAL_DIS - corridor, 0, 0);
	glRotatef(90, 0, 1, 0);
	part_width = COURT_AD2_HALF_WIDTH / 4.5;
	offset = COURT_AD2_HALF_WIDTH / 1.7;
	for(int i = 0; i < 5; i++) {
		trans_x = (i - 2) * offset;
		trans_y =  LEVEL_VERTICAL_DIS + base_height + 0.1;
		trans_z = 0;
	    glPushMatrix();
		glTranslatef(trans_x, trans_y, trans_z);
		draw_steps(part_width, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 0, 0, LEVEL_STEPS);
		glPopMatrix();
	}
	for(int i = 0; i < 4; i++) {
		trans_x = (i - 2) * offset + (offset - 2 *  part_width) / 2 + part_width;
		trans_y = LEVEL_VERTICAL_DIS * 1.5 + base_height + 0.1 - LEVEL_VERTICAL_DIS / (LEVEL_STEPS) / 2;
		trans_z = - LEVEL_HORIZONTAL_DIS * 0.5 + LEVEL_HORIZONTAL_DIS / LEVEL_STEPS / 2;
	    glPushMatrix();
		glTranslatef(trans_x, trans_y, trans_z);
		draw_steps((offset - 2.0 * part_width) / 2.0, LEVEL_VERTICAL_DIS / 2.0, LEVEL_HORIZONTAL_DIS / 2.0, 0, 0, LEVEL_STEPS / 2.0,
			true);
		glPopMatrix();
	}
	glPopMatrix();

	//ǰ��ս�
	glPushMatrix();
	trans_x = -COURT_AD_OFFSET1 - LEVEL_HORIZONTAL_DIS + 2;
	trans_y = LEVEL_VERTICAL_DIS + base_height + 0.1;
	trans_z = - LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET2 + 2;
	glTranslatef(trans_x, trans_y, trans_z);
	glRotatef(45, 0, 1, 0);
	draw_steps(7, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 0.8, 0.8, LEVEL_STEPS);
	glPopMatrix();
	//�ս�(��һ��)
	glPushMatrix();
	glScaled(-1, 1, 1);
	glPushMatrix();
	trans_x = -COURT_AD_OFFSET1 - LEVEL_HORIZONTAL_DIS + 2;
	trans_y = LEVEL_VERTICAL_DIS + base_height + 0.1;
	trans_z = - LEVEL_HORIZONTAL_DIS - COURT_AD_OFFSET2 + 2;
	glTranslatef(trans_x, trans_y, trans_z);
	glRotatef(45, 0, 1, 0);
	draw_steps(7, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 0.8, 0.8, LEVEL_STEPS);
	glPopMatrix();
	glPopMatrix();
}

//�����м��
void Court::draw_middle_level() {
	float edge_step = 1.5;
	float corridor = 5;                         //���ȿ��
	float second_level_hor_dis = 60 + corridor;   //10Ϊ�ߵ����
	float gap = 2;             //��һ���߶ȱȹ���Ƶ�СС
	float base_height = COURT_AD1_HEIGHT - gap;
	float trans_x = 0, trans_y = 0, trans_z = 0;
	Point p1, p2, p3, p4;
	float forward_floor_half_width = LEVEL_STEPS * edge_step + COURT_AD1_HALF_WIDTH;
    float forward_floor_height = second_level_hor_dis - 15;
	float left_floor_half_height = LEVEL_STEPS * edge_step + COURT_AD2_HALF_WIDTH;
	float left_floor_width = second_level_hor_dis - 15;

	glColor3f(1, 1, 1);
	//�м��
	//ǰ����
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floor2_texture_id);
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + base_height, -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor);	
	//��������
	draw_railing((LEVEL_STEPS * edge_step + COURT_AD1_HALF_WIDTH) * 2);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-forward_floor_half_width, 0, 0);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(forward_floor_half_width, 0, 0);
		glTexCoord2f(10.0f, 10.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(forward_floor_half_width, 0, -forward_floor_height);
		glTexCoord2f(0.0f, 10.0f); glVertex3f(-forward_floor_half_width, 0, -forward_floor_height);
	glEnd();
	glPopMatrix();
	//�����    
	glPushMatrix();
	glTranslatef(-LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor, LEVEL_VERTICAL_DIS * 2 + base_height, 0);
	//��������
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	draw_railing((LEVEL_STEPS * edge_step + COURT_AD2_HALF_WIDTH) * 2);
	glPopMatrix();
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-left_floor_width, 0, left_floor_half_height);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(0, 0, left_floor_half_height);
		glTexCoord2f(10.0f, 10.0f); glVertex3f(0, 0, -left_floor_half_height);
		glTexCoord2f(0.0f, 10.0f); glVertex3f(-left_floor_width, 0, -left_floor_half_height);
	glEnd();
	glPopMatrix();
	//�м��ǰ����Ĺսǵ���
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + base_height, 0);
	p1 = Point();
	p2 = Point();
	p3 = Point();
	p4 = Point();
	p1.x = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor;
	p1.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	p2.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p2.z = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor;
	p3.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p3.z = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor + 15;
	p4.x = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor + 15;
	p4.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(10.0f, 10.0f); glVertex3f(p3.x, p3.y, p3.z);
		glTexCoord2f(0.0f, 10.0f); glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
	glPopMatrix();

	//�м��ǰ����Ĺսǵ��棨��һ�ࣩ
	glPushMatrix();
	glScalef(-1, 1, 1);
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + base_height, 0);
	p1 = Point();
	p2 = Point();
	p3 = Point();
	p4 = Point();
	p1.x = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor;
	p1.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	p2.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p2.z = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor;
	p3.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p3.z = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor + 15;
	p4.x = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor + 15;
	p4.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(10.0f, 10.0f); glVertex3f(p3.x, p3.y, p3.z);
		glTexCoord2f(0.0f, 10.0f); glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	//�м��ǽ��
	//ǰǽ��
	glBindTexture(GL_TEXTURE_2D, middle_wall1_texture_id);
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + base_height, -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor * 2);	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH, 0, 0);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(LEVEL_STEPS * edge_step + COURT_AD1_HALF_WIDTH, 0, 0);
		glTexCoord2f(10.0f, 1.0f); glVertex3f(LEVEL_STEPS * edge_step + COURT_AD1_HALF_WIDTH, WALL_HEIGHT, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH, WALL_HEIGHT, 0);
	glEnd();
	glPopMatrix();
	//��ǽ��  
	glPushMatrix();
	glTranslatef(-LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor * 2, LEVEL_VERTICAL_DIS * 2 + base_height, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, LEVEL_STEPS * edge_step + COURT_AD2_HALF_WIDTH);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(0, 0, -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH);
		glTexCoord2f(10.0f, 1.0f); glVertex3f(0, WALL_HEIGHT, -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0, WALL_HEIGHT, LEVEL_STEPS * edge_step + COURT_AD2_HALF_WIDTH);
	glEnd();
	glPopMatrix();
	//�м��ǰ����Ĺս�ǽ��
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + base_height, 0);
	p1 = Point();
	p2 = Point();
	p3 = Point();
	p4 = Point();
	p1.x = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor;
	p1.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	p2.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p2.z = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor;

	p3.x = p2.x;
	p3.y = WALL_HEIGHT;
	p3.z = p2.z;
	p4.x = p1.x;
	p4.y = WALL_HEIGHT;
	p4.z = p1.z;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);
		glTexCoord2f(3.0f, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(3.0f, 1.0f); glVertex3f(p3.x, p3.y, p3.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
	glBegin(GL_QUADS);
	    glTexCoord2f(0.0f, 0.0f); glVertex3f(-LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor * 2, 0, -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH);
		glTexCoord2f(0.2f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);		
		glTexCoord2f(0.2f, 1.0f); glVertex3f(p4.x, p4.y, p4.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor * 2, WALL_HEIGHT, -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH);
	glEnd();
	glBegin(GL_QUADS);
	    glTexCoord2f(0, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(0.2f, 0.0f); glVertex3f(-LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH, 0, -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor * 2);	
		glTexCoord2f(0.2f, 1.0f); glVertex3f(-LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH, WALL_HEIGHT, -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor * 2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(p3.x, p3.y, p3.z);
	glEnd();
	glPopMatrix();

	//�м��ǰ����Ĺս�ǽ��(��һ��)
	glPushMatrix();
	glScalef(-1, 1, 1);
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + base_height, 0);
	p1 = Point();
	p2 = Point();
	p3 = Point();
	p4 = Point();
	p1.x = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor;
	p1.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	p2.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p2.z = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor;

	p3.x = p2.x;
	p3.y = WALL_HEIGHT;
	p3.z = p2.z;
	p4.x = p1.x;
	p4.y = WALL_HEIGHT;
	p4.z = p1.z;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);
		glTexCoord2f(3.0f, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(3.0f, 1.0f); glVertex3f(p3.x, p3.y, p3.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
	glBegin(GL_QUADS);
	    glTexCoord2f(0.0f, 0.0f); glVertex3f(-LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor * 2, 0, -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH);
		glTexCoord2f(0.2f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);		
		glTexCoord2f(0.2f, 1.0f); glVertex3f(p4.x, p4.y, p4.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor * 2, WALL_HEIGHT, -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH);
	glEnd();
	glBegin(GL_QUADS);
	    glTexCoord2f(0, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(0.2f, 0.0f); glVertex3f(-LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH, 0, -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor * 2);	
		glTexCoord2f(0.2f, 1.0f); glVertex3f(-LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH, WALL_HEIGHT, -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor * 2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(p3.x, p3.y, p3.z);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//���Ƶ��������λ
void Court::draw_third_level() {
	float part_width, offset;
	float edge_step = 1.5;
	float corridor = 5;                         //���ȿ��
	float second_level_hor_dis = 60 + corridor;   //10Ϊ�ߵ����
	float gap = 2;             //��һ���߶ȱȹ���Ƶ�СС
	float base_height = COURT_AD1_HEIGHT - gap;
	float trans_x = 0, trans_y = 0, trans_z = 0;
	Point p1, p2, p3, p4;
	float forward_floor_half_width = LEVEL_STEPS * edge_step + COURT_AD1_HALF_WIDTH;
    float forward_floor_height = second_level_hor_dis - 7;
	float left_floor_half_height = LEVEL_STEPS * edge_step + COURT_AD2_HALF_WIDTH;
	float left_floor_width = second_level_hor_dis - 7;

	//������
	//ǰ����
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floor2_texture_id);
	glColor3f(1, 1, 1); 
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height, -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor);	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-forward_floor_half_width, 0, 0);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(forward_floor_half_width, 0, 0);
		glTexCoord2f(10.0f, 10.0f); glVertex3f(forward_floor_half_width, 0, -forward_floor_height);
		glTexCoord2f(0.0f, 10.0f); glVertex3f(-forward_floor_half_width, 0, -forward_floor_height);
	glEnd();
	glPopMatrix();
	//�����    
	glPushMatrix();
	glTranslatef(-LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor, LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-left_floor_width, 0, left_floor_half_height);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(0, 0, left_floor_half_height);
		glTexCoord2f(10.0f, 10.0f); glVertex3f(0, 0, -left_floor_half_height);
		glTexCoord2f(0.0f, 10.0f); glVertex3f(-left_floor_width, 0, -left_floor_half_height);
	glEnd();
	glPopMatrix();
	//�м��ǰ����Ĺսǵ���
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height, 0);
	p1 = Point();
	p2 = Point();
	p3 = Point();
	p4 = Point();
	p1.x = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor;
	p1.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	p2.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p2.z = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor;
	p3.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p3.z = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor + 15;
	p4.x = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor + 15;
	p4.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(10.0f, 10.0f); glVertex3f(p3.x, p3.y, p3.z);
		glTexCoord2f(0.0f, 10.0f); glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
	glPopMatrix();
	//�м��ǰ����Ĺսǵ���(��һ��)
	glPushMatrix();
	glScalef(-1, 1, 1);
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height, 0);
	p1 = Point();
	p2 = Point();
	p3 = Point();
	p4 = Point();
	p1.x = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor;
	p1.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	p2.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p2.z = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor;
	p3.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
		p3.z = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor + 15;
	p4.x = -second_level_hor_dis - LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor + 15;
	p4.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(10.0f, 10.0f); glVertex3f(p3.x, p3.y, p3.z);
		glTexCoord2f(0.0f, 10.0f); glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	//�����
	//ǰ�����
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, third_ad1_texture_id);
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height, -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor);	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(LEVEL_STEPS * edge_step + COURT_AD1_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(LEVEL_STEPS * edge_step + COURT_AD1_HALF_WIDTH, COURT_AD1_HEIGHT, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH, COURT_AD1_HEIGHT, 0);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, third_ad2_texture_id);
	//������
	glPushMatrix();
	glTranslatef(-LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor, LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, LEVEL_STEPS * edge_step + COURT_AD2_HALF_WIDTH);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0, COURT_AD1_HEIGHT, -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0, COURT_AD1_HEIGHT, LEVEL_STEPS * edge_step + COURT_AD2_HALF_WIDTH);
	glEnd();
	glPopMatrix();
	//�м��ǰ����Ĺսǹ����
	glBindTexture(GL_TEXTURE_2D, third_ad3_texture_id);
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height, 0);
	p1 = Point();
	p2 = Point();
	p3 = Point();
	p4 = Point();
	p1.x = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor;
	p1.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	p2.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p2.z = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor;

	p3.x = p2.x;
	p3.y = COURT_AD1_HEIGHT;
	p3.z = p2.z;
	p4.x = p1.x;
	p4.y = COURT_AD1_HEIGHT;
	p4.z = p1.z;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(p3.x, p3.y, p3.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
	glPopMatrix();
	//�м��ǰ����Ĺսǹ����(��һ��)
	glBindTexture(GL_TEXTURE_2D, third_ad3_texture_id);
	glPushMatrix();
	glScalef(-1, 1, 1);
	glPushMatrix();
	glTranslatef(0, LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height, 0);
	p1 = Point();
	p2 = Point();
	p3 = Point();
	p4 = Point();
	p1.x = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET1 - corridor;
	p1.z = -LEVEL_STEPS * edge_step - COURT_AD2_HALF_WIDTH;
	p2.x = -LEVEL_STEPS * edge_step - COURT_AD1_HALF_WIDTH;
	p2.z = -LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor;

	p3.x = p2.x;
	p3.y = COURT_AD1_HEIGHT;
	p3.z = p2.z;
	p4.x = p1.x;
	p4.y = COURT_AD1_HEIGHT;
	p4.z = p1.z;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(p3.x, p3.y, p3.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	//ǰ
	part_width = COURT_AD1_HALF_WIDTH / 7.0;
	offset = COURT_AD1_HALF_WIDTH / 2.8;
	for(int i = 0; i < 7; i++) {
		trans_x = (i - 3) * offset;
		trans_y = LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height + 0.1;
		trans_z = - LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor * 2;
	    glPushMatrix();
		glTranslatef(trans_x, trans_y, trans_z);
		if(i == 0 || i == 6) {
		    draw_steps(part_width, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 0, 0, LEVEL_STEPS);
		} 
		else {
			draw_steps(part_width, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 0, 0, LEVEL_STEPS);
		}
		glPopMatrix();
	}
	for(int i = 0; i < 6; i++) {
		trans_x = (i - 3) * offset + (offset - 2 *  part_width) / 2 + part_width;
		trans_y = LEVEL_VERTICAL_DIS * 2.5 + WALL_HEIGHT + base_height + 0.1 - LEVEL_VERTICAL_DIS / (LEVEL_STEPS) / 2;
		trans_z = - LEVEL_HORIZONTAL_DIS * 2.5 - COURT_AD_OFFSET2 - corridor * 2 + LEVEL_HORIZONTAL_DIS / LEVEL_STEPS / 2;
	    glPushMatrix();
		glTranslatef(trans_x, trans_y, trans_z);
		draw_steps((offset - 2.0 * part_width) / 2.0, LEVEL_VERTICAL_DIS / 2.0, LEVEL_HORIZONTAL_DIS / 2.0, 0, 0, LEVEL_STEPS / 2.0,
			true);
		glPopMatrix();
	}

	//��
	glPushMatrix();
	glTranslatef(-COURT_AD_OFFSET1 - LEVEL_HORIZONTAL_DIS * 2 - corridor * 2, 0, 0);
	glRotatef(90, 0, 1, 0);
	part_width = COURT_AD2_HALF_WIDTH / 4.6;
	offset = COURT_AD2_HALF_WIDTH / 1.7;
	for(int i = 0; i < 5; i++) {
		trans_x = (i - 2) * offset;
		trans_y = LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height + 0.1;
		trans_z = 0;
	    glPushMatrix();
		glTranslatef(trans_x, trans_y, trans_z);
		draw_steps(part_width, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 0, 0, LEVEL_STEPS);
		glPopMatrix();
	}
	for(int i = 0; i < 4; i++) {
		trans_x = (i - 2) * offset + (offset - 2 *  part_width) / 2 + part_width;
		trans_y = LEVEL_VERTICAL_DIS * 2.5 + WALL_HEIGHT + base_height + 0.1 - LEVEL_VERTICAL_DIS / (LEVEL_STEPS) / 2;
		trans_z = - LEVEL_HORIZONTAL_DIS * 0.5 + LEVEL_HORIZONTAL_DIS / LEVEL_STEPS / 2;
	    glPushMatrix();
		glTranslatef(trans_x, trans_y, trans_z);
		draw_steps((offset - 2.0 * part_width) / 2.0, LEVEL_VERTICAL_DIS / 2.0, LEVEL_HORIZONTAL_DIS / 2.0, 0, 0, LEVEL_STEPS / 2.0,
			true);
		glPopMatrix();
	}
	glPopMatrix();

	//ǰ��ս�
	glPushMatrix();
	trans_x = -COURT_AD_OFFSET1 - LEVEL_HORIZONTAL_DIS * 2 - corridor * 2 + 22.1;
	trans_y = LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height + 0.1;
	trans_z = - LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor * 2 + 22.1;
	glTranslatef(trans_x, trans_y, trans_z);
	glRotatef(45, 0, 1, 0);
	draw_steps(27, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 1.3, 1.3, LEVEL_STEPS);
	glPopMatrix();
	//ǰ��սǣ���һ�ߣ�
	glPushMatrix();
	glScalef(-1, 1, 1);
	glPushMatrix();
	trans_x = -COURT_AD_OFFSET1 - LEVEL_HORIZONTAL_DIS * 2 - corridor * 2 + 22.1;
	trans_y = LEVEL_VERTICAL_DIS * 2 + WALL_HEIGHT + base_height + 0.1;
	trans_z = - LEVEL_HORIZONTAL_DIS * 2 - COURT_AD_OFFSET2 - corridor * 2 + 22.1;
	glTranslatef(trans_x, trans_y, trans_z);
	glRotatef(45, 0, 1, 0);
	draw_steps(27, LEVEL_VERTICAL_DIS, LEVEL_HORIZONTAL_DIS, 1.3, 1.3, LEVEL_STEPS);
	glPopMatrix();
	glPopMatrix();
}

//����̨��
void Court::draw_steps(float length, float height, float width, float l_edge_step, float r_edge_step, float step_count,
					   bool mid_air) {
    float gap = 2;             //��һ���߶ȱȹ���Ƶ�СС
	float base_height = COURT_AD1_HEIGHT - gap;
	float vertical_step = height / step_count;
	float horizontal_step = width / step_count;
	float l_edge = 0.0;
	float r_edge = 0.0;
	for(int i = 0; i < step_count; i++) {
		//ˮƽ
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, audience_seat_horizontal_texture_id);
		glPushMatrix();
		glTranslatef(0, i * vertical_step, -i * horizontal_step);
		glColor3f(0.7,0.7,0.7); 		
		glBegin(GL_QUADS);
		int count_ = (length + r_edge) * 2;
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-length - l_edge, 0, 0);
			glTexCoord2f(count_, 0.0f); glVertex3f(length + r_edge, 0, 0);
			l_edge += l_edge_step;
			r_edge += r_edge_step;
			glTexCoord2f(count_, 1.0f); glVertex3f(length + r_edge, 0, -horizontal_step);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-length - l_edge, 0, -horizontal_step);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		//��ֱ
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, audience_seat_vertical_texture_id);
		glTranslatef(0, 0, -horizontal_step);
		//glColor3f(0.2,0.2,0.2); 
		int count = (length + r_edge) * 2;
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-length - l_edge, 0, 0);
			glTexCoord2f(count, 0.0f); glVertex3f(length + r_edge, 0, 0);
			glTexCoord2f(count, 1); glVertex3f(length + r_edge, vertical_step, 0);
			glTexCoord2f(0.0f, 1); glVertex3f(-length - l_edge, vertical_step,0);
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		if(show_audience) {
			//���ƹ���
			glDisable(GL_COLOR_MATERIAL);
			glEnable(GL_TEXTURE_2D);
			int audience_count;
			if(mid_air) audience_count = (length + (l_edge + r_edge) / 2) * 2 / (AUDIENCE_WIDTH + AUDIENCE_GAP);
			else audience_count = (length + (l_edge + r_edge) / 2 - 1) * 2 / (AUDIENCE_WIDTH + AUDIENCE_GAP);
			for(int n = 0; n < audience_count; n++) {
				glPushMatrix();
				glTranslatef((AUDIENCE_WIDTH + AUDIENCE_GAP) * (n - audience_count / 2) + (r_edge - l_edge)/ 2, 0, 0);		
				glBindTexture(GL_TEXTURE_2D, audience_texture_id);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -horizontal_step / 2);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 0, -horizontal_step / 2);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 2, -horizontal_step / 2);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 2, -horizontal_step / 2);
				glEnd();
		
				glPopMatrix();
			}
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_COLOR_MATERIAL);
		}

		//��ǽ��
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, wall_texture_id);
		glPushMatrix();
		glTranslatef(-i * l_edge_step - length, 0, -i * horizontal_step);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-l_edge_step, -base_height, -horizontal_step);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, -base_height, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0, i * vertical_step, 0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-l_edge_step, i * vertical_step, -horizontal_step);
		glEnd();
		glPopMatrix();
		//��ǽ��
		glPushMatrix();
		glTranslatef(i * r_edge_step + length, 0, -i * horizontal_step); 
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, -base_height, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(r_edge_step, -base_height, -horizontal_step);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(r_edge_step, i * vertical_step, -horizontal_step);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0, i * vertical_step,0);
		glEnd();
		glPopMatrix();	
		glDisable(GL_TEXTURE_2D);
	}
	//����
	glPushMatrix();
	glTranslatef(0, -0.001, 0);
	glColor3f(0.1,0.1,0.1); 
	glBegin(GL_QUADS);
		glVertex3f(-length, 0, 0);
		glVertex3f(length, 0, 0);
		glVertex3f(length + r_edge, 0, -width);
		glVertex3f(-length - l_edge, 0, -width);
	glEnd();
	glPopMatrix();
	//��ͨ���Ϸ��Ľ��ݣ��·��ٻ���һ�������
	glColor3f(0.1, 0.4, 0.5);
	if(mid_air) {
		/*glPushMatrix();
		glTranslatef(0, 0, 0);
		render_bmp_text(0, 0, "chen");
		glPopMatrix();*/
	    glBegin(GL_QUADS);
			glVertex3f(-length, -COURT_AD1_HEIGHT + 3, 0);
			glVertex3f(length, -COURT_AD1_HEIGHT + 3, 0);
			glVertex3f(length, 0, 0);
			glVertex3f(-length, 0, 0);
		glEnd();
		//��������
		glPushMatrix();
		float scale = 0.02f;
		glTranslatef(0, 1, 0);
		glScalef(0.03, scale, scale);
		glRotatef(-90, 1, 0, 0);
		glCallList(railing_model_index);
		glPopMatrix();
	}
	glColor3f(1, 1, 1);
}

//��������
void Court::draw_goal() {
	glColor3f(0.5, 0.5, 0.5);

	//���ƺ��
	glPushMatrix();
	glTranslatef(0, GOAL_HEIGHT, 0);	
    GLUquadricObj *horizontal_bar = gluNewQuadric();
    gluQuadricDrawStyle(horizontal_bar, GLU_FILL);
	gluCylinder(horizontal_bar, GOAL_BAR_RADIUS, GOAL_BAR_RADIUS, GOAL_WIDTH, 26, 13);
	gluDeleteQuadric(horizontal_bar);
	glPopMatrix();
	//����һ������
	glPushMatrix();
	glTranslatef(0, GOAL_HEIGHT, 0);
	glRotatef(90, 1, 0, 0);
    GLUquadricObj *vertical_bar = gluNewQuadric();
    gluQuadricDrawStyle(vertical_bar, GLU_FILL);
	gluCylinder(vertical_bar, GOAL_BAR_RADIUS, GOAL_BAR_RADIUS, GOAL_HEIGHT, 26, 13);
	glPopMatrix();
	//������һ������
	glPushMatrix();
	glTranslatef(0, GOAL_HEIGHT, GOAL_WIDTH);
	glRotatef(90, 1, 0, 0);
    gluQuadricDrawStyle(vertical_bar, GLU_FILL);
	gluCylinder(vertical_bar, GOAL_BAR_RADIUS, GOAL_BAR_RADIUS, GOAL_HEIGHT, 26, 13);
	gluDeleteQuadric(vertical_bar);
	glPopMatrix();
	//����һ��˵����Ӳ���
	glPushMatrix();
	glTranslatef(0, GOAL_HEIGHT, GOAL_WIDTH);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj *connect_ball = gluNewQuadric();
    gluQuadricDrawStyle(connect_ball, GLU_FILL);
	gluSphere(connect_ball, GOAL_BAR_RADIUS, 26, 13);
	glPopMatrix();
	//������һ��˵����Ӳ���
	glPushMatrix();
	glTranslatef(0, GOAL_HEIGHT, 0);
	glRotatef(90, 1, 0, 0);
    gluQuadricDrawStyle(connect_ball, GLU_FILL);
	gluSphere(connect_ball, GOAL_BAR_RADIUS, 26, 13);
	gluDeleteQuadric(connect_ball);
	glPopMatrix();

	//���Ƶ�
	GLint u_number = 3;
	GLint v_number = 3;
	GLfloat ***ctrl_points;
	//�������
	//ת����ʽ
	ctrl_points = new GLfloat**[u_number];
	for(int i = 0; i < u_number; i++) {
		ctrl_points[i] = new GLfloat*[v_number];
		for(int j = 0; j < v_number; j++) {
		    //ctrl_points[i][j] = new GLfloat[3];
			ctrl_points[i][j] = ctrl_points_data_up[i][j];
		}
	}
	draw_bessel_face(ctrl_points, u_number, v_number, GL_LINE, 15, 40);
	//�ͷſռ�
	for(int i = 0; i < u_number; i++) {
		if(!ctrl_points[i]) continue;
		delete[] ctrl_points[i];
	}
	if(ctrl_points) delete[] ctrl_points;

	//һ�����
	//ת����ʽ
	ctrl_points = new GLfloat**[u_number];
	for(int i = 0; i < u_number; i++) {
		ctrl_points[i] = new GLfloat*[v_number];
		for(int j = 0; j < v_number; j++) {
			ctrl_points[i][j] = ctrl_points_data_side[i][j];
		}
	}
	draw_bessel_face(ctrl_points, u_number, v_number, GL_LINE, 15, 15);
	//��һ�����
	glPushMatrix();
	glTranslatef(0, 0, GOAL_WIDTH);
	draw_bessel_face(ctrl_points, u_number, v_number, GL_LINE, 15, 15);
	glPopMatrix();
	//�ͷſռ�
	for(int i = 0; i < u_number; i++) {
		if(!ctrl_points[i]) continue;
		delete[] ctrl_points[i];
	}
	if(ctrl_points) delete[] ctrl_points;

	//�������	
	//ת����ʽ
	ctrl_points = new GLfloat**[u_number];
	for(int i = 0; i < u_number; i++) {
		ctrl_points[i] = new GLfloat*[v_number];
		for(int j = 0; j < v_number; j++) {
		    //ctrl_points[i][j] = new GLfloat[3];
			ctrl_points[i][j] = ctrl_points_data_back[i][j];
		}
	}
	draw_bessel_face(ctrl_points, u_number, v_number, GL_LINE, 15, 40);
	//�ͷſռ�
	for(int i = 0; i < u_number; i++) {
		if(!ctrl_points[i]) continue;
		delete[] ctrl_points[i];
	}
	if(ctrl_points) delete[] ctrl_points;

	//�������ź����һ��֧�Ÿ�
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(GOAL_LENGTH * BACK_X_SCALE, GOAL_HEIGHT * BACK_Y_SCALE, GOAL_WIDTH * BACK_Z_SCALE);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj *back_bar = gluNewQuadric();
    gluQuadricDrawStyle(back_bar, GLU_FILL);
	gluCylinder(back_bar, GOAL_BAR_RADIUS / 4, GOAL_BAR_RADIUS / 4, GOAL_HEIGHT * BACK_Y_SCALE, 26, 13);
	//�������ź������һ��֧�Ÿ�
	glPopMatrix();
	glPushMatrix();
	glTranslatef(GOAL_LENGTH * BACK_X_SCALE, GOAL_HEIGHT * BACK_Y_SCALE, -GOAL_WIDTH * (BACK_Z_SCALE - 1));
	glRotatef(90, 1, 0, 0);
	gluCylinder(back_bar, GOAL_BAR_RADIUS / 4, GOAL_BAR_RADIUS / 4, GOAL_HEIGHT * BACK_Y_SCALE, 26, 13);
	gluDeleteQuadric(back_bar);
	glPopMatrix();

	//����һ��������֧�Ÿ˵�����
	GLfloat **line_ctrl_points;
	GLint ctrl_number = 4;
	//ת����ʽ
	line_ctrl_points = new GLfloat*[ctrl_number];
	for(int i = 0; i < ctrl_number; i++) {
		line_ctrl_points[i] = net_bar_ctrl_points[i];
	}
	draw_bessel_line(line_ctrl_points, ctrl_number, GL_LINE);
	//������һ��������֧�Ÿ˵�����
	glPushMatrix();
	glTranslatef(0, 0, GOAL_WIDTH);
	glScalef(1, 1, -1);
	draw_bessel_line(line_ctrl_points, ctrl_number, GL_LINE);
	glPopMatrix();
	//�ͷſռ�
	if(line_ctrl_points) delete[] line_ctrl_points;
}


//�����油��Ա�ͽ�������λ
void Court::draw_bench_seat() {
	//���Ƶ�
	GLint u_number = 3;
	GLint v_number = 3;
	GLfloat ***ctrl_points;
	//�Ϸ��ĵ���
	//ת����ʽ
	ctrl_points = new GLfloat**[u_number];
	for(int i = 0; i < u_number; i++) {
		ctrl_points[i] = new GLfloat*[v_number];
		for(int j = 0; j < v_number; j++) {
			ctrl_points[i][j] = ctrl_points_bench_seat_up[i][j];
		}
	}
	glColor4f(0.7f, 0.7f, 0.7f, 0.9f);
	draw_bessel_face(ctrl_points, u_number, v_number, GL_FILL, 15, 40);
	//�ͷſռ�
	for(int i = 0; i < u_number; i++) {
		if(!ctrl_points[i]) continue;
		delete[] ctrl_points[i];
	}
	if(ctrl_points) delete[] ctrl_points;

	//��������
	float scale = 0.02f;
	float trans_y = 1.2;
	float trans_x = 1.6;
	for(int n = 0; n < 3; n++) {
	    glPushMatrix();
		glTranslatef(trans_x, trans_y, (2 - n) * 3.6 + 3);
		glRotatef(-90, 0, 1, 0);
		glScalef(scale, scale, scale);
		//glCallList(seat_model_index);
		draw_3ds_model(seat_model, seat_models_texture);
		glPopMatrix();
	}

}

//��������
void Court::draw_railing(float length) {
	glPushAttrib(GL_CURRENT_BIT);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);

	// enable cube mpapping
    glEnable(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, env_texture_id);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//glColor3f(0.7, 0.7, 0.7);
	glPushMatrix();
	glTranslatef(-length / 2, RAILING_HEIGHT, 0);
	glRotatef(90, 0, 1, 0);
    GLUquadricObj *horizontal_bar = gluNewQuadric();
    gluQuadricDrawStyle(horizontal_bar, GLU_FILL);
	gluCylinder(horizontal_bar, RAILING_RADIUS, RAILING_RADIUS, length, 26, 13);
	glTranslatef(0, -RAILING_HEIGHT / 3, 0);
	gluCylinder(horizontal_bar, RAILING_RADIUS, RAILING_RADIUS, length, 26, 13);
	glTranslatef(0, -RAILING_HEIGHT / 3, 0);
	gluCylinder(horizontal_bar, RAILING_RADIUS, RAILING_RADIUS, length, 26, 13);
	gluDeleteQuadric(horizontal_bar);

	glPopMatrix();
	GLUquadricObj *vertical_bar = gluNewQuadric();
	gluQuadricDrawStyle(vertical_bar, GLU_FILL);
	int part_count = length / RAILING_PART_WIDTH;
	for(int i = 0; i < part_count; i++) {
		glPushMatrix();
		glTranslatef(RAILING_PART_WIDTH * (i - part_count / 2), 0, 0);
		glRotatef(-90, 1, 0, 0);
		gluCylinder(vertical_bar, RAILING_RADIUS, RAILING_RADIUS, RAILING_HEIGHT, 26, 13);
		glPopMatrix();
	}
	gluDeleteQuadric(vertical_bar);

	glDisable(GL_TEXTURE_CUBE_MAP);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);

	glPopAttrib();
}

//����3dsģ��
void Court::draw_3ds_model(t3DModel model, unsigned int* texture) {
	glPushAttrib(GL_CURRENT_BIT);
    for(int i = 0; i < model.numOfObjects; i++) {
		// �������Ĵ�СС��0�����˳�
		if(model.pObject.size() <= 0) break;
		// ��õ�ǰ��ʾ�Ķ���
		t3DObject *pObject = &model.pObject[i];	
		// �жϸö����Ƿ�������ӳ��
		if(pObject->bHasTexture) {
			// ������ӳ��
			glEnable(GL_TEXTURE_2D);
			glColor3ub(255, 255, 255);
			glBindTexture(GL_TEXTURE_2D, texture[pObject->materialID]);
		} else {
			// �ر�����ӳ��
			glDisable(GL_TEXTURE_2D);
			glColor3ub(255, 255, 255);
		}
		// ��ʼ��g_ViewModeģʽ����
		glBegin(GL_TRIANGLES);					
			// �������е���
			for(int j = 0; j < pObject->numOfFaces; j++) {
				// ���������ε����е�
				for(int whichVertex = 0; whichVertex < 3; whichVertex++) {
					// ������ÿ���������
					int index = pObject->pFaces[j].vertIndex[whichVertex];
					// ����������
					glNormal3f(pObject->pNormals[ index ].x, pObject->pNormals[ index ].y, pObject->pNormals[ index ].z);
					// ��������������
					if(pObject->bHasTexture) {
						// ȷ���Ƿ���UVW��������
						if(pObject->pTexVerts) {
							glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
						}
					} else {
						if(model.pMaterials.size() && pObject->materialID >= 0) {
							BYTE *pColor = model.pMaterials[pObject->materialID].color;
							glColor3ub(pColor[0], pColor[1], pColor[2]);
						}
					}
					glVertex3f(pObject->pVerts[ index ].x, pObject->pVerts[ index ].y, pObject->pVerts[ index ].z);
				}
			}
		glEnd();								// ���ƽ���
	}
	glPopAttrib();
}

//������ݵ�����
void Court::draw_wall() {
	glColor3f(0.5, 0.5, 0.5);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	//glTranslatef(0, 100, 0);
	
	glScalef(1.377, 1, 1.17);
	glRotatef(-90, 1, 0, 0);
	GLUquadricObj *top = gluNewQuadric();
	gluQuadricTexture(top,GLU_TRUE);  
    gluQuadricDrawStyle(top, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, wall_inside_texture_id);
	//����
    gluCylinder(top, 150, 150, 3 * LEVEL_VERTICAL_DIS + COURT_AD1_HEIGHT * 2 + 25, 40, 20);
	glBindTexture(GL_TEXTURE_2D, wall_outside_texture_id);
	//����
    gluCylinder(top, 150, 175, 3 * LEVEL_VERTICAL_DIS + COURT_AD1_HEIGHT * 2 + 25 + 25, 40, 20);
	glTranslatef(0, 0, 3 * LEVEL_VERTICAL_DIS + COURT_AD1_HEIGHT * 2 + 25);
	//����
	gluCylinder(top, 150, 175, 25, 40, 20);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(top);
}

//��������
void Court::draw_football() {
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, 0.3, 0);
	GLUquadricObj *football = gluNewQuadric();
	gluQuadricTexture(football,GLU_TRUE);  
    gluQuadricDrawStyle(football, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, football_texture_id);
	gluSphere(football, 0.3, 20, 20);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(football);
}

//���ƴ���Ļ
void Court::draw_tv() {
	glPushMatrix();
	glTranslatef(0, TV_HEIGHT, 0);
	glEnable(GL_TEXTURE_2D);
	//����
	glBindTexture(GL_TEXTURE_2D, tv_texture_id[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-TV_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(TV_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(TV_HALF_WIDTH, TV_HEIGHT, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-TV_HALF_WIDTH, TV_HEIGHT, 0);
	glEnd();
	//����
	glBindTexture(GL_TEXTURE_2D, tv_texture_id[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-TV_HALF_WIDTH, 0, -TV_LENGTH);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(TV_HALF_WIDTH, 0, -TV_LENGTH);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(TV_HALF_WIDTH, TV_HEIGHT, -TV_LENGTH);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-TV_HALF_WIDTH, TV_HEIGHT, -TV_LENGTH);
	glEnd();
	//����
	glBindTexture(GL_TEXTURE_2D, tv_texture_id[2]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-TV_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-TV_HALF_WIDTH, 0, -TV_LENGTH);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-TV_HALF_WIDTH, TV_HEIGHT, -TV_LENGTH);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-TV_HALF_WIDTH, TV_HEIGHT, 0);
	glEnd();
	//����
	glBindTexture(GL_TEXTURE_2D, tv_texture_id[3]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(TV_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(TV_HALF_WIDTH, 0, -TV_LENGTH);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(TV_HALF_WIDTH, TV_HEIGHT, -TV_LENGTH);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(TV_HALF_WIDTH, TV_HEIGHT, 0);
	glEnd();
	//�ײ�
	glBindTexture(GL_TEXTURE_2D, tv_texture_id[4]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-TV_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(TV_HALF_WIDTH, 0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(TV_HALF_WIDTH, 0, -TV_LENGTH);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-TV_HALF_WIDTH, 0, -TV_LENGTH);
	glEnd();
	//����
	glBindTexture(GL_TEXTURE_2D, tv_texture_id[5]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-TV_HALF_WIDTH, TV_HEIGHT, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(TV_HALF_WIDTH, TV_HEIGHT, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(TV_HALF_WIDTH, TV_HEIGHT, -TV_LENGTH);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-TV_HALF_WIDTH, TV_HEIGHT, -TV_LENGTH);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//֧�Ŵ���Ļ������
	glPushMatrix();
	glTranslatef(0, TV_HEIGHT, -TV_LENGTH / 2);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj *vertical_bar = gluNewQuadric();
    gluQuadricDrawStyle(vertical_bar, GLU_FILL);
	glTranslatef(TV_HALF_WIDTH / 3, 0, 0);
	gluCylinder(vertical_bar, 2, 2, TV_HEIGHT, 26, 13);
	glTranslatef(-2 * TV_HALF_WIDTH / 3, 0, 0);
	gluCylinder(vertical_bar, 2, 2, TV_HEIGHT, 26, 13);
	gluDeleteQuadric(vertical_bar);
	glPopMatrix();
}

void Court::draw_match_floor() {
    //���Ƴ��صĲ�ƺ
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grass_texture_id);
	glBegin(GL_POLYGON);  
		//glNormal3f(0, 1, 0);
		glTexCoord2f(12.0, 0.0);  glVertex3f(COURT_HALF_WIDTH, 0, COURT_HALF_HEIGHT);
		glTexCoord2f(12.0, 12.0); glVertex3f(COURT_HALF_WIDTH, 0, -COURT_HALF_HEIGHT);
		glTexCoord2f(0.0, 12.0);  glVertex3f(-COURT_HALF_WIDTH, 0, -COURT_HALF_HEIGHT);
		glTexCoord2f(0.0, 0.0);   glVertex3f(-COURT_HALF_WIDTH, 0, COURT_HALF_HEIGHT);
    glEnd();  
	glDisable(GL_TEXTURE_2D);

	//���Ƶ���
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floor_texture_id);
	glBegin(GL_QUADS);
		//glNormal3f(0, 1, 0);
		glTexCoord2f(12.0, 0.0); glVertex3f(150, -0.9, -150);
		glTexCoord2f(12.0, 12.0); glVertex3f(150, -0.9, 150);
		glTexCoord2f(0.0, 12.0); glVertex3f(-150, -0.9, 150);
		glTexCoord2f(0.0, 0.0); glVertex3f(-150, -0.9, -150);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}