#include "globalDef.h"
#include "MapEditor.h"
#include "TowerDefense.h"
#include "MenuInicial.h"

#include <stdio.h>

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

Tela* MapEditor::proximaTela()
{
	C2D2_Botao* teclas = C2D2_PegaTeclas();

	if (teclas[C2D2_ENCERRA].pressionado || btnExit->getEstado() == SOLTO)
		return nullptr;	
	if (teclas[C2D2_R].pressionado)
		return new MapEditor();
	if (teclas[C2D2_M].pressionado || btnTD->getEstado() == SOLTO)
		return new TowerDefense();
	if(btnBack->getEstado() == SOLTO)
		return new MenuInicial();
	return this;
}

void MapEditor::inicializar()
{
	C2D2_TrocaCorLimpezaTela(25, 25, 25);
	mapSprite = C2D2_CarregaSpriteSet("imgs/map.png", 32, 32);
	mouseSprite = C2D2_CarregaSpriteSet("imgs/mouse.png", 0, 0);
	tahoma32 = C2D2_CarregaFonte("imgs/tahoma32.bmp", 32);
	tahoma16 = C2D2_CarregaFonte("imgs/tahoma16.bmp", 16);
	tahoma16r = C2D2_CarregaFonte("imgs/tahoma16r.bmp", 16);

	mapaTD = Mapa();
	mapaTD.inicializar();
	qtdTiles = 3;
	id = 0;
	tile = 0;

	menus.push_back(btnTD = new MenuButton("TowerDefense", 700, 490, tahoma16));
	menus.push_back(btnBack = new MenuButton("Menu Inicial", 700, 530, tahoma16));
	menus.push_back(btnExit = new MenuButton("Sair", 700, 570, tahoma16));
}

void MapEditor::atualizar()
{
	C2D2_Mouse* m = C2D2_PegaMouse();
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	mouseX = m->x;
	mouseY = m->y;

	if(teclas[C2D2_S].pressionado)
		mapaTD.save();
	if(teclas[C2D2_D].pressionado)
		mapaTD.load();
	if(teclas[C2D2_N].pressionado){
		mapaTD = Mapa();
	}
	if(teclas[C2D2_0].pressionado)
		id = 0;
	if(teclas[C2D2_1].pressionado)
		id = 1;
	if(teclas[C2D2_2].pressionado)
		id = 2;
	if(teclas[C2D2_3].pressionado)
		id = 3;
	if(teclas[C2D2_4].pressionado)
		id = 4;
	if(m->botoes[C2D2_MESQUERDO].ativo && mouseX > 575){
		for(int j = 0; j < qtdTiles; j++){
			if(C2D2_ColidiuSprites(mouseSprite, 0, mouseX, mouseY, mapSprite, j, 625+j%2*75, 100+j/2*48)){
				tile = j;
			}
		}
	}

	if(m->botoes[C2D2_MESQUERDO].ativo && mouseX < 576 && mouseY < 576){
		mapaTD.construir(mouseX, mouseY, tile, id);
	}
	if(m->botoes[C2D2_MDIREITO].ativo && mouseX < 576 && mouseY < 576){
		mapaTD.construir(mouseX, mouseY, 0, 0);
	}
	for(Menu* menu : menus){
		menu->atualizar();
	}
}

void MapEditor::desenhar()
{
	char txttile[50];
	sprintf_s(txttile, "Tile:%d\tId:%d\t(%d,%d)\t(%d,%d)[%d]", tile, id, mouseX, mouseY, mouseX < 576 && mouseY < 576 ? mouseX/32 : 0, mouseY < 576 && mouseX < 576 ? mouseY/32 : 0, mouseY < 576 && mouseX < 576 ? mapaTD.conteudo(mouseX, mouseY) : 0);
	
	C2D2P_Linha(577, 0, 577, 577, 255, 255, 255);
	C2D2P_Linha(0, 577, 577, 577, 255, 255, 255);

	mapaTD.desenhar();

	for(int j = 0; j < qtdTiles; j++)
		C2D2_DesenhaSprite(mapSprite, j, 625+j%2*75, 100+j/2*48);
	C2D2P_Retangulo(625+tile % 2 * 75, 100 + tile / 2 * 48, 658+tile % 2 * 75, 133 + tile / 2 * 48, 0, 255, 0);
	if(mouseX < 576 && mouseY < 576){
		C2D2P_Retangulo((16+mouseX-mouseX%32)-16, (16+mouseY-mouseY%32)-16, (16+mouseX-mouseX%32)+16, (16+mouseY-mouseY%32)+16, 0, 255, 0);
	}
	int ytxt = 15;
	C2D2_DesenhaTexto(tahoma32, 600, 32, "Map Editor", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 32, 580, txttile, C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 600, ytxt++*20, "Mouse Esquerdo - Coloca tile", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 600, ytxt++*20, "Mouse Direiro - Remove Tile", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 600, ytxt++*20, "0-4 - Muda id", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 600, ytxt++*20, "S - Salvar mapa", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 600, ytxt++*20, "D - Carregar mapa", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 600, ytxt++*20, "N - Novo mapa", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 600, ytxt++*20, "R - Reset", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(tahoma16, 600, ytxt++*20, "M - Retorna ao TD", C2D2_TEXTO_ESQUERDA);
	for(Menu* menu : menus){
		menu->desenhar();
	}
	for(int x = 0; x < 18; x++){
		for(int y = 0; y < 18; y++){
			char c[5];
			sprintf_s(c, "%d", mapaTD.conteudo32(x, y));
			C2D2_DesenhaTexto(tahoma16r, x*32+16, y*32+8, c, C2D2_TEXTO_CENTRALIZADO);
		}
	}
	C2D2_DesenhaSprite(mouseSprite, 0, mouseX, mouseY);
}

void MapEditor::finalizar()
{
	for(Menu* menu : menus){
		delete menu;
	}
	C2D2_RemoveSpriteSet(mapSprite);
	C2D2_RemoveSpriteSet(mouseSprite);
	C2D2_RemoveFonte(tahoma16);
	C2D2_RemoveFonte(tahoma32);
	C2D2_RemoveFonte(tahoma16r);
}
