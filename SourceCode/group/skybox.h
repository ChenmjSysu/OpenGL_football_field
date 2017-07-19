#ifndef __SKYBOX__H__
#define __SKYBOX__H__

#include "CTargaImage.h"



class SkyBox {
public:
	SkyBox();
	~SkyBox();

	void init(float size);
	bool load_texture(char *top, char *bottom, char *front, char *back, char *left, char *right);
	void render(float x, float y, float z);
	void release_textures();

	enum {
		SKY_TOP,
		SKY_BOTTOM,
		SKY_FRONT,
		SKY_BACK,
		SKY_LEFT,
		SKY_RIGHT
	};

private:
	unsigned int m_textures[6];
	float m_size;
};


#endif //__SKYBOX__H__