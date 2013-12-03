#ifndef _TorreB_H_
#define _TorreB_H_

#include "Torre.h"

class TorreB : public Torre
{
public:	
	TorreB(GerenteAtor& _gerente, int _x, int _y);
	
	
	void aoColidir(Ator* ator);

	bool estaNoJogo();

	void inicializar();		
	void atualizar();
	void upgrade();
	void desenhar();		
	void finalizar();
};

#endif

