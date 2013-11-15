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
	double r, g, b;
	unsigned char alfa;

public:
	Menu(std::string _name, int _x, int _y, int& _fonte, double _r = 1, double _g = 0, double _b = 0, unsigned char _alfa = 255);
	Menu(std::string _name, int _x, int _y, int& _fonte, char* _cor, unsigned char _alfa = 255);
	std::string getName();
	int altura();
	int largura();
	virtual void atualizar() = 0;
	virtual void desenhar() = 0;
	virtual ~Menu(){};
};

#endif


