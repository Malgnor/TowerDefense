#include "Torre2.h"
#include "ProjetilExemplo.h"
#include "GerenteAtor.h"


#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>
#include <c2d2\chienaudio2.h>

Torre2::Torre2(GerenteAtor& _gerente, int _x, int _y)
	: Torre(_gerente, _x, _y, 50, 120)
{
}



void Torre2::aoColidir(Ator* ator){

}

bool Torre2::estaNoJogo(){
	return alive;
}

void Torre2::inicializar(){
	alcance = 100;
	aTiro = CA2_CarregaEfeito("audio/tiro.ogg");
	RoF = 40;
	cd = RoF;
	tSprite = C2D2_CarregaSpriteSet("imgs/torre2.bmp", 32, 32);	
	Torre::inicializar();
}

void Torre2::atualizar(){
	Ator* alvo = gerente.maisPerto(posX, posY, alcance, INIMIGO);
	switch (estado)
	{
	case RTF:
		if(alvo != nullptr){
			gerente.adicionar(new ProjetilExemplo(gerente, posX, posY, 5, *alvo, 10, 1));
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

void Torre2::desenhar(){
	C2D2_DesenhaSpriteCentro(tSprite, ind, posX, posY, largura, altura);
}

void Torre2::finalizar(){
	C2D2_RemoveSpriteSet(tSprite);
	CA2_RemoveEfeito(aTiro);
}

void Torre2::upgrade()
{
	switch (ind)
	{
	case 0:
		alcance = 140;
		RoF = 45;
		ind++;
		valor += custo;
		custo = 150;
		break;
	case 1:
		alcance = 180;
		RoF = 50;
		ind++;
		valor += custo;
		custo = 0;
		break;
	}
}
