#ifndef __TERRAIN__H__
#define __TERRAIN__H__

//#include "gl/glew.h"
#include "base.h"


const int TERRAIN_SIZE = 128;
const char heightmapFilename[] = "resource/terrain/heightmap.raw";

const float MAX_HEIGHT = 10.0f;
const float SCALE_FACTOR = 256.0f / MAX_HEIGHT;
const float WATER_HEIGHT = 0.8f;
const float TC_SCALE = 4.0f/TERRAIN_SIZE;

class Terrain {
public:
    bool init();
	void render();

	GLubyte heightmap[TERRAIN_SIZE * TERRAIN_SIZE];
	int m_windowWidth;
	int m_windowHeight;

	GLuint m_grassTexture;
    GLuint m_waterTexture;
    GLuint m_heightTexture;
};

#endif //__TERRAIN__H__