#include "Tutorial.h"
#include "MenuInicial.h"

#include "InimigoDrone.h"
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
	if(btnRetry->getEstado() == SOLTO)
		return new Tutorial();
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
	delete btnRetry;
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
				gAtor.adicionar(pInimigoTuto = new InimigoDrone(gAtor, mapaTD, 384, 0, 1, 50, 10, this));
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
				gAtor.adicionar(pInimigoTuto = new InimigoDrone(gAtor, mapaTD, 0, 0, 1, 50, 10, this));
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
			if(pCoinTuto == nullptr){
				stage = 0;
				fase = TORRE1;
			}else if(!pCoinTuto->estaNoJogo()){
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
				gAtor.adicionar(pInimigoTuto = new InimigoDrone(gAtor, mapaTD, 0, 0, 1, 50, 10, this));
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
		switch (fase)
		{
		case INTRO:
			break;
		case PRIMEIROSPASSOS:
			for(int j = 1; j < 3; j++)
				if(timer % 30 >= 15)
					C2D2P_Retangulo(625+(j - 1) % 2 * 75, 100 + (j - 1) / 2 * 48, 658+(j - 1) % 2 * 75, 133 + (j - 1) / 2 * 48, 255, 0, 0);
			break;
		case TORRE0:
			if(timer % 30 >= 15){
				C2D2P_Retangulo(0, 1, 576, 9*32, 255, 0, 0);
				C2D2P_Retangulo(0, 10*32, 576, 576, 255, 0, 0);
			}
			break;
		case TORRE1:
			break;
		case MOEDAS:
			if(timer % 30 >= 15 && pCoinTuto != nullptr)
				C2D2P_Retangulo(pCoinTuto->x()-pCoinTuto->l()/2-1, pCoinTuto->y()-pCoinTuto->a()/2-1, pCoinTuto->x()+pCoinTuto->l()/2, pCoinTuto->y()+pCoinTuto->a()/2+2, 255, 0, 0);
			break;
		case TORRE2:
			if(timer % 30 >= 15 && pTorreTuto != nullptr)
				C2D2P_Retangulo(pTorreTuto->x()-pTorreTuto->l()/2-1, pTorreTuto->y()-pTorreTuto->a()/2-1, pTorreTuto->x()+pTorreTuto->l()/2+1, pTorreTuto->y()+pTorreTuto->a()/2+1, 255, 0, 0);
			break;
		case UPGRADE:
			if(timer % 30 >= 15)
				C2D2P_Retangulo(685-btnUpgrade.largura()/2-4, 414, 685+btnUpgrade.largura()/2+4, 414+btnUpgrade.altura()+2, 0, 0, 255);
			break;
		case VENDER:
			if(timer % 30 >= 15)
				C2D2P_Retangulo(630-btnSell.largura()/2-4, 414, 630+btnSell.largura()/2+4, 414+btnSell.altura()+2, 0, 0, 255);
			break;
		case RTORRE:
			if(timer % 30 >= 15){
				C2D2P_Retangulo(0, 1, 576, 9*32, 255, 0, 0);
				C2D2P_Retangulo(0, 10*32, 576, 576, 255, 0, 0);
			}
			break;
		case RMOEDAS:
			break;
		case FIM:
			break;
		}
		break;
	case PAUSE:
		C2D2P_RetanguloPintadoAlfa(200, 270, 550, 450, 0, 127, 127, 127);
		C2D2P_Retangulo(200, 270, 550, 450, 255, 255, 255);
		btnOk.desenhar();
		switch (fase)
		{
		case INTRO:
			desenhaTextoML(tahoma16, 375, 280, "Bem-Vindo ao Tutorial!\n\nAtrav�s deste tutorial voc� ir� aprender o\nb�sico de como jogar um Tower Defense.");
			break;
		case PRIMEIROSPASSOS:
			desenhaTextoML(tahoma16, 375, 280, "Parece que um inimigo acabou de nos atacar!\nPrecisamos criar uma defesa contra eles!\n\nVamos come�ar escolhendo uma torre ao lado.");
			break;
		case TORRE0:
			desenhaTextoML(tahoma16, 375, 280, "Agora temos que colocar a torre no mapa,\n para isso simplesmente escolha um local e clique com o\n bot�o esquerdo do mouse.\n\nAten��o: cada torre tem um custo para coloc�-la.\nN�o se preocupe agora, n�s iremos\nte dar dinheiro suficiente para uma torre.");
			break;
		case TORRE1:
			desenhaTextoML(tahoma16, 375, 280, "Excelente! Agora temos uma defesa contra os\n pr�ximos inimigos.\nVamos test�-la!\n\nObs: durante o jogo, ondas de inimigos\nir�o aparecer periodicamente!");
			break;
		case MOEDAS:
			desenhaTextoML(tahoma16, 375, 280, "�timo, conseguimos eliminar o inimigo.\nQuando eliminados, eles derrubam moedas.\nPara pega-las passe o mouse por cima delas.\nElas aumentam seu dinheiro, que � necess�rio para\nadquirir novas torres e melhorar essas torres.");
			break;
		case TORRE2:
			desenhaTextoML(tahoma16, 375, 280, "� poss�vel verificar as estat�sticas das suas torres.\nPara seleciona-la clique com o bot�o esquerdo do mouse\nem cima dela.");
			break;
		case UPGRADE:
			desenhaTextoML(tahoma16, 375, 280, "N�s podemos melhorar essa torre!\nSimplesmente clique no bot�o \"Upgrade\" ao lado.");
			break;
		case VENDER:
			desenhaTextoML(tahoma16, 375, 280, "E tamb�m � poss�vel vender as torres!\n� s� clicar no bot�o \"Vender\" ao lado.");
			break;
		case RTORRE:
			desenhaTextoML(tahoma16, 375, 280, "Parece que a nossa nova torre n�o conseguiu\neliminar o inimigo. Em um Tower Defense,\no posicionamento das torres � importante!\n\nVamos te dar dinheiro suficiente para colocar outra torre!");
			break;
		case RMOEDAS:
			desenhaTextoML(tahoma16, 375, 280, "� importante tentar coletar o maior n�mero\nde moedas poss�veis durante o jogo!\nCaso contr�rio, seu dinheiro n�o ser� suficiente\n para adquirir e melhorar novas torres!");
			break;
		case FIM:
			desenhaTextoML(tahoma16, 375, 280, "Parab�ns!\n\nVoc� chegou ao fim deste tutorial!");
			break;
		}
		break;
	case PAUSEF1:
		break;
	}
	desenhaMouse();
}
