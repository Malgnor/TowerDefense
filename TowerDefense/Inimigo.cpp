#include "Inimigo.h"
#include "GerenteAtor.h"

Inimigo::Inimigo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel, int _vida, int _dinheiro, TDBase *_td)
	: Ator(_gerente, 4), mapa(_map), offX(_x), offY(_y), posX(-500), posY(-500), vel(_vel), alive(true), passos(0), dir(iPARADO), vida(_vida), dinheiro(_dinheiro), td(_td)
{

}

Tipo Inimigo::tipo(){
	return INIMIGO;
}