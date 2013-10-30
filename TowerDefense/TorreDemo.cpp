#include "TorreDemo.h"
#include "GerenteAtor.h"
#include "ProjetilExemplo.h"

#include <c2d2/chien2d2.h>

TorreDemo::TorreDemo(GerenteAtor& _gerente, int _x, int _y)
	:Torre(_gerente, _x, _y)
{
	posX = _x;
	posY = _y;
}

int TorreDemo::x(){
	return posX;
}

int TorreDemo::y(){
	return posY;
}

int TorreDemo::l(){
	return 32;
}

int TorreDemo::a(){
	return 32;
}

int TorreDemo::sprite(){
	return tSprite;
}

int TorreDemo::indice(){
	return 0;
}

void TorreDemo::aoColidir(Ator* ator){

}

bool TorreDemo::estaNoJogo(){
	return alive;
}

void TorreDemo::inicializar(){
	tSprite = C2D2_CarregaSpriteSet("imgs/torreE.png", 0, 0);
	alcance = 200;
	RoF = 60;
	cd = RoF/10;
#ifdef LOG
	if(tSprite == 0)
		addToLog("Falha ao carregar sprite da Torre!(TorreDemo.cpp)");
#endif
}

void TorreDemo::atualizar(){
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

void TorreDemo::desenhar(){	
	C2D2_DesenhaSpriteCentro(tSprite, 0, posX, posY, l(), a());
}

void TorreDemo::finalizar(){
	C2D2_RemoveSpriteSet(tSprite);
}
