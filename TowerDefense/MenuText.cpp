#include "MenuText.h"

#include "globalDef.h"

#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>

MenuText::MenuText(std::string _name, int _x, int _y, int& _fonte, double _r , double _g , double _b, unsigned char _alfa)
	:Menu(_name, _x, _y, _fonte, _r, _g, _b, _alfa)
{
}

MenuText::MenuText(std::string _name, int _x, int _y, int& _fonte, char* _cor, unsigned char _alfa)
	:Menu(_name, _x, _y, _fonte, _cor, _alfa)
{
}

void MenuText::atualizar()
{

}

void MenuText::desenhar()
{
	C2D2P_RetanguloPintadoAlfa((int)(posX-l/1.75), posY, (int)(posX+l/1.75), posY+a, (unsigned char)(r*127), (unsigned char)(g*127), (unsigned char)(b*127), alfa);
	C2D2P_Retangulo((int)(posX-l/1.75), posY, (int)(posX+l/1.75), posY+a, (unsigned char)(r*255), (unsigned char)(g*255), (unsigned char)(b*255));
	C2D2_DesenhaTexto(fonte, posX, posY, name.c_str(), C2D2_TEXTO_CENTRALIZADO);
}

