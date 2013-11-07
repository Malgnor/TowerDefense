#include "Tutorial.h"
#include "MenuInicial.h"

#include "InimigoExemplo.h"

#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>

Tutorial::Tutorial()
	: btnOk("Ok", 400-16, 416, tahoma16)
{
	mapaTD.load("Default");
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
	pInimigoTuto = nullptr;
	pTorreTuto = nullptr;
	pCoinTuto = nullptr;
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
		}
		switch (stage)
		{
		case 0:
			if(btnOk.getEstado() == SOLTO){
				stage++;
				gAtor.adicionar(pInimigoTuto = new InimigoExemplo(gAtor, mapaTD, -16, 304, 1, 50, 10, this));
			}
			break;
		case 1:
			if(!pInimigoTuto->estaNoJogo()){
				stage++;
				pInimigoTuto = nullptr;
			}
			break;
		case 2:
			if(btnOk.getEstado() == SOLTO){
				stage++;
				gold = 50;
			}
			break;
		case 3:			
			if(pTorreTuto == nullptr)
				pTorreTuto = (Torre*)gAtor.maisPerto(0, 0, 1000, TORRE);
			else
				stage++;
			break;
		case 4:
			if(btnOk.getEstado() == SOLTO){
				stage++;
				gAtor.adicionar(pInimigoTuto = new InimigoExemplo(gAtor, mapaTD, -16, 304, 1, 50, 10, this));
			}
			break;
		case 5:
			if(!pInimigoTuto->estaNoJogo()){
				pInimigoTuto = nullptr;
				if(chances == 19)
					stage++;
				else
					stage = 100;
			}
			break;
		case 6:
			if(btnOk.getEstado() == SOLTO){
				stage++;
				pCoinTuto = (Coin*)gAtor.maisPerto(0, 0, 1000, COIN);
			}
			break;
		case 7:
			if(!pCoinTuto->estaNoJogo()){
				pCoinTuto = nullptr;
				if(gold = 10)
					stage++;
				else
					stage = 110;
			}
			break;
		case 8:
			if(btnOk.getEstado() == SOLTO){
				stage++;
			}
			break;
		case 9:
			
			break;
		case 10:
			if(btnOk.getEstado() == SOLTO){
				stage++;
			}
			break;
		case 100:
			if(btnOk.getEstado() == SOLTO){
				stage++;
				gold = 50;
			}
			break;
		case 101:
			if(gold != 50)
				stage = 4;
			break;
		case 110:
			if(btnOk.getEstado() == SOLTO){
				stage++;
				gAtor.adicionar(pInimigoTuto = new InimigoExemplo(gAtor, mapaTD, -16, 304, 1, 50, 10, this));
			}
			break;
		case 111:
			if(!pInimigoTuto->estaNoJogo()){
				pInimigoTuto = nullptr;
				stage = 6;
			}
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
	int ytxt = 0;
	switch (estado)
	{
	case PLAY:
		if(stage%2 == 0){
			C2D2P_RetanguloPintado(200, 150, 550, 450, 0, 127, 127);
			C2D2P_Retangulo(200, 150, 550, 450, 255, 255, 255);
			btnOk.desenhar();
		}
		switch (stage)
		{
		case 0:
			//15 linhas
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "1", C2D2_TEXTO_CENTRALIZADO);
			break;
		case 1:
			break;
		case 2:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "2", C2D2_TEXTO_CENTRALIZADO);
			break;
		case 3:
			break;
		case 4:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "3", C2D2_TEXTO_CENTRALIZADO);
			break;
		case 5:
			break;
		case 6:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "4", C2D2_TEXTO_CENTRALIZADO);
			break;
		case 7:
			break;
		case 8:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "5", C2D2_TEXTO_CENTRALIZADO);
			break;
		case 9:
			break;
		case 10:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "6", C2D2_TEXTO_CENTRALIZADO);
			break;
		case 100:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "2-2", C2D2_TEXTO_CENTRALIZADO);
			break;
		case 101:
			break;
		case 110:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "3-2", C2D2_TEXTO_CENTRALIZADO);
			break;
		case 111:
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
