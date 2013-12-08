#ifndef _ProjetilAOE_H_
#define _ProjetilAOE_H_

#include "Projetil.h"

class ProjetilAOE : public Projetil
{
private:
	int decay;
public:
	ProjetilAOE(GerenteAtor& _gerente, int _x, int _y, int _dano);

	int indice();
	
	void aoColidir(Ator* ator);
	void hit();
	
	void inicializar();		
	void atualizar();		
	void desenhar();		
	void finalizar();
};

#endif
