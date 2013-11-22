#ifndef _COIN_H_
#define _COIN_H_

#include "Ator.h"
#include "TDBase.h"

class Coin : public Ator
{
private:
	int valor, decay;
	int posX, posY, altura, largura;
	int spriteSet;
	bool alive;
	TDBase* td;

public:
	Coin(GerenteAtor& _gerente, TDBase* _td, int _valor, int _x, int _y);

	int x();
	int y();
	int l();
	int a();
	int sprite();
	int indice();

	Tipo tipo();

	void aoColidir(Ator* ator);

	bool estaNoJogo();

	void inicializar();		
	void atualizar();

	void desenhar();	

	void finalizar();
};

#endif