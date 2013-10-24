#ifndef _INIMIGOEXEMPLO_H_
#define _INIMIGOEXEMPLO_H_

#include "Inimigo.h"

class InimigoExemplo : public Inimigo
{
public:
	InimigoExemplo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel, int _vida);

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
