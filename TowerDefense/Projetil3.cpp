#include "Projetil3.h"
#include "GerenteAtor.h"
#include <c2d2\chien2d2.h>
#include <c2d2\chienaudio2.h>
#include <c2d2\chien2d2primitivas.h>
#include <math.h>

using namespace std;

Projetil3::Projetil3(GerenteAtor& _gerente, int _x, int _y, int _vel, Ator* _alvo, int _dano)
	: Projetil(_gerente, _x, _y, _vel, _alvo, 0), danoS(_dano), decay(15)
{
}

int Projetil3::indice(){
	return 0;
}

void Projetil3::aoColidir(Ator* ator){
	if(ator->tipo() == INIMIGO)
		if(dano == 0){
			dano = danoS;
			C2D2_RemoveSpriteSet(pSprite);
			pSprite = C2D2_CarregaSpriteSet("imgs/explo.png" , 0, 0);
			CA2_TocaEfeito(explo, 0);
			Projetil::inicializar();
		}	
}

void Projetil3::hit(){

}

void Projetil3::inicializar(){
	explo = CA2_CarregaEfeito("audio/bang.ogg");
	pSprite = C2D2_CarregaSpriteSet("imgs/gran.png" , 0, 0);
	Projetil::inicializar();
}

void Projetil3::atualizar(){
	if(!alvo->estaNoJogo()){
		alvo = gerente.maisPerto(posX, posY, 100, INIMIGO);
		if(alvo == nullptr){
			alive = false;
			return;
		}
	}
	if(dano == 0){
		int dx = posX-alvo->x();
		int dy = posY-alvo->y();
		float d = sqrt((float)dx*dx+dy*dy);
		float xx = (float)dx/d;
		float yy = (float)dy/d;
		posY-=(int)(vel*yy);	
		posX-=(int)(vel*xx);
	} else if(--decay <= 0)
		alive = false;
}

void Projetil3::desenhar(){
	C2D2_DesenhaSpriteCentro(pSprite, 0, posX, posY, l(), a());
#ifdef DEBUG	
	if(alvo != nullptr)
		C2D2P_Linha(posX, posY, alvo->x(), alvo->y(), 0, 255, 0);
#endif
}

void Projetil3::finalizar(){
	C2D2_RemoveSpriteSet(pSprite);
}
