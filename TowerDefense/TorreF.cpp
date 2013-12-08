#include "TorreF.h"
#include "ProjetilF.h"
#include "GerenteAtor.h"

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>
#include <c2d2\chienaudio2.h>

TorreF::TorreF(GerenteAtor& _gerente, int _x, int _y)
	: Torre(_gerente, _x, _y, 250, 150)
{
}

void TorreF::aoColidir(Ator* ator){

}

bool TorreF::estaNoJogo(){
	return alive;
}

void TorreF::inicializar(){
	alcance = 125;
	aTiro = CA2_CarregaEfeito("audio/tiro.ogg");
	RoF = 30;
	cd = RoF;
	tSprite = C2D2_CarregaSpriteSet("imgs/Torre2.png", 32, 32);	
	Torre::inicializar();
}

void TorreF::atualizar(){
	if(!tiros.empty()){
		std::vector<Ator*> vivos;
		for(Ator* ator : tiros){
			if(ator->estaNoJogo())
				vivos.push_back(ator);
		}
		swap(tiros, vivos);
	}
	switch (estado)
	{
	case RTF:
		if(tiros.size() < (unsigned)3+ind*2){
			tiros.push_back(alvo = new ProjetilF(gerente, posX, posY, 5, 30+ind*15, 1));
			gerente.adicionar(alvo);
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

void TorreF::desenhar(){
	C2D2_DesenhaSpriteCentro(tSprite, ind, posX, posY, largura, altura);
#ifdef DEBUG
	C2D2P_Linha(posX-largura/2, posY, posX-largura/2+(int)((float)cd/(float)RoF*32.0), posY, 255, 0, 0);
#endif
}

void TorreF::finalizar(){
	if(!tiros.empty())
		for(Ator* ator : tiros){
			Projetil* tiro = (Projetil*)ator;
			tiro->hit();
		}			
	C2D2_RemoveSpriteSet(tSprite);
}

void TorreF::upgrade()
{
	switch (ind)
	{
	case 0:
		ind++;
		valor += custo;
		custo = 150;
		break;
	case 1:
		ind++;
		valor += custo;
		custo = 0;
		break;
	}
}
