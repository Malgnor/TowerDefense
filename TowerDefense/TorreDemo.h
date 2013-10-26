#ifndef _TORREDEMO_H_
#define _TORREDEMO_H_

#include "Torre.h"

class TorreDemo : public Torre
{
public:
	TorreDemo(GerenteAtor& _gerente, int _x, int _y);

	int x();
	int y();
	int l();
	int a();
	int sprite();
	int indice();
	
	void aoColidir(Ator* ator);

	bool estaNoJogo();

	void inicializar();		
	void atualizar();		
	void desenhar();		
	void finalizar();
};

#endif


