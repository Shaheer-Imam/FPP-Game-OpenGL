//This example program is created by thecplusplusuy for demonstration purposes. It's a simple skybox:
//http://www.youtube.com/user/thecplusplusguy
//Free source, modify if you want, LGPL licence (I guess), I would be happy, if you would not delete the link
//so other people can see the tutorial
//this file is functions.h, it's contain the function prototypes
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cmath>
#include "objloader.h"
#include "vector.h"
#ifndef FUNCTION_H
#define FUNCTION_H



void drawCube(float size);
void drawSkybox(float size);	//draw the skybox
void initskybox();	//load the textures
void killskybox();	//delete the textures
void lockCamera();
void moveCamera(float,float);
void moveCamerraUp(float,float);
void Control(float,float,bool);
void UpdateCamera();
unsigned int loadTexture(const char*);
float dotproduct(float x1,float y1,float z1,float x2,float y2,float z2);
bool sphereplane(vector3d& sp,vector3d pn,vector3d p1,vector3d p2,vector3d p3,vector3d p4, float r);
bool raysphere(float xc,float yc,float zc,float xd,float yd,float zd,float xs,float ys,float zs,float r);
bool rayplane(const float& nx,float ny,float nz,float x0,float y0,float z0,float xs,float ys,float zs,float xd,float yd,float zd,vector3d p1,vector3d p2,vector3d p3,vector3d p4);
float trianglearea(vector3d p1,vector3d p2,vector3d p3);
bool spheresphere(vector3d c1,float r1,vector3d c2,float r2);
vector3d getcamcoord();
void setcamcoord(float x,float y,float z);
#endif
