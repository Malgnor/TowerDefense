#include "Inimigo.h"
#include "GerenteAtor.h"

Inimigo::Inimigo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel, int _vida)
	: Ator(_gerente), mapa(_map), posX(_x), posY(_y), vel(_vel), alive(true), passos(32), dir(iDIREITA), vida(_vida)
{

}

Tipo Inimigo::tipo(){
	return INIMIGO;
}