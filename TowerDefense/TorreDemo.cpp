#include "TorreDemo.h"
#include "GerenteAtor.h"
#include "ProjetilExemplo.h"

#include <c2d2/chien2d2.h>

TorreDemo::TorreDemo(GerenteAtor& _gerente, int _x, int _y)
	:Torre(_gerente, _x, _y, 0, 0)
{
	posX = _x;
	posY = _y;
}



void TorreDemo::aoColidir(Ator* ator){

}

bool TorreDemo::estaNoJogo(){
	return alive;
}

void TorreDemo::inicializar(){
	tSprite = C2D2_CarregaSpriteSet("imgs/torreE.png", 0, 0);
	Torre::inicializar();
	alcance = 200;
	RoF = 60;
	cd = RoF/10;
}

void TorreDemo::atualizar(){
	Ator* alvo = gerente.maisPerto(posX, posY, alcance, INIMIGO);
	switch (estado)
	{
	case RTF:
		if(alvo != nullptr){
			gerente.adicionar(new ProjetilExemplo(gerente, posX, posY, 5, *alvo, 0, 1));
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
	C2D2_DesenhaSpriteCentro(tSprite, 0, posX, posY, largura, altura);
}

void TorreDemo::finalizar(){
	C2D2_RemoveSpriteSet(tSprite);
}

void TorreDemo::upgrade()
{

}
