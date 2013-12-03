#include "Projetil1.h"

#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>

#include <math.h>

using namespace std;

Projetil1::Projetil1(GerenteAtor& _gerente, int _x, int _y, int _vel, Ator* _alvo, int _dano, int _hp)
	: Projetil(_gerente, _x, _y, _vel, _alvo, _dano, _hp)
{
}

int Projetil1::indice(){
	return 0;
}

void Projetil1::aoColidir(Ator* ator){
}

void Projetil1::hit(){
	if(--hp <= 0)
		alive = false;
}

void Projetil1::inicializar(){
	pSprite = C2D2_CarregaSpriteSet("imgs/projE.png" , 0, 0);
	Projetil::inicializar();
}
		
void Projetil1::atualizar(){
	if(!alvo->estaNoJogo()){
		alvo = gerente.maisPerto(posX, posY, 100, INIMIGO);
		if(alvo == nullptr){
			alive = false;
			return;
		}
	}
	int dx = posX-alvo->x();
	int dy = posY-alvo->y();
	float d = sqrt((float)dx*dx+dy*dy);
	float xx = (float)dx/d;
	float yy = (float)dy/d;
	posY-=(int)(vel*yy);	
	posX-=(int)(vel*xx);
}
		
void Projetil1::desenhar(){
	C2D2_DesenhaSpriteCentro(pSprite, 0, posX, posY, l(), a());
}

void Projetil1::finalizar(){
	C2D2_RemoveSpriteSet(pSprite);
}
