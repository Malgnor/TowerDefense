#ifndef _MENUTEXT_H_
#define _MENUTEXT_H_

#include "Menu.h"

class MenuText : public Menu
{
public:
	MenuText(std::string _name, int _x, int _y, int& _fonte);
	void atualizar();
	void desenhar();
};

#endif

