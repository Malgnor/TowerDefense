#include "ControladorVolume.h"
#include <c2d2\chien2d2.h>
#include <c2d2\chienaudio2.h>

unsigned int ControladorVolume::efeitos = 50;
unsigned int ControladorVolume::musica = 50;

ControladorVolume::ControladorVolume(int _x, int _y)
	:posX(_x), posY(_y), indEfeito(0), indMusica(0)
{
}

void ControladorVolume::inicializar(){
	sprEfeito = C2D2_CarregaSpriteSet("imgs/volume1.bmp", 96, 32);
	sprMusica = C2D2_CarregaSpriteSet("imgs/volume1.bmp", 96, 32);
}

void ControladorVolume::atualizar(){
	C2D2_Mouse* m = C2D2_PegaMouse();
	if(m->botoes[C2D2_MESQUERDO].ativo)
		if(C2D2_ColidiuQuadrados(posX-48, posY-32, 32, 32, m->x, m->y, 1, 1)){
			efeitos < 1 ? 0 : efeitos--;
			indEfeito = 2;
		}else if(C2D2_ColidiuQuadrados(posX+16, posY-32, 32, 32, m->x, m->y, 1, 1)){
			efeitos > 100 ? 0 : efeitos++;
			indEfeito = 1;
		} else
			indEfeito = 0;
		if(C2D2_ColidiuQuadrados(posX-48, posY, 32, 32, m->x, m->y, 1, 1)){
			musica < 1 ? 0 : musica--;
			indMusica = 2;
		}else if(C2D2_ColidiuQuadrados(posX+16, posY, 32, 32, m->x, m->y, 1, 1)){
			musica > 100 ? 0 : musica++;
			indMusica = 1;
		} else
			indMusica = 0;
		CA2_AjustaVolume(musica, efeitos);
}

void ControladorVolume::desenhar(){

}

void ControladorVolume::finalizar(){
	C2D2_RemoveSpriteSet(sprEfeito);
	C2D2_RemoveSpriteSet(sprMusica);
}

unsigned int ControladorVolume::volumeEfeitos(){
	return efeitos;
}

unsigned int ControladorVolume::volumeMusica(){
	return musica;
}