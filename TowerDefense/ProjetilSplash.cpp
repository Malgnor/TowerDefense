#include "ProjetilSplash.h"

#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>

#include <math.h>

using namespace std;

ProjetilSplash::ProjetilSplash(GerenteAtor& _gerente, int _x, int _y, int _vel, Ator* _alvo, int _dano)
	: Projetil(_gerente, _x, _y, _vel, _alvo, 0), danoS(_dano), decay(15)
{
}

int ProjetilSplash::indice(){
	return 0;
}

void ProjetilSplash::aoColidir(Ator* ator){
	if(ator->tipo() == INIMIGO)
		if(dano == 0){
			dano = danoS;
			C2D2_RemoveSpriteSet(pSprite);
			pSprite = C2D2_CarregaSpriteSet("imgs/projS.png" , 0, 0);
			Projetil::inicializar();
		}	
}

void ProjetilSplash::hit(){

}

void ProjetilSplash::inicializar(){
	pSprite = C2D2_CarregaSpriteSet("imgs/projE.png" , 0, 0);
	Projetil::inicializar();
}
		
void ProjetilSplash::atualizar(){
	if(!alvo->estaNoJogo()){
		alvo = gerente.maisPerto(posX, posY, 100, INIMIGO);
		if(alvo == nullptr){
			alive = false;
			return;
		}
	}
	if(dano == 0){
		int dx = posX-alvo->x();
		int dy = posY-alvo->y();
		float d = sqrt((float)dx*dx+dy*dy);
		float xx = (float)dx/d;
		float yy = (float)dy/d;
		posY-=(int)(vel*yy);	
		posX-=(int)(vel*xx);
	} else if(--decay <= 0)
		alive = false;
}
		
void ProjetilSplash::desenhar(){
	C2D2_DesenhaSpriteCentro(pSprite, 0, posX, posY, l(), a());
}

void ProjetilSplash::finalizar(){
	C2D2_RemoveSpriteSet(pSprite);
}
