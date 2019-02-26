#include "zombie.h"
std::vector<unsigned int> zombie::frames;
unsigned int zombie::walk=0;
unsigned int zombie::attack=0;
unsigned int zombie::die=0;

zombie::zombie(std::vector<unsigned int>& f,unsigned int& w,unsigned int& at,unsigned int& di,int h,float s,int str,collisionsphere c,vector3d rot,vector3d playerpos)
{
	frames=f;
	walk=w;
	attack=at;
	die=di;
	health=h;
	speed=s;
	strength=str;
	isattack=false;
	iswalk=true;
	isdead=false;
	cs=c;
	rotation=rot;
	direction.change(playerpos-cs.center);
	direction.normalize();
	curframe=0;
}

zombie::zombie(int h,float s,int str,collisionsphere c,vector3d rot,vector3d playerloc)
{
//	if(frames.size()!=0)
//	{
		health=h;
		speed=s;
		strength=str;
		isattack=false;
		iswalk=true;
		isdead=false;
		cs=c;
		rotation=rot;
		direction.change(playerloc-cs.center);
		direction.normalize();
		curframe=0;
//	}
}

bool zombie::update(std::vector<collisionplane>& map2,vector3d playerpos)
{
	if(!isdead)
	{
		direction.change(playerpos-cs.center);
		direction.normalize();
		rotation.y=std::acos(direction.z);
		if(direction.x>0)
			rotation.y=-rotation.y;
	}
//	std::cout << "dir: " << direction;
//	std::cout << rotation.y*(180/M_PI) << std::endl;
//	std::cout << direction;
	if(health<=0 && !isdead)
	{
		isdead=true;
		iswalk=false;
		isattack=false;
		curframe=walk+attack;
		return 1;
	}
//	std::cout << isdead << iswalk << isattack << std::endl;
	curframe++;
	if(iswalk && curframe>=walk)
		curframe=0;
	if(isattack && curframe>=walk+attack)
		curframe=walk;
	if(isdead && curframe>=walk+attack+die)
		curframe=walk+attack+die-1;
	if(!isdead)
	{
		vector3d newpos(cs.center);
//		std::cout << direction;
	//	newpos.y-=0.1;
		newpos+=direction*speed;
		newpos.y-=0.3;
		for(int i=0;i<map2.size();i++)
			sphereplane(newpos,map2[i].normal,map2[i].p[0],map2[i].p[1],map2[i].p[2],map2[i].p[3],cs.r);
		//		std::cout << "collision" << std::endl;
		setLocation(newpos);

	}
    return 0;
//	std::cout << cs.center << " ----- " << iswalk << " " << isattack << " "  << curframe <<  "  ---- " << direction << std::endl;
}

void zombie::show()
{
	glEnable(GL_NORMALIZE);
	glPushMatrix();
	//	std::cout << rotation.y << std::endl;
		glTranslatef(cs.center.x,cs.center.y-1.0,cs.center.z);
		glRotatef(rotation.x,1,0,0);
		glRotatef(-rotation.y*(180/M_PI),0,1,0);
		glRotatef(rotation.z,0,0,1);
		glScalef(1.5,1.5,1.5);
		glCallList(frames[curframe]);
	glPopMatrix();
	glDisable(GL_NORMALIZE);
}

collisionsphere* zombie::getSphere()
{
	return &cs;
}

void zombie::setLocation(vector3d& loc)
{
	cs.center=loc;
}

bool zombie::setAttack(collisionsphere playerloc)
{
	if(spheresphere(cs.center,cs.r,playerloc.center,playerloc.r) && !isdead)
	{
		isattack=true;
		iswalk=false;
		return 1;
	}else if(!isdead){
		iswalk=true;
		isattack=false;
		return 0;
	}
}


void zombie::decreaseHealth(int num)
{
	health-=num;
}

int zombie::getHealth()
{
	return health;
}

int zombie::getStrength()
{
	return strength;
}

bool zombie::isDead()
{
	return isdead;
}
