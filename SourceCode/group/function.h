#ifndef __FUNCTION__H__
#define __FUNCTION__H__

#include "base.h"
#include "CTargaImage.h"
#include "c3ds.h"

#define TEXT_LIST_LENGTH 96

struct Point{
    float x;
	float y;
	float z;
	Point(float x_ = 0, float y_ = 0, float z_ = 0):x(x_), y(y_), z(z_) {}
};

void create_bmp_text(char *font_name, int font_size);
void render_bmp_text(int x_pos, int y_pos, char *str);

void load_tga_texture(char *filename, unsigned int &texture_obj);
void load_bmp_texture(char *filename);

void draw_terrain();

void draw_bessel_line();
void draw_bessel_face();
void draw_bessel_line(GLfloat *ctrl_points[], int ctrl_number, GLenum draw_mode);
void draw_bessel_face(GLfloat **ctrl_points[], int u_number, int v_number, GLenum draw_mode, float un, float vn);

CVector3 transform(double matrix[], CVector3 point);


//void draw_3ds_model(t3DModel model);


#endif //__FUNCTION__H__