#include "TorreExemplo.h"
#include "ProjetilExemplo.h"
#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

TorreExemplo::TorreExemplo(GerenteAtor& _gerente, int _x, int _y)
	: Torre(_gerente, _x, _y)
{
}

int TorreExemplo::x(){
	return posX;
}

int TorreExemplo::y(){
	return posY;
}

int TorreExemplo::l(){
	return 32;
}

int TorreExemplo::a(){
	return 32;
}

int TorreExemplo::sprite(){
	return tSprite;
}

int TorreExemplo::indice(){
	return 0;
}

void TorreExemplo::aoColidir(Ator* ator){

}

bool TorreExemplo::estaNoJogo(){
	return alive;
}

void TorreExemplo::inicializar(){
	tSprite = C2D2_CarregaSpriteSet("imgs/torreE.png", 0, 0);
	alcance = 200;
	RoF = 60; // 1*segundos(60 frames)
	cd = RoF/10;
}

void TorreExemplo::atualizar(){
	Ator* alvo = gerente.maisPerto(posX, posY, alcance, INIMIGO);
	switch (estado)
	{
	case RTF:
		if(alvo != nullptr){
			gerente.adicionar(new ProjetilExemplo(gerente, posX, posY, 5, *alvo));
			cd = RoF;
			estado = COOLDOWN;
		} else {
			cd = RoF/10;
		}
	break;
	case COOLDOWN:
		if(--cd <= 0 )
			estado = RTF;
		break;
	}
}

void TorreExemplo::desenhar(){	
	C2D2_Mouse* mouse = C2D2_PegaMouse();
	if(C2D2_ColidiuQuadrados(mouse->x, mouse->y, 1, 1, posX-16, posY-16, 32, 32)){
		C2D2P_Circulo(posX, posY, alcance, 255, 255, 255);
	}
	C2D2_DesenhaSpriteCentro(tSprite, 0, posX, posY, l(), a());
}

void TorreExemplo::finalizar(){
	C2D2_RemoveSpriteSet(tSprite);
}
