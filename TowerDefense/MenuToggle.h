#ifndef _MENUTOGGLE_H_
#define _MENUTOGGLE_H_

#include "Menu.h"

class MenuToggle : public Menu
{
private:
	mToggle estado;

public:
	MenuToggle(std::string _name, int _x, int _y, int& _fonte, mToggle _estado = DESATIVADO);
	mToggle getEstado();
	void atualizar();
	void desenhar();
};

#endif


