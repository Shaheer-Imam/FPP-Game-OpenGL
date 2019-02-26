#ifndef PENGINE_H
#define PENGINE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "vector.h"

class particle{
	vector3d pos;
	vector3d direction;
	vector3d clone;
	Uint32 startTime;
	Uint32 endTime;
	public:
	particle(float x,float y,float z,float Xvel,float Yvel,float Zvel,int life);
	void move();
	void show();
	bool isDead();
};


class particleSystem{
	std::vector<particle*> particles;
	vector3d pos;
	int maxparticle;
	bool istest;
	void test();
	public:
	particleSystem(int partnum,vector3d p);
	~particleSystem();
	void refresh();
};
#endif
