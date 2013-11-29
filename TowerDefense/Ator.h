#ifndef _ATOR_H_
#define _ATOR_H_

#include "globalDef.h"

class GerenteAtor;

enum Tipo {TORRE, PROJETIL, INIMIGO, COIN, SCOLISAO};

class Ator
{
	protected:
		GerenteAtor& gerente;
		//0-fundo
		//1-Torre
		//2-Moedas
		//3-Tiro
		//4-Inimigos
		//5-UI
		int layer;

	public:

		Ator(GerenteAtor& gerente, int _layer);

		virtual int x() = 0;
		virtual int y() = 0;
		virtual int l() = 0;
		virtual int a() = 0;
		virtual int sprite() = 0;
		virtual int indice() = 0;

		virtual Tipo tipo() = 0;
		
		virtual void aoColidir(Ator* ator) = 0;

		virtual bool estaNoJogo() = 0;

		virtual void inicializar() = 0;		
		virtual void atualizar() = 0;

		virtual void desenhar() = 0;	

		virtual void finalizar() = 0;
		int getLayer();
		virtual ~Ator() {};
};

#endif
