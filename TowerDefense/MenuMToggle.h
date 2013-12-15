#ifndef _MENUMTOGGLE_H_
#define _MENUMTOGGLE_H_

#include "Menu.h"
#include <vector>

class MenuMToggle : public Menu
{
private:
	mToggle estado;
	std::vector<MenuMToggle*>& menus;

public:
	MenuMToggle(std::string _name, int _x, int _y, int& _fonte, std::vector<MenuMToggle*>& _menus, mToggle _estado = DESATIVADO);
	mToggle getEstado();
	void atualizar();
	void desenhar();
};

#endif