#include "function.h"
#include "gl/glaux.h"

unsigned int bmp_text_list_base;

//����λͼ����
void create_bmp_text(char *font_name, int font_size) {
    HFONT h_font;
	bmp_text_list_base = glGenLists(TEXT_LIST_LENGTH);
	if(!strcmp(font_name, "symbol")) {
		h_font = CreateFontA(font_size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			SYMBOL_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
			font_name);
	}
	else {
	    h_font = CreateFontA(font_size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
			font_name);
	}
	if (!h_font)
		return;

	SelectObject(wglGetCurrentDC(), h_font);
	wglUseFontBitmaps(wglGetCurrentDC(), 32, 96, bmp_text_list_base);
}

//����bmp����
void render_bmp_text(int x_pos, int y_pos, char *str) {
    if ((bmp_text_list_base == 0) || (!str))
		return;

	glRasterPos2i(x_pos, x_pos);

	glPushAttrib(GL_LIST_BIT);
		glListBase(bmp_text_list_base - 32);
		glCallLists((int)strlen(str), GL_UNSIGNED_BYTE, str);
	glPopAttrib();
}

//����tga��ʽ����
void load_tga_texture(char *filename, unsigned int &texture_obj) {
	CTargaImage texture;
	//��������ͼ��
	if (!texture.Load(filename))
		return;

	//��ȡһ��δʹ�õ��������
	glGenTextures(1, &texture_obj);

	//���������֮���������������������������
	glBindTexture(GL_TEXTURE_2D, texture_obj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// now that the texture object is bound, specify a texture for it
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.GetWidth(), texture.GetHeight(),
				 0, GL_RGB, GL_UNSIGNED_BYTE, texture.GetImage());

	texture.Release();
}

#pragma comment ( lib, "glaux.lib" )
//����bmp��ʽ����
void load_bmp_texture(char* filename) {
    AUX_RGBImageRec* TextureImage[1];
	TextureImage[0]=auxDIBImageLoad((LPCWSTR)filename);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
}

void draw_terrain() {

}

//���Ƶ�
GLint numOfPoints = 4;
static GLfloat controlPoints[4][3] = {{-4.0f, 0.0f, 0.0f},
{-6.0f, 4.0f, 0.0f},
{6.0f, -4.0f, 0.0f},
{4.0f, 0.0f, 0.0f}}; 

//���Ʊ���������
void draw_bessel_line() {
	/*glPointSize(2.5f);
    glBegin(GL_POINTS); for (int i = 0; i < numOfPoints; ++i) {
		glVertex3fv(controlPoints[i]);
    }
    glEnd();*/

    //���ñ��������ߣ����������ʵֻ��Ҫ����һ�Σ����Է���SetupRC������
    glMap1f(GL_MAP1_VERTEX_3, //���ɵ���������
            0.0f, //uֵ���½�
            100.0f, //uֵ���Ͻ�
            3, //�����������еļ����x,y,z���Լ����3
            numOfPoints, //u�����ϵĽף������Ƶ�ĸ���
            &controlPoints[0][0] ); //ָ����Ƶ����ݵ�ָ��
    //�����ڻ��ƶ���֮ǰ����
    glEnable(GL_MAP1_VERTEX_3);
	glMapGrid1f(100, 0.0f, 100.0f);
    glEvalMesh1(GL_LINE, 0, 100);
}

//���Ʊ���������
void draw_bessel_line(GLfloat *ctrl_points[], int u_number,GLenum draw_mode) {
	/*glPointSize(4.0f);
	glColor3f(0, 1, 0);
    glBegin(GL_POINTS); for (int i = 0; i < u_number; ++i) {
		glVertex3fv(ctrl_points[i]);
    }
    glEnd();*/
	glColor3f(0.5f, 0.5f, 0.5f);
    //���ñ��������ߣ����������ʵֻ��Ҫ����һ�Σ����Է���SetupRC������
    glMap1f(GL_MAP1_VERTEX_3, //���ɵ���������
            0.0f, //uֵ���½�
            100.0f, //uֵ���Ͻ�
            3, //�����������еļ����x,y,z���Լ����3
            u_number, //u�����ϵĽף������Ƶ�ĸ���
            &ctrl_points[0][0] ); //ָ����Ƶ����ݵ�ָ��
    //�����ڻ��ƶ���֮ǰ����
    glEnable(GL_MAP1_VERTEX_3);
	glMapGrid1f(100, 0.0f, 100.0f);
    glEvalMesh1(GL_LINE, 0, 100);
}

