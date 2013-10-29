#include "Torre2.h"
#include "ProjetilExemplo.h"
#include "GerenteAtor.h"


#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

Torre2::Torre2(GerenteAtor& _gerente, int _x, int _y, int _ind)
	: Torre(_gerente, _x, _y), ind(_ind)
{
}

int Torre2::x(){
	return posX;
}

int Torre2::y(){
	return posY;
}

int Torre2::l(){
	return 32;
}

int Torre2::a(){
	return 32;
}

int Torre2::sprite(){
	return tSprite;
}

int Torre2::indice(){
	return ind;
}

void Torre2::aoColidir(Ator* ator){

}

bool Torre2::estaNoJogo(){
	return alive;
}

void Torre2::inicializar(){
	alcance = 100;
	RoF = 40;
	cd = RoF;
	tSprite = C2D2_CarregaSpriteSet("imgs/torre2.bmp", 32, 32);	
#ifdef LOG
	if(tSprite == 0)
		addToLog("Falha ao carregar sprite da Torre!(Torre2.cpp)");
#endif
}

void Torre2::atualizar(){
	Ator* alvo = gerente.maisPerto(posX, posY, alcance, INIMIGO);
	switch (estado)
	{
	case RTF:
		if(alvo != nullptr){
			gerente.adicionar(new ProjetilExemplo(gerente, posX, posY, 5, *alvo));
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
	//C2D2_Mouse* mouse = C2D2_PegaMouse();
	//if(C2D2_ColidiuQuadrados(mouse->x, mouse->y, 1, 1, posX-16, posY-16, 32, 32)){
	//	C2D2P_Circulo(posX, posY, alcance, 255, 255, 255);
	//}
	C2D2_DesenhaSprite(tSprite, ind, posX-l()/2, posY-a()/2);
}

void Torre2::finalizar(){
	C2D2_RemoveSpriteSet(tSprite);
}