#ifndef _COIN_H_
#define _COIN_H_

#include "Ator.h"
#include "TowerDefense.h"

class Coin : public Ator
{
private:
	int valor, decay;
	int posX, posY, offX, offY, altura, largura;
	int spriteSet;
	bool alive;
	TowerDefense* td;

public:
	Coin(GerenteAtor& _gerente, TowerDefense* _td, int _valor, int _x, int _y);

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