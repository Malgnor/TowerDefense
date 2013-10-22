#include "GerenteAtor.h"

#include <math.h>

#include <c2d2\chien2d2.h>

using namespace std;

GerenteAtor::GerenteAtor()
{
}

void GerenteAtor::adicionar(Ator* ator)
{
	// 0.1 Adiciona os novos atores para a lista de adicionados
	adicionados.push_back(ator);
	ator->inicializar();
}

void GerenteAtor::atualizar()
{
	//0.2 Adiciona os novos atores para a lista de atores
	for (Ator* ator : adicionados)
	{
		atores.push_back(ator);
	}
	adicionados.clear();

	//1. Excluir os atores na lista excluido
	//para libera-la. 
	for (Ator* ator : excluidos)
	{
		delete ator;
	}
	excluidos.clear();

	//2. Mover os mortos para a lista de excluídos
	//para liberar a lista de mortos.
	for (Ator* ator : mortos)
	{
		excluidos.push_back(ator);
	}
	mortos.clear();

	//3. Atualiza a lógica do ator e, caso queira sair do jogo
	//finaliza e move para a lista de mortos. Caso contrário,
	//mantém o ator numa lista de vivos.
	std::vector<Ator*> vivos;
	for (Ator* ator : atores) 
	{
		ator->atualizar();
		if (ator->estaNoJogo())
		{
			vivos.push_back(ator);
		}
		else
		{
			ator->finalizar();
			mortos.push_back(ator);
		}
	}

	//Substitui a lista de atores pela de vivos.
	swap(atores, vivos);

	//Testa a colisão entre os atores vivos
	for (unsigned i = 0; i < atores.size() - 1; i++) 
	{
		if(atores[i]->tipo() == TORRE){

		} else {
			for (unsigned j = i+1; j < atores.size(); j++) 
			{
				if(atores[j]->tipo() == TORRE || atores[j]->tipo() == atores[i]->tipo()){

				} else {
					if (C2D2_ColidiuSprites(
						atores[i]->sprite(), atores[i]->indice(),
						atores[i]->x()-atores[i]->l()/2, atores[i]->y()-atores[i]->a()/2,
						atores[j]->sprite(), atores[j]->indice(),
						atores[j]->x()-atores[j]->l()/2, atores[j]->y()-atores[j]->a()/2))
					{
						atores[i]->aoColidir(atores[j]);
						atores[j]->aoColidir(atores[i]);
					}
				}
			}
		}
	}
}


void GerenteAtor::desenhar()
{
	for (Ator* ator : atores) 
	{
			ator->desenhar();
	}
}

Ator* GerenteAtor::maisPerto(int x, int y, int alcance, Tipo tipo){
	float dis = alcance;
	Ator* alvo = nullptr;
	for (Ator* ator : atores) 
	{
		if(ator->tipo() == tipo){
			int dx = x-ator->x();
			int dy = y-ator->y();
			float dd = sqrt(dx*dx+dy*dy);
			if ( dd <= dis){ 
				dis = dd;
				alvo = ator;
			}
		}
	}
	return alvo;
}

GerenteAtor::~GerenteAtor()
{
	for (Ator* ator : atores) 
	{
		delete ator;
	}
}
