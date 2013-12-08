#include "globalDef.h"
#include "color.h"

#include "dirent.h"

#include "MenuInicial.h"
#include "TowerDefense.h"

#include "MapEditor.h"
#include "Tutorial.h"

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

	if(btnTUTO->getEstado() == SOLTO)
		return new Tutorial();
	if(btnME->getEstado() == SOLTO)
		return new MapEditor();

	return this;
}

void MenuInicial::inicializar()
{
	C2D2_TrocaCorLimpezaTela(0, 0, 0);
	estado = MENU;
	cVolume = ControladorVolume(400, 432);
	cVolume.inicializar();
	mapSelected = "";
	mouseSprite = C2D2_CarregaSpriteSet("imgs/mouse.png", 0, 0);
	tahoma16 = C2D2_CarregaFonte("imgs/tahoma16.bmp", 16);
	tahoma32 = C2D2_CarregaFonte("imgs/tahoma32.bmp", 32);
	tahoma64 = C2D2_CarregaFonte("imgs/tahoma64.bmp", 64);

	menus.push_back(new MenuText("Drone Attack", 400, 100, tahoma64, "Verde-limao"));
	menus.push_back(btnTD = new MenuButton("Jogar", 400, 200, tahoma32, "purple"));
	menus.push_back(btnMS = new MenuButton("Selecionar Mapa", 400, 250, tahoma32, "indigo"));
	menus.push_back(btnTUTO = new MenuButton("Tutorial", 400, 300, tahoma32, "purple1"));
	menus.push_back(btnME = new MenuButton("MapEditor", 400, 350, tahoma32, "purple1"));
	menus.push_back(btnExit = new MenuButton("Sair!", 400, 490, tahoma32));

	gAtor.adicionar(new InimigoDemo(gAtor, Mapa(), 51, 549, iDIREITA, new TowerDefense()));
	gAtor.adicionar(new InimigoDemo(gAtor, Mapa(), 749, 51, iESQUERDA, new TowerDefense()));
	gAtor.adicionar(new InimigoDemo(gAtor, Mapa(), 749, 549, iCIMA, new TowerDefense()));
	gAtor.adicionar(new InimigoDemo(gAtor, Mapa(), 51, 51, iBAIXO, new TowerDefense()));
	gAtor.adicionar(new TorreDemo(gAtor, 20, 20));
	gAtor.adicionar(new TorreDemo(gAtor, 20, 580));
	gAtor.adicionar(new TorreDemo(gAtor, 780, 580));
	gAtor.adicionar(new TorreDemo(gAtor, 780, 20));
	
	string buffer = "";
	int xpos = 0;
	int ypos = -1;
	DIR* dir = opendir("map");
	dirent* dent;
	while(dir){
		if((dent = readdir(dir)) != NULL){
			buffer = dent->d_name;
			if(buffer.size() > 4){
				if(buffer == "Default.map")
					continue;
				if(buffer[buffer.size()-1] != 'p')
					continue;
				buffer.pop_back(); //p
				if(buffer[buffer.size()-1] != 'a')
					continue;
				buffer.pop_back(); //a
				if(buffer[buffer.size()-1] != 'm')
					continue;
				buffer.pop_back(); //m
				if(buffer[buffer.size()-1] != '.')
					continue;
				buffer.pop_back(); //.
				while(buffer.size() > 9) // Max 9 char
					buffer.pop_back();
				menusMS.push_back(new MenuButton(buffer, 140+xpos++%5*130, 90+(xpos % 5 == 0 ? ++ypos : ypos)*75, tahoma32));
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
	cVolume.atualizar();
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
		cVolume.desenhar();
		break;
	case MAPSELECT:
		for(Menu* menu : menusMS){
			menu->desenhar();
		}
		
		break;
	}
	if(!(mapSelected == "")){
		Mapa m = Mapa();
		m.load(mapSelected);
		C2D2P_Retangulo(624, 424, 698, 498, 0, 0, 255);
		for (int x = 0; x < 18; x++){
			for (int y = 0; y < 18; y++){
				m.sprite32(x, y) == 1 ? C2D2P_RetanguloPintado(625+x*4, 425+y*4, 625+x*4+4, 425+y*4+4, 255, 255, 255) : m.sprite32(x, y) ==  2 ? C2D2P_RetanguloPintado(625+x*4, 425+y*4, 625+x*4+4, 425+y*4+4, 200, 200, 200) : C2D2P_RetanguloPintado(625+x*4, 425+y*4, 625+x*4+4, 425+y*4+4, 0, 0, 0);
			}
		}
	}
	C2D2_DesenhaSprite(mouseSprite, 0, mouseX, mouseY);
}

void MenuInicial::finalizar()
{
	cVolume.finalizar();
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