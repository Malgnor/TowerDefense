#include "Menu.h"
#include "globalDef.h"

#include <c2d2/chien2d2.h>

Menu::Menu( std::string _name, int _x, int _y, int& _fonte)
	: name(_name), posX(_x), posY(_y), fonte(_fonte)
{
	C2D2_DimensoesTexto(fonte, name.c_str(), &l, &a);
}
