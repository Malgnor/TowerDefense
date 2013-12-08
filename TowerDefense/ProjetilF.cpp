#include "ProjetilF.h"

#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

#include <math.h>

using namespace std;

ProjetilF::ProjetilF(GerenteAtor& _gerente, int _x, int _y, int _vel, int _dano, int _hp)
	: Projetil(_gerente, _x, _y, _vel, nullptr, _dano, _hp)
{
}

int ProjetilF::indice(){
	return 0;
}

void ProjetilF::aoColidir(Ator* ator){
}

void ProjetilF::hit(){
	if(--hp <= 0)
		alive = false;
}

void ProjetilF::inicializar(){
	pSprite = C2D2_CarregaSpriteSet("imgs/projE.png" , 0, 0);
	int r = rand()%360;
	int r2 = rand()%17;
	posX+= cos(r)*r2;
	posY+= sin(r)*r2;
	Projetil::inicializar();
}
		
void ProjetilF::atualizar(){
	if(alvo == nullptr){
		alvo = gerente.maisPerto(posX, posY, 125, INIMIGO);
	} else if(!alvo->estaNoJogo()){
		alive = false;
		return;
	} else {
		int dx = posX-alvo->x();
		int dy = posY-alvo->y();
		float d = sqrt((float)dx*dx+dy*dy);
		float xx = (float)dx/d;
		float yy = (float)dy/d;
		posY-=(int)(vel*yy);	
		posX-=(int)(vel*xx);
	}
}
		
void ProjetilF::desenhar(){
		C2D2_DesenhaSpriteCentro(pSprite, 0, posX, posY, l(), a());
#ifdef DEBUG	
	if(alvo != nullptr)
		C2D2P_Linha(posX, posY, alvo->x(), alvo->y(), 0, 255, 0);
#endif
}

void ProjetilF::finalizar(){
	C2D2_RemoveSpriteSet(pSprite);
}
