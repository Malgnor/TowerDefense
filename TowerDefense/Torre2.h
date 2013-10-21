#ifndef _TORRE2_H_
#define _TORRE2_H_

#include "torre.h"

class Torre2 : public Torre
{
private:
	int image;

public:	
	Torre2(GerenteAtor& _gerente, int _x, int _y);
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

