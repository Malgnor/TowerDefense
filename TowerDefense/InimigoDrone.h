#ifndef _INIMIGODRONE_H_
#define _INIMIGODRONE_H_

#include "Inimigo.h"

class InimigoDrone : public Inimigo
{
private:
	int sprite;
	int danoinimigo;
	int vidaMax;

public:
	InimigoDrone(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel, int _vida, int _dinheiro, int _sprite, TDBase* _td);

	void inicializar();		
    void atualizar();	
	void desenhar();		
	void finalizar();
};

#endif
