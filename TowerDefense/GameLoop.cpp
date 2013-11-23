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
		return false;
	}
	
	if (!CA2_Inicia()){
		return false;
	}

	if(primitivas){
		if(C2D2P_Inicia()){
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
	return true;
}

GameLoop::~GameLoop()
{	
}