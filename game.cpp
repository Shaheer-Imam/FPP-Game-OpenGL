#include "game.h"

game::game()
{
	int screenX = DEFAULT_SCREEN_X, screenY = DEFAULT_SCREEN_Y, input = 0;

	std::cout << "Enter screenX or 0 to keep default resolution (";
	std::cout << DEFAULT_SCREEN_X << " x " << DEFAULT_SCREEN_Y << "): ";

	std::cin >> input;

	if(input != 0){
		screenX = input;
		std::cout << "Enter screenY: ";
		std::cin >> input;
		screenY = input;
	}

	std::cout << "Fullscreen? (y/n): ";

	char inputc = 'y';
	std::cin >> inputc;

	out.open("report.txt");
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);

	std::cout << "Loading-- (this may take a while!) ...\n\n";

	if(inputc == 'y' || inputc == 'Y')
		SDL_Surface* screen=SDL_SetVideoMode(screenX,screenY,32,SDL_SWSURFACE|SDL_OPENGL|SDL_FULLSCREEN);
	else
		SDL_Surface* screen=SDL_SetVideoMode(screenX,screenY,32,SDL_SWSURFACE|SDL_OPENGL);


	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	glClearColor(0.5,0.5,0.5,1.0);
	glClearDepth(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640.0/480.0,0.1,500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float col[]={0.5,0.5,0.5,1.0};
	float amb[]={0.3,0.3,0.3,1.0};
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,col);
	//glShadeModel(GL_SMOOTH);
	std::ifstream in("weapons.dat");
	char tmp[10][300];
	int tmparr[10];
	float floatarr[12];
	while(!in.eof())
	{
		in.getline(tmp[0],300);
		if(tmp[0][0]=='\0')
			break;
		sscanf(tmp[0],"%s %s %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d %d %d %d %d %s %s %s %s %s",tmp[1],tmp[2],&tmparr[2],&tmparr[0],&tmparr[1],&floatarr[0],&floatarr[1],&floatarr[2],&floatarr[3],&floatarr[4],&floatarr[5],&floatarr[6],&floatarr[7],&floatarr[8],&floatarr[9],&floatarr[10],&floatarr[11],&tmparr[3],&tmparr[4],&tmparr[5],&tmparr[6],&tmparr[7],&tmparr[8],&tmparr[9],tmp[3],tmp[4],tmp[5],tmp[6],tmp[7]);
		std::vector<unsigned int> weaponanim;
		loadAnimation(weaponanim,tmp[2],tmparr[0]+tmparr[1]+tmparr[2]);
		Mix_Chunk* sound1=Mix_LoadWAV(tmp[3]);
		Mix_Chunk* sound2=Mix_LoadWAV(tmp[4]);
		Mix_Chunk* sound3=Mix_LoadWAV(tmp[5]);
		Mix_Chunk* sound4=Mix_LoadWAV(tmp[6]);
		weapons.push_back(weapon(weaponanim,tmparr[2],tmparr[0],tmparr[1],sound1,sound2,sound3,sound4,vector3d(floatarr[0],floatarr[1],floatarr[2]),vector3d(floatarr[3],floatarr[4],floatarr[5]),vector3d(floatarr[6],floatarr[7],floatarr[8]),vector3d(floatarr[9],floatarr[10],floatarr[11]),tmparr[3],tmparr[4],tmparr[5],tmparr[6],tmparr[7],tmparr[8],tmparr[9],tmp[1],obj.load(tmp[7],NULL)));
	}
	std::cout << weapons.size() << std::endl;
	player1=new player("name",collisionsphere(vector3d(0,0,0),3.0),&weapons[0],0.2,0.2,0.7);
//	player1->addWeapon(&weapons[1]);
//	player1->addWeapon(&weapons[2]);
	in.close();
	in.open("spawn.dat");
	std::vector<vector3d> sp;
	while(!in.eof())
	{
		in.getline(tmp[0],300);
		sscanf(tmp[0],"%d %d %d",&tmparr[0],&tmparr[1],&tmparr[2]);
		sp.push_back(vector3d(tmparr[0],tmparr[1],tmparr[2]));
	}
	in.close();
	in.open("game.dat");
	out << "2\n";
	std::vector<std::string> skyb;
	std::vector<collisionplane> cp;
	isfired=false;
//	while(!in.eof())
//	{
		in.getline(tmp[9],300);
	out << "3\n";
		sscanf(tmp[9],"%s %s %s %s %s %s %s %s",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5],tmp[6],tmp[7]);
		for(int i=1;i<7;i++)
				out << tmp[i] << "\t";
