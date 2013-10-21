#ifndef _MAPA_H_
#define _MAPA_H_

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
	void construir(int x, int y);
	void construir(int x, int y, int sprite, int id);
	void save();
	void load();
	void finalizar();
};

#endif