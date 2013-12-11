#include "globalDef.h"
#include "MapEditor.h"
#include "TowerDefense.h"
#include "c2d2f.h"
#include "dirent.h"

#include <c2d2\chien2d2.h>
#include <c2d2\chien2d2primitivas.h>

Tela* MapEditor::proximaTela()
{
	C2D2_Botao* teclas = C2D2_PegaTeclas();

	if (teclas[C2D2_ENCERRA].pressionado || btnExit->getEstado() == SOLTO)
		return nullptr;	
	if (btnTD->getEstado() == SOLTO)
		return new TowerDefense(mapaTD.getNome().c_str());
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
	nomeMapa = "";
	estado = MENU;
	
	menus.push_back(btnNM = new MenuToggle("Clique aqui para nomear o mapa", 700, 390, tahoma16, DESATIVADO));
	menus.push_back(btnNew = new MenuButton("Novo Mapa", 700, 420, tahoma16));
	menus.push_back(btnLoad = new MenuButton("Carregar mapa", 700, 450, tahoma16));
	menus.push_back(btnSave = new MenuButton("Salvar mapa", 700, 480, tahoma16));
	menus.push_back(btnTD = new MenuButton("TowerDefense", 700, 510, tahoma16));
	menus.push_back(btnBack = new MenuButton("Menu Inicial", 700, 540, tahoma16));
	menus.push_back(btnExit = new MenuButton("Sair", 700, 570, tahoma16));
	menus.push_back(btn0 = new MenuMToggle("0", 625, 350, tahoma16, menusID, ATIVADO));
	menus.push_back(btn1 = new MenuMToggle("1", 650, 350, tahoma16, menusID));
	menus.push_back(btn2 = new MenuMToggle("2", 675, 350, tahoma16, menusID));
	menus.push_back(btn3 = new MenuMToggle("3", 700, 350, tahoma16, menusID));
	menus.push_back(btn4 = new MenuMToggle("4", 725, 350, tahoma16, menusID));
	
	menusMS.push_back(new MenuButton("Voltar", 400, 500, tahoma32));
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
				while(buffer.size() > 8) // Max 8 char
					buffer.pop_back();
				menusMS.push_back(new MenuButton(buffer, 70+xpos++%6*130, 15+(xpos % 6 == 0 ? ++ypos : ypos)*75, tahoma32));
			}
		} else {
			break;
		}
	}
	closedir(dir);
}

void MapEditor::atualizar()
{
	C2D2_Mouse* m = C2D2_PegaMouse();
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	mouseX = m->x;
	mouseY = m->y;
	switch (estado)
	{
		case MENU:
		if(btnNM->getEstado() == ATIVADO){
			stringInput(nomeMapa);
			btnNM->mudarNome(nomeMapa);
		}
		if(btnSave->getEstado() == SOLTO){
			mapaTD.save(nomeMapa);
			bool existe = false;
			for(Menu* menu : menusMS)
				if(menu->getName() == nomeMapa)
					existe = true;
			if(!existe){
				string nome = nomeMapa;
				while(nome.size() > 8) // Max 8 char
					nome.pop_back();
				menusMS.push_back(new MenuButton(nome, 70+(menusMS.size()-1)%6*130, 15+(menusMS.size()-1)/6*75, tahoma32));
			}
		}
		if(btnLoad->getEstado() == SOLTO)
			estado = MAPSELECT;
		if(btnNew->getEstado() == SOLTO){
			mapaTD.finalizar();
			mapaTD = Mapa();
			mapaTD.inicializar();
			nomeMapa = "";
			btnNM->mudarNome("Clique aqui para nomear o mapa");
		}
		if (btn0->getEstado() == ATIVADO)
			id = 0;
		if (btn1->getEstado() == ATIVADO)
			id = 1;
		if (btn2->getEstado() == ATIVADO)
			id = 2;
		if (btn3->getEstado() == ATIVADO)
			id = 3;
		if (btn4->getEstado() == ATIVADO)
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
		break;
	case MAPSELECT:
		for(Menu* menu : menusMS){
			menu->atualizar();
			if(menu->getName() == "Voltar"){
				MenuButton* m = (MenuButton*) menu;
				if(m->getEstado() == SOLTO){
					estado = MENU;
					mapaTD.load(nomeMapa);
					btnNM->mudarNome(nomeMapa);
				}
			} else {
				MenuButton* m = (MenuButton*) menu;
				if(m->getEstado() == SOLTO)
					nomeMapa = m->getName();
			}
		}
		break;
	}
}

