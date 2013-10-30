#ifndef _INIMIGODEMO_H_
#define _INIMIGODEMO_H_

#include "inimigo.h"

class InimigoDemo :	public Inimigo
{
public:
	InimigoDemo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, iDirecao _dir, TowerDefense *_td);
	
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


