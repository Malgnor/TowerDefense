#include "ProjetilAOE.h"

#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>

#include <math.h>

using namespace std;

ProjetilAOE::ProjetilAOE(GerenteAtor& _gerente, int _x, int _y, int _dano)
	: Projetil(_gerente, _x, _y, 1, nullptr, _dano, 1), decay(16)
{
}

int ProjetilAOE::indice(){
	return 0;
}

void ProjetilAOE::aoColidir(Ator* ator){
}

void ProjetilAOE::hit(){
}

void ProjetilAOE::inicializar(){
	pSprite = C2D2_CarregaSpriteSet("imgs/projAOE.png" , 0, 0);
	Projetil::inicializar();
}
		
void ProjetilAOE::atualizar(){
	if(--decay <= 0)
		alive = false;
}
		
void ProjetilAOE::desenhar(){
	C2D2_DesenhaSpriteCentro(pSprite, 0, posX, posY, l(), a());
}

void ProjetilAOE::finalizar(){
	C2D2_RemoveSpriteSet(pSprite);
}
