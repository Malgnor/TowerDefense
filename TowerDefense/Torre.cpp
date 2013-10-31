#include "Torre.h"
#include "GerenteAtor.h"
#include <c2d2/chien2d2.h>

Torre::Torre(GerenteAtor& _gerente, int _x, int _y, int _valor, int _custo)
	: Ator(_gerente), posX(16+_x-_x%32), posY(16+_y-_y%32), valor(_valor), custo(_custo), 
	alive(true), estado(COOLDOWN), largura(0), altura(0), ind(0)
{

}

Tipo Torre::tipo(){
	return TORRE;
}

int Torre::x(){
	return posX;
}

int Torre::y(){
	return posY;
}

int Torre::l(){
	return largura;
}

int Torre::a(){
	return altura;
}

int Torre::sprite(){
	return tSprite;
}

int Torre::indice(){
	return ind;
}

void Torre::inicializar()
{
	C2D2_DimensoesSprite(tSprite, &largura, &altura);
}

int Torre::vender()
{
	alive = false;
	return valor;
}

int Torre::comprar()
{
	return custo;
}

int Torre::getAlcance()
{
	return alcance;
}

int Torre::getRof()
{
	return RoF;
}
