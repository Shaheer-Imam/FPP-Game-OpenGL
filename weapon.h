#ifndef WEAPON_H
#define WEAPON_H
#include <vector>
#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <cstdlib>
#include <ctime>
#include "vector.h"
#include "camera.h"

class weapon{
	std::vector<unsigned int> frames;
	unsigned int outerview;
	unsigned int normalanimation;	//2,3,4
	unsigned int fireanimation;	//0,1
	unsigned int reloadanimation;	//2,3,4
	Mix_Chunk *firesound;					//5,6,7,8
	Mix_Chunk *reloadsound;
	Mix_Chunk *normalsound;		//not used
	Mix_Chunk *emptysound;
	vector3d curpos;
	vector3d currot;
	vector3d position;
	vector3d rotation;
	vector3d curPos;
	vector3d curRot;
	
	vector3d aimposition;
	vector3d aimrotation;
	float precision;
	float aimprecision;
	int strength;
	bool isaim;
	bool isreloading;
	bool isautomatic;
	bool isfired;
	bool istest;
	unsigned int numbullets;
	float length;							//not used
	unsigned int speed;
	unsigned int curframe;
	unsigned int curmode;
	unsigned int lastshot;
	unsigned int bullets;
	unsigned int allbullets;
	std::string name;
	public:
		weapon(std::vector<unsigned int>& anim,unsigned int na,unsigned int fa,unsigned int ra,Mix_Chunk *fs,Mix_Chunk* rs,Mix_Chunk* ns,Mix_Chunk* es,vector3d pos,vector3d rot,vector3d apos,vector3d arot,float prec,float aprec,unsigned int numb,float length,unsigned int sp,bool isauto,int strength,const char* name,unsigned int);
		void aim();
		bool fire(vector3d& direction,vector3d& startpoint,vector3d& camdirection);
		void nofire();
		bool reload();
		void update();
		void show();
		void test();
		void addBullets(unsigned int num);
		void setBullets(unsigned int num);
		int getStrength();
		int getAmmo();
		int getAllAmmo();
		std::string& getName();
		std::vector<unsigned int>& getAnimation();
		bool isaimed();
		unsigned int getOuterView();
};

#endif
