#ifndef _TOWERDEFENSE_H_
#define _TOWERDEFENSE_H_

#include "Tela.h"
#include "GerenteAtor.h"
#include "Mapa.h"

class TowerDefense : public Tela
{
private:
	GerenteAtor gAtor;
	Mapa mapaTD;
	int tIndice;
	int mouseX, mouseY;
	int mouseSprite;
	int tahoma16, tahoma32;

public:
	Tela* proximaTela();

	void inicializar();		
	void atualizar();
	void desenhar();
	void wave();
	void wave2();
	void wave3();
	void wave4();
	void wave5();
	void wave6();
	void wave7();
	void wave8();
	void wave9();
	void waveBoss();
	void finalizar();
};

#endif
