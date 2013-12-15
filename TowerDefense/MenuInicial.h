#ifndef _MENUINICIAL_H_
#define _MENUINICIAL_H_

#include "Tela.h"

#include "Menu.h"
#include "MenuButton.h"
#include "GerenteAtor.h"
#include "ControladorVolume.h"

#include <vector>

class MenuInicial :	public Tela
{
private:
	int mouseSprite;
	int tahoma16, tahoma32, tahoma64;
	int mouseX, mouseY;
	miEstado estado;
	GerenteAtor gAtor;
	MenuButton* btnTD;
	MenuButton* btnExit;
	MenuButton* btnTUTO;
	MenuButton* btnME;
	MenuButton* btnMS;
	std::vector <Menu*> menus;
	std::vector <Menu*> menusMS;
	std::string mapSelected;
	ControladorVolume cVolume;

public:
	Tela* proximaTela();

	void inicializar();		
	void atualizar();
	void desenhar();
	void finalizar();
};

#endif

