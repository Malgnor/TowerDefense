#ifndef _TORRE2_H_
#define _TORRE2_H_

#include "torre.h"

class Torre2 : public Torre
{
public:	
	Torre2(GerenteAtor& _gerente, int _x, int _y);
	
	
	void aoColidir(Ator* ator);

	bool estaNoJogo();

	void inicializar();		
	void atualizar();
	void upgrade();
	void desenhar();		
	void finalizar();
};

#endif

