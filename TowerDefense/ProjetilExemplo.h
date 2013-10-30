#ifndef _PROJETILEXEMPLO_H_
#define _PROJETILEXEMPLO_H_

#include "Projetil.h"

class ProjetilExemplo : public Projetil
{
public:
	ProjetilExemplo(GerenteAtor& _gerente, int _x, int _y, int vel, Ator& _alvo, int _dano);
	
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
