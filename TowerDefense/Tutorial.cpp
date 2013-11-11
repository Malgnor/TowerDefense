#include "Tutorial.h"
#include "MenuInicial.h"

#include "InimigoExemplo.h"
#include "Torre.h"
#include "Torre2.h"

#include "c2d2f.h"

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
	if(btnBack->getEstado() == SOLTO || (fase == FIM && stage == 1))
		return new MenuInicial();
	return this;
}

void Tutorial::inicializar()
{
	TDBase::inicializar();
	fase = INTRO;
	stage = 0;
	gold = 0;
	pInimigoTuto = nullptr;
	pTorreTuto = nullptr;
	pCoinTuto = nullptr;
	delete btnPause;
	menus.clear();
	menus.push_back(btnBack);
	menus.push_back(btnExit);
}

void Tutorial::atualizar()
{
	TDBase::atualizar();
	
	if (stage == 0)
	{
		estado = PAUSE;
		btnOk.atualizar();
	} else {
		estado = estado == PAUSE ? PLAY : estado;
	}

	switch (fase)
	{
	case INTRO:
		if(stage == 0){
			if(btnOk.getEstado() == SOLTO){
				stage++;
				gAtor.adicionar(pInimigoTuto = new InimigoExemplo(gAtor, mapaTD, 112, 304, 1, 50, 10, this));
			}
		} else {
			if(!pInimigoTuto->estaNoJogo()){
				stage = 0;
				fase = PRIMEIROSPASSOS;
				pInimigoTuto = nullptr;
			}
		}
		break;
	case PRIMEIROSPASSOS:
		if(stage == 0){
			if(btnOk.getEstado() == SOLTO){
				stage++;
				gold = 50;
			}
		} else {
			if( torreSelecionada == 0 ){
			} else{
				stage=0;
				fase = TORRE0;
			}
		}
		break;
	case TORRE0:
		if(stage == 0){
			if(btnOk.getEstado() == SOLTO){
				stage++;
				gold = 50;
			}
		} else {
			if(pTorreTuto == nullptr)
				pTorreTuto = (Torre*)gAtor.maisPerto(0, 0, 1000, TORRE);
			else{
				stage=0;
				fase = TORRE1;
			}
		}
		break;
	case TORRE1:
		if(stage == 0){
			if(btnOk.getEstado() == SOLTO){
				stage++;
				chances = 19;
				gAtor.adicionar(pInimigoTuto = new InimigoExemplo(gAtor, mapaTD, 16, 304, 1, 50, 10, this));
			}
		} else {
			if(!pInimigoTuto->estaNoJogo()){
				pInimigoTuto = nullptr;
				stage = 0;
				if(chances == 19)
					fase = MOEDAS;
				else
					fase = RTORRE;
			}
		}
		break;
	case MOEDAS:
		if(stage == 0){
			if(btnOk.getEstado() == SOLTO){
				stage++;
				pCoinTuto = (Coin*)gAtor.maisPerto(0, 0, 1000, COIN);
			}
		} else {
			if(!pCoinTuto->estaNoJogo()){
				pCoinTuto = nullptr;
				stage = 0;
				if(gold > 9)
					fase = TORRE2;
				else
					fase = RMOEDAS;
			}
		}
		break;
	case TORRE2:
		if(stage == 0){
			if(btnOk.getEstado() == SOLTO){
				stage++;
				while((pTorreTuto = (Torre*)gAtor.maisPerto(0,0, 1000, TORRE)) != nullptr){
					pTorreTuto->vender();
					mapaTD.removeTorre(pTorreTuto->x(), pTorreTuto->y());
				}
				gAtor.adicionar(pTorreTuto = new Torre2(gAtor, 300, 320));
				mapaTD.addTorre(300,320);
			}
		} else {
			if(pTorreTuto == pTorre){
				stage = 0;
				fase = UPGRADE;
			}
		}
		break;
	case UPGRADE:
		if(stage == 0){
			if(btnOk.getEstado() == SOLTO){
				stage++;
				gold = 120;
			}
		} else {
			if(btnUpgrade.getEstado() == SOLTO){
				stage = 0;
				fase = VENDER;
			} else if(gold != 120){
				gold = 120;
			}
		}
		break;
	case VENDER:
		if(stage == 0){
			if(btnOk.getEstado() == SOLTO){
				stage++;
			}
		} else {
			if(btnSell.getEstado() == SOLTO){
				stage = 0;
				fase = FIM;
			}
		}
		break;
	case RTORRE:
		if(stage == 0){
			if(btnOk.getEstado() == SOLTO){
				stage++;
				gold = 50;
			}
		} else {
			if(gold != 50){
				stage = 0;
				fase = TORRE1;
			}
		}
		break;
	case RMOEDAS:
		if(stage == 0){
			if(btnOk.getEstado() == SOLTO){
				stage++;
				gAtor.adicionar(pInimigoTuto = new InimigoExemplo(gAtor, mapaTD, 16, 304, 1, 50, 10, this));
			}
		} else {
			if(!pInimigoTuto->estaNoJogo()){
				pInimigoTuto = nullptr;
				stage = 0;
				fase = MOEDAS;
			}
		}
		break;
	case FIM:
		if(stage == 0){
			if(btnOk.getEstado() == SOLTO){
				stage++;
			}
		}
		break;
	}

	switch (estado)
	{
	case PLAY:
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

	C2D2_DesenhaTexto(tahoma32, 632, 16, "Tutorial", C2D2_TEXTO_ESQUERDA);
	int ytxt = 0;

	switch (estado)
	{
	case PLAY:
		break;
	case PAUSE:
		C2D2P_RetanguloPintadoAlfa(200, 150, 550, 450, 0, 127, 127, 127);
		C2D2P_Retangulo(200, 150, 550, 450, 255, 255, 255);
		btnOk.desenhar();
		switch (fase)
		{
		case INTRO:
			//15 linhas
			//C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "Intro", C2D2_TEXTO_CENTRALIZADO);
			//desenhaTextoML(tahoma16, 375, 160, "Teste\nTeste2\nafaoisudfasiu\nabsodfiuashf98uaz\nasufiadygiu");
			desenhaTextoML(tahoma16, 375, 160, "Teste fshuifa gnaoidfhy8 asfuihasf af9asiu adsnfiuosf asdfhui", 0, ' ');
			dimentsoesTextoML(tahoma16, "Teste fshuifa gnaoidfhy8 asfuihasf af9asiu adsnfiuosf asdfhui", ytxt, ' ');
			desenhaTextoML(tahoma16, 375, 160+ytxt, "Teste\nfayui\nfaio");
			break;
		case PRIMEIROSPASSOS:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "O que fazer", C2D2_TEXTO_CENTRALIZADO);
			break;
		case TORRE0:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "Colocar torre", C2D2_TEXTO_CENTRALIZADO);
			break;
		case TORRE1:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "Inimigos", C2D2_TEXTO_CENTRALIZADO);
			break;
		case MOEDAS:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "Moedas", C2D2_TEXTO_CENTRALIZADO);
			break;
		case TORRE2:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "Selecionar Torre", C2D2_TEXTO_CENTRALIZADO);
			break;
		case UPGRADE:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "Upgrade Torre", C2D2_TEXTO_CENTRALIZADO);
			break;
		case VENDER:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "Vender Torre", C2D2_TEXTO_CENTRALIZADO);
			break;
		case RTORRE:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "Torres 2", C2D2_TEXTO_CENTRALIZADO);
			break;
		case RMOEDAS:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "Moedas 2", C2D2_TEXTO_CENTRALIZADO);
			break;
		case FIM:
			C2D2_DesenhaTexto(tahoma16, 375, 160+ytxt++*16, "Fim Tutorial", C2D2_TEXTO_CENTRALIZADO);
			break;
		}
		break;
	case PAUSEF1:
		break;
	}
	desenhaMouse();
}
