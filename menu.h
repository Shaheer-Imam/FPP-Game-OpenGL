#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include "collisionplane.h"
#include "collision.h"
#include "text.h"
#ifndef MENU_H
#define MENU_H

class menu{
	unsigned int background;
	std::vector<collisionplane> planes;
	std::vector<std::string> strings;
	text* tex;
	collisionplane* backpos;
	int curselection;
	bool istest;
	void test();
public:
	menu(unsigned int back,std::vector<collisionplane>& pl,std::vector<std::string>& str,collisionplane backposition,text* t);
	~menu();
	int run();
};

#endif
