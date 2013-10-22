#include "InimigoExemplo.h"

#include <c2d2\chien2d2.h>

InimigoExemplo::InimigoExemplo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel)
	: Inimigo(_gerente, _map, _x, _y, _vel)
{
}

int InimigoExemplo::x(){
	return posX;
}

int InimigoExemplo::y(){
	return posY;
}

int InimigoExemplo::l(){
	return 30;
}

int InimigoExemplo::a(){
	return 30;
}

int InimigoExemplo::sprite(){
	return iSprite;
}

int InimigoExemplo::indice(){
	return 0;
}

void InimigoExemplo::aoColidir(Ator* ator){

}

bool InimigoExemplo::estaNoJogo(){
	return alive;
}

void InimigoExemplo::inicializar(){
	iSprite = C2D2_CarregaSpriteSet("imgs/inimE.png", 0, 0);
}
		
void InimigoExemplo::atualizar(){
	if(--passos >= 0){
		switch (dir)
		{
		case iCIMA:
			posY--;
			break;
		case iBAIXO:
			posY++;
			break;
		case iESQUERDA:
			posX--;
			break;
		case iDIREITA:
			posX++;
			break;
		}
	} else {
		passos = 32;
		if(mapa.conteudo(posX + 32, posY) == 5 && dir != iESQUERDA)
			dir = iDIREITA;
		else if(mapa.conteudo(posX - 32, posY) == 5 && dir != iDIREITA)
			dir = iESQUERDA;
		else if(mapa.conteudo(posX, posY + 32) == 5 && dir != iCIMA)
			dir = iBAIXO;
		else if(mapa.conteudo(posX, posY - 32) == 5 && dir != iBAIXO)
			dir = iCIMA;
		else
			passos = 0;
	}	
	if(posX > 576)
		alive = false;
	else if (posX > 544)
		passos = 32;
}
		
void InimigoExemplo::desenhar(){
	C2D2_DesenhaSpriteCentro(iSprite, 0, posX, posY, l(), a());
}

void InimigoExemplo::finalizar(){
	C2D2_RemoveSpriteSet(iSprite);
}
