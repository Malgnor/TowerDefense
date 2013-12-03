#ifndef _Projetil3_H_
#define _Projetil3_H_

#include "projetil.h"

class Projetil3 : public Projetil
{
private:
	int danoS, decay, explo;
public:
	Projetil3(GerenteAtor& _gerente, int _x, int _y, int vel, Ator* _alvo, int _dano);

	int indice();

	void aoColidir(Ator* ator);
	void hit();

	void inicializar();		
	void atualizar();		
	void desenhar();		
	void finalizar();
};

#endif