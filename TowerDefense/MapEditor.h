#ifndef _MAPEDITOR_H_
#define _MAPEDITOR_H_

#include "Tela.h"
#include "Mapa.h"

class MapEditor : public Tela
{
private:
	int mapSprite, mouseSprite;
	int mouseX, mouseY;
	int tile, id;
	int tahoma16, tahoma32;
	Mapa mapaTD;

public:
	Tela* proximaTela();

	void inicializar();		
	void atualizar();
	void desenhar();
	void finalizar();
};

#endif _MAPEDITOR_H_
