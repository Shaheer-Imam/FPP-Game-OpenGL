#include "skybox.h"

skybox::skybox()
{
	for(int i=0;i<6;i++)
		images[i]=999;
}

skybox::skybox(const char* left,const char* back,const char* right,const char* front,const char* top,const char* bottom)
{
	images[SKY_LEFT]=loadTexture(left);
	images[SKY_BACK]=loadTexture(back);
	images[SKY_RIGHT]=loadTexture(right);
	images[SKY_FRONT]=loadTexture(front);
	images[SKY_TOP]=loadTexture(top);
	images[SKY_BOTTOM]=loadTexture(bottom);
	
//	"data/left.bmp","data/back.bmp","data/right.bmp","data/front.bmp","data/top.bmp","data/bottom.bmp"
}

void skybox::change(const char* left,const char* back,const char* right,const char* front,const char* top,const char* bottom)
{
	if(images[0]!=999)
		glDeleteTextures(6,&images[0]);
	images[SKY_LEFT]=loadTexture(left);
	images[SKY_BACK]=loadTexture(back);
	images[SKY_RIGHT]=loadTexture(right);
	images[SKY_FRONT]=loadTexture(front);
	images[SKY_TOP]=loadTexture(top);
	images[SKY_BOTTOM]=loadTexture(bottom);
}

unsigned int skybox::loadTexture(const char* filename)	//load the filename named texture
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

skybox::~skybox()
{
	glDeleteTextures(6,&images[0]);
}

void skybox::drawSkybox(float size)
{
	bool b1=glIsEnabled(GL_TEXTURE_2D);	//new, we left the textures turned on, if it was turned on
	bool b2=glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);	//turn off lighting, when making the skybox
	glDisable(GL_DEPTH_TEST);	//turn off depth texting
	glEnable(GL_TEXTURE_2D);	//and turn on texturing
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,images[SKY_BACK]);	//use the texture we want
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
	glBindTexture(GL_TEXTURE_2D,images[SKY_LEFT]);
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
	glBindTexture(GL_TEXTURE_2D,images[SKY_FRONT]);
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
	glBindTexture(GL_TEXTURE_2D,images[SKY_RIGHT]);	
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
	glBindTexture(GL_TEXTURE_2D,images[SKY_TOP]);		
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
	glBindTexture(GL_TEXTURE_2D,images[SKY_BOTTOM]);		
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
	glEnable(GL_DEPTH_TEST);
	if(!b1)
		glDisable(GL_TEXTURE_2D);
	if(b2)
		glEnable(GL_LIGHTING);	//turn everything back, which we turned on, and turn everything off, which we have turned on.
	//	std::cout << "called" << std::endl;
}
