#include "globalDef.h"

#include "TowerDefense.h"
#include "MapEditor.h"
#include "MenuInicial.h"

#include "TorreExemplo.h"
#include "Torre2.h"
#include "InimigoExemplo.h"

#include <stdio.h>

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

TowerDefense::TowerDefense()
	: mapaTD()
{
	mapaTD.load("Default");
}

TowerDefense::TowerDefense(const char* _map )
	: mapaTD()
{
	mapaTD.load(_map);
}

Tela* TowerDefense::proximaTela(){
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	
	if (teclas[C2D2_ENCERRA].pressionado || btnExit->getEstado() == SOLTO)
		return nullptr;	
	if(btnBack->getEstado() == SOLTO)
		return new MenuInicial();
	if (teclas[C2D2_R].pressionado && estado != PAUSE)
		return new TowerDefense();
#ifdef DEBUG
	if ((teclas[C2D2_M].pressionado && estado != PAUSE) || btnME->getEstado() == SOLTO)
		return new MapEditor();
#endif
	return this;
}

void TowerDefense::inicializar(){
	C2D2_TrocaCorLimpezaTela(25, 25, 25);
	estado = PLAY;
	mouseSprite = C2D2_CarregaSpriteSet("imgs/mouse.png", 0, 0);
	tahoma16 = C2D2_CarregaFonte("imgs/tahoma16.bmp", 16);
	tahoma32 = C2D2_CarregaFonte("imgs/tahoma32.bmp", 32);
	eheart = C2D2_CarregaSpriteSet("imgs/eheart.png", 0, 0);
	heart = C2D2_CarregaSpriteSet("imgs/heart.png", 16, 16);
	tIndice = 0;
	chances = 20;
	mapaTD.inicializar();

#ifdef LOG
	if(mouseSprite == 0)
		addToLog("Falha ao carregar sprite do mouse!(TowerDefense.cpp)");
	if(tahoma16 == 0)
		addToLog("Falha ao carregar a fonte Tahoma de tamanho 16!(TowerDefense.cpp)");
	if(tahoma32 == 0)
		addToLog("Falha ao carregar a fonte Tahoma de tamanho 32!(TowerDefense.cpp)");
	if(eheart == 0)
		addToLog("Falha ao carregar o sprite eheart!(TowerDefense.cpp)");
	if(heart == 0)
		addToLog("Falha ao carregar o sprite heart!(TowerDefense.cpp)");
#endif
	
#ifdef DEBUG
	menus.push_back(btnME = new MenuButton("MapEditor", 700, 460, tahoma16));
#endif
	menus.push_back(btnPause = new MenuButton("Pausa", 700, 480, tahoma16));
	menus.push_back(btnBack = new MenuButton("Menu Inicial", 700, 500, tahoma16));
	menus.push_back(btnExit = new MenuButton("Sair", 700, 520, tahoma16));
}

void TowerDefense::atualizar(){
	C2D2_Mouse* m = C2D2_PegaMouse();
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	mouseX = m->x;
	mouseY = m->y;

	estado = teclas[C2D2_P].pressionado || teclas[C2D2_ESC].pressionado || btnPause->getEstado() == SOLTO ? estado == PLAY ? PAUSE : PLAY : estado;
	for(Menu* menu : menus){
		menu->atualizar();
	}
	switch (estado)
	{
	case PLAY:
		m->botoes[C2D2_MMEIO].pressionado ? tIndice == 3 ? tIndice = 0 : tIndice++ : 0;

		if(m->botoes[C2D2_MESQUERDO].ativo && mouseX < 576 && mouseY < 576 && mapaTD.conteudo(mouseX, mouseY) == 0){
			mapaTD.construir(mouseX, mouseY);
			if(tIndice != 3)
				gAtor.adicionar(new Torre2(gAtor, mouseX, mouseY, tIndice));
			else
				gAtor.adicionar(new TorreExemplo(gAtor, mouseX, mouseY));

		}

#ifdef DEBUG
		if(m->botoes[C2D2_MDIREITO].pressionado)
			gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -16, 304, 1, 50));

		if(teclas[C2D2_Z].pressionado)
			chances--;
		if(teclas[C2D2_X].pressionado)
			chances++;

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
			mapaTD.load();
#endif

		gAtor.atualizar();
		break;
	case PAUSE:
		break;
	}

}

