#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include "vector.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "collisionsphere.h"
#include "collision.h"

struct oneItem
{
	int id;
	unsigned int mesh;
	vector3d rotation;
	collisionsphere cs;
	vector3d scale;
	oneItem(int& i,unsigned int& m,collisionsphere c);
};

class item:public collision{
	std::vector<oneItem> items;
	public:
	item(int i,unsigned int mesh,collisionsphere& c);
	item();
	int update(collisionsphere playerloc);
	void show();
	void add(int i,unsigned int mesh,collisionsphere c);
	void del(int id);
};

#endif
