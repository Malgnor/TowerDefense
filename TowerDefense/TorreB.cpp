#include "TorreB.h"
#include "ProjetilB.h"
#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>
#include <c2d2\chienaudio2.h>

#include <iostream>

TorreB::TorreB(GerenteAtor& _gerente, int _x, int _y)
	: Torre(_gerente, _x, _y, 150, 150)
{
}

void TorreB::aoColidir(Ator* ator){

}

bool TorreB::estaNoJogo(){
	return alive;
}

void TorreB::inicializar(){
	aTiro = CA2_CarregaEfeito("audio/tiro.ogg");
	alcance = 70;
	RoF = 60;
	cd = RoF;
	tSprite = C2D2_CarregaSpriteSet("imgs/TorreB.png", 32, 32);	
	Torre::inicializar();
}

void TorreB::atualizar(){
	alvo = gerente.maisPerto(posX, posY, alcance, INIMIGO);
	switch (estado)
	{
	case RTF:
		if(alvo != nullptr){
			//for(int r = 0; r <= 359; r+=15){
			//	gerente.adicionar(new ProjetilB(gerente, posX, posY, 10, 25*(ind+1), 1, cos(r), sin(r)));
			//}
			gerente.adicionar(new ProjetilB(gerente, posX, posY, 10*(ind+1)));
			CA2_TocaEfeito(aTiro, 0);
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

void TorreB::desenhar(){
	C2D2_DesenhaSpriteCentro(tSprite, ind, posX, posY, largura, altura);
#ifdef DEBUG
	if(alvo != nullptr)
		C2D2P_Linha(posX, posY, alvo->x(), alvo->y(), 255, 255, 255);
	C2D2P_Linha(posX-largura/2, posY, posX-largura/2+(int)((float)cd/(float)RoF*32.0), posY, 255, 0, 0);
#endif
}

void TorreB::finalizar(){
	C2D2_RemoveSpriteSet(tSprite);
}

void TorreB::upgrade()
{
	switch (ind)
	{
	case 0:
		RoF = 60;
		ind++;
		valor += custo;
		custo = 150;
		break;
	case 1:
		RoF = 60;
		ind++;
		valor += custo;
		custo = 0;
		break;
	}
}
