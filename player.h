#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <cstdlib>
#include "weapon.h"
#include "vector.h"
#include "collisionsphere.h"
#include "collision.h"
#include "collisionplane.h"
#include <string>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

class player:private collision {
	std::vector<weapon*> weapons;
	std::string name;
	collisionsphere cs;
	int health;
	int curweapon;
	vector3d force;
	vector3d direction;
	bool isground;
	bool iscollision;
	float sprintspeed;
	float normalspeed;
	float lookspeed;
	bool issprint;
	float energy;
	int points;
	bool isWeapon;
	public:
	camera cam;
	player(std::string n,collisionsphere sphere,weapon* defweapon,float,float, float);
	void update(std::vector<collisionplane>& cp);
	void show();
	void changeWeapon(unsigned int num);
	void changeWeaponUp();
	void changeWeaponDown();
	void jump();
	collisionsphere getCollisionSphere();
	std::string getName();
	camera* getCamera();
	void setPosition(vector3d pos);
	void addWeapon(weapon* w);
	weapon* getCurWeapon();
	void decreaseHealth(int num);
	int getHealth();
	void setHealth(int h);
	void addHealth(int h);
	void setSprint(bool b);
	bool isSprinting();
	void addPoints(int num);
	int getPoints();
	int getNumWeapons();
	void holdWeapon(bool);
};
#endif
