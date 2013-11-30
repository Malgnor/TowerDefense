#include "globalDef.h"
#include "Mapa.h"

#include "c2d2f.h"

#include <iostream>
#include <fstream>

#include <c2d2/chien2d2.h>

using namespace std;

Mapa::Mapa()
	:initX(16), initY(304)
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
void Mapa::getInit(int &x, int &y){
	x = initX;
	y = initY;
}

unsigned int Mapa::conteudo( int x, int y )
{
	return map[x/32][y/32]%5;
}

unsigned int Mapa::conteudo32(int x, int y){
	return map[x][y]%5;
}

int Mapa::sprite32( int x, int y )
{
	return map[x][y]/5;
}

void Mapa::addTorre( int x, int y )
{
	map[x/32][y/32] += 1;
}

void Mapa::removeTorre( int x, int y )
{
	map[x/32][y/32] -= 1;
}

void Mapa::construir( int x, int y, int sprite, int id)
{
	map[x/32][y/32] = (sprite*5)+id;
}

void Mapa::save()
{
	for(int x = 0; x < 18; x++){
		for(int y = 0; y < 18; y++){
			if(map[x][y]%5 == 2){
				initX = x*32+16;
				initY = y*32+16;
			}
		}
	}
	ofstream ofile("map/"+stringFInput("(SAVE)Nome do mapa:", ".map")+".map");
	ofile << "[" << endl;
	for(int y = 0; y < 18; y++){
		for(int x = 0; x < 18; x++){
			ofile << map[x][y] << " ";
		}
		ofile << endl;
	}
	ofile << "]" << endl;
	ofile << "( " << initX << " , " << initY << " )" << endl;
	ofile.close();
	/*
	C2D2_RemoveSpriteSet(sprite);
	ofstream ofile("map/"+stringFInput("(SAVE)Nome do mapa:", ".map")+".map", ios_base::binary);
	ofile.write((char*)this, sizeof(Mapa));
	ofile.close();
	sprite = C2D2_CarregaSpriteSet("imgs/map.png", 32, 32);
	*/
}

void Mapa::load()
{
	string nome = "";
	string buffer;
	stringFInput(nome, "(LOAD)Nome do mapa:", ".map");
	ifstream ifile("map/"+nome+".map");
	ifile >> buffer;
	for(int y = 0; y < 18; y++){
		for(int x = 0; x < 18; x++){
			ifile >> map[x][y];
		}
		ifile;
	}
	ifile >> buffer;
	ifile >> buffer >> initX >> buffer >> initY >> buffer;
	ifile.close();
	/*
	C2D2_RemoveSpriteSet(sprite);
	ifstream ifile("map/"+nome+".map", ios_base::binary);
	ifile.read((char*)this, sizeof(Mapa));
	ifile.close();
	sprite = C2D2_CarregaSpriteSet("imgs/map.png", 32, 32);
	*/
}

void Mapa::load(string nome)
{
	string buffer;
	ifstream ifile("map/"+nome+".map");
	ifile >> buffer;
	for(int y = 0; y < 18; y++){
		for(int x = 0; x < 18; x++){
			ifile >> map[x][y];
		}
		ifile;
	}
	ifile >> buffer;
	ifile >> buffer >> initX >> buffer >> initY >> buffer;
	ifile.close();
	/*
	C2D2_RemoveSpriteSet(sprite);
	ifstream ifile("map/"+nome+".map", ios_base::binary);
	ifile.read((char*)this, sizeof(Mapa));
	ifile.close();
	sprite = C2D2_CarregaSpriteSet("imgs/map.png", 32, 32);
	*/
}

void Mapa::finalizar()
{
	C2D2_RemoveSpriteSet(sprite);
}
