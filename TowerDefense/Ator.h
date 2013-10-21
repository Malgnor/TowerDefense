#pragma once

class GerenteAtor;
enum Tipo {TORRE, PROJETIL, INIMIGO};
class Ator
{
	protected:
		GerenteAtor& gerente;

	public:

		Ator(GerenteAtor& gerente);

		virtual int x() = 0;
		virtual int y() = 0;
		virtual int sprite() = 0;
		virtual int indice() = 0;

		virtual Tipo tipo() = 0;

		virtual bool primitiva() = 0;

		virtual void aoColidir(Ator* ator) = 0;

		virtual bool estaNoJogo() = 0;

		virtual void inicializar() = 0;		
		virtual void atualizar() = 0;

		//Somente é usando quando primitiva() retorna TRUE
		virtual void desenhar() = 0;	

		virtual void finalizar() = 0;
		virtual ~Ator() {};
};

