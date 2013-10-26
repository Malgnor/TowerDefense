#ifndef _MENU_H_
#define _MENU_H_

#include <string>
class Menu
{
protected:
	std::string name;
	int& fonte;
	int posX;
	int posY;
	int l;
	int a;

public:
	Menu(std::string _name, int _x, int _y, int& _fonte);
	virtual void atualizar() = 0;
	virtual void desenhar() = 0;
	virtual ~Menu(){};
};

#endif


