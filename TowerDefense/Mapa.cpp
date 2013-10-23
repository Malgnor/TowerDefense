#include "Mapa.h"

#include "c2d2f.h"

#include <iostream>
#include <fstream>
#include <string>

#include <c2d2/chien2d2.h>

using namespace std;

Mapa::Mapa()
{
	for(int x = 0; x < 18; x++){
		for(int y = 0; y < 18; y++){
				map[x][y] = 0;
		}
	}
}

void Mapa::inicializar()
{
	sprite = C2D2_CarregaSpriteSet("imgs/map.png", 32, 32);
}


void Mapa::desenhar()
{
	for(int x = 0; x < 18; x++){
			for(int y = 0; y < 18; y++){
				C2D2_DesenhaSprite(sprite, map[x][y]/5, x*32, y*32);
		}
	}
}

char Mapa::conteudo( int x, int y )
{
	return map[x/32][y/32]%5;
}

void Mapa::construir( int x, int y )
{
	map[x/32][y/32] += 1;
}

void Mapa::construir( int x, int y, int sprite, int id)
{
	map[x/32][y/32] = (sprite*5)+id;
}

void Mapa::save()
{
	C2D2_RemoveSpriteSet(sprite);
	string strmap = "";
	stringFInput(strmap,"(SAVE)Nome do mapa:");
	ofstream ofile("map/"+strmap+".map", ios_base::binary);
	ofile.write((char*)this, sizeof(Mapa));
	ofile.close();
	sprite = C2D2_CarregaSpriteSet("imgs/map.png", 32, 32);
}

void Mapa::load()
{
	C2D2_RemoveSpriteSet(sprite);
	string strmap = "";
	stringFInput(strmap, "(LOAD)Nome do mapa:");
	ifstream ifile("map/"+strmap+".map", ios_base::binary);
	ifile.read((char*)this, sizeof(Mapa));
	ifile.close();
	sprite = C2D2_CarregaSpriteSet("imgs/map.png", 32, 32);
}

void Mapa::finalizar()
{
	C2D2_RemoveSpriteSet(sprite);
}
