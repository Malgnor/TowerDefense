#ifndef _MENUTEXT_H_
#define _MENUTEXT_H_

#include "Menu.h"

class MenuText : public Menu
{
public:
	MenuText(std::string _name, int _x, int _y, int& _fonte, double _r = 1, double _g = 0, double _b = 0);
	MenuText(std::string _name, int _x, int _y, int& _fonte, char* _cor);
	void atualizar();
	void desenhar();
};

#endif

