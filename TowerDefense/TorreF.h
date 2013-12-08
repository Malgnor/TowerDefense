#ifndef _TORREF_H_
#define _TORREF_H_

#include "Torre.h"
#include <vector>

class TorreF : public Torre
{
private:
	std::vector<Ator*> tiros;

public:	
	TorreF(GerenteAtor& _gerente, int _x, int _y);
	
	void aoColidir(Ator* ator);

	bool estaNoJogo();

	void inicializar();		
	void atualizar();
	void upgrade();
	void desenhar();		
	void finalizar();
};

#endif

