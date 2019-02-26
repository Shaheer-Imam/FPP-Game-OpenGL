#include "object.h"

OneObject::OneObject(std::vector<unsigned int>& f,std::vector<collisionplane>& c,std::string n,int i)
{
	frames=f;
	cp=c;
	name=n;
	id=i;
}
std::string& OneObject::getName()
{
	return name;
}

int OneObject::getId()
{
	return id;
}



void Object::add(std::vector<unsigned int>& f,std::vector<collisionplane>& c,vector3d& p,std::string n,int idd)
{
	for(int i=0;i<obj.size();i++)
		if(obj[i].getId()==idd)
		{
			objects.push_back(ObjectPos(idd,p));
			return;
		}else{
			obj.push_back(OneObject(f,c,n,idd));
			objects.push_back(ObjectPos(idd,p));
			return;
		}
}

	void Object::add(int id,vector3d pos)
	{
		for(int i=0;i<obj.size();i++)
			if(obj[i].getId()==id)
			{
				objects.push_back(ObjectPos(id,pos));
				return;
			}
	}
	void Object::add(std::string name,vector3d pos)
	{
		for(int i=0;i<obj.size();i++)
			if(obj[i].getName()==name)
			{
				objects.push_back(ObjectPos(obj[i].getId(),pos));
				return;
			}
	}
	bool Object::del(int id)
	{
		for(int i=0;i<obj.size();i++)
			if(obj[i].getId()==id)
			{
				obj.erase(obj.begin()+i);
				return 1;
			}
			return 0;
	}
	bool Object::del(std::string name)
	{
		for(int i=0;i<obj.size();i++)
			if(obj[i].getName()==name)
			{
				obj.erase(obj.begin()+i);
				return 1;
			}
			return 0;
	}
