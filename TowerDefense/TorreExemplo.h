#ifndef _TORREEXEMPLO_H_
#define _TORREEXEMPLO_H_

#include "Torre.h"

class TorreExemplo : public Torre
{

public:	
	TorreExemplo(GerenteAtor& _gerente, int _x, int _y);
	int x();
	int y();
	int sprite();
	int indice();
	
	bool primitiva();

	void aoColidir(Ator* ator);

	bool estaNoJogo();

	void inicializar();		
	void atualizar();		
	void desenhar();		
	void finalizar();
};

#endif
