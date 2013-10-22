#include "TowerDefense.h"
#include "MapEditor.h"

#include "TorreExemplo.h"
#include "Torre2.h"
#include "InimigoExemplo.h"

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

Tela* TowerDefense::proximaTela(){
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	
	if (teclas[C2D2_ENCERRA].pressionado || teclas[C2D2_ESC].pressionado)
		return nullptr;	
	if (teclas[C2D2_R].pressionado)
		return new TowerDefense();
	if (teclas[C2D2_M].pressionado)
		return new MapEditor();
	return this;
}

void TowerDefense::inicializar(){
	mapa = Mapa();
	tIndice = 0;
	mapa.inicializar();
	gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -16, 304, 1));
}
void TowerDefense::atualizar(){
	C2D2_Mouse* m = C2D2_PegaMouse();
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	if (teclas[C2D2_1].pressionado) {
		tIndice = 0;
	}
	if (teclas[C2D2_2].pressionado) {
		tIndice = 1;
	}
	if (teclas[C2D2_3].pressionado) {
		tIndice = 2;
	}
	mouseX = m->x;
	mouseY = m->y;
	if(m->botoes[C2D2_MESQUERDO].ativo && mouseX < 576 && mouseY < 576 && mapa.conteudo(mouseX, mouseY) == 0){
		mapa.construir(mouseX, mouseY);
		
		gAtor.adicionar(new Torre2(gAtor, mouseX, mouseY, tIndice));
		//gAtor.adicionar(new TorreExemplo(gAtor, mouseX, mouseY));
	
	}
	if(m->botoes[C2D2_MDIREITO].pressionado)
		gAtor.adicionar(new InimigoExemplo(gAtor, mapa, -16, 304, 1));
	if(teclas[C2D2_A].pressionado)
		mapa.load();
	gAtor.atualizar();

}
void TowerDefense::desenhar(){
	C2D2P_Linha(577, 0, 577, 577, 255, 255, 255);
	C2D2P_Linha(0, 577, 577, 577, 255, 255, 255);
	mapa.desenhar();
	if(mouseX < 576 && mouseY < 576 && mapa.conteudo(mouseX, mouseY) == 0){
		C2D2P_RetanguloPintado((16+mouseX-mouseX%32)-16, (16+mouseY-mouseY%32)-16, (16+mouseX-mouseX%32)+16, (16+mouseY-mouseY%32)+16, 127, 127, 127);
		C2D2P_Retangulo((16+mouseX-mouseX%32)-16, (16+mouseY-mouseY%32)-16, (16+mouseX-mouseX%32)+16, (16+mouseY-mouseY%32)+16, 0, 255, 0);
	}
	gAtor.desenhar();
	C2D2P_RetanguloPintado(mouseX-2, mouseY-2, mouseX+2, mouseY+2, 255, 255, 255);
}

void TowerDefense::finalizar(){

}