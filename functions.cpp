#include "functions.h"

float camX=0.0,camY=0.0,camZ=5.0;
float camYaw=0.0;
float camPitch=0.0;
enum {SKY_LEFT=0,SKY_BACK,SKY_RIGHT,SKY_FRONT,SKY_TOP,SKY_BOTTOM};	//constants for the skybox faces, so we don't have to remember so much number
unsigned int skybox[6];	//the ids for the textures
#ifndef M_PI
#define M_PI 3.1415926535
#endif
void initskybox()
{
	skybox[SKY_LEFT]=loadTexture("data/left.bmp");
	skybox[SKY_BACK]=loadTexture("data/back.bmp");
	skybox[SKY_RIGHT]=loadTexture("data/right.bmp");
	skybox[SKY_FRONT]=loadTexture("data/front.bmp");
	skybox[SKY_TOP]=loadTexture("data/top.bmp");
	skybox[SKY_BOTTOM]=loadTexture("data/bottom.bmp");
}
void killskybox()
{
	glDeleteTextures(6,&skybox[0]);
}

void drawSkybox(float size)
{
	bool b1=glIsEnabled(GL_TEXTURE_2D);	//new, we left the textures turned on, if it was turned on
	glDisable(GL_LIGHTING);	//turn off lighting, when making the skybox
	glDisable(GL_DEPTH_TEST);	//turn off depth texting
	glEnable(GL_TEXTURE_2D);	//and turn on texturing
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);	//use the texture we want
	glBegin(GL_QUADS);	//and draw a face
		//back face
		glTexCoord2f(0,0);	//use the correct texture vector3d
		glVertex3f(size/2,size/2,size/2);	//and a vertex
		glTexCoord2f(1,0);	//and repeat it...
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(1,1);
		glVertex3f(-size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(size/2,-size/2,size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
	glBegin(GL_QUADS);	
		//left face
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(1,0);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
	glBegin(GL_QUADS);	
		//front face
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,-size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);	
	glBegin(GL_QUADS);	
		//right face
		glTexCoord2f(0,0);
		glVertex3f(size/2,size/2,-size/2);
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_TOP]);		
	glBegin(GL_QUADS);			//top face
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,size/2,-size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_BOTTOM]);		
	glBegin(GL_QUADS);	
		//bottom face
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(1,0);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();
	glEnable(GL_LIGHTING);	//turn everything back, which we turned on, and turn everything off, which we have turned on.
	glEnable(GL_DEPTH_TEST);
	if(!b1)
		glDisable(GL_TEXTURE_2D);
}






void lockCamera()
{
	if(camPitch>90)
		camPitch=90;
	if(camPitch<-90)
		camPitch=-90;
	if(camYaw<0.0)
		camYaw+=360.0;
	if(camYaw>360.0)
		camYaw-=360;
}

void moveCamera(float dist,float dir)
{
	float rad=(camYaw+dir)*M_PI/180.0;
	camX-=sin(rad)*dist;
	camZ-=cos(rad)*dist;
}

void moveCameraUp(float dist,float dir)
{
	float rad=(camPitch+dir)*M_PI/180.0;
	camY+=sin(rad)*dist;	
}

void Control(float movevel,float mousevel,bool mi)
{
	if(mi)
	{
		int MidX=320;
		int MidY=240;
		SDL_ShowCursor(SDL_DISABLE);
		int tmpx,tmpy;
		SDL_GetMouseState(&tmpx,&tmpy);
		camYaw+=mousevel*(MidX-tmpx);
		camPitch+=mousevel*(MidY-tmpy);
		lockCamera();
		SDL_WarpMouse(MidX,MidY);
		Uint8* state=SDL_GetKeyState(NULL);
		if(state[SDLK_w])
		{
	//		if(camPitch!=90 && camPitch!=-90)
				moveCamera(movevel,0.0);
	//		moveCameraUp(movevel,0.0);
		}else if(state[SDLK_s])
		{
	//		if(camPitch!=90 && camPitch!=-90)
				moveCamera(movevel,180.0);
	//		moveCameraUp(movevel,180.0);
		}		
		if(state[SDLK_a])
			moveCamera(movevel,90.0);
		else if(state[SDLK_d])
			moveCamera(movevel,270);	
	}
	glRotatef(-camPitch,1.0,0.0,0.0);
	glRotatef(-camYaw,0.0,1.0,0.0);
}

