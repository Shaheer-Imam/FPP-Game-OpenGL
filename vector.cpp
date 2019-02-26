#include "vector.h"

vector3d::vector3d()
{
	x=y=z=0;
}

vector3d::vector3d(float a,float b)
{
	x=a;
	y=b;
	z=0;
}

vector3d::vector3d(float a,float b,float c)
{
	x=a;
	y=b;
	z=c;
}

float vector3d::dotproduct(const vector3d& vec2)
{
	return (x*vec2.x+y*vec2.y+z*vec2.z);
}

vector3d vector3d::crossproduct(const vector3d& vec2)
{
	return (vector3d(y*vec2.z-z*vec2.y,x*vec2.z-z*vec2.x,x*vec2.y-y*vec2.x));
}

float vector3d::length()
{
	return (sqrt(x*x+y*y+z*z));
}

void vector3d::change(float a,float b,float c)
{
	x=a;
	y=b;
	z=c;
}

void vector3d::change(vector3d vec)
{
	x=vec.x;
	y=vec.y;
	z=vec.z;
}

void vector3d::change(vector3d& vec)
{
	x=vec.x;
	y=vec.y;
	z=vec.z;
}

void vector3d::changeX(float a)
{
	x=a;
}

void vector3d::changeY(float b)
{
	y=b;
}

void vector3d::changeZ(float c)
{
	z=c;
}


void vector3d::normalize()
{
	float len=length();
	if(len!=0)
	{
		x/=len;
		y/=len;
		z/=len;
	}
}

vector3d vector3d::operator+(const vector3d& vec2)
{
	return (vector3d(x+vec2.x,y+vec2.y,z+vec2.z));
}

vector3d vector3d::operator-(const vector3d& vec2)
{
	return (vector3d(x-vec2.x,y-vec2.y,z-vec2.z));
}

vector3d vector3d::operator*(const float& num)
{
	return (vector3d(x*num,y*num,z*num));
}

vector3d& vector3d::operator+=(const vector3d& vec2)
{
	x+=vec2.x;
	y+=vec2.y;
	z+=vec2.z;
	return *this;
}

vector3d& vector3d::operator-=(const vector3d& vec2)
{
	x-=vec2.x;
	y-=vec2.y;
	z-=vec2.z;
	return *this;
}

vector3d& vector3d::operator*=(const float& num)
{
	x*=num;
	y*=num;
	z*=num;
	return *this;
}

vector3d& vector3d::operator/=(const float& num)
{
	if(num!=0)
	{
		x/=num;
		y/=num;
		z/=num;
	}
	return *this;
}

bool vector3d::operator==(const vector3d& vec2)
{
	return (x==vec2.x && y==vec2.y && z==vec2.z);
}

bool vector3d::operator!=(const vector3d& vec2)
{
	return (x!=vec2.x && y!=vec2.y && z!=vec2.z);
}

std::ostream& operator<<(std::ostream& out,vector3d vec2)
{
	out << vec2.x << "\t" << vec2.y << "\t" << vec2.z << std::endl;
	return out;
}
