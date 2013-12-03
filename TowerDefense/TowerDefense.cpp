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
	if(btnRetry->getEstado() == SOLTO)
		return new TowerDefense(mapaTD.getNome().c_str());
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
		//wave 1
		if(timer == 60*8)
			formation1();
		if(timer == 60*9)
		    formation1();
	    if(timer == 60*10)
		    formation1();
     	if(timer == 60*11)
		    formation1();
		if(timer == 60*12)
			formation1();
		if(timer == 60*13)
		    formation1();
	    if(timer == 60*14)
		    formation1();
     	if(timer == 60*15)
		    formation1();
		if(timer == 60*16)
			formation1();
		if(timer == 60*17)
		    formation1();
	    if(timer == 60*18)
		    formation1();
     	if(timer == 60*19)
		    formation1();
		if(timer == 60*20)
			formation1();
		if(timer == 60*21)
		    formation1();
	    if(timer == 60*22)
		    formation1();
     	if(timer == 60*23)
		    formation1();
		//wave 1

		//wave 2
		if(timer == 60*30)
			formation1();
		if(timer == 60*31)
		    formation1();
	    if(timer == 60*32)
		    formation1();
     	if(timer == 60*33)
		    formation1();
		if(timer == 60*34)
			formation1();
		if(timer == 60*35)
		    formation1();
		if(timer == 60*36)
			formation2();
		if(timer == 60*37)
			formation2();
		if(timer == 60*39)
			formation2();
		if(timer == 60*41)
			formation2();
		if(timer == 60*43)
			formation2();
		if(timer == 60*45)
			formation2();
		if(timer == 60*47)
			formation2();
		if(timer == 60*49)
			formation2();
		if(timer == 60*51)
			formation2();
		if(timer == 60*53)
			formation2();
		if(timer == 60*55)
			formation2();
		//wave 2

		//wave 3
		if(timer == 60*60)
			formation1();
		if(timer == 60*61)
		    formation1();
	    if(timer == 60*62)
		    formation1();
     	if(timer == 60*63)
		    formation1();
		if(timer == 60*64)
			formation1();
		if(timer == 60*65)
		    formation1();
		if(timer == 60*66)
			formation2();
		if(timer == 60*67)
			formation2();
		if(timer == 60*69)
			formation2();
		if(timer == 60*71)
			formation2();
		if(timer == 60*73)
			formation2();
		if(timer == 60*75)
			formation2();
		if(timer == 60*77)
			formation2();
		if(timer == 60*79)
			formation2();
		if(timer == 60*81)
			formation2();
		if(timer == 60*83)
			formation2();
		if(timer == 60*85)
			formation2();
		if(timer == 60*88)
			formation3();
		if(timer == 60*91)
			formation3();
		if(timer == 60*94)
			formation3();
		if(timer == 60*97)
			formation3();
		if(timer == 60*100)
			formation3();
		if(timer == 60*103)
			formation3();
		if(timer == 60*106)
			formation3();
		if(timer == 60*109)
			formation3();
		if(timer == 60*112)
			formation3();
		if(timer == 60*115)
			formation3();
		//wave 3

		//wave 4
		if(timer == 60*120)
			formation1();
		if(timer == 60*121)
		    formation1();
	    if(timer == 60*123)
		    formation1();
     	if(timer == 60*124)
		    formation1();
		if(timer == 60*125)
			formation1();
		if(timer == 60*126)
		    formation1();
		if(timer == 60*127)
			formation2();
		if(timer == 60*129)
			formation2();
		if(timer == 60*131)
			formation2();
		if(timer == 60*133)
			formation2();
		if(timer == 60*135)
			formation2();
		if(timer == 60*137)
			formation2();
		if(timer == 60*139)
			formation2();
		if(timer == 60*141)
			formation2();
		if(timer == 60*143)
			formation2();
		if(timer == 60*145)
			formation2();
		if(timer == 60*148)
			formation3();
		if(timer == 60*151)
			formation3();
		if(timer == 60*154)
			formation3();
		if(timer == 60*157)
			formation3();
		if(timer == 60*160)
			formation3();
		if(timer == 60*163)
			formation3();
		if(timer == 60*166)
			formation3();
		if(timer == 60*169)
			formation3();
		if(timer == 60*172)
			formation3();
		if(timer == 60*175)
			formation3();
		if(timer == 60*179)
			formation4();
		if(timer == 60*183)
			formation4();
		if(timer == 60*187)
			formation4();
		if(timer == 60*191)
			formation4();
		if(timer == 60*195)
			formation4();
		if(timer == 60*199)
			formation4();
		if(timer == 60*203)
			formation4();
		if(timer == 60*207)
			formation4();
		if(timer == 60*201)
			formation4();
		if(timer == 60*205)
			formation4();
		if(timer == 60*209)
			formation4();
		//wave 4

		//wave 5
		if(timer == 60*220)
			formation1();
		if(timer == 60*221)
		    formation1();
	    if(timer == 60*223)
		    formation1();
     	if(timer == 60*224)
		    formation1();
		if(timer == 60*225)
			formation1();
		if(timer == 60*226)
		    formation1();
		if(timer == 60*227)
			formation2();
		if(timer == 60*229)
			formation2();
		if(timer == 60*231)
			formation2();
		if(timer == 60*233)
			formation2();
		if(timer == 60*235)
			formation2();
		if(timer == 60*237)
			formation2();
		if(timer == 60*239)
			formation2();
		if(timer == 60*241)
			formation2();
		if(timer == 60*243)
			formation2();
		if(timer == 60*245)
			formation2();
		if(timer == 60*248)
			formation3();
		if(timer == 60*251)
			formation3();
		if(timer == 60*254)
			formation3();
		if(timer == 60*257)
			formation3();
		if(timer == 60*260)
			formation3();
		if(timer == 60*263)
			formation3();
		if(timer == 60*266)
			formation3();
		if(timer == 60*269)
			formation3();
		if(timer == 60*272)
			formation3();
		if(timer == 60*275)
			formation3();
		if(timer == 60*279)
			formation4();
		if(timer == 60*283)
			formation4();
		if(timer == 60*287)
			formation4();
		if(timer == 60*291)
			formation4();
		if(timer == 60*295)
			formation4();
		if(timer == 60*299)
			formation4();
		if(timer == 60*303)
			formation4();
		if(timer == 60*307)
			formation4();
		if(timer == 60*301)
			formation4();
		if(timer == 60*305)
			formation4();
		if(timer == 60*309)
			formation4();
		if(timer == 60*313)
			formation5();
		if(timer == 60*317)
			formation5();
		if(timer == 60*321)
			formation5();
		if(timer == 60*325)
			formation5();
		if(timer == 60*329)
			formation5();
		if(timer == 60*333)
			formation5();
		if(timer == 60*337)
			formation5();
		if(timer == 60*341)
			formation5();
		if(timer == 60*344)
			formation5();
		if(timer == 60*347)
			formation5();
		if(timer == 60*351)
			formation5();
		if(timer == 60*354)
			formation5();
		if(timer == 60*359)
			formation5();
		//wave 5
		
		//wave boss
		if(timer == 60*370)
			formation1();
		if(timer == 60*371)
		    formation1();
	    if(timer == 60*373)
		    formation1();
     	if(timer == 60*374)
		    formation1();
		if(timer == 60*375)
			formation1();
		if(timer == 60*376)
		    formation1();
		if(timer == 60*377)
			formation2();
		if(timer == 60*379)
			formation2();
		if(timer == 60*381)
			formation2();
		if(timer == 60*383)
			formation2();
		if(timer == 60*385)
			formation2();
		if(timer == 60*387)
			formation2();
		if(timer == 60*389)
			formation2();
		if(timer == 60*391)
			formation2();
		if(timer == 60*393)
			formation2();
		if(timer == 60*395)
			formation2();
		if(timer == 60*398)
			formation3();
		if(timer == 60*401)
			formation3();
		if(timer == 60*404)
			formation3();
		if(timer == 60*407)
			formation3();
		if(timer == 60*410)
			formation3();
		if(timer == 60*413)
			formation3();
		if(timer == 60*416)
			formation3();
		if(timer == 60*419)
			formation3();
		if(timer == 60*422)
			formation3();
		if(timer == 60*425)
			formation3();
		if(timer == 60*429)
			formation4();
		if(timer == 60*433)
			formation4();
		if(timer == 60*437)
			formation4();
		if(timer == 60*441)
			formation4();
		if(timer == 60*445)
			formation4();
		if(timer == 60*449)
			formation4();
		if(timer == 60*453)
			formation4();
		if(timer == 60*457)
			formation4();
		if(timer == 60*461)
			formation4();
		if(timer == 60*465)
			formation4();
		if(timer == 60*469)
			formation4();
		if(timer == 60*473)
			formation5();
		if(timer == 60*477)
			formation5();
		if(timer == 60*481)
			formation5();
		if(timer == 60*485)
			formation5();
		if(timer == 60*489)
			formation5();
		if(timer == 60*493)
			formation5();
		if(timer == 60*497)
			formation5();
		if(timer == 60*501)
			formation5();
		if(timer == 60*504)
			formation5();
		if(timer == 60*507)
			formation5();
		if(timer == 60*511)
			formation5();
		if(timer == 60*514)
			formation5();
		if(timer == 60*519)
			formation5();
		if(timer == 60*525)
			queen();
		//wave boss

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
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 0, 0, 1, 100, 10, this));
}

void TowerDefense::formation2()
{
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 0, 8, 1, 250, 15, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 0, -8, 1, 250, 15, this));
}

void TowerDefense::formation3()
{
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 15, 0, 1, 450, 20, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 0, 8, 1, 450, 20, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 0, -8, 1, 450, 20, this));
}

void TowerDefense::formation4()
{
    gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 0, 0, 1, 600, 25, this));
    gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 30, 0, 1, 600, 25, this));
    gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 15, 8, 1, 600, 25, this));
    gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 15, -8, 1, 600, 25, this));
}

void TowerDefense::formation5()
{
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 0, 8, 1, 720, 30, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 0, -8, 1, 720, 30, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 15, 8, 1, 720, 30, this));
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 15, -8, 1, 720, 30, this));
}

void TowerDefense::queen()
{
	gAtor.adicionar(new InimigoExemplo(gAtor, mapaTD, 0, 0, 1, 10500, 0, this));
}