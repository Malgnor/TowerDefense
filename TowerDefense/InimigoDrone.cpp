#include "InimigoDrone.h"

#include "Projetil.h"
#include "Coin.h"

#include <c2d2\chien2d2.h>

#include <c2d2\chien2d2primitivas.h>

InimigoDrone::InimigoDrone(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel, int _vida, int _dinheiro, int _sprite, TDBase* _td)
	: Inimigo(_gerente, _map, _x, _y, _vel, _vida, _dinheiro, _td), sprite(_sprite), vidaMax(_vida)
{
}

void InimigoDrone::inicializar(){
	indiceVar = 0;
	danoinimigo = 0;
	mapa.getInit(posX, posY);
	posX += offX;
    posY += offY;
	switch (sprite){
	    case 1:
		    danoinimigo = 1;
			iSprite = C2D2_CarregaSpriteSet("imgs/inimE.png", 0, 0);	
	    	break;
		case 2:
			danoinimigo = 1;
        	iSprite = C2D2_CarregaSpriteSet("imgs/inimE2.png", 0, 0);	
        	break;
		case 3:
			danoinimigo = 1;
        	iSprite = C2D2_CarregaSpriteSet("imgs/inimE3.png", 0, 0);	
        	break;
		case 4:
			danoinimigo = 1;
        	iSprite = C2D2_CarregaSpriteSet("imgs/inimE4.png", 0, 0);	
        	break;
		case 5:
			danoinimigo = 1;
        	iSprite = C2D2_CarregaSpriteSet("imgs/inimE5.png", 0, 0);	
        	break;
		case 6:
			danoinimigo = 20;
        	iSprite = C2D2_CarregaSpriteSet("imgs/inimEBoss.png", 0, 0);	
        break;
    }
	Inimigo::inicializar();
}

void InimigoDrone::atualizar(){
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
		else if((mapa.conteudo(posX, posY + 32) == 3 || mapa.conteudo(posX, posY + 32) == 4) && dir != iCIMA)
			dir = iBAIXO;
		else if((mapa.conteudo(posX, posY - 32) == 3 || mapa.conteudo(posX, posY - 32) == 4) && dir != iBAIXO)
			dir = iCIMA;
		else if (mapa.conteudo(posX, posY) == 4){
		    alive = false;
		    td->DanoRecebido(danoinimigo);
		} else
			passos = -1;
	}	
	if(posX > 576){
		alive = false;
		td->DanoRecebido(danoinimigo);
	}
}
		
void InimigoDrone::desenhar(){
	C2D2_DesenhaSpriteCentro(iSprite, indiceVar, posX, posY, l(), a());
#ifdef DEBUG
	C2D2P_Retangulo(posX-9, posY-altura/2-9, posX+9, posY-altura/2-5, 0, 0, 0);
	C2D2P_RetanguloPintado(posX-8, posY-altura/2-8, posX-8+(int)((float)vida/(float)vidaMax*16.0), posY-altura/2-6, 0, 255, 0);
#endif
}

void InimigoDrone::finalizar(){
	C2D2_RemoveSpriteSet(iSprite);
}