void UpdateCamera()
{
	glTranslatef(-camX,-camY,-camZ);
}

void drawCube(float size)
{
	float difamb[]={1.0,0.5,0.3,1.0};
	glBegin(GL_QUADS);
		//front face
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,difamb);
		glNormal3f(0.0,0.0,1.0);
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,-size/2,size/2);
		glVertex3f(size/2,-size/2,size/2);

		//left face
		glNormal3f(-1.0,0.0,0.0);
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,-size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(-size/2,-size/2,size/2);

		//back face
		glNormal3f(0.0,0.0,-1.0);
		glVertex3f(size/2,size/2,-size/2);
		glVertex3f(-size/2,size/2,-size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(size/2,-size/2,-size/2);

		//right face
		glNormal3f(1.0,0.0,0.0);
		glVertex3f(size/2,size/2,-size/2);
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(size/2,-size/2,size/2);
		glVertex3f(size/2,-size/2,-size/2);

		//top face
		glNormal3f(0.0,1.0,0.0);
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,-size/2);
		glVertex3f(size/2,size/2,-size/2);

		//bottom face
		glNormal3f(0.0,-1.0,0.0);
		glVertex3f(size/2,-size/2,size/2);
		glVertex3f(-size/2,-size/2,size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();
}





unsigned int loadTexture(const char* filename)	//load the filename named texture
{
	unsigned int num;	//the id for the texture
	glGenTextures(1,&num);	//we generate a unique one
	SDL_Surface* img=SDL_LoadBMP(filename);	//load the bmp image
	glBindTexture(GL_TEXTURE_2D,num);	//and use the texture, we have just generated
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	//we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	//we do it for vertically and horizontally (previous line)
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);	//we make the actual texture
	SDL_FreeSurface(img);	//we delete the image, we don't need it anymore
	return num;	//and we return the id
}


float dotproduct(float x1,float y1,float z1,float x2,float y2,float z2)
{
	return (x1*x2+y1*y2+z1*z2);
}

bool raysphere(float xc,float yc,float zc,float xd,float yd,float zd,float xs,float ys,float zs,float r)
{
	float b=2*(xd*(xs-xc)+yd*(ys-yc)+zd*(zs-zc));
	float c=xs*xs-2*xs*xc+xc*xc+ys*ys-2*ys*yc+yc*yc+zs*zs-2*zs*zc+zc*zc-r*r;
	float disc=(b*b-4*c);
	if(disc<0)	//if the discriminant is less then 0, there is no intersection
		return false;
	else
		return true;
}

float trianglearea(vector3d p1,vector3d p2,vector3d p3)
{
	//area of the triangle with the heron fomula
	float a=sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y)+(p2.z-p1.z)*(p2.z-p1.z));
	float b=sqrt((p3.x-p2.x)*(p3.x-p2.x)+(p3.y-p2.y)*(p3.y-p2.y)+(p3.z-p2.z)*(p3.z-p2.z));
	float c=sqrt((p1.x-p3.x)*(p1.x-p3.x)+(p1.y-p3.y)*(p1.y-p3.y)+(p1.z-p3.z)*(p1.z-p3.z));
	float s=(a+b+c)/2.;
	return (sqrt(s*((s-a)*(s-b)*(s-c))));
}
	//distance of 2 point (with 3d pythagoras formula)
float pointdistace(vector3d p1,vector3d p2)
{
	vector3d vec(p2.x-p1.x,p2.y-p1.y,p2.z-p1.z);
	return (sqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z));
}

