#ifndef _PROJETIL_H_
#define _PROJETIL_H_

#include "Ator.h"

class Projetil : public Ator
{
protected:
	int posX, posY, vel;
	int pSprite;
	Ator& alvo;
	bool alive;

public:
	Projetil(GerenteAtor& _gerente, int _x, int _y, int _vel, Ator& _alvo);

	Tipo tipo();

	virtual ~Projetil(){ }
};

#endif
