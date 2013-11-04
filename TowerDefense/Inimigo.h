#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "Ator.h"
#include "Mapa.h"
#include "TowerDefense.h"

enum iDirecao { iCIMA, iBAIXO, iESQUERDA, iDIREITA };

class Inimigo : public Ator
{
protected:
	int posX, posY, passos, vel, vida, dinheiro;
	int iSprite;
	iDirecao dir;
	Mapa& mapa;
	bool alive;
	TowerDefense* td;
	
public:

	Inimigo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel, int _vida, int _dinheiro, TowerDefense *_td);

	Tipo tipo();

	virtual ~Inimigo(){ }
};

#endif
