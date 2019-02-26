#ifndef LEVEL_H
#define LEVEL_H
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <string>
#include "skybox.h"
#include "vector.h"
#include "collisionplane.h"
#include "collision.h"
#include "object.h"
#include "collisionsphere.h"

class map{
	unsigned int mesh;
	std::vector<collisionplane> cp;
	std::vector<vector3d> spawnPoints;
	std::string name;
	skybox* sky;
	public:
	map(unsigned int m,std::vector<collisionplane>& cplane,std::string n,std::vector<std::string>& skyImages,std::vector<vector3d>& sp);
	void update();
	void show();
	std::vector<collisionplane>& getCollisionPlanes();
	std::string& getName();
	skybox* getSkybox();
	void change(unsigned int m,std::vector<collisionplane>& cplane,std::string n,std::string skyImages[]);
	std::vector<vector3d>* getSpawnPoints();
	vector3d* getRandomSpawnPoint();
};
#endif
