#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "Ator.h"
#include "Mapa.h"

enum iDirecao { iCIMA, iBAIXO, iESQUERDA, iDIREITA };

class Inimigo : public Ator
{
protected:
	int posX, posY, passos, vel;
	iDirecao dir;
	Mapa& mapa;
	bool alive;
	
public:

	Inimigo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel);

	Tipo tipo();

	virtual ~Inimigo(){ }
};

#endif
