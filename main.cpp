#include "game.h"


#ifdef main
#undef main
#endif

int main(int argc,char** argv)
{
	game g;
	g.start();
	return 0;
}
