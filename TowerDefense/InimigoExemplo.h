#ifndef _INIMIGOEXEMPLO_H_
#define _INIMIGOEXEMPLO_H_

#include "Inimigo.h"

class InimigoExemplo : public Inimigo
{
public:
	InimigoExemplo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel);

	int x();
	int y();
	int sprite();
	int indice();

	bool primitiva();

	void aoColidir(Ator* ator);

	bool estaNoJogo();

	void inicializar();		
	void atualizar();		
	void desenhar();		
	void finalizar();
};

#endif
