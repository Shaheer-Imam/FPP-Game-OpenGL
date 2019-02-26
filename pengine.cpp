#include "pengine.h"


particle::particle(float x,float y,float z,float Xvel,float Yvel,float Zvel,int life)
{
	pos.change(x,y,z);
	direction.change(Xvel,Yvel,Zvel);
	startTime=SDL_GetTicks();
	endTime=SDL_GetTicks()+life;
}

void particle::move()
{
//	std::cout << pos << SDL_GetTicks() << " " << endTime << std::endl;
	pos+=direction;
}

void particle::show()
{
		glVertex3f(pos.x,pos.y,pos.z);
}

bool particle::isDead()
{
	return (SDL_GetTicks()>=endTime);
}


particleSystem::particleSystem(int partnum,vector3d vec)
{
	pos=vec;
	maxparticle=partnum;
	istest=true;
	for(int i=0;i<maxparticle;i++)
	{
		particles.push_back(new particle(pos.x,pos.y,pos.z,(rand()%10+(float)rand()/(float)RAND_MAX-5),(rand()%10+(float)rand()/(float)RAND_MAX-5),(rand()%10+(float)rand()/(float)RAND_MAX-5),50+(rand()%70)));
	//	particles.push_back(new particle(0.0,0.0,0.0,0.3,0.3,0.3,1000));
	}
}

particleSystem::~particleSystem()
{
	for(int i=0;i<maxparticle;i++)
		delete particles[i];
}

void particleSystem::refresh()
{
	bool b1=glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	test();
	glColor4f(1,1,1,0.5);
	glBegin(GL_POINTS);
	for(int i=0;i<maxparticle;i++)
	{
		if(particles[i]->isDead())
		{
			delete particles[i];
			particles[i]=new particle(pos.x+(rand()%6-3)/100.0,pos.y+(rand()%6-3)/100.0,pos.z+(rand()%6-3)/100.0,(rand()%10+(float)rand()/(float)RAND_MAX-5)/500.0,(rand()%10+(float)rand()/(float)RAND_MAX-3)/400.0,(rand()%10+(float)rand()/(float)RAND_MAX-5)/500.0,30+(rand()%7));	
		//	particles[i]=new particle(0.0,0.0,0.0,0.3,0.3,0.3,1000);	
		}else{
			particles[i]->move();
			particles[i]->show();
		}
	}
	glEnd();
	if(b1)
		glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glColor3f(1.0,1.0,1.0);
//	std::cout << "--------------------" << std::endl; 
}


void particleSystem::test()
{
	if(istest)
	{
		Uint8* keys=SDL_GetKeyState(NULL);
		if(keys[SDLK_j])
		{
			pos.x-=0.1;
		}
		if(keys[SDLK_l])
		{
			pos.x+=0.1;
		}
		if(keys[SDLK_k])
		{
			pos.y-=0.1;
		}
		if(keys[SDLK_i])
		{
			pos.y+=0.1;
		}
		if(keys[SDLK_u])
		{
			pos.z-=0.1;
		}
		if(keys[SDLK_o])
		{
			pos.z+=0.1;
		}
		std::cout << pos  << std::endl;
		
	}
}
