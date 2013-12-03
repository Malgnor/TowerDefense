#include "Projetil.h"
#include "GerenteAtor.h"

#include <c2d2/chien2d2.h>

Projetil::Projetil(GerenteAtor& _gerente, int _x, int _y, int _vel, Ator* _alvo, int _dano, int _hp)
	: Ator(_gerente, 3), posX(_x), posY(_y), vel(_vel), alive(true), alvo(_alvo), dano(_dano), hp(_hp)
{

}

int Projetil::x(){
	return posX;
}

int Projetil::y(){
	return posY;
}

int Projetil::l(){
	return largura;
}

int Projetil::a(){
	return altura;
}

bool Projetil::estaNoJogo(){
	return alive;
}

void Projetil::inicializar(){
	C2D2_DimensoesSprite(pSprite, &largura, &altura);
}

int Projetil::sprite(){
	return pSprite;
}

int Projetil::retornaDano(){
	return dano;
}

Tipo Projetil::tipo(){
	return PROJETIL;
}