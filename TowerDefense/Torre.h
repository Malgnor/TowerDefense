#ifndef _TORRE_H_
#define _TORRE_H_

#include "Ator.h"
#include "Projetil.h"

//RTF = Ready to fire
enum tESTADO { RTF, COOLDOWN };

class Torre : public Ator
{
protected:
	int posX, posY, alcance;
	tESTADO estado;

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