//		std::cout << std::endl;
		for(int i=1;i<7;i++)
			skyb.push_back(tmp[i]);
	out << "4\n";

		out << tmp[7] << std::endl;
		unsigned int m=obj.load(tmp[7],&cp);
		levels.push_back(map(m,cp,tmp[0],skyb,sp));
		std::cout << "cp size: " << cp.size() << std::endl;
		for(int i=0;i<cp.size();i++)
			std::cout << cp[i].normal << cp[i].p[0] << cp[i].p[1] << cp[i].p[2] << cp[i].p[3] << std::endl;
//	}
	in.close();
	out << "1\n";
	in.open("zombie.dat");
	std::vector<unsigned int> frames;
	out << "5\n";
		unsigned int a,b,c2;
		in.getline(tmp[9],300);
		sscanf(tmp[9],"%s %d %d %d",tmp[0],&a,&b,&c2);
	out << "7\n";
	loadAnimation(frames,std::string(tmp[0]),a+b+c2);
	out << "zombie 1 " << a << " " << b << " " << c2 << std::endl;
	zombies.push_back(zombie(frames,a,b,c2,100,0.1,1,collisionsphere(*levels[0].getRandomSpawnPoint(),2),vector3d(0,0,0),player1->cam.getLocation()));
	running=true;


	std::vector<unsigned int> chars;
	char c[50];
	for(int i=0;i<94;i++)
	{
		sprintf(c,"font/%d.obj",i);
		unsigned int tmp=obj.load(c,NULL);
		chars.push_back(tmp);
	}
	tex=new text(chars,0.8,0.8);
    out << "Text" << std::endl;

	int h=obj.load("data/allammo.obj",NULL);
	models.push_back(h);
	h=obj.load("data/health.obj",NULL);
	models.push_back(h);
	unsigned int texture=loadTexture("data/menu.bmp");
	std::vector<collisionplane> cps;
	cps.push_back(collisionplane(0,0,1,-0.13,0.16,-1,-0.13,0.16,-1,-0.13,0.16,-1,-0.13,0.16,-1));
	cps.push_back(collisionplane(0,0,1,-0.13,0.08,-1,-0.13,0.16,-1,-0.08,0.16,-1,-0.13,0.16,-1));
	std::vector<std::string> strs;
	strs.push_back(std::string("Continue"));
	strs.push_back(std::string("Exit"));
	collisionplane xyz(0,0,1,-1.33,1,-2.4,-1.33,-1,-2.4,1.33,-1,-2.4,1.33,1,-2.4);
	gameMenu=new menu(texture,cps,strs,xyz,tex);
//	tex->setTest(true);
    out << "vmi" << std::endl;
	music=Mix_LoadMUS("data/hive.wav");
	Mix_PlayMusic(music,-1);

	std::cout << "constructor over" << std::endl;
//	pe=new particleSystem(1000,vector3d(0.5,0,-2));
	isgod=false;

	std::vector<unsigned int> frames2;
	loadAnimation(frames2,"data/knife/knife",5);
	Mix_Chunk* tmpSound1=loadSound("data/hit.wav");
	Mix_Chunk* tmpSound2=loadSound("data/nhit.wav");
	kn=new knife(frames2,1000,30,30,vector3d(-0.5,-0.6,-1.3),tmpSound1,tmpSound2);
}


unsigned int game::loadTexture(const char* filename)
{
	unsigned int num;	//the id for the texture
	glGenTextures(1,&num);	//we generate a unique one
	SDL_Surface* img=SDL_LoadBMP(filename);	//load the bmp image
	if(!img)
		std::cout << "problem with texture" << std::endl;
	glBindTexture(GL_TEXTURE_2D,num);	//and use the texture, we have just generated
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	//we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	//we do it for vertically and horizontally (previous line)
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);	//we make the actual texture
	SDL_FreeSurface(img);	//we delete the image, we don't need it anymore
	textures.push_back(num);
	std::cout << num << " " << filename << std::endl;
	return num;	//and we return the id
//	std::cout << "load texture" << std::endl;
}


void game::loadAnimation(std::vector<unsigned int>& anim,const std::string filename,int frames)
{
	char frame[8];
	char tmp[7];
	for(int i=1;i<=frames;i++)
	{
		std::string s(filename+'_');
		sprintf(frame,"%d",i);
		int len=strlen(frame);
		for(int j=0;j<len;j++)
			tmp[j]=frame[j];
		for(int j=0;j<6-len;j++)
			frame[j]='0';
		for(int j=6-len;j<6;j++)
			frame[j]=tmp[j-6+len];
		frame[6]=NULL;
		s+=frame;
		s+=".obj";
		out << s << std::endl;
		anim.push_back(obj.load(s,NULL));
	}

//	std::cout << "load animation" << std::endl;
}

