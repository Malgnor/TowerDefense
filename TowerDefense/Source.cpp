#include "globalDef.h"
#include "GameLoop.h"
#include "MenuInicial.h"

#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
	srand((unsigned)time(0));
	GameLoop gameLoop(new MenuInicial());
	gameLoop.executar("Drone Attack", 800, 600, true);
	return 0;
}
