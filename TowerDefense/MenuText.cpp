#include "MenuText.h"

#include "globalDef.h"

#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>

MenuText::MenuText(std::string _name, int _x, int _y, int& _fonte)
	:Menu(_name, _x, _y, _fonte)
{
}

void MenuText::atualizar()
{

}

void MenuText::desenhar()
{
	C2D2P_RetanguloPintadoAlfa((int)(posX-l/1.75), posY, (int)(posX+l/1.75), posY+a, 127, 0, 0, 127);
	C2D2P_Retangulo((int)(posX-l/1.75), posY, (int)(posX+l/1.75), posY+a, 255, 0, 0);
	C2D2_DesenhaTexto(fonte, posX, posY, name.c_str(), C2D2_TEXTO_CENTRALIZADO);
}

