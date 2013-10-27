#include "globalDef.h"
#include "GameLoop.h"
#include "MenuInicial.h"

int main(int argc, char* argv[])
{
	GameLoop gameLoop(new MenuInicial());
	gameLoop.executar("Tower Defense", 800, 600, true);
	return 0;
}