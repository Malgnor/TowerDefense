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
	timer = 0;
	TDBase::inicializar();
#ifdef DEBUG
		menus.push_back(btnME = new MenuButton("MapEditor", 700, 460, tahoma16));
#endif
}

void TowerDefense::atualizar(){
	TDBase::atualizar();
	timer++;
	C2D2_Mouse* m = C2D2_PegaMouse();
	C2D2_Botao* teclas = C2D2_PegaTeclas();

	switch (estado)
	{
	case PLAY:

		if(timer == 60*10)
			formation4();
		if(timer == 60*11)
		    formation1();
	    if(timer == 60*12)
		    formation1();
     	if(timer == 60*13)
		    formation1();

		if(timer == 60*60)
			formation4();
		if(timer == 60*120)
			formation4();
		if(timer == 60*180)
			formation4();
		if(timer == 60*240)
			formation4();
		if(timer == 60*300)
			formation4();
		if(timer == 60*360)
			formation4();
		if(timer == 60*420)
			formation4();
		if(timer == 60*480)
			formation4();
		if(timer == 60*540)
			formation4();

#ifdef DEBUG
		if(m->botoes[C2D2_MDIREITO].pressionado && teclas[C2D2_LSHIFT].ativo)
			gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -16, 304, 1, 50, 10, this));

		if(teclas[C2D2_Z].pressionado)
			chances--;
		if(teclas[C2D2_X].pressionado)
			chances++;

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


void TowerDefense::formation1()
{
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 15, 0, 1, 50, 10, this));
}

void TowerDefense::formation2()
{
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 312, 1, 50, 10, this));
}

void TowerDefense::formation3()
{
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 304, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -46, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -46, 312, 1, 50, 10, this));
}

void TowerDefense::formation4()
{
    gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 0, 0, 1, 50, 10, this));
    gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 30, 0, 1, 50, 10, this));
    gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 15, 8, 1, 50, 10, this));
    gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 15, -8, 1, 50, 10, this));
}

void TowerDefense::formation5()
{
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -30, 312, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -46, 296, 1, 50, 10, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, -46, 312, 1, 50, 10, this));
}