void MapEditor::desenhar()
{
	char txttile[50];
	int ytxt = 14;
	sprintf_s(txttile, "Tile:%d\tId:%d\t(%d,%d)\t(%d,%d)[%d]", tile, id, mouseX, mouseY, mouseX < 576 && mouseY < 576 ? mouseX/32 : 0, mouseY < 576 && mouseX < 576 ? mouseY/32 : 0, mouseY < 576 && mouseX < 576 ? mapaTD.conteudo(mouseX, mouseY) : 0);
	switch (estado)
	{
	case MENU:
		C2D2P_Linha(577, 0, 577, 577, 255, 255, 255);
		C2D2P_Linha(0, 577, 577, 577, 255, 255, 255);

		mapaTD.desenhar();

		for(int j = 0; j < qtdTiles; j++)
			C2D2_DesenhaSprite(mapSprite, j, 625+j%2*75, 100+j/2*48);
		C2D2P_Retangulo(625+tile % 2 * 75, 100 + tile / 2 * 48, 658+tile % 2 * 75, 133 + tile / 2 * 48, 0, 255, 0);

		if(mouseX < 576 && mouseY < 576){
			C2D2P_Retangulo((16+mouseX-mouseX%32)-16, (16+mouseY-mouseY%32)-16, (16+mouseX-mouseX%32)+16, (16+mouseY-mouseY%32)+16, 0, 255, 0);
		}

		C2D2_DesenhaTexto(tahoma32, 600, 32, "Map Editor", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 32, 580, txttile, C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 600, ytxt++*20, "Mouse Esquerdo - Coloca tile", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 600, ytxt++*20, "Mouse Direiro - Remove Tile", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 600, ytxt++*20, "Alterar ID:", C2D2_TEXTO_ESQUERDA);

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
		break;
	case MAPSELECT:
		for(Menu* menu : menusMS){
			menu->desenhar();
		}
		if(!(nomeMapa == "")){
			Mapa m = Mapa();
			m.load(nomeMapa);
			C2D2P_Retangulo(624, 424, 698, 498, 0, 0, 255);
			for (int x = 0; x < 18; x++){
				for (int y = 0; y < 18; y++){
					m.sprite32(x, y) == 1 ? C2D2P_RetanguloPintado(625+x*4, 425+y*4, 625+x*4+4, 425+y*4+4, 255, 255, 255) : m.sprite32(x, y) ==  2 ? C2D2P_RetanguloPintado(625+x*4, 425+y*4, 625+x*4+4, 425+y*4+4, 200, 200, 200) : C2D2P_RetanguloPintado(625+x*4, 425+y*4, 625+x*4+4, 425+y*4+4, 0, 0, 0);
				}
			}
		}
		break;
	}
	C2D2_DesenhaSprite(mouseSprite, 0, mouseX, mouseY);
}

void MapEditor::finalizar()
{
	for(Menu* menu : menus){
		delete menu;
	}
	for(Menu* menu : menusMS){
		delete menu;
	}
	C2D2_RemoveSpriteSet(mapSprite);
	C2D2_RemoveSpriteSet(mouseSprite);
	C2D2_RemoveFonte(tahoma16);
	C2D2_RemoveFonte(tahoma32);
	C2D2_RemoveFonte(tahoma16r);
}
