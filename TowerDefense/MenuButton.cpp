#include "MenuButton.h"

#include "globalDef.h"

#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>

MenuButton::MenuButton(std::string _name, int _x, int _y, int& _fonte)
	: Menu(_name, _x, _y, _fonte), estado(NAOPRESSIONADO)
{
}

mButton MenuButton::getEstado()
{
	return estado;
}

void MenuButton::atualizar()
{
	C2D2_Mouse* m = C2D2_PegaMouse();
	if(C2D2_ColidiuQuadrados((int)(posX-l/1.75), posY, (int)((posX+l/1.75)-(posX-l/1.75)), a, m->x, m->y, 1, 1)){
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
		C2D2P_RetanguloPintadoAlfa((int)(posX-l/1.75), posY, (int)(posX+l/1.75), posY+a, 127, 0, 0, 127);
		C2D2P_Retangulo((int)(posX-l/1.75), posY, (int)(posX+l/1.75), posY+a, 255, 0, 0);
		break;
	case PRESSIONADO:
		C2D2P_RetanguloPintadoAlfa((int)(posX-l/1.75), posY, (int)(posX+l/1.75), posY+a, 0, 127, 0, 127);
		C2D2P_Retangulo((int)(posX-l/1.75), posY, (int)(posX+l/1.75), posY+a, 0, 127, 0);
		break;
	case SOLTO:
		C2D2P_RetanguloPintadoAlfa((int)(posX-l/1.75), posY, (int)(posX+l/1.75), posY+a, 0, 127, 127, 127);
		C2D2P_Retangulo((int)(posX-l/1.75), posY, (int)(posX+l/1.75), posY+a, 0, 255, 255);
		break;
	}
	C2D2_DesenhaTexto(fonte, posX, posY, name.c_str(), C2D2_TEXTO_CENTRALIZADO);
}
