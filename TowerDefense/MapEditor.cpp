#include "globalDef.h"
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
#ifdef LOG
	if(mouseSprite == 0)
		addToLog("Falha ao carregar sprite do mouse!(MapEditor.cpp)");
	if(OpenSymbol16 == 0)
		addToLog("Falha ao carregar a fonte OpenSymbol de tamanho 16!(MapEditor.cpp)");
	if(OpenSymbol32 == 0)
		addToLog("Falha ao carregar a fonte OpenSymbol de tamanho 32!(MapEditor.cpp)");
	if(mapSprite == 0)
		addToLog("Falha ao carregar o sprite do mapa!(MapEditor.cpp)");
#endif
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
	if(teclas[C2D2_N].pressionado){
		for(int x = 0; x < 18; x++){
			for(int y = 0; y < 18; y++){
				mapa.construir(x*32, y*32, -1, 0);
			}
		}
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
		for(int j = 0; j < 2; j++){
			if(C2D2_ColidiuSprites(mouseSprite, 0, mouseX, mouseY, mapSprite, j, 625+j*75, 100)){
				tile = j;
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
	sprintf(txttile, "Tile:%d\tId:%d\t(%d,%d)\t(%d,%d)[%d]", tile, id, mouseX, mouseY, mouseX < 576 && mouseY < 576 ? mouseX/32 : 0, mouseY < 576 && mouseX < 576 ? mouseY/32 : 0, mouseY < 576 && mouseX < 576 ? mapa.conteudo(mouseX, mouseY) : 0);
	
	C2D2P_Linha(577, 0, 577, 577, 255, 255, 255);
	C2D2P_Linha(0, 577, 577, 577, 255, 255, 255);

	mapa.desenhar();

	for(int j = 0; j < 2; j++)
		C2D2_DesenhaSprite(mapSprite, +j, 625+j*75, 100);
	if(mouseX < 576 && mouseY < 576){
		C2D2P_Retangulo((16+mouseX-mouseX%32)-16, (16+mouseY-mouseY%32)-16, (16+mouseX-mouseX%32)+16, (16+mouseY-mouseY%32)+16, 0, 255, 0);
	}

	C2D2_DesenhaTexto(OpenSymbol32, 600, 32, "Map Editor", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 32, 580, txttile, C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 450, "Mouse Esquerdo - Coloca tile", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 466, "Mouse Direiro - Remove Tile", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 482, "0-4 - Muda id", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 498, "S - Salvar mapa", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 514, "D - Carregar mapa", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 530, "N - Novo mapa", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 546, "R - Reset", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaTexto(OpenSymbol16, 600, 562, "M - Retorna ao TD", C2D2_TEXTO_ESQUERDA);
	C2D2_DesenhaSprite(mouseSprite, 0, mouseX, mouseY);
}

void MapEditor::finalizar()
{
	C2D2_RemoveSpriteSet(mapSprite);
	C2D2_RemoveSpriteSet(mouseSprite);
	C2D2_RemoveFonte(OpenSymbol16);
	C2D2_RemoveFonte(OpenSymbol32);
}
