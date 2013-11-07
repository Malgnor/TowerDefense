#include "globalDef.h"

#include "c2d2f.h"
#include "color.h"

#include "TowerDefense.h"
#include "MenuInicial.h"

#include "TorreExemplo.h"
#include "Torre2.h"
#include "InimigoExemplo.h"

#include <stdio.h>

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

#ifdef DEBUG
#include "MapEditor.h"
#endif

TowerDefense::TowerDefense()
{
	mapaTD.load("Default");
}

TowerDefense::TowerDefense(const char* _map)
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
	TDBase::inicializar();
#ifdef DEBUG
		menus.push_back(btnME = new MenuButton("MapEditor", 700, 460, tahoma16));
#endif
}

void TowerDefense::atualizar(){
	TDBase::atualizar();
	C2D2_Mouse* m = C2D2_PegaMouse();
	C2D2_Botao* teclas = C2D2_PegaTeclas();

	switch (estado)
	{
	case PLAY:
#ifdef DEBUG
		if(m->botoes[C2D2_MDIREITO].pressionado && teclas[C2D2_LSHIFT].ativo)
			gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -16, 304, 1, 50, 10, this));

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
		break;
	case PAUSE:
		break;
	case PAUSEF1:
		break;
	}

}

void TowerDefense::desenhar(){
	TDBase::desenhar();

	C2D2_DesenhaTexto(tahoma32, 600, 16, "Tower Defense", C2D2_TEXTO_ESQUERDA);

	switch (estado)
	{
	case PLAY:
		break;
	case PAUSE:
		break;
	case PAUSEF1:
		C2D2_DesenhaTexto(tahoma16, 300, 220, "R - Reset", C2D2_TEXTO_ESQUERDA);
#ifdef DEBUG
		char txt[99];
		int ytxt = 1;
		sprintf_s(txt, "(%d,%d) (%d,%d)[%d] Chances: %d Dinheiro: %d", mouseX, mouseY, mouseX < 576 && mouseY < 576 ? mouseX/32 : 0, mouseY < 576 && mouseX < 576 ? mouseY/32 : 0, mouseY < 576 && mouseX < 576 ? mapaTD.conteudo(mouseX, mouseY) : 0, chances, gold);
		C2D2_DesenhaTexto(tahoma16, 120, 580, txt, C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 300, 220+ytxt++*16, "Mouse Direito + Shift - Cria Inimigo", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 300, 220+ytxt++*16, "M - Map Editor", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 300, 220+ytxt++*16, "D - Carrega mapa", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 300, 220+ytxt++*16, "0-9 - Cria waves de inimigo", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 300, 220+ytxt++*16, "X - Aumenta chances", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 300, 220+ytxt++*16, "Z - Diminui chances", C2D2_TEXTO_ESQUERDA);
#endif
		break;
	}

	desenhaMouse();
}

#pragma region waves
void TowerDefense::wave(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 304, 1, 50, 10, this));
}

void TowerDefense::wave2(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 312, 1, 50, 10, this));
}

void TowerDefense::wave3(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 312, 1, 50, 10, this));
}

void TowerDefense::wave4(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 312, 1, 50, 10, this));
}

void TowerDefense::wave5(){ 
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 312, 1, 50, 10, this));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -294, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -364, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -434, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 312, 1, 50, 10, this));
}

void TowerDefense::wave6(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -294, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -364, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -434, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -504, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -574, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -644, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -714, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50, 10, this));
}

void TowerDefense::wave7(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -14, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -84, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -154, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -224, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -294, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -364, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -434, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -504, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -574, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 312, 1, 50, 10, this));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -654, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -670, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -670, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -686, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -724, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -740, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -740, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -756, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -794, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -810, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -810, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -826, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -864, 304, 1, 50, 10, this)); 
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -880, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -880, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -896, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -934, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -950, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -950, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -966, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1004, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1020, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1020, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1036, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1074, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1090, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1090, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1106, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1144, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1160, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1160, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1176, 304, 1, 50, 10, this));
}

void TowerDefense::wave8(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -14, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -46, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -104, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -120, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -120, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -136, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -174, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -190, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -190, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -206, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -244, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -260, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -260, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -276, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -314, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -330, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -330, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -346, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -384, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -400, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -400, 312, 1, 50, 10, this)); 
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -416, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -454, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -470, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -470, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -486, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -524, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -540, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -540, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -556, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -594, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -610, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -610, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -626, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -664, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -680, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -680, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -696, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -734, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -750, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -750, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -766, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -804, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -820, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -820, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -836, 304, 1, 50, 10, this));
}

void TowerDefense::wave9(){
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -870, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -870, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -940, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -940, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1010, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1010, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1064, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1080, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1080, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1134, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1150, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1150, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1204, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1220, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1220, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1274, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1290, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1290, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1344, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1360, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1360, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1414, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1430, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1430, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1484, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1500, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1500, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1516, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1554, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1570, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1570, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1586, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1624, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1640, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1640, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1656, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1694, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1710, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1710, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1726, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1764, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1780, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1780, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1796, 304, 1, 50, 10, this));
}

void TowerDefense::waveBoss(){ // simples, duplas, triplas, quadruplas, quadruplas blocos, simples em fila, boss lento mas com MUITA vida
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -100, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -170, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -240, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -310, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -380, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -450, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -520, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -590, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -660, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -730, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -800, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -870, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -870, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -940, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -940, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1010, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1010, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1064, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1080, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1080, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1134, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1150, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1150, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1204, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1220, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1220, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1274, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1290, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1290, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1344, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1360, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1360, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1414, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1430, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1430, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1484, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1500, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1500, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1516, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1554, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1570, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1570, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1586, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1624, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1640, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1640, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1656, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1694, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1710, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1710, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1726, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1764, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1780, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1780, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1796, 304, 1, 50, 10, this));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1850, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1850, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1866, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1866, 312, 1, 50, 10, this));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1936, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1936, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1952, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -1952, 312, 1, 50, 10, this));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2022, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2022, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2038, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2038, 312, 1, 50, 10, this));

	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2108, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2108, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2124, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -2124, 312, 1, 50, 10, this));
}

#pragma endregion

