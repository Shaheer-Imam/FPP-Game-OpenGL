#include "player.h"

player::player(std::string n,collisionsphere sphere,weapon* defweapon,float speed,float looks,float ss)
{
	weapons.push_back(defweapon);
	name=n;
	cs=sphere;
	health=500;
	curweapon=0;
	force.change(0.0,-0.3,0.0);
	direction.change(0.0,0.0,0.0);
	setPosition(vector3d(0.0,10,0));
	cam.setSpeed(speed,looks);
	sprintspeed=ss;
	normalspeed=speed;
	lookspeed=looks;
	energy=10;
	issprint=false;
	points=0;
	isWeapon=true;
}

void player::show()
{
	if(isWeapon)
		weapons[curweapon]->show();
}

void player::changeWeapon(unsigned int num)
{
	if(num<weapons.size() && num>=0)
		curweapon=num;
}

void player::changeWeaponUp()
{
	curweapon++;
	if(curweapon>=weapons.size())
		curweapon=0;
	std::cout << curweapon << std::endl;
}

void player::changeWeaponDown()
{
	curweapon--;
	if(curweapon<0)
		curweapon=weapons.size()-1;
	std::cout << curweapon << std::endl;
}

void player::jump()
{
	if(isground)
	{
		isground=false;
		direction.change(0.0,2,0.0);
	}
}

collisionsphere player::getCollisionSphere()
{
	return cs;
}

std::string player::getName()
{
	return name;
}

void player::setPosition(vector3d pos)
{
	cs.center=pos;
	cam.setLocation(pos);
}

void player::update(std::vector<collisionplane>& cp)
{
	if(direction.y>=force.y)
		direction+=force;
//	std::cout << direction;
	vector3d newpos(cam.getLocation());
	newpos+=direction;
	vector3d tmp(newpos);
	for(int i=0;i<cp.size();i++)
		sphereplane(newpos,cp[i].normal,cp[i].p[0],cp[i].p[1],cp[i].p[2],cp[i].p[3],cs.r);
	//std::cout << "\n" << newpos;
	if(newpos.y>tmp.y)
		isground=true;
	setPosition(newpos);
	weapons[curweapon]->update();
	if(energy<10 && !issprint)
		energy+=0.01;
	if(issprint)
		energy-=0.05;
	if(energy<=0)
		setSprint(false);
	std::cout << curweapon << std::endl;
}

void player::addWeapon(weapon* w)
{
	weapons.push_back(w);
}

camera* player::getCamera()
{
	return &cam;
}

void player::decreaseHealth(int num)
{
	health-=num;
}

int player::getHealth()
{
	return health;
}


weapon* player::getCurWeapon()
{
	return weapons[curweapon];
}

void player::setHealth(int h)
{
	health=h;
}


void player::addHealth(int h)
{
	health+=h;
}

void player::setSprint(bool b)
{
	if(energy>3)
	{
		if(b && !weapons[curweapon]->isaimed())
		{
			issprint=true;
			cam.setSpeed(sprintspeed,lookspeed);
		}else{
			issprint=b;
			cam.setSpeed(normalspeed,lookspeed);
		}
	}else{
		issprint=false;
		cam.setSpeed(normalspeed,lookspeed);
	}
}

bool player::isSprinting()
{
	return issprint;
}

void player::addPoints(int num)
{
	points+=num;
}

int player::getPoints()
{
	return points;
}

int player::getNumWeapons()
{
	return weapons.size();
}

void player::holdWeapon(bool b)
{
	isWeapon=b;
}
