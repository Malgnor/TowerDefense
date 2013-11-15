#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "TDBase.h"
#include "Inimigo.h"
#include "Coin.h"

enum faseTutorial {INTRO, PRIMEIROSPASSOS, TORRE0, TORRE1, MOEDAS, TORRE2, UPGRADE, VENDER, RTORRE, RMOEDAS, FIM};

class Tutorial : public TDBase
{
private:
	unsigned int stage;
	int timer;
	faseTutorial fase;
	Inimigo* pInimigoTuto;
	Torre* pTorreTuto;
	Coin* pCoinTuto;
	MenuButton  btnOk;

public:
	Tutorial();
	Tela* proximaTela();

	void inicializar();

	void atualizar();

	void desenhar();

};
#endif