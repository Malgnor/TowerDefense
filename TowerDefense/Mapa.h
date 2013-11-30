#ifndef _MAPA_H_
#define _MAPA_H_

#include <string>

class Mapa
{
private:
	unsigned int map[18][18];
	int initX, initY;
	int sprite;

public:
	Mapa();
	void inicializar();
	void desenhar();
	void getInit(int &x, int &y);
	unsigned int conteudo(int x, int y);
	unsigned int conteudo32(int x, int y);
	int sprite32(int x, int y);
	void addTorre(int x, int y);
	void removeTorre(int x, int y);
	void construir(int x, int y, int sprite, int id);
	void save();
	void load();
	void load(std::string nome);
	void finalizar();
};

#endif