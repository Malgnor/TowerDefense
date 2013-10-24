#include "GameLoop.h"
#include "TowerDefense.h"

int main(int argc, char* argv[])
{
	GameLoop gameLoop(new TowerDefense());
	gameLoop.executar("Tower Defense", 800, 600, true);
	return 0;
}