void game::update()
{
	player1->update(levels[0].getCollisionPlanes());
	levels[0].update();
	int k=zombies.size();
	out << zombies.size() << std::endl;
	for(int i=0;i<k;i++)
	{
		if(zombies[i].update(levels[0].getCollisionPlanes(),player1->cam.getLocation()))
		{
			int g=rand()%20;
			if(g==1)
				object.add(0,models[0],collisionsphere(zombies[i].getSphere()->center,1.0));
			else if(g==2)
				object.add(1,models[1],collisionsphere(zombies[i].getSphere()->center,1.0));
			else if(g==3 && weapons.size()>player1->getNumWeapons())
				object.add(player1->getNumWeapons()+10,weapons[player1->getNumWeapons()].getOuterView(),collisionsphere(zombies[i].getSphere()->center,1.0));

			zombies.push_back(zombie(100,0.1,1,collisionsphere(*levels[0].getRandomSpawnPoint(),2.0),vector3d(0,0,0),player1->cam.getLocation()));
			player1->addPoints(10);
		}
		if(zombies[i].setAttack(player1->getCollisionSphere()) && !isgod)
		{
			player1->decreaseHealth(zombies[i].getStrength());
		}
	}
	if(isfired)
	{
		camdirection=player1->getCamera()->getVector();
		isshot=player1->getCurWeapon()->fire(direction,startpoint,camdirection);
		direction.normalize();
		if(isshot)
		{
			for(int i=0;i<zombies.size();i++)
			{
				if(collision::raysphere(zombies[i].getSphere()->center.x,zombies[i].getSphere()->center.y,zombies[i].getSphere()->center.z,direction.x,direction.y,direction.z,player1->cam.getLocation().x,player1->cam.getLocation().y,player1->cam.getLocation().z,3.0))
				{
					std::cout << "collision\n" << zombies[i].getSphere()->center.x << "\t" << zombies[i].getSphere()->center.y << "\t" << zombies[i].getSphere()->center.z << std::endl << direction;
					zombies[i].decreaseHealth(player1->getCurWeapon()->getStrength());
		//			std::cout << zombies[i].getHealth() << std::endl;
				}
			}
		}
	}else{
		player1->getCurWeapon()->nofire();
	}
	int h=object.update(player1->getCollisionSphere());
	switch(h){
		case -1:
			break;
		case 0:
			player1->getCurWeapon()->setBullets(300);
			break;
		case 1:
			player1->setHealth(500);
			break;
		case 10:
			player1->addWeapon(&weapons[0]);
			break;
		case 11:
			player1->addWeapon(&weapons[1]);
			break;
		case 12:
			player1->addWeapon(&weapons[2]);
			break;
	}
//	std::cout << "update called" << std::endl;
//	if(isshot)
	if(player1->getHealth()<=0)
	{
		running=false;
		addToplist(player1->getPoints(),player1->getName().c_str());
	}
	else if(player1->getHealth()<=20)
	{
		glColorMask(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColorMask(1,player1->getHealth()/20.0>=0 ? player1->getHealth()/20.0 : 0,player1->getHealth()/20.0>=0 ? player1->getHealth()/20.0 : 0,1);
	}
	kn->update(player1);
}

void game::show()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glDisable(GL_DEPTH_TEST);
	player1->getCamera()->control();
	levels[0].getSkybox()->drawSkybox(200.0);
	player1->getCamera()->update();
	//glEnable(GL_DEPTH_TEST);
	levels[0].show();
	for(int i=0;i<zombies.size();i++)
		zombies[i].show();
	object.show();
	glLoadIdentity();
	player1->show();

	glClear(GL_DEPTH_BUFFER_BIT);

	drawMenu(player1->getHealth(),player1->getCurWeapon()->getAmmo(),player1->getCurWeapon()->getAllAmmo(),player1->getPoints(),player1->getCurWeapon()->getName());
	kn->show();
//	pe->refresh();


	//int health,int ammo,int allammo,int point,const char* weaponName
//	tex->drawText(vector3d(0,0,-1),vector3d(0,0,0),vector3d(1,1,1),"HEALTH");

//	std::cout << "show called" << std::endl;
}

