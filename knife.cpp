#include "knife.h"

knife::knife(std::vector<unsigned int>& f,int str,int del,int wdel,vector3d location,Mix_Chunk* hit,Mix_Chunk* notHit)
{
	frames=f;
	strength=str;
	delay=del;
	wepDelay=wdel;
	isknifing=false;
	lastKnifing=100;
	curframe=0;
	loc=location;
	hitSound=hit;
	notHitSound=notHit;
}

int knife::setKnife(player* p,std::vector<zombie>& zombies)
{
	if(lastKnifing>delay)
	{
		p->holdWeapon(false);
		lastKnifing=0;
		isknifing=true;
		curframe=0;
		vector3d direction=p->cam.getVector();
		float dist;
		for(int i=0;i<zombies.size();i++)
		{
		//float xc,float yc,float zc,float xd,float yd,float zd,float xs,float ys,float zs,float r
			if(collision::raysphere(zombies[i].getSphere()->center.x,zombies[i].getSphere()->center.y,zombies[i].getSphere()->center.z,direction.x,direction.y,direction.z,p->cam.getLocation().x,p->cam.getLocation().y,p->cam.getLocation().z,zombies[i].getSphere()->r,&dist))
			{
		//		std::cout << dist << std::endl;
				if(dist<9.0 && !zombies[i].isDead())
				{
					Mix_PlayChannel(-1,hitSound,0);
					return i;
				}
			}
		}
		Mix_PlayChannel(-1,notHitSound,0);
		return -1;
	}else	
		return -1;
}

void knife::update(player* p)
{
//	test();
	lastKnifing++;
	if(lastKnifing>wepDelay)
		p->holdWeapon(true);
	if(isknifing)
	{
		curframe++;
		if(curframe>=frames.size())
		{
			isknifing=false;
			curframe=0;
		}
	}
}


void knife::show()
{
//	isknifing=true;
//	curframe=3;
	if(isknifing)
	{
		glTranslatef(loc.x,loc.y,loc.z);
		glCallList(frames[curframe]);
	}
}

int knife::getStrength()
{
	return strength;
}

bool knife::isKnifing()
{
	return isknifing;
}

void knife::test()
{
		Uint8* keys=SDL_GetKeyState(NULL);
		if(keys[SDLK_j])
			loc.x-=0.1;
		if(keys[SDLK_l])
			loc.x+=0.1;
		if(keys[SDLK_k])
			loc.z-=0.1;
		if(keys[SDLK_i])
			loc.z+=0.1;
		if(keys[SDLK_u])
			loc.y-=0.1;
		if(keys[SDLK_o])
			loc.y+=0.1;
		std::cout << loc.x << " " << loc.y << " " << loc.z << std::endl;
}
