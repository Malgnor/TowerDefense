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
	int mouseX, mouseY;

public:
	Tela* proximaTela();

	void inicializar();		
	void atualizar();
	void desenhar();
	void finalizar();
};

#endif
