#include "Menu.h"
#include "globalDef.h"

#include "color.h"

#include <c2d2/chien2d2.h>

Menu::Menu( std::string _name, int _x, int _y, int& _fonte, double _r , double _g, double _b, unsigned char _alfa)
	: name(_name), posX(_x), posY(_y), fonte(_fonte), r(_r > 1 ? 1 : _r < 0 ? 0 : _r), g(_g > 1 ? 1 : _g < 0 ? 0 : _g), b(_b > 1 ? 1 : _b < 0 ? 0 : _b), alfa(_alfa)
{
	C2D2_DimensoesTexto(fonte, name.c_str(), &l, &a);

}Menu::Menu( std::string _name, int _x, int _y, int& _fonte, char* _cor, unsigned char _alfa)
	: name(_name), posX(_x), posY(_y), fonte(_fonte), r(getCorDoubleR(_cor)), g(getCorDoubleG(_cor)), b(getCorDoubleB(_cor)), alfa(_alfa)
{
	C2D2_DimensoesTexto(fonte, name.c_str(), &l, &a);
}

std::string Menu::getName()
{
	return name;
}
