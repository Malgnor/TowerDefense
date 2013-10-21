#include "Torre.h"
#include "GerenteAtor.h"

Torre::Torre(GerenteAtor& _gerente, int _x, int _y)
	: Ator(_gerente), posX(16+_x-_x%32), posY(16+_y-_y%32), alive(true), estado(COOLDOWN)
{

}

Tipo Torre::tipo(){
	return TORRE;
}