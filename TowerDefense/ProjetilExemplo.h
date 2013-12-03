#ifndef _PROJETILEXEMPLO_H_
#define _PROJETILEXEMPLO_H_

#include "Projetil.h"

class ProjetilExemplo : public Projetil
{
public:
	ProjetilExemplo(GerenteAtor& _gerente, int _x, int _y, int vel, Ator* _alvo, int _dano, int _hp);

	int indice();
	
	void aoColidir(Ator* ator);
	void hit();
	
	void inicializar();		
	void atualizar();		
	void desenhar();		
	void finalizar();
};

#endif
