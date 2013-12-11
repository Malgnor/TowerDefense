#include "MenuToggle.h"

#include "globalDef.h"

#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>

MenuToggle::MenuToggle(std::string _name, int _x, int _y, int& _fonte, mToggle _estado)
	: Menu(_name, _x, _y, _fonte), estado(_estado)
{
}

mToggle MenuToggle::getEstado()
{
	return estado;
}

void MenuToggle::atualizar()
{
	C2D2_Mouse* m = C2D2_PegaMouse();
	if (C2D2_ColidiuQuadrados((int)(posX - l / 2 - 3), posY, (int)((posX + l / 2 + 3) - (posX - l / 2 - 3)), a, m->x, m->y, 1, 1) && m->botoes[C2D2_MESQUERDO].pressionado){
		estado = estado == ATIVADO ? DESATIVADO : ATIVADO;
	}
}

void MenuToggle::desenhar()
{
	switch (estado)
	{
	case DESATIVADO:
		C2D2P_RetanguloPintadoAlfa((int)(posX-l/2-3), posY, (int)(posX+l/2+3), posY+a, 127, 0, 0, 127);
		C2D2P_Retangulo((int)(posX-l/2-3), posY, (int)(posX+l/2+3), posY+a, 255, 0, 0);
		break;
	case ATIVADO:
		C2D2P_RetanguloPintadoAlfa((int)(posX-l/2-3), posY, (int)(posX+l/2+3), posY+a, 0, 127, 0, 127);
		C2D2P_Retangulo((int)(posX-l/2-3), posY, (int)(posX+l/2+3), posY+a, 0, 255, 0);
		break;
	}
	C2D2_DesenhaTexto(fonte, posX, posY, name.c_str(), C2D2_TEXTO_CENTRALIZADO);
}
