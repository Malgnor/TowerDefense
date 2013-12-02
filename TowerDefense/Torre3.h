#ifndef _TORRE3_H_
#define _TORRE3_H_

#include "torre.h"

class Torre3 : public Torre
{
private:
	int tDano;
public:
	Torre3(GerenteAtor& _gerente, int _x, int _y);


	void aoColidir(Ator* ator);

	bool estaNoJogo();

	void inicializar();		
	void atualizar();
	void upgrade();
	void desenhar();		
	void finalizar();
};

#endif