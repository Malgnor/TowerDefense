#include "ProjetilExemplo.h"

#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>

#include <math.h>

using namespace std;

ProjetilExemplo::ProjetilExemplo(GerenteAtor& _gerente, int _x, int _y, int _vel, Ator& _alvo)
	: Projetil(_gerente, _x, _y, _vel, _alvo)
{
}

int ProjetilExemplo::x(){
	return posX;
}

int ProjetilExemplo::y(){
	return posY;
}

int ProjetilExemplo::l(){
	return 16;
}

int ProjetilExemplo::a(){
	return 16;
}


int ProjetilExemplo::sprite(){
	return pSprite;
}

int ProjetilExemplo::indice(){
	return 0;
}

void ProjetilExemplo::aoColidir(Ator* ator){
	if(ator->tipo() == INIMIGO)
		alive = false;
}

bool ProjetilExemplo::estaNoJogo(){
	return alive;
}


void ProjetilExemplo::inicializar(){
	pSprite = C2D2_CarregaSpriteSet("imgs/projE.png" , 0, 0);
}
		
void ProjetilExemplo::atualizar(){
	int dx = posX-alvo.x();
	int dy = posY-alvo.y();
	float d = sqrt(dx*dx+dy*dy);
	float xx = (float)dx/d;
	float yy = (float)dy/d;
	posY-=vel*yy;	
	posX-=vel*xx;
}
		
void ProjetilExemplo::desenhar(){
	C2D2_DesenhaSpriteCentro(pSprite, 0, posX, posY, l(), a());
}
void ProjetilExemplo::finalizar(){
	C2D2_RemoveSpriteSet(pSprite);
}