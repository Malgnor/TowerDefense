#ifndef _TORREMULTI_H_
#define _TORREMULTI_H_

#include "torre.h"
#include <vector>

class TorreMulti : public Torre
{
private:
	std::vector<Ator*> alvos;

public:	
	TorreMulti(GerenteAtor& _gerente, int _x, int _y);
	
	void aoColidir(Ator* ator);

	bool estaNoJogo();

	void inicializar();		
	void atualizar();
	void upgrade();
	void desenhar();		
	void finalizar();
};

#endif

