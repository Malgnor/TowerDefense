#include "Projetil.h"
#include "GerenteAtor.h"

Projetil::Projetil(GerenteAtor& _gerente, int _x, int _y, int _vel, Ator& _alvo, int _dano)
	: Ator(_gerente), posX(_x), posY(_y), vel(_vel), alive(true), alvo(_alvo), dano(_dano)
{

}

int Projetil::retornaDano(){
	return dano;
}

Tipo Projetil::tipo(){
	return PROJETIL;
}