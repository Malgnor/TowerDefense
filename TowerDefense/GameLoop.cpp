#include "globalDef.h"

#include "GameLoop.h"

#include "Tela.h"
#include "GerenteTela.h"

#include <time.h>

#include <c2d2\chien2d2.h>
#include <c2d2\chienaudio2.h>
#include <c2d2\chien2d2primitivas.h>

GameLoop::GameLoop(Tela* telaInicial)
	: tela(telaInicial)
{
}

bool GameLoop::executar(char* titulo, int largura, int altura, bool primitivas, bool janela)
{
	if (!C2D2_Inicia(largura, altura, 
		janela ? C2D2_JANELA : C2D2_TELA_CHEIA, 
		C2D2_DESENHO_OPENGL, titulo)){
#ifdef LOG
			addToLog("Chien2d2 falhou!(GameLoop.cpp)");
#endif 
		return false;
	}

#ifdef LOG
	addToLog("Chien2D2 Iniciado!(GameLoop.cpp)\nTime", time(0));
#endif

	if (!CA2_Inicia()){
#ifdef LOG
		addToLog("Chien2d2 Audio falhou!(GameLoop.cpp)");
#endif 
		return false;
	}

	if(primitivas){
		if(C2D2P_Inicia()){
#ifdef LOG
			addToLog("Chien2d2 Primitivas falhou!(GameLoop.cpp)");
#endif 
			return false;
		}
	}

	GerenteTela gerente(tela);	
	while (!gerente.jogoAcabou())
	{
		gerente.atualizar();
		C2D2_LimpaTela();
		gerente.desenhar();
		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	}	

	CA2_Encerra();
	C2D2_Encerra();
#ifdef LOG
	addToLog("Chien2D2 Encerrado!(GameLoop.cpp)\nTime", time(0));
	addToLog("");
#endif
	return true;
}

GameLoop::~GameLoop()
{	
}