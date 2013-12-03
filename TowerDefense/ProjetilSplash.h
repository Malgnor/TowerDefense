#ifndef _ProjetilSplash_H_
#define _ProjetilSplash_H_

#include "Projetil.h"

class ProjetilSplash : public Projetil
{
private:
	int danoS, decay;
public:
	ProjetilSplash(GerenteAtor& _gerente, int _x, int _y, int vel, Ator* _alvo, int _dano);

	int indice();
	
	void aoColidir(Ator* ator);
	void hit();
	
	void inicializar();		
	void atualizar();		
	void desenhar();		
	void finalizar();
};

#endif
