#include "TDBase.h"

#include "TorreExemplo.h"
#include "Torre2.h"

#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>

TDBase::TDBase()
	:btnSell("Vender", 630, 415, tahoma16 = C2D2_CarregaFonte("imgs/tahoma16.bmp", 16)), btnUpgrade("Upgrade", 685, 415, tahoma16)
{
}

void TDBase::Lucro(int money){
	gold += money;
}

void TDBase::DanoRecebido(int porrada){
	chances -= porrada;
}

void TDBase::inicializar()
{
	C2D2_TrocaCorLimpezaTela(255, 255, 255);

	estado = PLAY;
	pTorre = nullptr;
	tahoma16 = C2D2_CarregaFonte("imgs/tahoma16.bmp", 16);
	tahoma32 = C2D2_CarregaFonte("imgs/tahoma32.bmp", 32);
	mouseSprite = C2D2_CarregaSpriteSet("imgs/mouse.png", 0, 0);
	eheart = C2D2_CarregaSpriteSet("imgs/eheart.png", 0, 0);
	heart = C2D2_CarregaSpriteSet("imgs/heart.png", 16, 16);
	goldcoins = C2D2_CarregaSpriteSet("imgs/goldcoins.png", 0, 0);
	torreSprite = C2D2_CarregaSpriteSet("imgs/torres.png", 32, 32);
	chances = 20;
	gold = 600;
	torreSelecionada = 0;
	mapaTD.inicializar();

	menus.push_back(btnPause = new MenuButton("Pausa", 700, 480, tahoma16));
	menus.push_back(btnBack = new MenuButton("Menu Inicial", 700, 500, tahoma16));
	menus.push_back(btnExit = new MenuButton("Sair", 700, 520, tahoma16));

#ifdef LOG
	if(mouseSprite == 0)
		addToLog("Falha ao carregar sprite do mouse!(TDBase.cpp)");
	if(tahoma16 == 0)
		addToLog("Falha ao carregar a fonte Tahoma de tamanho 16!(TDBase.cpp)");
	if(tahoma32 == 0)
		addToLog("Falha ao carregar a fonte Tahoma de tamanho 32!(TDBase.cpp)");
	if(eheart == 0)
		addToLog("Falha ao carregar o sprite eheart!(TDBase.cpp)");
	if(heart == 0)
		addToLog("Falha ao carregar o sprite heart!(TDBase.cpp)");
	if(goldcoins == 0)
		addToLog("Falha ao carregar o sprite goldcoins!(TDBase.cpp)");
	if(torreSprite == 0)
		addToLog("Falha ao carregar o sprite das torres!(TDBase.cpp)");
#endif
}

void TDBase::atualizar()
{
	C2D2_Mouse* m = C2D2_PegaMouse();
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	mouseX = m->x;
	mouseY = m->y;

	estado = teclas[C2D2_F1].pressionado ? estado == PAUSEF1 ? PLAY : PAUSEF1 : teclas[C2D2_P].pressionado || teclas[C2D2_ESC].pressionado || btnPause->getEstado() == SOLTO ? estado == PLAY ? PAUSE : PLAY : estado;
	
	for(Menu* menu : menus){
		menu->atualizar();
	}
	switch (estado)
	{
	case PLAY:
		if(m->botoes[C2D2_MESQUERDO].ativo && mouseX > 575){
			torreSelecionada = 0;
			for(int j = 0; j < 2; j++){
				if(C2D2_ColidiuSprites(mouseSprite, 0, mouseX, mouseY, torreSprite, j, 625+j*75, 100)){
					torreSelecionada = j+1;
				}
			}
		}
		if(mouseX < 576 && mouseY < 576){
			if(m->botoes[C2D2_MESQUERDO].ativo && mapaTD.conteudo(mouseX, mouseY) == 0 && gold >= 50){
				switch (torreSelecionada)
				{
				case 1:
					gold -= 50;
					mapaTD.addTorre(mouseX, mouseY);
					gAtor.adicionar(new Torre2(gAtor, mouseX, mouseY));
					break;
				case 2:
					gold -= 50;
					mapaTD.addTorre(mouseX, mouseY);
					gAtor.adicionar(new TorreExemplo(gAtor, mouseX, mouseY));
				default:
					break;
				}
			} else if(m->botoes[C2D2_MESQUERDO].pressionado) {
				pTorre = (Torre*)(gAtor.maisPerto(mouseX, mouseY, 16, TORRE));
			}
		}
		if(m->botoes[C2D2_MDIREITO].pressionado)
			pTorre = nullptr;
		if( pTorre != nullptr){
			btnSell.atualizar();
			btnUpgrade.atualizar();
			if (btnUpgrade.getEstado() == SOLTO && gold>=pTorre->comprar() && pTorre->comprar() != 0){
				gold -= pTorre->comprar();
				pTorre->upgrade();
			}
			if(btnSell.getEstado() == SOLTO){
				gold += pTorre->getValor()/2;
				pTorre->vender();
				mapaTD.removeTorre(pTorre->x(), pTorre->y());
				pTorre = nullptr;

			}
		}
		gAtor.atualizar();
		break;
	case PAUSE:
		break;
	case PAUSEF1:
		break;
	}
}

