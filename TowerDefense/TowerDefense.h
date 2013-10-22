#ifndef _TOWERDEFENSE_H_
#define _TOWERDEFENSE_H_

#include "Tela.h"
#include "GerenteAtor.h"
#include "Mapa.h"

class TowerDefense : public Tela
{
private:
	GerenteAtor gAtor;
	Mapa mapa;
	int tIndice;
	int mouseX, mouseY;
	int mouseSprite;
	int OpenSymbol16, OpenSymbol32;

public:
	Tela* proximaTela();

	void inicializar();		
	void atualizar();
	void desenhar();
	void finalizar();
};

#endif
