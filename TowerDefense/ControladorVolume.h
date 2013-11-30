#ifndef _CONTROLADORVOLUME_H_
#define _CONTROLADORVOLUME_H_

class ControladorVolume
{
private:
	static unsigned int efeitos, musica;
	int posX, posY;	
	int sprEfeito, sprMusica;
	int indEfeito, indMusica;
	int fonte;
	
public:
	ControladorVolume();
	ControladorVolume(int _x, int _y);

	void inicializar();		
	void atualizar();
	void desenhar();
	void finalizar();

	static unsigned int volumeEfeitos();
	static unsigned int volumeMusica();
};
#endif