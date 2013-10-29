#ifndef _TORRE_H_
#define _TORRE_H_

#include "Ator.h"
#include "Projetil.h"

//RTF = Ready to fire
enum tESTADO { RTF, COOLDOWN };

class Torre : public Ator
{
public:
	int posX, posY, alcance;
	tESTADO estado;
	int tSprite;

	//Rate of Fire
	int RoF;

	//Cooldown
	int cd;

	bool alive;

public:
	Torre(GerenteAtor& _gerente, int _x, int _y);

	Tipo tipo();

	virtual ~Torre(){ }
};

#endif
