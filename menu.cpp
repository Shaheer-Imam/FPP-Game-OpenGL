#include "menu.h"

menu::menu(unsigned int back,std::vector<collisionplane>& pl,std::vector<std::string>& str,collisionplane backposition2,text* t)
{
	background=back;
	planes=pl;
	strings=str;
	backpos=new collisionplane(backposition2);
	tex=t;
	curselection=0;
	istest=false;
}


int menu::run()
{
	bool b1=glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();
	curselection=0;
	Uint32 start;
	SDL_Event event;
	while(true)
	{
		start=SDL_GetTicks();
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT);
		test();
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							if(b1)
								glEnable(GL_LIGHTING);
							glColor3f(1,1,1);
							return 1;
							break;
						case SDLK_UP:
							curselection--;
							if(curselection<0)
								curselection=planes.size()-1;
							break;
						case SDLK_DOWN:
							curselection++;
							if(curselection>planes.size()-1)
								curselection=0;
							break;
						case SDLK_RETURN:
							if(b1)
								glEnable(GL_LIGHTING);
							glColor3f(1,1,1);
							return curselection;
							break;
						}
						break;
			}
		}
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,background);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);
			glVertex3f(backpos->p[0].x,backpos->p[0].y,backpos->p[0].z);
			glTexCoord2f(0.0,1.0);
			glVertex3f(backpos->p[1].x,backpos->p[1].y,backpos->p[1].z);
			glTexCoord2f(1.0,1.0);
			glVertex3f(backpos->p[2].x,backpos->p[2].y,backpos->p[2].z);
			glTexCoord2f(1.0,0.0);
			glVertex3f(backpos->p[3].x,backpos->p[3].y,backpos->p[3].z);
	//		glVertex3f(-1,1,-2);
	//		glVertex3f(-1,-1,-2);
	//		glVertex3f(1,-1,-2);
	//		glVertex3f(1,1,-2);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		std::cout << curselection << std::endl;
		for(int i=0;i<planes.size();i++)
		{
			if(i==curselection)
			{
				std::cout << "i n" << std::endl;
				glBegin(GL_QUADS);
					glColor3f(1,0,0);
					glVertex3f(planes[i].p[0].x,planes[i].p[0].y+0.032,planes[i].p[0].z);
					glColor3f(0,0,0);
					glVertex3f(planes[i].p[0].x,planes[i].p[0].y,planes[0].p[0].z);
					glVertex3f(planes[i].p[0].x+strings[i].length()*0.032,planes[i].p[0].y,planes[i].p[0].z);
					glColor3f(1,0,0);
					glVertex3f(planes[i].p[0].x+strings[i].length()*0.032,planes[i].p[0].y+0.032,planes[i].p[0].z);
				glEnd();
			}
			glColor3f(0,0,0);
			tex->drawText(planes[i].p[0],vector3d(0,0,0),vector3d(0.035,0.035,0.035),strings[i].c_str());
		}
		SDL_GL_SwapBuffers();
		if(1000/30>(SDL_GetTicks()-start))
			SDL_Delay(1000/30-(SDL_GetTicks()-start));
	}
	return 0;
}

menu::~menu()
{
	delete backpos;
}

void menu::test()
{
	if(istest)
	{
		Uint8* keys=SDL_GetKeyState(NULL);
		if(keys[SDLK_j])
		{
			planes[0].p[0].x-=0.1;
		}
		if(keys[SDLK_l])
		{
			planes[0].p[0].x+=0.1;
		}
		if(keys[SDLK_k])
		{
			planes[0].p[0].y-=0.01;
		}
		if(keys[SDLK_i])
		{
			planes[0].p[0].y+=0.01;
		}
		if(keys[SDLK_u])
		{
			backpos->p[0].y-=0.1;
			backpos->p[1].y-=0.1;
			backpos->p[2].y-=0.1;
			backpos->p[3].y-=0.1;
		}
		if(keys[SDLK_o])
		{
			backpos->p[0].y+=0.1;
			backpos->p[1].y+=0.1;
			backpos->p[2].y+=0.1;
			backpos->p[3].y+=0.1;
		}
		std::cout << planes[0].p[0]  << std::endl;
		
	}
}