void TowerDefense::desenhar(){
	int ytxt = 5;

	C2D2_DesenhaTexto(tahoma32, 580, 16, "Tower Defense", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 580, ytxt++*20, "Mouse Esquerdo - Coloca Torre", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 580, ytxt++*20, "Mouse meio - Muda torre", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 580, ytxt++*20, "P/ESC - Pausa/Despausa", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 580, ytxt++*20, "R - Reset", C2D2_TEXTO_ESQUERDA);

#ifdef DEBUG
	char txt[50];
	sprintf_s(txt, "indiceTorre:%d\t(%d,%d)\t(%d,%d)[%d]\tChances: %d", tIndice, mouseX, mouseY, mouseX < 576 && mouseY < 576 ? mouseX/32 : 0, mouseY < 576 && mouseX < 576 ? mouseY/32 : 0, mouseY < 576 && mouseX < 576 ? mapaTD.conteudo(mouseX, mouseY) : 0, chances);
	C2D2_DesenhaTexto(tahoma16, 32, 580, txt, C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 580, ytxt++*20, "Mouse Direito - Cria Inimigo", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 580, ytxt++*20, "M - Map Editor", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 580, ytxt++*20, "D - Carrega mapa", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 580, ytxt++*20, "0-9 - Cria waves de inimigo", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 580, ytxt++*20, "X - Aumenta chances", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 580, ytxt++*20, "Z - Diminui chances", C2D2_TEXTO_ESQUERDA);
#endif

	C2D2P_Linha(577, 0, 577, 577, 255, 255, 255);
	C2D2P_Linha(0, 577, 577, 577, 255, 255, 255);
	mapaTD.desenhar();
	gAtor.desenhar();

	int i;
	C2D2_DesenhaSprite(eheart, 0, 400, 580);
	for(i = 0; i < (int)(chances/2); i++){
		C2D2_DesenhaSprite(heart, 0, 400+i*16, 580);
	}
	if(chances % 2 == 1){
		C2D2_DesenhaSprite(heart, 1, 400+i*16, 580);
	}
	switch (estado)
	{
	case PLAY:
		if(mouseX < 576 && mouseY < 576 && mapaTD.conteudo(mouseX, mouseY) == 0){
			C2D2P_Retangulo((16+mouseX-mouseX%32)-16, (16+mouseY-mouseY%32)-16, (16+mouseX-mouseX%32)+16, (16+mouseY-mouseY%32)+16, 0, 155, 0);
		}
		break;
	case PAUSE:
		C2D2P_RetanguloPintadoAlfa(0, 0, 800, 600, 25, 25, 25, 200);
		C2D2_DesenhaTexto(tahoma32, 400-32, 150, "PAUSE", C2D2_TEXTO_CENTRALIZADO);
		break;
	}

	for(Menu* menu : menus){
		menu->desenhar();
	}
	C2D2_DesenhaSprite(mouseSprite, 0, mouseX, mouseY);
}

#pragma region waves
void TowerDefense::wave(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 304, 1, 50));
}

void TowerDefense::wave2(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 312, 1, 50));
}

void TowerDefense::wave3(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 312, 1, 50));
}

void TowerDefense::wave4(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 312, 1, 50));
}

void TowerDefense::wave5(){ 
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 312, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -294, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -364, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -434, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 312, 1, 50));
}

void TowerDefense::wave6(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -294, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -364, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -434, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -504, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -574, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -644, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -714, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50));
}

void TowerDefense::wave7(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -14, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -84, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -154, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -224, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -294, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -364, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -434, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -504, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -574, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 312, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -654, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -670, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -670, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -686, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -724, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -740, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -740, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -756, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -794, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -810, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -810, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -826, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -864, 304, 1, 50)); 
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -880, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -880, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -896, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -934, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -950, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -950, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -966, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1004, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1020, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1020, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1036, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1074, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1090, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1090, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1106, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1144, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1160, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1160, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1176, 304, 1, 50));
}

void TowerDefense::wave8(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -14, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -46, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -104, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -120, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -120, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -136, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -174, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -190, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -190, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -206, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -244, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -260, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -260, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -276, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -314, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -330, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -330, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -346, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -384, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -400, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -400, 312, 1, 50)); 
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -416, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -454, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -470, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -470, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -486, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -524, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -540, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -540, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -556, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -594, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -610, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -610, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -626, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -664, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -680, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -680, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -696, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -734, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -750, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -750, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -766, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -804, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -820, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -820, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -836, 304, 1, 50));
}

void TowerDefense::wave9(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -870, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -870, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -940, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -940, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1010, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1010, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1064, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1080, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1080, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1134, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1150, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1150, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1204, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1220, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1220, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1274, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1290, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1290, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1344, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1360, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1360, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1414, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1430, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1430, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1484, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1500, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1500, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1516, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1554, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1570, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1570, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1586, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1624, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1640, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1640, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1656, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1694, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1710, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1710, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1726, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1764, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1780, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1780, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1796, 304, 1, 50));
}

void TowerDefense::waveBoss(){ // simples, duplas, triplas, quadruplas, quadruplas blocos, simples em fila, boss lento mas com MUITA vida
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -870, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -870, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -940, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -940, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1010, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1010, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1064, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1080, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1080, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1134, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1150, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1150, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1204, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1220, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1220, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1274, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1290, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1290, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1344, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1360, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1360, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1414, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1430, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1430, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1484, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1500, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1500, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1516, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1554, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1570, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1570, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1586, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1624, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1640, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1640, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1656, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1694, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1710, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1710, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1726, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1764, 304, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1780, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1780, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1796, 304, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1850, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1850, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1866, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1866, 312, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1936, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1936, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1952, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1952, 312, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2022, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2022, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2038, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2038, 312, 1, 50));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2108, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2108, 312, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2124, 296, 1, 50));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2124, 312, 1, 50));
}

#pragma endregion

void TowerDefense::finalizar(){
	for(Menu* menu : menus){
		delete menu;
	}
	C2D2_RemoveSpriteSet(mouseSprite);
	C2D2_RemoveSpriteSet(eheart);
	C2D2_RemoveSpriteSet(heart);
	C2D2_RemoveFonte(tahoma16);
	C2D2_RemoveFonte(tahoma32);
}
