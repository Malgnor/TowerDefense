#include "Inimigo.h"
#include "GerenteAtor.h"
#include <c2d2/chien2d2.h>
#include "Coin.h"
#include "Projetil.h"

Inimigo::Inimigo(GerenteAtor& _gerente, Mapa& _map, int _x, int _y, int _vel, int _vida, int _dinheiro, TDBase *_td)
	: Ator(_gerente, 4), mapa(_map), offX(_x), offY(_y), posX(-500), posY(-500), vel(_vel), alive(true), passos(0), dir(iPARADO), vida(_vida), dinheiro(_dinheiro), td(_td)
{

}

Tipo Inimigo::tipo(){
	return INIMIGO;
}

int Inimigo::x(){
	return posX;
}

int Inimigo::y(){
	return posY;
}

int Inimigo::l(){
	return largura;
}

int Inimigo::a(){
	return altura;
}

int Inimigo::sprite(){
	return iSprite;
}

int Inimigo::indice(){
	return indiceVar;
}

void Inimigo::inicializar()
{
	C2D2_DimensoesSprite(iSprite, &largura, &altura);
}


bool Inimigo::estaNoJogo(){
	return alive;
}

void Inimigo::aoColidir(Ator* ator){
	if(ator->tipo() == PROJETIL && ator->estaNoJogo()){
		Projetil* acerto = (Projetil *)ator; 
		vida -= acerto->retornaDano();
		acerto->hit();
	}
}

