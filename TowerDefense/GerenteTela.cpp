#include "GerenteTela.h"

GerenteTela::GerenteTela(Tela* _tela)
	: tela(_tela)
{
	tela->inicializar();
}

void GerenteTela::atualizar()
{
	Tela* proximaTela = tela->proximaTela();
	if (proximaTela == nullptr)
	{
		tela->finalizar();
		delete tela;
		tela = nullptr;
	}
	else
	{
		if (proximaTela != tela) 
		{
			tela->finalizar();
			delete tela;
			tela = proximaTela;
			tela->inicializar();
		}

		tela->atualizar();
	}
}

void GerenteTela::desenhar()
{
	if (tela != nullptr)
		tela->desenhar();
}

bool GerenteTela::jogoAcabou()
{
	return tela == nullptr;
}

