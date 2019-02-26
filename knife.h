#ifndef KNIFE_H
#define KNIFE_H
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "zombie.h"
#include "vector.h"
#include "collision.h"
#include <SDL/SDL_mixer.h>

class knife{
	std::vector<unsigned int> frames;
	bool isknifing;
	int strength;
	int delay;
	int wepDelay;
	int lastKnifing;
	int curframe;
	vector3d loc;
	Mix_Chunk* hitSound;
	Mix_Chunk* notHitSound;
	public:
	knife(std::vector<unsigned int>& f,int str,int del,int wdel,vector3d location,Mix_Chunk*,Mix_Chunk*);
	int setKnife(player* p,std::vector<zombie>& zombies);
	void update(player* p);
	void show();
	bool isKnifing();
	int getStrength();
	void test();
};


#endif
