#include "ControladorVolume.h"
#include <c2d2\chien2d2.h>
#include <c2d2\chienaudio2.h>

using namespace std;

unsigned int ControladorVolume::efeitos = 50;
unsigned int ControladorVolume::musica = 50;
int ControladorVolume::space = 0;

ControladorVolume::ControladorVolume()
	:posX(0), posY(0), indEfeito(0), indMusica(0)
{
}

ControladorVolume::ControladorVolume(int _x, int _y)
	:posX(_x), posY(_y), indEfeito(0), indMusica(0)
{
}

void ControladorVolume::inicializar(){
	sprEfeito = C2D2_CarregaSpriteSet("imgs/volume1.bmp", 96, 32);
	sprMusica = C2D2_CarregaSpriteSet("imgs/volume1.bmp", 96, 32);
	fonte = C2D2_CarregaFonte("imgs/tahoma16.bmp", 16);
}

void ControladorVolume::atualizar(){
	C2D2_Mouse* m = C2D2_PegaMouse();
	indEfeito = 0;
	indMusica = 0;
	if(m->botoes[C2D2_MESQUERDO].ativo){
		if(C2D2_ColidiuQuadrados(posX-48, posY-32, 32, 32, m->x, m->y, 1, 1)){
			efeitos < 1 ? 0 : efeitos--;
			indEfeito = 2;
		}else if(C2D2_ColidiuQuadrados(posX+16, posY-32, 32, 32, m->x, m->y, 1, 1)){
			efeitos > 99 ? 0 : efeitos++;
			indEfeito = 1;
		}
		if(C2D2_ColidiuQuadrados(posX-48, posY, 32, 32, m->x, m->y, 1, 1)){
			musica < 1 ? 0 : musica--;
			indMusica = 2;
		}else if(C2D2_ColidiuQuadrados(posX+16, posY, 32, 32, m->x, m->y, 1, 1)){
			musica > 99 ? 0 : musica++;
			indMusica = 1;
		}
		CA2_AjustaVolume(musica, efeitos);
	} else{
		if(C2D2_ColidiuQuadrados(posX-48, posY-32, 32, 32, m->x, m->y, 1, 1)){
			indEfeito = 4;
		}else if(C2D2_ColidiuQuadrados(posX+16, posY-32, 32, 32, m->x, m->y, 1, 1)){
			indEfeito = 3;
		}
		if(C2D2_ColidiuQuadrados(posX-48, posY, 32, 32, m->x, m->y, 1, 1)){
			indMusica = 4;
		}else if(C2D2_ColidiuQuadrados(posX+16, posY, 32, 32, m->x, m->y, 1, 1)){
			indMusica = 3;
		}
	}
}

void ControladorVolume::desenhar(){
	C2D2_Mouse* m = C2D2_PegaMouse();
	char c[10];
	C2D2_DesenhaSprite(sprEfeito, indEfeito, posX-48, posY-32);
	C2D2_DesenhaSprite(sprMusica, indMusica, posX-48, posY);
	sprintf_s(c, "%d", efeitos);
	C2D2_DesenhaTexto(fonte, posX, posY-24, c, C2D2_TEXTO_CENTRALIZADO);
	sprintf_s(c, "%d", musica);
	C2D2_DesenhaTexto(fonte, posX, posY+8, c, C2D2_TEXTO_CENTRALIZADO);
	if(C2D2_ColidiuQuadrados(posX-48, posY-32, 96, 32, m->x, m->y, 1, 1)){
		C2D2_DesenhaTexto(fonte, m->x, m->y+16, "Efeitos sonoros", C2D2_TEXTO_CENTRALIZADO);
	}else if(C2D2_ColidiuQuadrados(posX-48, posY, 96, 32, m->x, m->y, 1, 1)){
		C2D2_DesenhaTexto(fonte, m->x, m->y+16, "Música", C2D2_TEXTO_CENTRALIZADO);
	}
}

void ControladorVolume::finalizar(){
	C2D2_RemoveSpriteSet(sprEfeito);
	C2D2_RemoveSpriteSet(sprMusica);
	C2D2_RemoveFonte(fonte);
}

void ControladorVolume::tocaMusica(){
	CA2_TocaMusica(space, -1);
}

void ControladorVolume::carregaMusica(){
	space = CA2_CarregaMusica("audio/space.ogg");
}

void ControladorVolume::removeMusica(){
	CA2_PausaMusica();
	CA2_RemoveMusica(space);
}

unsigned int ControladorVolume::volumeEfeitos(){
	return efeitos;
}

unsigned int ControladorVolume::volumeMusica(){
	return musica;
}