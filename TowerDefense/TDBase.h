#ifndef _TDBASE_H_
#define _TDBASE_H_

#include "Tela.h"
#include "GerenteAtor.h"
#include "Mapa.h"

#include <vector>

#include "ControladorVolume.h"
#include "Menu.h"
#include "MenuButton.h"

class Torre;

enum tdEstado {PLAY, PAUSE, PAUSEF1, GAVEOVER};

class TDBase : public Tela
{
protected:
	GerenteAtor gAtor;
	Mapa mapaTD;
	tdEstado estado;
	int mouseX, mouseY;
	int magneticRadius;
	int magnet;
	bool magMenu;
	int mouseSprite;
	int torreSprite;
	int tahoma16, tahoma32;
	int eheart, heart, goldcoins;
	int chances;
	int gold;
	int torreSelecionada;
	Torre* pTorre;
	int aMusic;
	ControladorVolume cVolume;

	std::vector <Menu*> menus;
	MenuButton* btnExit;
	MenuButton* btnBack;
	MenuButton* btnPause;
	MenuButton btnSell;
	MenuButton btnUpgrade;

public:

	TDBase();

	void Lucro(int money);
	void DanoRecebido(int porrada);
	void desenhaMouse();
	void posMouse(int &x, int &y);
	int magRadius();

	virtual Tela* proximaTela() = 0;

	virtual void inicializar();

	virtual void atualizar();

	virtual void desenhar();

	virtual void finalizar();

	virtual ~TDBase(){}
};

#endif