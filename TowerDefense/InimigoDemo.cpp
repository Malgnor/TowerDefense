#include "InimigoDemo.h"
#include <c2d2\chien2d2.h>

InimigoDemo::InimigoDemo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, iDirecao _dir)
	:Inimigo(_gerente, _map, _x, _y, 1, 1)
{
	dir = _dir;
}


int InimigoDemo::x(){
	return posX;
}

int InimigoDemo::y(){
	return posY;
}

int InimigoDemo::l(){
	return 16;
}

int InimigoDemo::a(){
	return 16;
}

int InimigoDemo::sprite(){
	return iSprite;
}

int InimigoDemo::indice(){
	return 0;
}

void InimigoDemo::aoColidir(Ator* ator){

}

bool InimigoDemo::estaNoJogo(){
	return true;
}

void InimigoDemo::inicializar(){
	iSprite = C2D2_CarregaSpriteSet("imgs/inimE.png", 0, 0);
#ifdef LOG
	if(iSprite == 0)
		addToLog("Falha ao carregar o sprite do inimigo!(InimigoDemo.cpp)");
#endif
}

void InimigoDemo::atualizar(){
	switch (dir)
	{
	case iCIMA:
		posY--;
		if (posY <= 50)
			dir = iESQUERDA;
		break;
	case iBAIXO:
		posY++;
		if (posY >= 550)
			dir = iDIREITA;
		break;
	case iESQUERDA:
		posX--;
		if (posX <= 50)
			dir = iBAIXO;
		break;
	case iDIREITA:
		posX++;
		if (posX >= 750)
			dir = iCIMA;
		break;
	}

}

void InimigoDemo::desenhar(){
	C2D2_DesenhaSpriteCentro(iSprite, 0, posX, posY, l(), a());
}

void InimigoDemo::finalizar(){
	C2D2_RemoveSpriteSet(iSprite);
}