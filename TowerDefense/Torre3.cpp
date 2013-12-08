#include "Torre3.h"
#include "Projetil3.h"
#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>
#include <c2d2\chienaudio2.h>

Torre3::Torre3(GerenteAtor& _gerente, int _x, int _y)
	: Torre(_gerente, _x, _y, 100, 160)
{
}

void Torre3::aoColidir(Ator* ator){

}

bool Torre3::estaNoJogo(){
	return alive;
}

void Torre3::inicializar(){
	tDano = 10;
	alcance = 120;
	aTiro = CA2_CarregaEfeito("audio/launcher.ogg");
	RoF = 80;
	cd = RoF;
	tSprite = C2D2_CarregaSpriteSet("imgs/Torre3.png", 32, 32);
	Torre::inicializar();
}

void Torre3::atualizar(){
	alvo = gerente.maisPerto(posX, posY, alcance, INIMIGO);
	switch (estado)
	{
	case RTF:
		if(alvo != nullptr){
			gerente.adicionar(new Projetil3(gerente, posX, posY, 3, alvo, tDano));
			CA2_TocaEfeito(aTiro, 0);
			cd = RoF;
			estado = COOLDOWN;
		} else {
			cd = RoF/10;
			estado = COOLDOWN;
		}
		break;
	case COOLDOWN:
		if(--cd <= 0 )
			estado = RTF;
		break;
	}
}

void Torre3::desenhar(){
	C2D2_DesenhaSpriteCentro(tSprite, ind, posX, posY, largura, altura);
#ifdef DEBUG
	if(alvo != nullptr)
		C2D2P_Linha(posX, posY, alvo->x(), alvo->y(), 255, 255, 255);
	C2D2P_Linha(posX-largura/2, posY, posX-largura/2+(int)((float)cd/(float)RoF*32.0), posY, 255, 0, 0);
#endif
}

void Torre3::finalizar(){
	C2D2_RemoveSpriteSet(tSprite);
}

void Torre3::upgrade()
{
	switch (ind)
	{
	case 0:
		tDano = 15;
		alcance = 150;
		RoF = 70;
		ind++;
		valor += custo;
		custo = 150;
		break;
	case 1:
		tDano = 20;
		alcance = 170;
		RoF = 60;
		ind++;
		valor += custo;
		custo = 0;
		break;
	}
}
