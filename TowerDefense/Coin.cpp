#include "Coin.h"
#include "globalDef.h"

#include <stdlib.h>
#include <math.h>

#include <c2d2/chien2d2.h>

Coin::Coin(GerenteAtor& _gerente, TowerDefense* _td, int _valor, int _x, int _y)
	: Ator(_gerente), td(_td), valor(_valor), posX(_x), posY(_y), alive(true), decay(60*15)
{
}

int Coin::x(){
	return posX;
}

int Coin::y(){
	return posY;
}

int Coin::l(){
	return largura;
}

int Coin::a(){
	return altura;
}

int Coin::sprite(){
	return spriteSet;
}

int Coin::indice(){
	return 0;
}

Tipo Coin::tipo(){
	return COIN;
}

void Coin::aoColidir(Ator* ator){

}

bool Coin::estaNoJogo(){
	return alive;
}

void Coin::inicializar(){
	int r = rand()%360;
	int r2 = rand()%17;
	offX = posX+(int)(r2*cos(r));
	offY = posY+(int)(r2*sin(r));
	spriteSet = C2D2_CarregaSpriteSet("imgs/goldcoin.png", 0, 0);
	C2D2_DimensoesSprite(spriteSet, &largura, &altura);
}		

void Coin::atualizar(){
	C2D2_Mouse* mouse = C2D2_PegaMouse();
	if(posX != offX || posY != offY){
		int dx = posX-offX;
		int dy = posY-offY;
		float d = sqrt((float)dx*dx+dy*dy);
		float xx = (float)dx/d;
		float yy = (float)dy/d;
		posY-=(int)(yy*1.5);	
		posX-=(int)(xx*1.5);
	}
	if(--decay <= 0)
		alive = false;
	if(C2D2_ColidiuQuadrados(posX-largura/2, posY-altura/2, largura, altura, mouse->x, mouse->y, 1, 1)){
		td->Lucro(valor);
		alive = false;
	}
}

void Coin::desenhar(){
	C2D2_DesenhaSpriteCentro(spriteSet, 0, posX, posY, largura, altura);
}	


void Coin::finalizar(){
	C2D2_RemoveSpriteSet(spriteSet);
}
