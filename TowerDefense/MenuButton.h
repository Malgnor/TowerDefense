#ifndef _MENUBUTTON_H_
#define _MENUBUTTON_H_

#include "Menu.h"

enum mButton { NAOPRESSIONADO, PRESSIONADO, SOLTO};

class MenuButton : public Menu
{
private:
	mButton estado;
public:
	MenuButton();
	MenuButton(std::string _name, int _x, int _y, int& _fonte);
	mButton getEstado();
	void atualizar();
	void desenhar();

};

#endif


