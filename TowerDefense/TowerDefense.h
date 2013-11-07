#ifndef _TOWERDEFENSE_H_
#define _TOWERDEFENSE_H_

#include "TDBase.h"

class TowerDefense : public TDBase
{
private:
#ifdef DEBUG
	MenuButton* btnME;
#endif // DEBUG
	int timer, chrono;

public:
	TowerDefense();
	TowerDefense(const char* _map);
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

};

#endif
