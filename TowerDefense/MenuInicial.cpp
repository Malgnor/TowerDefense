#include "globalDef.h"

#include "dirent.h"

#include "MenuInicial.h"
#include "TowerDefense.h"
#include "MapEditor.h"

#include "MenuToggle.h"
#include "MenuText.h"
#include "MenuButton.h"

#include "InimigoDemo.h"
#include "TorreDemo.h"
#include "Mapa.h"

#include <iostream>
#include <string>

#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>

using namespace std;

Tela* MenuInicial::proximaTela()
{
	C2D2_Botao* teclas = C2D2_PegaTeclas();

	if (teclas[C2D2_ENCERRA].pressionado || teclas[C2D2_ESC].pressionado || btnExit->getEstado() == SOLTO)
		return nullptr;	
	if(btnTD->getEstado() == SOLTO)
		return mapSelected == "" ? new TowerDefense() : new TowerDefense(mapSelected.c_str());

#ifdef DEBUG
	if(btnME->getEstado() == SOLTO)
		return new MapEditor();
#endif // DEBUG

	return this;
}

void MenuInicial::inicializar()
{
	C2D2_TrocaCorLimpezaTela(0, 0, 0);
	estado = MENU;
	mapSelected = "";
	mouseSprite = C2D2_CarregaSpriteSet("imgs/mouse.png", 0, 0);
	tahoma16 = C2D2_CarregaFonte("imgs/tahoma16.bmp", 16);
	tahoma32 = C2D2_CarregaFonte("imgs/tahoma32.bmp", 32);
	tahoma64 = C2D2_CarregaFonte("imgs/tahoma64.bmp", 64);

#ifdef LOG
	if(mouseSprite == 0)
		addToLog("Falha ao carregar sprite do mouse!(MenuInicial.cpp)");
	if(tahoma16 == 0)
		addToLog("Falha ao carregar a fonte Tahoma de tamanho 16!(MenuInicial.cpp)");
	if(tahoma32 == 0)
		addToLog("Falha ao carregar a fonte Tahoma de tamanho 32!(MenuInicial.cpp)");
	if(tahoma64 == 0)
		addToLog("Falha ao carregar a fonte Tahoma de tamanho 64!(MenuInicial.cpp)");
#endif

	menus.push_back(new MenuText("TowerDefense", 400, 90, tahoma64));
	menus.push_back(btnTD = new MenuButton("Jogar", 400, 250, tahoma32));
	menus.push_back(btnMS = new MenuButton("Selecionar Mapa", 400, 300, tahoma32));
#ifdef DEBUG
	menus.push_back(btnME = new MenuButton("MapEditor", 400, 350, tahoma32));
#endif
	menus.push_back(btnExit = new MenuButton("Sair!", 400, 490, tahoma32));

	gAtor.adicionar(new InimigoDemo(gAtor, Mapa(), 51, 549, iDIREITA));
	gAtor.adicionar(new InimigoDemo(gAtor, Mapa(), 749, 51, iESQUERDA));
	gAtor.adicionar(new InimigoDemo(gAtor, Mapa(), 749, 549, iCIMA));
	gAtor.adicionar(new InimigoDemo(gAtor, Mapa(), 51, 51, iBAIXO));
	gAtor.adicionar(new TorreDemo(gAtor, 84, 84));
	gAtor.adicionar(new TorreDemo(gAtor, 84, 516));
	gAtor.adicionar(new TorreDemo(gAtor, 716, 516));
	gAtor.adicionar(new TorreDemo(gAtor, 716, 84));
	
	string buffer = "";
	int xpos = 0;
	int ypos = 0;
	DIR* dir = opendir("map");
	dirent* dent;
	while(dir){
		if((dent = readdir(dir)) != NULL){
			buffer = dent->d_name;
			if(buffer.size() > 4){
				buffer.pop_back(); //p
				buffer.pop_back(); //a
				buffer.pop_back(); //m
				buffer.pop_back(); //.
				menusMS.push_back(new MenuButton(buffer, 200+xpos++%3*125, 50+(xpos % 3 == 0 ? ++ypos : ypos)*75, tahoma32));
			}
		} else {
			break;
		}
	}
	closedir(dir);
	menusMS.push_back(new MenuButton("Voltar", 400, 500, tahoma32));
}

void MenuInicial::atualizar()
{
	C2D2_Mouse* m = C2D2_PegaMouse();
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	mouseX = m->x;
	mouseY = m->y;
	switch (estado)
	{
	case MENU:
		for(Menu* menu : menus){
			menu->atualizar();
		}
		if(btnMS->getEstado() == SOLTO)
			estado = MAPSELECT;
		break;
	case MAPSELECT:
		for(Menu* menu : menusMS){
			menu->atualizar();
			if(menu->getName() == "Voltar"){
				MenuButton* m = (MenuButton*) menu;
				if(m->getEstado() == SOLTO)
					estado = MENU;
			} else {
				MenuButton* m = (MenuButton*) menu;
				if(m->getEstado() == SOLTO)
					mapSelected = m->getName();
			}
		}
		break;
	}
	gAtor.atualizar();
}

void MenuInicial::desenhar()
{
	C2D2P_RetanguloPintado(34, 34, 66, 566, 255, 255, 255);
	C2D2P_RetanguloPintado(66, 534, 766, 566, 255, 255, 255);
	C2D2P_RetanguloPintado(734, 534, 766, 34, 255, 255, 255);
	C2D2P_RetanguloPintado(734, 34, 66, 66, 255, 255, 255);

	gAtor.desenhar();

	switch(estado){
	case MENU:
		for(Menu* menu : menus){
			menu->desenhar();
		}
		break;
	case MAPSELECT:
		for(Menu* menu : menusMS){
			menu->desenhar();
		}
		if(!(mapSelected == "")){
			Mapa m = Mapa();
			m.load(mapSelected);
			C2D2P_Retangulo(599, 399, 673, 473, 0, 0, 255);
			for (int x = 0; x < 18; x++){
				for (int y = 0; y < 18; y++){
					m.sprite32(x, y) == 1 ? C2D2P_RetanguloPintado(600+x*4, 400+y*4, 600+x*4+4, 400+y*4+4, 255, 255, 255) : C2D2P_RetanguloPintado(600+x*4, 400+y*4, 600+x*4+4, 400+y*4+4, 0, 0, 0);
				}
			}
		}
		break;
	}
	C2D2_DesenhaSprite(mouseSprite, 0, mouseX, mouseY);
}

void MenuInicial::finalizar()
{
	for(Menu* menu : menus){
		delete menu;
	}
	for(Menu* menu : menusMS){
		delete menu;
	}
	C2D2_RemoveSpriteSet(mouseSprite);
	C2D2_RemoveFonte(tahoma16);
	C2D2_RemoveFonte(tahoma32);
	C2D2_RemoveFonte(tahoma64);
}