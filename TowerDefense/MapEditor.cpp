#include "MapEditor.h"
#include "TowerDefense.h"

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

using namespace std;

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
	mapSprite = C2D2_CarregaSpriteSet("map/map.png", 32, 32);
	mouseSprite = C2D2_CarregaSpriteSet("mouse.png", 0, 0);
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

	if(m->botoes[C2D2_MESQUERDO].pressionado && mouseX < 577 && mouseY < 577){
		mapa.construir(mouseX, mouseY, tile, id);
	}
	if(m->botoes[C2D2_MDIREITO].pressionado && mouseX < 577 && mouseY < 577){
		mapa.construir(mouseX, mouseY, -1, id);
	}
}

void MapEditor::desenhar()
{
	C2D2P_Linha(577, 0, 577, 577, 255, 255, 255);
	C2D2P_Linha(0, 577, 577, 577, 255, 255, 255);
	mapa.desenhar();
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 2; j++)
			C2D2_DesenhaSprite(mapSprite, i*2+j, 625+j*75, 100+i*75);
	}
	if(mouseX < 576 && mouseY < 576){
		C2D2_DesenhaSprite(mapSprite, tile, mouseX-mouseX%32, mouseY-mouseY%32);
	}
	C2D2_DesenhaSprite(mouseSprite, 0, mouseX, mouseY);
}

void MapEditor::finalizar()
{
	C2D2_RemoveSpriteSet(mapSprite);
	C2D2_RemoveSpriteSet(mouseSprite);
}
