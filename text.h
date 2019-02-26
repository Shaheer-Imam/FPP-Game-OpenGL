#include <SDL/SDL.h>
#ifndef TEXT_H
#define TEXT_H
#include <string>
#include <cstring>
#include <iostream>
#include <GL/gl.h>
#include "vector.h"
#include "collisionplane.h"
#include <vector>
#include <GL/glu.h>

class text{
	std::vector<unsigned int> characters;
	float width,height;
	bool istest;
	bool islocked;
	vector3d changepos,changerot,changescale;
	public:
	text(std::vector<unsigned int>& ch,float w,float h);
	void assignFont(std::vector<unsigned int>& ch,float w,float h);
	void drawText(vector3d pos,vector3d rot,vector3d scale,const char* tex);
	void test(vector3d& pos,vector3d& rot, vector3d& scale);
	void setTest(bool b);
};
#endif
