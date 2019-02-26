#include "weapon.h"

weapon::weapon(std::vector<unsigned int>& anim,unsigned int na,unsigned int fa,unsigned int ra,Mix_Chunk *fs,Mix_Chunk* rs,Mix_Chunk* ns,Mix_Chunk* es,vector3d pos,vector3d rot,vector3d apos,vector3d arot,float prec,float aprec,unsigned int numb,float leng,unsigned int sp,bool isauto,int stre,const char* nam,unsigned int ov)
{
	frames=anim;
	normalanimation=na;
	fireanimation=fa;
	reloadanimation=ra;
	firesound=fs;
	std::cout << firesound << std::endl;
	reloadsound=rs;
	normalsound=ns;
	emptysound=es;
	curpos=pos;
	currot=rot;
	position=pos;
	rotation=rot;
	aimposition=apos;
	aimrotation=arot;
	precision=(prec!=0 ? prec : 0.00001);
	aimprecision=(aprec!=0 ? aprec : 0.00001);
	isaim=false;
	isreloading=false;
	isautomatic=isauto;
	isfired=false;
	istest=true;
	numbullets=numb;			//bullets which can be put to the magazine
	length=leng;
	speed=sp;
	curframe=0;
	curmode=1;
	lastshot=1000;
	bullets=numbullets;	//bullets in the magazine
	srand(time(NULL));
	strength=stre;
	allbullets=300;		//all of my bullets
	name=nam;
	std::cout << "weapon.size = " << frames.size() << std::endl;
	outerview=ov;
	curPos=curpos;
	curRot=currot;
}


void weapon::aim()
{
	isaim=!isaim;
	if(isaim)
	{
		currot=aimrotation;
		curpos=aimposition;
	}else{
		curpos=position;
		currot=rotation;
	}
}

bool weapon::fire(vector3d& direction,vector3d& startpoint,vector3d& camdirection)
{
	if(isreloading)
		return 0;
	if((!isautomatic && !isfired) || isautomatic)
	{
		if(lastshot>=speed)
		{
			if(bullets>0)
			{
				if(isaim)
				{
					direction.x=camdirection.x+((float)(rand()%2-1)/aimprecision);
					direction.y=camdirection.y+((float)(rand()%2-1)/aimprecision);
					direction.z=camdirection.z+((float)(rand()%2-1)/aimprecision);
				}else{
					direction.x=camdirection.x+((float)(rand()%2-1)/precision);
					direction.y=camdirection.y+((float)(rand()%2-1)/precision);
					direction.z=camdirection.z+((float)(rand()%2-1)/precision);	
				}
				isfired=true;
				lastshot=0;
				Mix_PlayChannel(-1,firesound,0);
				bullets--;
				curframe=normalanimation;
				curmode=2;
				return 1;
			}else{
				Mix_PlayChannel(-1,emptysound,0);
				reload();
				return 0;
			}
		}
	}
	return 0;
}

void weapon::nofire()
{
	isfired=false;
}

bool weapon::reload()
{
	if(!isreloading && numbullets!=bullets)
	{
		isreloading=true;
		if(allbullets+bullets>numbullets)
		{
			allbullets-=numbullets-bullets;
			bullets=numbullets;
		}else{
			bullets=allbullets+bullets;
			allbullets=0;
		}
		curframe=normalanimation+fireanimation;
		curmode=3;
		Mix_PlayChannel(-1,reloadsound,0);
	}
}

void weapon::update()
{
//	test();
	lastshot++;
	curframe++;
	std::cout << curframe << std::endl;
	if(curmode==1)
	{
		if(curframe>normalanimation)
			curframe=0;
	}else if(curmode==2)
	{
		if(curframe>normalanimation+fireanimation)
		{
			if(isautomatic && isfired)
			{
				curframe=normalanimation;
			}else{
				curmode=1;
				curframe=0;
			}
		}
	}else if(curmode==3)
	{
		if(curframe>=normalanimation+fireanimation+reloadanimation-1)
		{
			curmode=1;
			curframe=0;
			isreloading=false;
		}
	}
	vector3d tmpVec(curpos-curPos);
	tmpVec.normalize();
//		std::cout << "tmpVec: " << tmpVec;
	tmpVec*=0.3;
	curPos+=tmpVec;
	if(std::abs(curPos.x-curpos.x)<0.3 && std::abs(curPos.y-curpos.y)<0.3 && std::abs(curPos.z-curpos.z)<0.3)
		curPos=curpos;
	std::cout << "curpos: " << curPos;
	tmpVec.change(currot-curRot);
	tmpVec.normalize();
	tmpVec*=0.3;
	curRot+=tmpVec;	
	if(std::abs(curRot.x-currot.x)<0.3 && std::abs(curRot.y-currot.y)<0.3 && std::abs(curRot.z-currot.z)<0.3)
		curRot=currot; 
	
}

void weapon::show()
{
//	curframe=0;
	test();
	glPushMatrix();
		glTranslatef(curPos.x,curPos.y,curPos.z);
		glRotatef(currot.x,1,0,0);
		glRotatef(currot.y,0,1,0);
		glRotatef(currot.z,0,0,1);
		glCallList(frames[curframe]);
	glPopMatrix();
}

void weapon::test()
{
	if(istest)
	{
		Uint8* keys=SDL_GetKeyState(NULL);
		if(keys[SDLK_j])
			curpos.x-=0.01;
		if(keys[SDLK_l])
			curpos.x+=0.01;
		if(keys[SDLK_k])
			curpos.z-=0.01;
		if(keys[SDLK_i])
			curpos.z+=0.01;
		if(keys[SDLK_u])
			curpos.y-=0.01;
		if(keys[SDLK_o])
			curpos.y+=0.01;
		std::cout << curpos.x << " " << curpos.y << " " << curpos.z << std::endl;
		
	}
}

void weapon::addBullets(unsigned int num)
{
	allbullets+=num;
}

void weapon::setBullets(unsigned int num)
{
	allbullets=num;
}

int weapon::getStrength()
{
	return strength;
}
int weapon::getAmmo()
{
	return bullets;
}
		
int weapon::getAllAmmo()
{
	return allbullets;
}

std::string& weapon::getName()
{
	return name;
}

std::vector<unsigned int>& weapon::getAnimation()
{
	return frames;
}

bool weapon::isaimed()
{
	return isaim;
}

unsigned int weapon::getOuterView()
{
	return outerview;
}
