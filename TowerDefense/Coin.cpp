#include "Coin.h"
#include "globalDef.h"

#include <stdlib.h>
#include <math.h>

#include <c2d2/chien2d2.h>

Coin::Coin(GerenteAtor& _gerente, TDBase* _td, int _valor, int _x, int _y)
	: Ator(_gerente, 2), td(_td), valor(_valor), posX(_x), posY(_y), alive(true), decay(60*15)
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
	int r2 = rand()%8;
	posX += (int)(r2*cos(r));
	posY += (int)(r2*sin(r));
	spriteSet = C2D2_CarregaSpriteSet("imgs/goldcoin.png", 0, 0);
	C2D2_DimensoesSprite(spriteSet, &largura, &altura);
}		

void Coin::atualizar(){
	C2D2_Mouse* mouse = C2D2_PegaMouse();
	if(--decay <= 0)
		alive = false;
	if(C2D2_ColidiuQuadrados(posX-largura/2, posY-altura/2, largura, altura, mouse->x-1, mouse->y-1, 3, 3)){
		td->Lucro(valor);
		alive = false;
		return;
	}
	if(td->magRadius() > 0){
		int mx;
		int my;
		td->posMouse(mx, my);
		int dx = posX-mx;
		int dy = posY-my;
		float d = sqrt((float)dx*dx+dy*dy);
		if(d <= td->magRadius()){
			float xx = (float)dx/d;
			float yy = (float)dy/d;
			posY-=(int)(2*yy);	
			posX-=(int)(2*xx); 
		}
	}	
}

void Coin::desenhar(){
	C2D2_DesenhaSpriteCentro(spriteSet, 0, posX, posY, largura, altura);
}	


void Coin::finalizar(){
	C2D2_RemoveSpriteSet(spriteSet);
}
