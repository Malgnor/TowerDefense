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
	return posX-16;
}

int Torre2::y(){
	return posY-16;
}

int Torre2::sprite(){
	return image;
}

int Torre2::indice(){
	return ind;
}

bool Torre2::primitiva(){
	return false;
}

void Torre2::aoColidir(Ator* ator){

}

bool Torre2::estaNoJogo(){
	return alive;
}

void Torre2::inicializar(){
	alcance = 100;
	RoF = 40; // 1*segundos(60 frames)
	cd = RoF;
	image = C2D2_CarregaSpriteSet("imgs/torre2.bmp", 32, 32);
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
	/*C2D2_Mouse* mouse = C2D2_PegaMouse();
	if(C2D2_ColidiuQuadrados(mouse->x, mouse->y, 1, 1, posX-16, posY-16, 32, 32)){
		C2D2P_Circulo(posX, posY, alcance, 255, 255, 255);
	}
	C2D2P_RetanguloPintado(posX-16, posY-16, posX+16, posY+16, 127, 127, 127);
	C2D2_DesenhaSprite(image, 0, posX-16, posY-16);
	C2D2P_Retangulo(posX-16, posY-16, posX+16, posY+16, 0, 255, 0);*/
}

void Torre2::finalizar(){
	C2D2_RemoveSpriteSet(image);
}