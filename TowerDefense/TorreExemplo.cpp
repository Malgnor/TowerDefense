#include "TorreExemplo.h"
#include "ProjetilSplash.h"
#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

TorreExemplo::TorreExemplo(GerenteAtor& _gerente, int _x, int _y)
	: Torre(_gerente, _x, _y, 0, 0)
{
}



void TorreExemplo::aoColidir(Ator* ator){

}

bool TorreExemplo::estaNoJogo(){
	return alive;
}

void TorreExemplo::inicializar(){
	tSprite = C2D2_CarregaSpriteSet("imgs/torreE.png", 0, 0);
	Torre::inicializar();
	alcance = 200;
	RoF = 60; // 1*segundos(60 frames)
	cd = RoF/10;
#ifdef LOG
	if(tSprite == 0)
		addToLog("Falha ao carregar sprite da Torre!(TorreExemplo.cpp)");
#endif
}

void TorreExemplo::atualizar(){
	Ator* alvo = gerente.maisPerto(posX, posY, alcance, INIMIGO);
	switch (estado)
	{
	case RTF:
		if(alvo != nullptr){
			gerente.adicionar(new ProjetilSplash(gerente, posX, posY, 5, *alvo, 1));
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
	C2D2_DesenhaSpriteCentro(tSprite, 0, posX, posY, l(), a());
}

void TorreExemplo::finalizar(){
	C2D2_RemoveSpriteSet(tSprite);
}

void TorreExemplo::upgrade()
{

}
