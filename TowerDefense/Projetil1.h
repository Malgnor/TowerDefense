#ifndef _PROJETIL1_H_
#define _PROJETIL1_H_

#include "Projetil.h"

class Projetil1 : public Projetil
{
public:
	Projetil1(GerenteAtor& _gerente, int _x, int _y, int vel, Ator* _alvo, int _dano, int _hp);

	int indice();
	
	void aoColidir(Ator* ator);
	void hit();
	
	void inicializar();		
	void atualizar();		
	void desenhar();		
	void finalizar();
};

#endif
