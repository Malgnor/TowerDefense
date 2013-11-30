#ifndef _MAPEDITOR_H_
#define _MAPEDITOR_H_

#include "Tela.h"
#include "Mapa.h"

#include <vector>

#include "Menu.h"
#include "MenuButton.h"

class MapEditor : public Tela
{
private:
	int mapSprite, mouseSprite;
	int mouseX, mouseY;
	int tile, id;
	int tahoma16, tahoma32, tahoma16r;
	int qtdTiles;
	Mapa mapaTD;
	MenuButton* btnExit;
	MenuButton* btnBack;
	MenuButton* btnTD;
	std::vector <Menu*> menus;

public:
	Tela* proximaTela();

	void inicializar();		
	void atualizar();
	void desenhar();
	void finalizar();
};

#endif _MAPEDITOR_H_
