#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <iostream>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "weapon.h"
#include "vector.h"
#include "collisionsphere.h"
#include "collisionplane.h"
#include "collision.h"
#include <string>
#include <vector>
#include <cmath>
#include <SDL/SDL_mixer.h>

class zombie : private collision
{
	static std::vector<unsigned int> frames;
	static unsigned int walk;
	static unsigned int attack;
	static unsigned int die;
	int health;
	float speed;
	int strength;
	vector3d direction;
	bool isattack;
	bool iswalk;
	collisionsphere cs;
	vector3d rotation;
	unsigned int curframe;
	bool isdead;
	
	public:
	zombie(std::vector<unsigned int>& f,unsigned int& w,unsigned int& at,unsigned int& di,int h,float s,int str,collisionsphere c,vector3d rot,vector3d playerloc);
	zombie(int h,float s,int str,collisionsphere c,vector3d rot,vector3d playerloc);
	bool update(std::vector<collisionplane>&,vector3d);
	void show();
	collisionsphere* getSphere();
	void setLocation(vector3d& loc);
	bool setAttack(collisionsphere playerloc);
	void decreaseHealth(int num);
	int getHealth();
	int getStrength();
	bool isDead();
};

#endif
