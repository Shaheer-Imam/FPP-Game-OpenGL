#ifndef SKYBOX_H
#define SKYBOX_H
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cmath>
#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
class skybox{
	unsigned int images[6];
	enum {SKY_LEFT=0,SKY_BACK,SKY_RIGHT,SKY_FRONT,SKY_TOP,SKY_BOTTOM};
	unsigned int loadTexture(const char* c);
	public:
	skybox();
	skybox(const char* left,const char* ack,const char* right,const char* front,const char* top,const char* bottom);
	void change(const char* left,const char* ack,const char* right,const char* front,const char* top,const char* bottom);
	void drawSkybox(float);
	~skybox();
};
#endif
