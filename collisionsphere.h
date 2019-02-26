#include "vector.h"
#ifndef COLLISIONSPHERE_H
#define COLLISIONSPHERE_H

class collisionsphere{
	public:
	float r;
	vector3d center;
	collisionsphere(vector3d c,float rad);
	collisionsphere();
};

#endif