void TDBase::desenhar()
{
	mapaTD.desenhar();
	gAtor.desenhar();

	if( pTorre != nullptr )
		C2D2P_Circulo(pTorre->x(), pTorre->y(), pTorre->getAlcance(), 255, 255, 255);

	C2D2P_RetanguloPintado(577, 0, 800, 600, 25, 25, 25);
	C2D2P_RetanguloPintado(0, 577, 577, 600, 25, 25, 25);

	if(pTorre != nullptr){
		C2D2P_RetanguloPintadoAlfa(590, 290, 725, 440, 100, 149, 237, 127);
		C2D2P_Retangulo(590, 290, 725, 440, 0, 127, 0);
		btnUpgrade.desenhar();
		btnSell.desenhar();
		int yt = 19;
		C2D2_DesenhaSprite(pTorre->sprite(), pTorre->indice(), 680, yt*16+35);
		C2D2_DesenhaTexto(tahoma32, 630, yt++*16-15, "Torre", C2D2_TEXTO_ESQUERDA);
		char temp[50];
		sprintf_s(temp, "Nível: %d", pTorre->indice()+1);
		C2D2_DesenhaTexto(tahoma16, 600, yt++*16, temp, C2D2_TEXTO_ESQUERDA);
		sprintf_s(temp, "Alcance: %d", pTorre->getAlcance());
		C2D2_DesenhaTexto(tahoma16, 600, yt++*16, temp, C2D2_TEXTO_ESQUERDA);
		sprintf_s(temp, "RoF: %d", pTorre->getRof());
		C2D2_DesenhaTexto(tahoma16, 600, yt++*16, temp, C2D2_TEXTO_ESQUERDA);
		sprintf_s(temp, "Custo: %d", pTorre->comprar());
		C2D2_DesenhaTexto(tahoma16, 600, yt++*16, temp, C2D2_TEXTO_ESQUERDA);
		sprintf_s(temp, "Valor: %d", pTorre->getValor()/2);
		C2D2_DesenhaTexto(tahoma16, 600, yt++*16, temp, C2D2_TEXTO_ESQUERDA);
	}

	C2D2_DesenhaSprite(goldcoins, 0, 360, 580);
	char g[9];
	sprintf_s(g, "%d", gold);
	C2D2_DesenhaTexto(tahoma16, 380, 580, g, C2D2_TEXTO_ESQUERDA);

	int i;
	C2D2_DesenhaSprite(eheart, 0, 415, 580);
	for(i = 0; i < (int)(chances/2); i++){
		C2D2_DesenhaSprite(heart, 0, 415+i*16, 580);
	}
	if(chances % 2 == 1){
		C2D2_DesenhaSprite(heart, 1, 415+i*16, 580);
	}

	for(int j = 0; j < 2; j++)
		C2D2_DesenhaSprite(torreSprite, +j, 625+j*75, 100);

	switch (estado)
	{
	case PLAY:
		if(mouseX < 576 && mouseY < 576 && mapaTD.conteudo(mouseX, mouseY) == 0){
			C2D2P_Retangulo((16+mouseX-mouseX%32)-16, (16+mouseY-mouseY%32)-16, (16+mouseX-mouseX%32)+16, (16+mouseY-mouseY%32)+16, 0, 155, 0);
		}
		break;
	case PAUSE:
		C2D2P_RetanguloPintadoAlfa(0, 0, 800, 600, 25, 25, 25, 200);
		C2D2_DesenhaTexto(tahoma32, 400-32, 75, "PAUSE", C2D2_TEXTO_CENTRALIZADO);
		break;
	case PAUSEF1:
		C2D2P_RetanguloPintadoAlfa(0, 0, 800, 600, 25, 25, 25, 200);
		C2D2_DesenhaTexto(tahoma32, 400-32, 100, "PAUSE", C2D2_TEXTO_CENTRALIZADO);
		int ytxt = 0;
		C2D2_DesenhaTexto(tahoma16, 300, 150+ytxt++*16, "Mouse Esquerdo - Coloca Torre", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 300, 150+ytxt++*16, "Mouse Esquerdo - Seleciona Torre", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 300, 150+ytxt++*16, "Mouse Direito - Deseleciona torre", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(tahoma16, 300, 150+ytxt++*16, "P/ESC/F1 - Pausa/Despausa", C2D2_TEXTO_ESQUERDA);
		break;
	}
	
	C2D2_DesenhaTexto(tahoma16, 8, 580, "F1 - Mostra atalhos", C2D2_TEXTO_ESQUERDA);

	for(Menu* menu : menus){
		menu->desenhar();
	}
}

void TDBase::finalizar()
{
	for(Menu* menu : menus){
		delete menu;
	}
	C2D2_RemoveSpriteSet(mouseSprite);
	C2D2_RemoveSpriteSet(eheart);
	C2D2_RemoveSpriteSet(heart);
	C2D2_RemoveSpriteSet(goldcoins);
	C2D2_RemoveSpriteSet(torreSprite);
	C2D2_RemoveFonte(tahoma16);
	C2D2_RemoveFonte(tahoma32);
}

void TDBase::desenhaMouse()
{
	C2D2_DesenhaSprite(mouseSprite, 0, mouseX, mouseY);
}

