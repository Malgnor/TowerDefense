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
				gAtor.adicionar(pInimigoTuto = new InimigoExemplo(gAtor, mapaTD, 384, 0, 1, 50, 10, this));
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
				gAtor.adicionar(pInimigoTuto = new InimigoExemplo(gAtor, mapaTD, 0, 0, 1, 50, 10, this));
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
				gAtor.adicionar(pInimigoTuto = new InimigoExemplo(gAtor, mapaTD, 0, 0, 1, 50, 10, this));
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
		C2D2P_RetanguloPintadoAlfa(200, 250, 550, 450, 0, 127, 127, 127);
		C2D2P_Retangulo(200, 250, 550, 450, 255, 255, 255);
		btnOk.desenhar();
		switch (fase)
		{
		case INTRO:
			desenhaTextoML(tahoma16, 375, 260, "Bem-Vindo ao Tutorial!\n\nAtrav�s deste tutorial voc� ir� aprender o\nb�sico de como jogar um Tower Defense.");
			break;
		case PRIMEIROSPASSOS:
			desenhaTextoML(tahoma16, 375, 260, "Parece que um inimigo acabou de nos atacar!\nPrecisamos criar uma defesa contra eles!\n\nVamos come�ar escolhendo uma torre ao lado.");
			break;
		case TORRE0:
			desenhaTextoML(tahoma16, 375, 260, "Agora temos que colocar a torre no mapa,\n para isso simplesmente escolha um local e clique com o\n bot�o esquerdo do mouse.\n\nAten��o: cada torre tem um custo para coloc�-la.\nN�o se preocupe agora, n�s iremos\nte dar dinheiro suficiente para uma torre.");
			break;
		case TORRE1:
			desenhaTextoML(tahoma16, 375, 260, "Excelente! Agora temos uma defesa contra os\n pr�ximos inimigos.\nVamos test�-la!\n\nObs: durante o jogo, ondas de inimigos\nir�o aparecer periodicamente!");
			break;
		case MOEDAS:
			desenhaTextoML(tahoma16, 375, 260, "�timo, conseguimos eliminar o inimigo.\nQuando eliminados, eles derrubam moedas.\nPara pega-las passe o mouse por cima delas.\nElas aumentam seu dinheiro, que � necess�rio para\nadquirir novas torres e melhorar essas torres.");
			break;
		case TORRE2:
			desenhaTextoML(tahoma16, 375, 260, "� poss�vel verificar as estat�sticas das suas torres.\nPara seleciona-la clique com o bot�o esquerdo do mouse\nem cima dela.");
			break;
		case UPGRADE:
			desenhaTextoML(tahoma16, 375, 260, "N�s podemos melhorar essa torre!\nSimplesmente clique no bot�o \"Upgrade\" ao lado.");
			break;
		case VENDER:
			desenhaTextoML(tahoma16, 375, 260, "E tamb�m � poss�vel vender as torres!\n� s� clicar no bot�o \"Vender\" ao lado.");
			break;
		case RTORRE:
			desenhaTextoML(tahoma16, 375, 260, "Parece que a nossa nova torre n�o conseguiu\neliminar o inimigo. Em um Tower Defense,\n o posicionamento das torres � importante!\n\nVamos te dar dinheiro suficiente para colocar outra torre!");
			break;
		case RMOEDAS:
			desenhaTextoML(tahoma16, 375, 260, "� importante tentar coletar o maior n�mero\nde moedas poss�veis durante o jogo!\nCaso contr�rio, seu dinheiro n�o ser� suficiente\n para adquirir e melhorar novas torres!");
			break;
		case FIM:
			desenhaTextoML(tahoma16, 375, 260, "Parab�ns!\n\nVoc� chegou ao fim deste tutorial!");

			break;
		}
		break;
	case PAUSEF1:
		break;
	}
	desenhaMouse();
}
