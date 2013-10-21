#include "Mapa.h"

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
	sprite = C2D2_CarregaSpriteSet("map/map.png", 32, 32);
}


void Mapa::desenhar()
{
	for(int x = 0; x < 18; x++){
			for(int y = 0; y < 18; y++){
				if(map[x][y] > 9){
					C2D2_DesenhaSprite(sprite, (map[x][y]/10)-1, x*32, y*32);
				}
		}
	}
}

char Mapa::conteudo( int x, int y )
{
	return map[x/32][y/32]%10;
}

void Mapa::construir( int x, int y )
{
	map[x/32][y/32] += 1;
}

void Mapa::construir( int x, int y, int sprite, int id)
{
	sprite++;
	map[x/32][y/32] = (sprite*10)+id;
	cout << (sprite*10)+id << "\tid: " << id << "\ttile: " << sprite << endl;
}

void Mapa::save()
{
	string strmap = "";
	cout << "Nome do mapa: ";
	getline(cin, strmap);
	ofstream ofile("map/"+strmap+".map", ios_base::binary);
	ofile.write((char*)this, sizeof(Mapa));
	ofile.close();
}

void Mapa::load()
{
	string strmap = "";
	cout << "Nome do mapa: ";
	getline(cin, strmap);
	ifstream ifile("map/"+strmap+".map", ios_base::binary);
	ifile.read((char*)this, sizeof(Mapa));
	ifile.close();
}

void Mapa::finalizar()
{
	C2D2_RemoveSpriteSet(sprite);
}