void game::start()
{
//	SDL_Init(SDL_INIT_EVERYTHING);
//	SDL_Surface* screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);
	SDL_Event event;
	Uint32 startTime;
	running=true;
	int menuoption=0;
	out << "started the game" << std::endl;
	while(running)
	{
		startTime=SDL_GetTicks();
		isshot=false;
//		std::cout << "while loop" << std::endl;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							menuoption=gameMenu->run();
							switch(menuoption)
							{
								case 0:
									break;
								case 1:
									running=false;
									break;
							}
							break;
					case SDLK_r:
						player1->getCurWeapon()->reload();
						break;
					case SDLK_SPACE:
						player1->jump();
						break;
					case SDLK_LSHIFT:
						player1->setSprint(true);
						break;
					case SDLK_0:
						player1->changeWeapon(0);
						break;
					case SDLK_1:
						player1->changeWeapon(1);
						break;
					case SDLK_2:
						player1->changeWeapon(2);
						break;
					case SDLK_3:
						player1->changeWeapon(3);
						break;
					case SDLK_e:
						int knifedzombie=kn->setKnife(player1,zombies);
						std::cout << knifedzombie << std::endl;
						if(knifedzombie!=-1)
							zombies[knifedzombie].decreaseHealth(kn->getStrength());
						break;
					}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym)
					{
						case SDLK_LSHIFT:
							player1->setSprint(false);
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(!player1->cam.IsMouseIn())
						player1->cam.mouseIn();
					else{
						switch(event.button.button)
						{
							case SDL_BUTTON_LEFT:
								if(!player1->cam.IsMouseIn())
								{
									player1->cam.mouseIn();
								}else{
									player1->setSprint(false);
									isfired=true;
								}
								break;
							case SDL_BUTTON_RIGHT:
								player1->getCurWeapon()->aim();
								break;
							case SDL_BUTTON_WHEELUP:
								player1->changeWeaponUp();
								break;
							case SDL_BUTTON_WHEELDOWN:
								player1->changeWeaponDown();
								break;
						}
						break;
					}
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button)
					{
						case SDL_BUTTON_LEFT:
			//				player1->getCurWeapon()->nofire();
							isfired=false;
							break;
					}
					break;
				case SDL_QUIT:
					running=false;
					std::cout << "quiting..." << std::endl;
					break;
			}
		}
		update();
		show();
		SDL_GL_SwapBuffers();
//		std::cout << "while loop, before fps regulation" << std::endl;
		if(1000/FPS>(SDL_GetTicks()-startTime))
			SDL_Delay(1000/FPS-(SDL_GetTicks()-startTime));
	}
}
game::~game()
{
	for(std::vector<unsigned int>::const_iterator it=textures.begin();it!=textures.end();it++)
	{
		glDeleteTextures(1,&(*it));
	}
	delete tex;
	delete kn;
//	delete pe;
	for(int i=0;i<sounds.size();i++)
		Mix_FreeChunk(sounds[i]);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
}

void game::drawMenu(int health,int ammo,int allammo,int point,std::string& weaponName)
{
	char tmp[200];
	sprintf(tmp,"health: %d",health);
	tex->drawText(vector3d(-0.5,0.35,-1),vector3d(0,0,0),vector3d(0.035,0.035,0.035),tmp);
	sprintf(tmp,"%s    %d / %d",weaponName.c_str(),ammo,allammo);
	tex->drawText(vector3d(-0.54,-0.39,-1),vector3d(0,0,0),vector3d(0.035,0.035,0.035),tmp);
	sprintf(tmp,"Points: %d",point);
	tex->drawText(vector3d(0.22,0.35,-1),vector3d(0,0,0),vector3d(0.035,0.035,0.035),tmp);
}


bool game::addToplist(int point,const char* name)
{
	bool res=false;
	std::ifstream in("toplist.dat");
	std::vector<std::string> names;
	std::vector<int> points;
	int tmp;
	char tmp2[2][200];
	if(!in.is_open())
	{
		return false;
	}
	while(!in.eof())
	{
		in.getline(tmp2[0],200);
		sscanf(tmp2[0],"%s %d",tmp2[1],&tmp);
	}
	in.close();
	points.push_back(point);
	names.push_back(name);
	for(int i=0;i<points.size()-1;i++)
	{
		for(int j=i;j<points.size();j++)
		{
			if(points[i]>points[j])
			{
				int tmp3=points[i];
				points[i]=points[j];
				points[j]=tmp3;

				std::string tmp4=names[i];
				names[i]=names[j];
				names[j]=tmp4;
			}
		}
	}
	if(points.size()>10)
	{
		if(names.back()!=name)
			res=true;
		else
			res=false;
		points.erase(points.end()-1);
		names.erase(names.end()-1);
	}else{
		res=true;
	}
	std::ofstream output("toplist.dat");
	for(int i=0;i<points.size();i++)
	{
		output << names[i].c_str() << " " << points[i] << std::endl;
	}
	output.close();
	return res;
}


Mix_Chunk* game::loadSound(const char* c)
{
	Mix_Chunk* sound=Mix_LoadWAV(c);
	if(!sound)
	{
		out << c << " is not loaded" << std::endl;
		return NULL;
	}
	sounds.push_back(sound);
	return sound;
}
