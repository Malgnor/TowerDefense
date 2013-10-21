#pragma once

#include "Tela.h"

class GerenteTela
{
	private:
		Tela* tela;
	public:
		GerenteTela(Tela* tela);
		void atualizar();
		void desenhar();
		bool jogoAcabou();
};

