#ifndef __RENDER__H__
#define __RENDER__H__

#include "Terrain.h"
#include "CTargaImage.h"
#include "skybox.h"
#include "court.h"
#include "fps.h"


void init();

void keyAction(unsigned char key, int x, int y);

void idle();

void Display();

void set_light();

void help();

void Reshape(int width, int height);

#endif //__RENDER__H__