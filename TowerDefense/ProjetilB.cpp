#include "ProjetilB.h"

#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>

#include <math.h>

using namespace std;

ProjetilB::ProjetilB(GerenteAtor& _gerente, int _x, int _y, int _vel, int _dano, int _hp, double _dirx, double _diry)
	: Projetil(_gerente, _x, _y, _vel, nullptr, _dano, _hp), decay(11), dirx(_dirx), diry(_diry)
{
}

int ProjetilB::indice(){
	return 0;
}

void ProjetilB::aoColidir(Ator* ator){
}

void ProjetilB::hit(){
	if(--hp <= 0)
		alive = false;
}

void ProjetilB::inicializar(){
	pSprite = C2D2_CarregaSpriteSet("imgs/projB.png" , 0, 0);
	Projetil::inicializar();
}
		
void ProjetilB::atualizar(){
	posY-=(int)(vel*dirx);	
	posX-=(int)(vel*diry);
	if(--decay <= 0)
		alive = false;
}
		
void ProjetilB::desenhar(){
	C2D2_DesenhaSpriteCentro(pSprite, 0, posX, posY, l(), a());
}

void ProjetilB::finalizar(){
	C2D2_RemoveSpriteSet(pSprite);
}
