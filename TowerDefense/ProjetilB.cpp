#include "ProjetilB.h"

#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>

#include <math.h>

using namespace std;

ProjetilB::ProjetilB(GerenteAtor& _gerente, int _x, int _y, int _dano)
	: Projetil(_gerente, _x, _y, 1, nullptr, _dano, 1), decay(16)
{
}

int ProjetilB::indice(){
	return 0;
}

void ProjetilB::aoColidir(Ator* ator){
}

void ProjetilB::hit(){
}

void ProjetilB::inicializar(){
	pSprite = C2D2_CarregaSpriteSet("imgs/projAOE.png" , 0, 0);
	Projetil::inicializar();
}
		
void ProjetilB::atualizar(){
	if(--decay <= 0)
		alive = false;
}
		
void ProjetilB::desenhar(){
	C2D2_DesenhaSpriteCentro(pSprite, 0, posX, posY, l(), a());
}

void ProjetilB::finalizar(){
	C2D2_RemoveSpriteSet(pSprite);
}