float pointdistacesquare(vector3d p1,vector3d p2)
{
	vector3d vec(p2.x-p1.x,p2.y-p1.y,p2.z-p1.z);
	return (vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
}


bool rayplane(const float& nx,float ny,float nz,float x0,float y0,float z0,float xs,float ys,float zs,float xd,float yd,float zd,vector3d p1,vector3d p2,vector3d p3,vector3d p4)
{
	if((xd*nx+yd*ny+zd*nz)==0)	//if the two vector dot product is 0, then there is no intersection (we don't like to divide by 0)
		return false;
	float t=((x0*nx+y0*ny+z0*nz-nx*xs-ny*ys-nz*zs)/(xd*nx+yd*ny+zd*nz));
	if(t<0)	//if t<0, the intersction point is in the opposite direction
		return false;
	float x=xs+t*xd;	//calculate the 3 point vector3d
	float y=ys+t*yd;
	float z=zs+t*zd;
	vector3d i(x,y,z);
	if((abs(trianglearea(p1,p2,p3)-(trianglearea(p1,p2,i)+trianglearea(p2,p3,i)+trianglearea(p1,p3,i)))<0.001) || abs(trianglearea(p1,p3,p4)-(trianglearea(p1,p3,i)+trianglearea(p3,p4,i)+trianglearea(p1,p4,i)))<0.001)	//we divide the quad to 2 triangle, we divide one triangle to 3 (one point is the
	//intersection point), and if the area of the 3 triangle is equal to the main triangle, then the point is inside the triangle. We do the same with
	//the other triangle, and if one is true, then the point is in the quad
		return true;
	return false;	//else not
}
	//we just give back the distance of the plane
float rayplanedist(float nx,float ny,float nz,float x0,float y0,float z0,float xs,float ys,float zs,float xd,float yd,float zd)
{
	if((xd*nx+yd*ny+zd*nz)==0)
		return 0;
	float t=((x0*nx+y0*ny+z0*nz-nx*xs-ny*ys-nz*zs)/(xd*nx+yd*ny+zd*nz));
	if(t<0)
		return 0;
	return t;
}

bool sphereplane(vector3d& sp,vector3d pn,vector3d p1,vector3d p2,vector3d p3,vector3d p4, float r)
{
		//if the distance is greater then the radius, there is no collision
		if(rayplanedist(pn.x,pn.y,pn.z,p1.x,p1.y,p1.z,sp.x,sp.y,sp.z,-pn.x,-pn.y,-pn.z)>r || rayplanedist(-pn.x,-pn.y,-pn.z,p1.x,p1.y,p1.z,sp.x,sp.y,sp.z,pn.x,pn.y,pn.z)>r)
			return false;
	//if the ray from the center of the sphere is intersect the plane, there is a collision
	if(rayplane(pn.x,pn.y,pn.z,p1.x,p1.y,p1.z,sp.x,sp.y,sp.z,-pn.x,-pn.y,-pn.z,p1,p2,p3,p4) || rayplane(-pn.x,-pn.y,-pn.z,p1.x,p1.y,p1.z,sp.x,sp.y,sp.z,pn.x,pn.y,pn.z,p1,p2,p3,p4))
	{
		float raycol=rayplanedist(pn.x,pn.y,pn.z,p1.x,p1.y,p1.z,sp.x,sp.y,sp.z,-pn.x,-pn.y,-pn.z);	//we calculate how far we are
		if(raycol)	//if not zero
		{
			sp.x=sp.x+pn.x*(r-raycol);	//calculate the point, and calculate our new location
			sp.y=sp.y+pn.y*(r-raycol);
			sp.z=sp.z+pn.z*(r-raycol);		
		}else	//else if we are in the opposite side, then the normal vector
		{
			raycol=rayplanedist(-pn.x,-pn.y,-pn.z,p1.x,p1.y,p1.z,sp.x,sp.y,sp.z,pn.x,pn.y,pn.z);
			sp.x=sp.x-pn.x*(r-raycol);
			sp.y=sp.y-pn.y*(r-raycol);
			sp.z=sp.z-pn.z*(r-raycol);				
		}

		return true;	//we return true, to indicate the collision, but the main thing is, that we changged the sp (so the sphere position) to the new position)
	}
	return false;
}

bool spheresphere(vector3d c1,float r1,vector3d c2,float r2)
{
	return (pointdistacesquare(c1,c2)<=(r1+r2)*(r1+r2));
}

vector3d getcamcoord()
{
	return (vector3d(camX,camY,camZ));
}

void setcamcoord(float x,float y,float z)
{
	camX=x;
	camY=y;
	camZ=z;
}



