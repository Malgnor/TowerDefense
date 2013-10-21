#include "Inimigo.h"
#include "GerenteAtor.h"

Inimigo::Inimigo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel)
	: Ator(_gerente), map(_map), posX(_x), posY(_y), vel(_vel), alive(true), passos(32), dir(iDIREITA)
{

}

Tipo Inimigo::tipo(){
	return INIMIGO;
}