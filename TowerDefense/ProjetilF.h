#ifndef _PROJETILF_H_
#define _PROJETILF_H_

#include "Projetil.h"

class ProjetilF : public Projetil
{
public:
	ProjetilF(GerenteAtor& _gerente, int _x, int _y, int vel, int _dano, int _hp);

	int indice();
	
	void aoColidir(Ator* ator);
	void hit();
	
	void inicializar();		
	void atualizar();		
	void desenhar();		
	void finalizar();
};

#endif
