#ifndef _MAPA_H_
#define _MAPA_H_

#include <string>

class Mapa
{
private:
	char map[18][18];
	int sprite;

public:
	Mapa();
	void inicializar();
	void desenhar();
	char conteudo(int x, int y);
	char conteudo32(int x, int y);
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