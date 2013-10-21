#pragma once

class Tela;

class GameLoop
{
	private:
		Tela *tela;
	public:
		GameLoop(Tela * telaInicial);
		bool executar(char* titulo, int largura=800, int altura=600, bool primitivas=false, bool janela=true);	
		~GameLoop();
};

