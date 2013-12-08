#ifndef _ProjetilB_H_
#define _ProjetilB_H_

#include "Projetil.h"

class ProjetilB : public Projetil
{
private:
	int decay;
public:
	ProjetilB(GerenteAtor& _gerente, int _x, int _y, int _dano);

	int indice();
	
	void aoColidir(Ator* ator);
	void hit();
	
	void inicializar();		
	void atualizar();		
	void desenhar();		
	void finalizar();
};

#endif
