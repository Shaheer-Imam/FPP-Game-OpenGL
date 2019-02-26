#ifndef GAME_H
#define GAME_H
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <SDL/SDL_mixer.h>
#include <GL/glu.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "camera.h"
#include "collisionplane.h"
#include "collisionsphere.h"
#include "player.h"
#include "level.h"
#include "skybox.h"
#include "objloader.h"
#include "collision.h"
#include "item.h"
#include "vector.h"
#include "weapon.h"
#include "zombie.h"
#include "menu.h"
#include "text.h"
#include "object.h"
#include "pengine.h"
#include "knife.h"
#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

#define DEFAULT_SCREEN_X 1024
#define DEFAULT_SCREEN_Y 768 // Peter: These should probably be const int's. I know how much you hate macros :D

class game{
	objloader obj;
	player* player1;
	std::vector<zombie> zombies;
	std::vector<weapon> weapons;
	std::vector<Mix_Chunk*> sounds;
	Mix_Music* music;
	menu* gameMenu;
	bool running;
	bool isfired;
	unsigned int loadTexture(const char* filename);
	void loadAnimation(std::vector<unsigned int>& anim,const std::string filename,int frames);
	vector3d direction;
	vector3d startpoint;
	vector3d camdirection;
	static const int FPS=30;
	bool isshot;
	bool isgod;
	std::vector<map> levels;
	std::ofstream out;
	text* tex;
	void drawMenu(int health,int ammo,int allammo,int point,std::string& weaponName);
	item object;
	std::vector<unsigned int> models;
	std::vector<unsigned int> textures;
	bool addToplist(int point,const char* name);
	particleSystem* pe;
	Mix_Chunk* loadSound(const char* c);
	knife* kn;
	public:
	game();
	~game();
	void start();
	void update();
	void show();
};


#endif
