#include "TorreMulti.h"
#include "Projetil1.h"
#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>
#include <c2d2\chienaudio2.h>

TorreMulti::TorreMulti(GerenteAtor& _gerente, int _x, int _y)
	: Torre(_gerente, _x, _y, 50, 100)
{
}

void TorreMulti::aoColidir(Ator* ator){

}

bool TorreMulti::estaNoJogo(){
	return alive;
}

void TorreMulti::inicializar(){
	alcance = 125;
	aTiro = CA2_CarregaEfeito("audio/tiro.ogg");
	RoF = 90;
	cd = RoF;
	tSprite = C2D2_CarregaSpriteSet("imgs/Torre2.png", 32, 32);	
	Torre::inicializar();
}

void TorreMulti::atualizar(){
	if(!alvos.empty()){
		std::vector<Ator*> vivos;
		for(Ator* ator : alvos){
			if(ator->estaNoJogo())
				vivos.push_back(ator);
		}
		swap(alvos, vivos);
	}
	switch (estado)
	{
	case RTF:
		if(!alvos.empty()){
			for(Ator* ator : alvos)
				if(ator != nullptr)
					gerente.adicionar(new Projetil1(gerente, posX, posY, 5, ator, 15+5*ind, 1));
			CA2_TocaEfeito(aTiro, 0);
			cd = RoF;
			estado = COOLDOWN;
			alvos.clear();
		} else {
			cd = RoF/10;
			estado = COOLDOWN;
		}
		break;
	case COOLDOWN:
		if(alvos.size() < (unsigned)4+2*ind){
			alvo = gerente.maisPerto(posX, posY, alcance, INIMIGO, alvos);
			if(alvo != nullptr)
				alvos.push_back(alvo);
			alvo = nullptr;
		}
		if(--cd <= 0 )
			estado = RTF;
		break;
	}
}

void TorreMulti::desenhar(){
	C2D2_DesenhaSpriteCentro(tSprite, ind, posX, posY, largura, altura);
#ifdef DEBUG
	if(!alvos.empty())
		for(Ator* ator : alvos)
			if(ator != nullptr)
				C2D2P_Linha(posX, posY, ator->x(), ator->y(), 255, 255, 255);
	C2D2P_Linha(posX-largura/2, posY, posX-largura/2+(int)((float)cd/(float)RoF*32.0), posY, 255, 0, 0);
#endif
}

void TorreMulti::finalizar(){
	C2D2_RemoveSpriteSet(tSprite);
}

void TorreMulti::upgrade()
{
	switch (ind)
	{
	case 0:
		alcance = 150;
		RoF = 75;
		ind++;
		valor += custo;
		custo = 150;
		break;
	case 1:
		alcance = 175;
		RoF = 60;
		ind++;
		valor += custo;
		custo = 0;
		break;
	}
}
