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
		gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -16, 304, 1, 50));

	if(teclas[C2D2_1].pressionado)
		wave();
	if(teclas[C2D2_2].pressionado)
		wave2();
	if(teclas[C2D2_3].pressionado)
		wave3();
	if(teclas[C2D2_4].pressionado)
		wave4();
	if(teclas[C2D2_5].pressionado)
		wave5();
	if(teclas[C2D2_6].pressionado)
		wave6();
	if(teclas[C2D2_7].pressionado)
		wave7();
	if(teclas[C2D2_8].pressionado)
		wave8();
	if(teclas[C2D2_9].pressionado)
		wave9();
	if(teclas[C2D2_0].pressionado)
		waveBoss();

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

void TowerDefense::wave(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -520, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -660, 304, 1, 50));
}

void TowerDefense::wave2(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -520, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -660, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -800, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -800, 312, 1, 50));
}

void TowerDefense::wave3(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -520, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -660, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -660, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -800, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -800, 312, 1, 50));
}

void TowerDefense::wave4(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -520, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -520, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -660, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -660, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -800, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -800, 312, 1, 50));
}

void TowerDefense::wave5(){ 
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 312, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -294, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -364, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -434, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 312, 1, 50));
}

void TowerDefense::wave6(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -100, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -100, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -294, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -364, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -434, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -504, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -520, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -520, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -574, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -644, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -660, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -660, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -714, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 312, 1, 50));
}

void TowerDefense::wave7(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -14, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -84, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -100, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -100, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -154, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -224, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -294, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -364, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -434, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -504, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -520, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -520, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -574, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 312, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -654, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -670, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -670, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -686, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -724, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -740, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -740, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -756, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -794, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -810, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -810, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -826, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -864, 304, 1, 50)); 
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -880, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -880, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -896, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -934, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -950, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -950, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -966, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1004, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1020, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1020, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1036, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1074, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1090, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1090, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1106, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1144, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1160, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1160, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1176, 304, 1, 50));
}

void TowerDefense::wave8(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -14, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -46, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -104, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -120, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -120, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -136, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -174, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -190, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -190, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -206, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -244, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -260, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -260, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -276, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -314, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -330, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -330, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -346, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -384, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -400, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -400, 312, 1, 50)); 
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -416, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -454, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -470, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -470, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -486, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -524, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -540, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -540, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -556, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -594, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -610, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -610, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -626, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -664, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -680, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -680, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -696, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -734, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -750, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -750, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -766, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -804, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -820, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -820, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -836, 304, 1, 50));
}

void TowerDefense::wave9(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -520, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -660, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -800, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -800, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -870, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -870, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -940, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -940, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1010, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1010, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1064, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1080, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1080, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1134, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1150, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1150, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1204, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1220, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1220, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1274, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1290, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1290, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1344, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1360, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1360, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1414, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1430, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1430, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1484, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1500, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1500, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1516, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1554, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1570, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1570, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1586, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1624, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1640, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1640, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1656, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1694, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1710, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1710, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1726, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1764, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1780, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1780, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1796, 304, 1, 50));
}

void TowerDefense::waveBoss(){ // simples, duplas, triplas, quadruplas, quadruplas blocos, simples em fila, boss lento mas com MUITA vida
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -170, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -240, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -310, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -380, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -450, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -520, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -590, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -660, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -730, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -800, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -800, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -870, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -870, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -940, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -940, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1010, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1010, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1064, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1080, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1080, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1134, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1150, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1150, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1204, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1220, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1220, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1274, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1290, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1290, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1344, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1360, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1360, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1414, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1430, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1430, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1484, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1500, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1500, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1516, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1554, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1570, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1570, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1586, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1624, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1640, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1640, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1656, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1694, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1710, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1710, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1726, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1764, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1780, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1780, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1796, 304, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1850, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1850, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1866, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1866, 312, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1936, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1936, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1952, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -1952, 312, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -2022, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -2022, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -2038, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -2038, 312, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -2108, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -2108, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -2124, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -2124, 312, 1, 50));
}

void TowerDefense::finalizar(){
	C2D2_RemoveSpriteSet(mouseSprite);
	C2D2_RemoveFonte(OpenSymbol16);
	C2D2_RemoveFonte(OpenSymbol32);
}