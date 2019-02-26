#include "item.h"

oneItem::oneItem(int& i,unsigned int& m,collisionsphere c)
{
	id=i;
	mesh=m;
	rotation.change(0,0,0);
	cs=c;
	scale=vector3d(1,1,1);
}


item::item(int i,unsigned int mesh,collisionsphere& c)
{
	items.push_back(oneItem(i,mesh,c));
}

item::item()
{

}

int item::update(collisionsphere playerpos)
{
	for(int i=0;i<items.size();i++)
	{
		items[i].rotation.y+=1;
		if(items[i].rotation.y>360)
			items[i].rotation.y-=360;
	}
	for(int i=0;i<items.size();i++)
	{
		if(spheresphere(items[i].cs.center,items[i].cs.r,playerpos.center,playerpos.r))
		{
			int id=items[i].id;
			items.erase(items.begin()+i);
			return id;
		}
	}
	return -1;
}

void item::show()
{
	glEnable(GL_NORMALIZE);
	for(int i=0;i<items.size();i++)
	{
		glPushMatrix();
			glTranslatef(items[i].cs.center.x,items[i].cs.center.y,items[i].cs.center.z);
			glRotatef(items[i].rotation.x,1.0,0.0,0.0);
			glRotatef(items[i].rotation.y,0.0,1.0,0.0);
			glRotatef(items[i].rotation.z,0.0,0.0,1.0);
			glScalef(items[i].scale.x,items[i].scale.y,items[i].scale.z);
			glCallList(items[i].mesh);
		glPopMatrix();
	}
	glDisable(GL_NORMALIZE);
}

void item::add(int i,unsigned int mesh,collisionsphere c)
{
	items.push_back(oneItem(i,mesh,c));
}

void item::del(int id)
{
	for(int i=0;i<items.size();i++)
	{
		if(items[i].id==id)
		{
			items.erase(items.begin()+i);
			break;
		}
	}
}
