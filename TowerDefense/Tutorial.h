#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "TDBase.h"
#include "Inimigo.h"

class Tutorial : public TDBase
{
private:
	unsigned int stage;
	Inimigo* pInimigo;
	MenuButton  btnOk;

public:
	Tutorial();
	Tela* proximaTela();

	void inicializar();

	void atualizar();

	void desenhar();

};
#endif