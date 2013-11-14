#ifndef _TOWERDEFENSE_H_
#define _TOWERDEFENSE_H_

#include "TDBase.h"

class TowerDefense : public TDBase
{
private:
#ifdef DEBUG
	MenuButton* btnME;
#endif // DEBUG
	int timer;

public:
	TowerDefense();
	TowerDefense(const char* _map);
	Tela* proximaTela();

	void inicializar();		
	void atualizar();
	void desenhar();

	void formation1();
	void formation2();
	void formation3();
	void formation4();
	void formation5();

	void formation6();
	void formation7();
	void formation8();
	void formation9();
	void formation10();

};

#endif
