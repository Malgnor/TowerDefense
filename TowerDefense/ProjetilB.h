#ifndef _ProjetilB_H_
#define _ProjetilB_H_

#include "Projetil.h"

class ProjetilB : public Projetil
{
private:
	int decay;
	double dirx, diry;
public:
	ProjetilB(GerenteAtor& _gerente, int _x, int _y, int _vel, int _dano, int _hp, double _dirx, double _diry);

	int indice();
	
	void aoColidir(Ator* ator);
	void hit();
	
	void inicializar();		
	void atualizar();		
	void desenhar();		
	void finalizar();
};

#endif
