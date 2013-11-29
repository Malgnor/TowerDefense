#include "InimigoExemplo.h"

#include "Projetil.h"
#include "Coin.h"

#include <c2d2\chien2d2.h>

#include <c2d2\chien2d2primitivas.h>

InimigoExemplo::InimigoExemplo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel, int _vida, int _dinheiro, TDBase* _td)
	: Inimigo(_gerente, _map, _x, _y, _vel, _vida, _dinheiro, _td)
{
}

void InimigoExemplo::inicializar(){
	iSprite = C2D2_CarregaSpriteSet("imgs/inimE.png", 0, 0);
	Inimigo::inicializar();
	indiceVar = 0;
	mapa.getInit(posX, posY);
	posX += offX;
    posY += offY;
}

void InimigoExemplo::atualizar(){
	if (vida <= 0){
		alive = false;
		gerente.adicionar(new Coin(gerente, td, dinheiro, posX, posY));
	}

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
		if((mapa.conteudo(posX + 32, posY) == 3 || mapa.conteudo(posX + 32, posY) == 4)  && dir != iESQUERDA)
			dir = iDIREITA;
		else if((mapa.conteudo(posX - 32, posY) == 3|| mapa.conteudo(posX - 32, posY) == 4) && dir != iDIREITA)
			dir = iESQUERDA;
		else if((mapa.conteudo(posX, posY + 32) == 3 || mapa.conteudo(posX, posY + 32) == 4)&& dir != iCIMA)
			dir = iBAIXO;
		else if((mapa.conteudo(posX, posY - 32) == 3 || mapa.conteudo(posX, posY - 32) == 4)&& dir != iBAIXO)
			dir = iCIMA;
		else if (mapa.conteudo(posX, posY) == 4){
		    alive = false;
		    td->DanoRecebido(1);
			passos = 0;
		}
	}	
	if(posX > 576){
		alive = false;
		td->DanoRecebido(1);
	}else if (posX > 544)
		passos = 32;
}
		
void InimigoExemplo::desenhar(){
	C2D2_DesenhaSpriteCentro(iSprite, indiceVar, posX, posY, l(), a());
	//C2D2P_RetanguloPintado(posX-8, posY-8, posX+8, posY+8, 155, 25, 25);
	//C2D2P_Retangulo(posX-8, posY-8, posX+8, posY+8, 50, 0, 0);
}

void InimigoExemplo::finalizar(){
	C2D2_RemoveSpriteSet(iSprite);
}
