#include "Tutorial.h"
#include "MenuInicial.h"

#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>

Tutorial::Tutorial()
	: btnOk("Ok", 400-32, 400, tahoma16)
{
}

Tela* Tutorial::proximaTela()
{
	C2D2_Botao* teclas = C2D2_PegaTeclas();

	if (teclas[C2D2_ENCERRA].pressionado || btnExit->getEstado() == SOLTO)
		return nullptr;	
	if(btnBack->getEstado() == SOLTO)
		return new MenuInicial();
	return this;
}

void Tutorial::inicializar()
{
	TDBase::inicializar();
	stage = 0;
	gold = 0;
	pInimigo = nullptr;
}

void Tutorial::atualizar()
{
	TDBase::atualizar();
	switch (estado)
	{
	case PLAY:
		if (stage%2 == 0)
		{
			btnOk.atualizar();
			if(btnOk.getEstado() == SOLTO)
				stage++;
		}
		switch (stage)
		{
		case 0:
			
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		}
		break;
	case PAUSE:
		break;
	case PAUSEF1:
		break;
	}
}

void Tutorial::desenhar()
{
	TDBase::desenhar();

	C2D2_DesenhaTexto(tahoma32, 600, 16, "Tutorial", C2D2_TEXTO_ESQUERDA);
	switch (estado)
	{
	case PLAY:
		if(stage%2 == 0){
			C2D2P_RetanguloPintado(250,150,550,450, 0, 0, 0);
			C2D2P_Retangulo(250,150,550,450, 0, 0, 0);
			btnOk.desenhar();
		}
		switch (stage)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		}
		break;
	case PAUSE:
		break;
	case PAUSEF1:
		break;
	}
	desenhaMouse();
}
