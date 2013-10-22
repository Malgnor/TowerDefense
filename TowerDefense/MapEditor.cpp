#include "MapEditor.h"
#include "TowerDefense.h"

#include <stdio.h>

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

Tela* MapEditor::proximaTela()
{
	C2D2_Botao* teclas = C2D2_PegaTeclas();

	if (teclas[C2D2_ENCERRA].pressionado || teclas[C2D2_ESC].pressionado)
		return nullptr;	
	if (teclas[C2D2_R].pressionado)
		return new MapEditor();
	if (teclas[C2D2_M].pressionado)
		return new TowerDefense();
	return this;
}

void MapEditor::inicializar()
{
	mapSprite = C2D2_CarregaSpriteSet("imgs/map.png", 32, 32);
	mouseSprite = C2D2_CarregaSpriteSet("imgs/mouse.png", 0, 0);
	OpenSymbol32 = C2D2_CarregaFonte("imgs/OpenSymbol32.bmp", 32);
	OpenSymbol16 = C2D2_CarregaFonte("imgs/OpenSymbol16.bmp", 16);
	mapa = Mapa();
	mapa.inicializar();
	id = 0;
	tile = 0;
}

void MapEditor::atualizar()
{
	C2D2_Mouse* m = C2D2_PegaMouse();
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	mouseX = m->x;
	mouseY = m->y;

	if(teclas[C2D2_S].pressionado)
		mapa.save();
	if(teclas[C2D2_D].pressionado)
		mapa.load();
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
	if(teclas[C2D2_5].pressionado)
		id = 5;
	if(teclas[C2D2_6].pressionado)
		id = 6;
	if(teclas[C2D2_7].pressionado)
		id = 7;
	if(teclas[C2D2_8].pressionado)
		id = 8;
	if(teclas[C2D2_9].pressionado)
		id = 9;
	if(m->botoes[C2D2_MESQUERDO].ativo && mouseX > 575){
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 2; j++){
				if(C2D2_ColidiuSprites(mouseSprite, 0, mouseX, mouseY, mapSprite, i*2+j, 625+j*75, 100+i*75)){
					tile = i*2+j;
				}
			}
		}
	}

	if(m->botoes[C2D2_MESQUERDO].ativo && mouseX < 576 && mouseY < 576){
		mapa.construir(mouseX, mouseY, tile, id);
	}
	if(m->botoes[C2D2_MDIREITO].ativo && mouseX < 576 && mouseY < 576){
		mapa.construir(mouseX, mouseY, -1, id);
	}
}

void MapEditor::desenhar()
{
	char txttile[50];
	sprintf(txttile, "Tile:%d\tId:%d\t(%d,%d)\t(%d,%d)", tile, id, mouseX, mouseY, mouseX < 576 && mouseY < 576 ? mouseX/32 : 0, mouseY < 576 && mouseX < 576 ? mouseY/32 : 0);
	C2D2P_Linha(577, 0, 577, 577, 255, 255, 255);
	C2D2P_Linha(0, 577, 577, 577, 255, 255, 255);
	mapa.desenhar();
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 2; j++)
			C2D2_DesenhaSprite(mapSprite, i*2+j, 625+j*75, 100+i*75);
	}
	if(mouseX < 576 && mouseY < 576){
		C2D2P_Retangulo((16+mouseX-mouseX%32)-16, (16+mouseY-mouseY%32)-16, (16+mouseX-mouseX%32)+16, (16+mouseY-mouseY%32)+16, 0, 255, 0);
	}
	C2D2_DesenhaTexto(OpenSymbol32, 600, 32, "Map Editor", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 32, 580, txttile, C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 450, "Mouse Esquerdo - Coloca tile", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 466, "Mouse Direiro - Remove Tile", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 482, "0-9 - Muda id", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 498, "S - Salvar mapa", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 514, "D - Carregar mapa", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 530, "R - Reset", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaSprite(mouseSprite, 0, mouseX, mouseY);
}

void MapEditor::finalizar()
{
	C2D2_RemoveSpriteSet(mapSprite);
	C2D2_RemoveSpriteSet(mouseSprite);
	C2D2_RemoveFonte(OpenSymbol16);
	C2D2_RemoveFonte(OpenSymbol32);
}
