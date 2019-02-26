#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <cmath>

class vector3d{
		public:
		float x,y,z;
		vector3d();
		vector3d(float a,float b);
		vector3d(float a,float b,float c);
		~vector3d(){};
		float dotproduct(const vector3d& vec2);
		vector3d crossproduct(const vector3d& vec2);
		float length();
		void change(float a,float b,float c);
		void change(vector3d&);
		void change(vector3d);
		void changeX(float a);
		void changeY(float b);
		void changeZ(float c);
		void normalize();
		vector3d operator+(const vector3d& vec2);
		vector3d operator-(const vector3d& vec2);
		vector3d operator*(const float& num);
		vector3d operator/(const float& num);
		vector3d& operator+=(const vector3d& vec2);
		vector3d& operator-=(const vector3d& vec2);
		vector3d& operator*=(const float& num);
		vector3d& operator/=(const float& num);
		bool operator==(const vector3d& vec2);
		bool operator!=(const vector3d& vec2);
		friend std::ostream& operator<<(std::ostream& out,vector3d vec2); 
};
#endif
