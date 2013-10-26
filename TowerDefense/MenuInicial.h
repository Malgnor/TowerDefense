#ifndef _MENUINICIAL_H_
#define _MENUINICIAL_H_

#include "Tela.h"
#include "Menu.h"

#include "MenuButton.h"

#include <vector>

class MenuInicial :	public Tela
{
private:
	int mouseSprite;
	int tahoma16, tahoma32, tahoma64;
	int mouseX, mouseY;
	MenuButton* btnTD;
	MenuButton* btnExit;
	MenuButton* btnME;
	std::vector <Menu*> menus;

public:
	Tela* proximaTela();

	void inicializar();		
	void atualizar();
	void desenhar();
	void finalizar();
};

#endif

