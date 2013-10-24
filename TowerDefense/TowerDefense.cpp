#include "globalDef.h"
#include "TowerDefense.h"
#include "MapEditor.h"

#include "TorreExemplo.h"
#include "Torre2.h"
#include "InimigoExemplo.h"

#include <stdio.h>

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

Tela* TowerDefense::proximaTela(){
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	
	if (teclas[C2D2_ENCERRA].pressionado || teclas[C2D2_ESC].pressionado)
		return nullptr;	
	if (teclas[C2D2_R].pressionado)
		return new TowerDefense();
#ifdef DEBUG
	if (teclas[C2D2_M].pressionado)
		return new MapEditor();
#endif
	return this;
}

void TowerDefense::inicializar(){
	C2D2_TrocaCorLimpezaTela(10, 10, 10);
	mouseSprite = C2D2_CarregaSpriteSet("imgs/mouse.png", 0, 0);
	OpenSymbol16 = C2D2_CarregaFonte("imgs/OpenSymbol16.bmp", 16);
	OpenSymbol32 = C2D2_CarregaFonte("imgs/OpenSymbol32.bmp", 32);
#ifdef LOG
	if(mouseSprite == 0)
		addToLog("Falha ao carregar sprite do mouse!(TowerDefense.cpp)");
	if(OpenSymbol16 == 0)
		addToLog("Falha ao carregar a fonte OpenSymbol de tamanho 16!(TowerDefense.cpp)");
	if(OpenSymbol32 == 0)
		addToLog("Falha ao carregar a fonte OpenSymbol de tamanho 32!(TowerDefense.cpp)");
#endif
	mapa = Mapa();
	mapa.inicializar();
	tIndice = 0;
}

void TowerDefense::atualizar(){
	C2D2_Mouse* m = C2D2_PegaMouse();
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	mouseX = m->x;
	mouseY = m->y;

	if (teclas[C2D2_1].pressionado) {
		tIndice = 0;
	}
	if (teclas[C2D2_2].pressionado) {
		tIndice = 1;
	}
	if (teclas[C2D2_3].pressionado) {
		tIndice = 2;
	}
	if (teclas[C2D2_4].pressionado) {
		tIndice = 3;
	}
	if(m->botoes[C2D2_MESQUERDO].ativo && mouseX < 576 && mouseY < 576 && mapa.conteudo(mouseX, mouseY) == 0){
		mapa.construir(mouseX, mouseY);
		if(tIndice != 3)
			gAtor.adicionar(new Torre2(gAtor, mouseX, mouseY, tIndice));
		else
			gAtor.adicionar(new TorreExemplo(gAtor, mouseX, mouseY));
	
	}
#ifdef DEBUG
	if(m->botoes[C2D2_MDIREITO].pressionado)
		gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -16, 304, 1));
	if(teclas[C2D2_D].pressionado)
		mapa.load();
#endif
	gAtor.atualizar();

}
void TowerDefense::desenhar(){
#ifdef DEBUG
	char txt[50];
	sprintf(txt, "iTorre:%d\t(%d,%d)\t(%d,%d)[%d]", tIndice, mouseX, mouseY, mouseX < 576 && mouseY < 576 ? mouseX/32 : 0, mouseY < 576 && mouseX < 576 ? mouseY/32 : 0, mouseY < 576 && mouseX < 576 ? mapa.conteudo(mouseX, mouseY) : 0);
	C2D2_DesenhaTexto(OpenSymbol16, 32, 580, txt, C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 580, 140, "Mouse Direito - Cria Inimigo", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 580, 200, "M - Map Editor", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 580, 220, "D - Carrega mapa", C2D2_TEXTO_ESQUERDA);
#endif

	C2D2P_Linha(577, 0, 577, 577, 255, 255, 255);
	C2D2P_Linha(0, 577, 577, 577, 255, 255, 255);
	mapa.desenhar();
	if(mouseX < 576 && mouseY < 576 && mapa.conteudo(mouseX, mouseY) == 0){
		C2D2P_Retangulo((16+mouseX-mouseX%32)-16, (16+mouseY-mouseY%32)-16, (16+mouseX-mouseX%32)+16, (16+mouseY-mouseY%32)+16, 0, 155, 0);
	}
	gAtor.desenhar();

	C2D2_DesenhaTexto(OpenSymbol32, 580, 16, "Tower Defense", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 580, 120, "Mouse Esquerdo - Coloca Torre", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 580, 160, "1-4 - Muda torre", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 580, 180, "R - Reset", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaSprite(mouseSprite, 0, mouseX, mouseY);
}

void TowerDefense::finalizar(){
	C2D2_RemoveSpriteSet(mouseSprite);
	C2D2_RemoveFonte(OpenSymbol16);
	C2D2_RemoveFonte(OpenSymbol32);
}