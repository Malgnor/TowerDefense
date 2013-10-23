#pragma once

#include <vector>

#include "Ator.h"

class GerenteAtor
{
	private:
		std::vector<Ator*> atores;
		std::vector<Ator*> mortos;
		std::vector<Ator*> adicionados;
		std::vector<Ator*> excluidos;

	public:
		GerenteAtor();
		void adicionar(Ator* ator);
		void atualizar();
		void desenhar();
		Ator* maisPerto(int x, int y, int alcance, Tipo tipo);
		~GerenteAtor();
};

