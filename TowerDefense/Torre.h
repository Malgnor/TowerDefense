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
	int tSprite;
	int ind;
	int largura;
	int altura;
	int valor;
	int custo;

	//Rate of Fire
	int RoF;

	//Cooldown
	int cd;

	bool alive;

public:
	Torre(GerenteAtor& _gerente, int _x, int _y, int _valor, int _custo);

	Tipo tipo();
	int x();
	int y();
	int l();
	int a();
	int sprite();
	int indice();
	virtual void upgrade() = 0;
	virtual void inicializar();
	int vender();
	int comprar();
	int getAlcance();
	int getRof();

	virtual ~Torre(){ }
};

#endif