//���Ƶ�
GLint nNumPoints = 3;
GLfloat ctrlPoints[3][3][3]= {
{{  -4.0f, 0.0f, 4.0f},    
{ -2.0f, 4.0f, 4.0f},    
{  4.0f, 0.0f, 4.0f }},

{{  -4.0f, 0.0f, 0.0f},    
{ -2.0f, 4.0f, 0.0f},    
{  4.0f, 0.0f, 0.0f }},

{{  -4.0f, 0.0f, -4.0f},    
{ -2.0f, 4.0f, -4.0f},    
{  4.0f, 0.0f, -4.0f }}};

GLfloat myPoints[3][3][3]= {
{{  -4.0f, 0.0f, 0.0f},    
{ -2.0f, 0.0f, -14.0f},    
{  0.0f, 0.0f, -4.0f }},

{{  -4.0f, 2.0f, 0.0f},    
{ -2.0f, 2.0f, -14.0f},    
{  0.0f, 2.0f, -4.0f }},

{{  -4.0f, 14.0f, 0.0f},    
{ -2.0f, 14.0f, -14.0f},
{  0.0f, 14.0f, -4.0f }},};
//���Ʊ���������
void draw_bessel_face() {
	glEnable(GL_AUTO_NORMAL);
	int i,j;    
    glColor3f(1.0f, 0.0f, 0.0f); //�ѵ�Ŵ�һ�㣬���ø����  glPointSize(5.0f); 
    /*glBegin(GL_POINTS); 
    for(i = 0; i < nNumPoints; i++)
		for(j = 0; j < 3; j++)
			glVertex3fv(myPoints[i][j]);
	glEnd();*/

	glColor3f(0.0f, 0.0f, 1.0f); //����ӳ�䷽ʽ��ֻ��Ҫ����һ�ο�����SetupRC�е��á�  
    glMap2f(GL_MAP2_VERTEX_3, //���ɵ���������  
        0.0f, // u���½� 
		10.0f, //u���Ͻ�  
		3, //�����е�ļ��  
		3, //u�����ϵĽ�  
		0.0f, //v���½�  
		10.0f, //v���Ͻ�  
		9, // ���Ƶ�֮��ļ��  ÿ������һ�����Ƶ㣿��
		3, // v�����ϵĽ�  
		&myPoints[0][0][0]); //���Ƶ����� 
	//������ֵ��  
	glEnable(GL_MAP2_VERTEX_3); 
	//��0��10ӳ��һ������10���������  
    glMapGrid2f(10,0.0f,10.0f,10,0.0f,10.0f); 
	// ��������  
    glEvalMesh2(GL_LINE,0,10,0,10); 
	glDisable(GL_AUTO_NORMAL);
}

void draw_bessel_face(GLfloat **ctrl_points[], int u_number, int v_number, GLenum draw_mode,
					  float un, float vn) {
	glEnable(GL_AUTO_NORMAL);
	int i,j;    
    //glColor3f(1.0f, 0.0f, 0.0f); //�ѵ�Ŵ�һ�㣬���ø���� 
	/*glPointSize(5.0f); 
    glBegin(GL_POINTS); 
    for(i = 0; i < u_number; i++)
		for(j = 0; j < v_number; j++)
			glVertex3fv(ctrl_points[i][j]);
	glEnd();*/

    glMap2f(GL_MAP2_VERTEX_3, //���ɵ���������  
        0.0f, // u���½� 
		un, //u���Ͻ�  
		3, //�����е�ļ��  
		u_number, //u�����ϵĽ�??
		0.0f, //v���½�  
		vn, //v���Ͻ�  
		u_number * 3, // ���Ƶ�֮��ļ��  ÿ������һ�����Ƶ㣿��
		v_number, // v�����ϵĽ�??
		&ctrl_points[0][0][0]); //���Ƶ����� 
	//������ֵ��  
	glEnable(GL_MAP2_VERTEX_3); 
	//��0��10ӳ��һ������10���������  
    glMapGrid2f(un, 0.0f, un, vn, 0.0f, vn); 
	// ��������  
    glEvalMesh2(draw_mode, 0, un, 0, vn); 
	glDisable(GL_AUTO_NORMAL);
}

extern CVector3 DivideVectorByScaler(CVector3 vVector1, float Scaler);

//ͨ������matrix�任�����point
CVector3 transform(double matrix[], CVector3 point) {
    CVector3 result;
	float scale;
	result.x = matrix[0] * point.x + matrix[4] * point.y + matrix[8] * point.z + matrix[12] * 1;
	result.y = matrix[1] * point.x + matrix[5] * point.y + matrix[9] * point.z + matrix[13] * 1;
	result.z = matrix[2] * point.x + matrix[6] * point.y + matrix[10] * point.z + matrix[14] * 1;
	scale = matrix[3] * point.x + matrix[7] * point.y + matrix[11] * point.z + matrix[15] * 1;
	return DivideVectorByScaler(result, scale);
}