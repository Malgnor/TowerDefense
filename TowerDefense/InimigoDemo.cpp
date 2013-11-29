#include "InimigoDemo.h"
#include "Projetil.h"
#include <c2d2\chien2d2.h>

InimigoDemo::InimigoDemo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, iDirecao _dir, TDBase *_td)
	:Inimigo(_gerente, _map, _x, _y, 1, 1, 1, _td)
{
	dir = _dir;
}

void InimigoDemo::inicializar(){
	iSprite = C2D2_CarregaSpriteSet("imgs/inimE.png", 0, 0);
	indiceVar = 0;
	Inimigo::inicializar();
	posX = offX;
	posY = offY;
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
