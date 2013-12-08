#include "TorreDemo.h"
#include "GerenteAtor.h"
#include "Projetil1.h"
#include <stdlib.h>

#include <c2d2/chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

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
	ind = rand()%3;
	switch (rand()%3)
	{
	case 0:		
		tSprite = C2D2_CarregaSpriteSet("imgs/torreB.png", 32, 32);
		break;
	case 1:		
		tSprite = C2D2_CarregaSpriteSet("imgs/torre2.png", 32, 32);
		break;
	case 2:		
		tSprite = C2D2_CarregaSpriteSet("imgs/torre3.png", 32, 32);
		break;
	default:
		tSprite = C2D2_CarregaSpriteSet("imgs/torre2.png", 32, 32);
		break;
	}
	Torre::inicializar();
	alcance = 200;
	RoF = 60;
	cd = RoF/10;
}

void TorreDemo::atualizar(){
	alvo = gerente.maisPerto(posX, posY, alcance, INIMIGO);
	switch (estado)
	{
	case RTF:
		if(alvo != nullptr){
			gerente.adicionar(new Projetil1(gerente, posX, posY, 5, alvo, 0, 1));
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
	C2D2_DesenhaSpriteCentro(tSprite, ind, posX, posY, largura, altura);
#ifdef DEBUG
	if(alvo != nullptr)
		C2D2P_Linha(posX, posY, alvo->x(), alvo->y(), 255, 255, 255);
	C2D2P_Linha(posX-largura/2, posY, posX-largura/2+(int)((float)cd/(float)RoF*32.0), posY, 255, 0, 0);
#endif
}

void TorreDemo::finalizar(){
	C2D2_RemoveSpriteSet(tSprite);
}

void TorreDemo::upgrade()
{

}
