#include "ProjetilExemplo.h"

#include "GerenteAtor.h"

#include <c2d2\chien2d2primitivas.h>
#include <c2d2\chien2d2.h>

#include <iostream>
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

int ProjetilExemplo::sprite(){
	return 0;
}

int ProjetilExemplo::indice(){
	return 0;
}

bool ProjetilExemplo::primitiva(){
	return true;
}


void ProjetilExemplo::aoColidir(Ator* ator){

}


bool ProjetilExemplo::estaNoJogo(){
	return alive;
}


void ProjetilExemplo::inicializar(){
}
		
void ProjetilExemplo::atualizar(){
	int size = 4;
	if( ((posX >= alvo.x()-size && posY >= alvo.y()-size && posX <= alvo.x()+size && posY <= alvo.y()+size) || (!alvo.estaNoJogo())) ){
		alive = false;
		return;
	}
	int dx = posX-alvo.x();
	int dy = posY-alvo.y();
	float d = sqrt(dx*dx+dy*dy);
	float xx = (float)dx/d;
	float yy = (float)dy/d;
	posY-=vel*yy;	
	posX-=vel*xx;
}
		
void ProjetilExemplo::desenhar(){
	C2D2P_RetanguloPintado(posX-3, posY-3, posX+3, posY+3, 0, 0, 255);
}
void ProjetilExemplo::finalizar(){

}