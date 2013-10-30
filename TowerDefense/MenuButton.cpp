#include "MenuButton.h"

#include "globalDef.h"

#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>

MenuButton::MenuButton(std::string _name, int _x, int _y, int& _fonte, double _r, double _g, double _b, unsigned char _alfa)
	: Menu(_name, _x, _y, _fonte, _r, _g, _b, _alfa), estado(NAOPRESSIONADO)
{
}

MenuButton::MenuButton(std::string _name, int _x, int _y, int& _fonte, char* _cor, unsigned char _alfa)
	: Menu(_name, _x, _y, _fonte, _cor, _alfa), estado(NAOPRESSIONADO)
{
}

mButton MenuButton::getEstado()
{
	return estado;
}

void MenuButton::atualizar()
{
	C2D2_Mouse* m = C2D2_PegaMouse();
	if(C2D2_ColidiuQuadrados((int)(posX-l/2-3), posY, (int)((posX+l/2+3)-(posX-l/2-3)), a, m->x, m->y, 1, 1)){
		switch (estado)
		{
		case NAOPRESSIONADO:
			if(m->botoes[C2D2_MESQUERDO].pressionado)
				estado = PRESSIONADO;
			break;
		case PRESSIONADO:
			if(!m->botoes[C2D2_MESQUERDO].ativo)
				estado = SOLTO;
			break;
		case SOLTO:
			estado = NAOPRESSIONADO;
			break;
		}
	} else
		estado = NAOPRESSIONADO;
}

void MenuButton::desenhar()
{
	switch (estado)
	{
	case NAOPRESSIONADO:
		C2D2P_RetanguloPintadoAlfa((int)(posX-l/2-3), posY, (int)(posX+l/2+3), posY+a, (unsigned char)(r*127), (unsigned char)(g*127), (unsigned char)(b*127), alfa);
		C2D2P_Retangulo((int)(posX-l/2-3), posY, (int)(posX+l/2+3), posY+a, (unsigned char)(r*255), (unsigned char)(g*255), (unsigned char)(b*255));
		break;
	case PRESSIONADO:
		C2D2P_RetanguloPintadoAlfa((int)(posX-l/2-3), posY, (int)(posX+l/2+3), posY+a, 0, 127, 0, alfa);
		C2D2P_Retangulo((int)(posX-l/2-3), posY, (int)(posX+l/2+3), posY+a, 0, 255, 0);
		break;
	case SOLTO:
		C2D2P_RetanguloPintadoAlfa((int)(posX-l/2-3), posY, (int)(posX+l/2+3), posY+a, 0, 127, 127, alfa);
		C2D2P_Retangulo((int)(posX-l/2-3), posY, (int)(posX+l/2+3), posY+a, 0, 255, 255);
		break;
	}
	C2D2_DesenhaTexto(fonte, posX, posY, name.c_str(), C2D2_TEXTO_CENTRALIZADO);
}
