#include "terrain.h"

#include "CTargaImage.h"

#include <cmath>
#include <cstdio>


bool Terrain::init() {
	if (!GLeeInit())
        return false;

    if (!GLEE_VERSION_1_3)
		return false;
	FILE *pFile = fopen(heightmapFilename, "rb");
	if (!pFile)
	return false;

	fread(&heightmap, TERRAIN_SIZE * TERRAIN_SIZE, 1, pFile);
	fclose(pFile);

	CTargaImage image;

	image.Load("resource/terrain/grass.tga");
	glGenTextures(1, &m_grassTexture);
	glBindTexture(GL_TEXTURE_2D, m_grassTexture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());
	image.Release();

	image.Load("resource/terrain/water.tga");
	glGenTextures(1, &m_waterTexture);
	glBindTexture(GL_TEXTURE_2D, m_waterTexture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());
	image.Release();

	image.Load("resource/terrain/height.tga");
	glGenTextures(1, &m_heightTexture);
	glBindTexture(GL_TEXTURE_1D, m_heightTexture);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, image.GetWidth(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());
	image.Release();
	//glClearColor(0.7f, 0.7f, 0.9f, 1.0);

	return true;
}

void Terrain::render() {
    // select texture unit 1
	glActiveTexture(GL_TEXTURE1);
	// enable object linear texture coordinate generation based on the water plane
	glEnable(GL_TEXTURE_GEN_S);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	GLfloat waterPlane[] = { 0.0, 1.0, 0.0, -WATER_HEIGHT };
	glTexGenfv(GL_S, GL_OBJECT_PLANE, waterPlane);

	// switch back to texture unit 0
	glActiveTexture(GL_TEXTURE0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glScalef(10, 1, 10);
	glTranslatef(0, -2, 0);
      
    // load the grass texture into texture unit 0
	glBindTexture(GL_TEXTURE_2D, m_grassTexture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// load the height texture into texture unit 1
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_1D);
	glBindTexture(GL_TEXTURE_1D, m_heightTexture);

	// scale the generated texture coordinates to fall between
	// 0 and 1.
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(1.0f/MAX_HEIGHT, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	// draw the terrain
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	for (int z = 0; z < TERRAIN_SIZE - 1; ++z) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < TERRAIN_SIZE; ++x) {
			GLfloat scaledHeight = heightmap[z * TERRAIN_SIZE + x] / SCALE_FACTOR;
			GLfloat nextScaledHeight = heightmap[(z + 1)*TERRAIN_SIZE + x]/SCALE_FACTOR;

			// assign texture coordinates for texture unit 0
			glMultiTexCoord2f(GL_TEXTURE0, x * TC_SCALE, z * TC_SCALE);
			glVertex3f((GLfloat)x - TERRAIN_SIZE/2, scaledHeight, (GLfloat)z - TERRAIN_SIZE/2);

			// assign texture coordinates for texture unit 0
			glMultiTexCoord2f(GL_TEXTURE0, x * TC_SCALE, (z+1) * TC_SCALE);
			glVertex3f((GLfloat)x - TERRAIN_SIZE/2, nextScaledHeight, (GLfloat)(z + 1) - TERRAIN_SIZE/2);
		}
		glEnd();
	}
	// disable texture unit 1 and switch back to texture unit 0
	glDisable(GL_TEXTURE_1D);
	glActiveTexture(GL_TEXTURE0);

	//draw the water. only one texture will be applied (from texture unit 0).
	glBindTexture(GL_TEXTURE_2D, m_waterTexture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-TERRAIN_SIZE/2.1f, WATER_HEIGHT, TERRAIN_SIZE/2.1f);
	glTexCoord2f(TERRAIN_SIZE/4.0f, 0.0);
	glVertex3f(TERRAIN_SIZE/2.1f, WATER_HEIGHT, TERRAIN_SIZE/2.1f);
	glTexCoord2f(TERRAIN_SIZE/4.0f, TERRAIN_SIZE/4.0f);
	glVertex3f(TERRAIN_SIZE/2.1f, WATER_HEIGHT, -TERRAIN_SIZE/2.1f);
	glTexCoord2f(0.0, TERRAIN_SIZE/4.0f);
	glVertex3f(-TERRAIN_SIZE/2.1f, WATER_HEIGHT, -TERRAIN_SIZE/2.1f);
	glEnd();
	glPopMatrix();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}