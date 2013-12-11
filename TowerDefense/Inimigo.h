#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "Ator.h"
#include "Mapa.h"
#include "TDBase.h"

class Inimigo : public Ator
{
protected:
	int posX, posY, passos, vel, vida, dinheiro, offX, offY;
	int iSprite;
	iDirecao dir;
	Mapa& mapa;
	bool alive;
	TDBase* td;
	int indiceVar;
	int largura;
	int altura;

public:

	Inimigo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel, int _vida, int _dinheiro, TDBase *_td);
	int x();
	int y();
	int l();
	int a();
	int sprite();
	int indice();
	Tipo tipo();
	void aoColidir(Ator* ator);
    bool estaNoJogo();
    virtual void inicializar();

	virtual ~Inimigo(){ }
};

#endif
