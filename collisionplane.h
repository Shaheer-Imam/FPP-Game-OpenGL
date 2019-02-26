#ifndef collisionplane_H
#define collisionplane_H
#include <iostream>
#include "vector.h"

class collisionplane{
	public:
	vector3d p[4];
	vector3d normal;
		collisionplane(float n1,float n2,float n3, float a,float b, float c,    float d, float e, float f,   float g, float h, float i,   float j, float k, float l);
		vector3d get1point();
		vector3d get2point();
		vector3d get3point();
		vector3d get4point();
		vector3d getnormal();
		bool isok();
};
#endif
