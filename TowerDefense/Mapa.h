#ifndef _MAPA_H_
#define _MAPA_H_

#include <string>
#include "globalDef.h"

class Mapa
{
private:
	unsigned int map[18][18];
	int initX, initY;
	int sprite;
	std::string nome;
	orientacao ori;

public:
	Mapa();
	void inicializar();
	void desenhar();
	void getInit(int &x, int &y);
	std::string getNome();
	orientacao getOrientacao();
	unsigned int conteudo(int x, int y);
	unsigned int conteudo32(int x, int y);
	int sprite32(int x, int y);
	void addTorre(int x, int y);
	void removeTorre(int x, int y);
	void construir(int x, int y, int sprite, int id);
	void save();
	void load();
	void save(std::string _nome);
	void load(std::string _nome);
	void finalizar();
};

#endif