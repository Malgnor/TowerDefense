#include "c2d2f.h"

bool stringInput( string& x ){
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	if(teclas[C2D2_A].pressionado)
		x+="A";
	if(teclas[C2D2_B].pressionado)
		x+="B";
	if(teclas[C2D2_C].pressionado)
		x+="C";
	if(teclas[C2D2_D].pressionado)
		x+="D";
	if(teclas[C2D2_E].pressionado)
		x+="E";
	if(teclas[C2D2_F].pressionado)
		x+="F";
	if(teclas[C2D2_G].pressionado)
		x+="G";
	if(teclas[C2D2_H].pressionado)
		x+="H";
	if(teclas[C2D2_I].pressionado)
		x+="I";
	if(teclas[C2D2_J].pressionado)
		x+="J";
	if(teclas[C2D2_K].pressionado)
		x+="K";
	if(teclas[C2D2_L].pressionado)
		x+="L";
	if(teclas[C2D2_M].pressionado)
		x+="M";
	if(teclas[C2D2_N].pressionado)
		x+="N";
	if(teclas[C2D2_O].pressionado)
		x+="O";
	if(teclas[C2D2_P].pressionado)
		x+="P";
	if(teclas[C2D2_Q].pressionado)
		x+="Q";
	if(teclas[C2D2_R].pressionado)
		x+="R";
	if(teclas[C2D2_S].pressionado)
		x+="S";
	if(teclas[C2D2_T].pressionado)
		x+="T";
	if(teclas[C2D2_U].pressionado)
		x+="U";
	if(teclas[C2D2_V].pressionado)
		x+="V";
	if(teclas[C2D2_W].pressionado)
		x+="W";
	if(teclas[C2D2_X].pressionado)
		x+="X";
	if(teclas[C2D2_Y].pressionado)
		x+="Y";
	if(teclas[C2D2_Z].pressionado)
		x+="Z";
	if(teclas[C2D2_1].pressionado)
		x+="1";
	if(teclas[C2D2_2].pressionado)
		x+="2";
	if(teclas[C2D2_3].pressionado)
		x+="3";
	if(teclas[C2D2_4].pressionado)
		x+="4";
	if(teclas[C2D2_5].pressionado)
		x+="5";
	if(teclas[C2D2_6].pressionado)
		x+="6";
	if(teclas[C2D2_7].pressionado)
		x+="7";
	if(teclas[C2D2_8].pressionado)
		x+="8";
	if(teclas[C2D2_9].pressionado)
		x+="9";
	if(teclas[C2D2_0].pressionado)
		x+="0";
	return true;
}

bool stringFInput( string& x, char* txt)
{
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	int OpenSymbol16 = C2D2_CarregaFonte("imgs/OpenSymbol16.bmp", 16);
	C2D2_Sincroniza(C2D2_FPS_PADRAO);
	while(true){
		C2D2_LimpaTela();
		teclas = C2D2_PegaTeclas();
		if(teclas[C2D2_ENTER].pressionado || teclas[C2D2_ESC].pressionado)
			break;
		if(teclas[C2D2_A].pressionado)
			x+="A";
		if(teclas[C2D2_B].pressionado)
			x+="B";
		if(teclas[C2D2_C].pressionado)
			x+="C";
		if(teclas[C2D2_D].pressionado)
			x+="D";
		if(teclas[C2D2_E].pressionado)
			x+="E";
		if(teclas[C2D2_F].pressionado)
			x+="F";
		if(teclas[C2D2_G].pressionado)
			x+="G";
		if(teclas[C2D2_H].pressionado)
			x+="H";
		if(teclas[C2D2_I].pressionado)
			x+="I";
		if(teclas[C2D2_J].pressionado)
			x+="J";
		if(teclas[C2D2_K].pressionado)
			x+="K";
		if(teclas[C2D2_L].pressionado)
			x+="L";
		if(teclas[C2D2_M].pressionado)
			x+="M";
		if(teclas[C2D2_N].pressionado)
			x+="N";
		if(teclas[C2D2_O].pressionado)
			x+="O";
		if(teclas[C2D2_P].pressionado)
			x+="P";
		if(teclas[C2D2_Q].pressionado)
			x+="Q";
		if(teclas[C2D2_R].pressionado)
			x+="R";
		if(teclas[C2D2_S].pressionado)
			x+="S";
		if(teclas[C2D2_T].pressionado)
			x+="T";
		if(teclas[C2D2_U].pressionado)
			x+="U";
		if(teclas[C2D2_V].pressionado)
			x+="V";
		if(teclas[C2D2_W].pressionado)
			x+="W";
		if(teclas[C2D2_X].pressionado)
			x+="X";
		if(teclas[C2D2_Y].pressionado)
			x+="Y";
		if(teclas[C2D2_Z].pressionado)
			x+="Z";
		if(teclas[C2D2_1].pressionado)
			x+="1";
		if(teclas[C2D2_2].pressionado)
			x+="2";
		if(teclas[C2D2_3].pressionado)
			x+="3";
		if(teclas[C2D2_4].pressionado)
			x+="4";
		if(teclas[C2D2_5].pressionado)
			x+="5";
		if(teclas[C2D2_6].pressionado)
			x+="6";
		if(teclas[C2D2_7].pressionado)
			x+="7";
		if(teclas[C2D2_8].pressionado)
			x+="8";
		if(teclas[C2D2_9].pressionado)
			x+="9";
		if(teclas[C2D2_0].pressionado)
			x+="0";
		C2D2_DesenhaTexto(OpenSymbol16, 400, 280, txt, C2D2_TEXTO_CENTRALIZADO);
		C2D2_DesenhaTexto(OpenSymbol16, 400, 300, x.c_str(), C2D2_TEXTO_CENTRALIZADO);
		C2D2_DesenhaTexto(OpenSymbol16, 400, 320, "Pressione ENTER ou ESC", C2D2_TEXTO_CENTRALIZADO);
		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	}
	C2D2_RemoveFonte(OpenSymbol16);
	return true;
}

std::string stringFInput( char* txt )
{
	string x = "";
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	int OpenSymbol16 = C2D2_CarregaFonte("imgs/OpenSymbol16.bmp", 16);
	C2D2_Sincroniza(C2D2_FPS_PADRAO);
	while(true){
		C2D2_LimpaTela();
		teclas = C2D2_PegaTeclas();
		if(teclas[C2D2_ENTER].pressionado || teclas[C2D2_ESC].pressionado)
			break;
		if(teclas[C2D2_A].pressionado)
			x+="A";
		if(teclas[C2D2_B].pressionado)
			x+="B";
		if(teclas[C2D2_C].pressionado)
			x+="C";
		if(teclas[C2D2_D].pressionado)
			x+="D";
		if(teclas[C2D2_E].pressionado)
			x+="E";
		if(teclas[C2D2_F].pressionado)
			x+="F";
		if(teclas[C2D2_G].pressionado)
			x+="G";
		if(teclas[C2D2_H].pressionado)
			x+="H";
		if(teclas[C2D2_I].pressionado)
			x+="I";
		if(teclas[C2D2_J].pressionado)
			x+="J";
		if(teclas[C2D2_K].pressionado)
			x+="K";
		if(teclas[C2D2_L].pressionado)
			x+="L";
		if(teclas[C2D2_M].pressionado)
			x+="M";
		if(teclas[C2D2_N].pressionado)
			x+="N";
		if(teclas[C2D2_O].pressionado)
			x+="O";
		if(teclas[C2D2_P].pressionado)
			x+="P";
		if(teclas[C2D2_Q].pressionado)
			x+="Q";
		if(teclas[C2D2_R].pressionado)
			x+="R";
		if(teclas[C2D2_S].pressionado)
			x+="S";
		if(teclas[C2D2_T].pressionado)
			x+="T";
		if(teclas[C2D2_U].pressionado)
			x+="U";
		if(teclas[C2D2_V].pressionado)
			x+="V";
		if(teclas[C2D2_W].pressionado)
			x+="W";
		if(teclas[C2D2_X].pressionado)
			x+="X";
		if(teclas[C2D2_Y].pressionado)
			x+="Y";
		if(teclas[C2D2_Z].pressionado)
			x+="Z";
		if(teclas[C2D2_1].pressionado)
			x+="1";
		if(teclas[C2D2_2].pressionado)
			x+="2";
		if(teclas[C2D2_3].pressionado)
			x+="3";
		if(teclas[C2D2_4].pressionado)
			x+="4";
		if(teclas[C2D2_5].pressionado)
			x+="5";
		if(teclas[C2D2_6].pressionado)
			x+="6";
		if(teclas[C2D2_7].pressionado)
			x+="7";
		if(teclas[C2D2_8].pressionado)
			x+="8";
		if(teclas[C2D2_9].pressionado)
			x+="9";
		if(teclas[C2D2_0].pressionado)
			x+="0";
		C2D2_DesenhaTexto(OpenSymbol16, 400, 280, txt, C2D2_TEXTO_CENTRALIZADO);
		C2D2_DesenhaTexto(OpenSymbol16, 400, 300, x.c_str(), C2D2_TEXTO_CENTRALIZADO);
		C2D2_DesenhaTexto(OpenSymbol16, 400, 320, "Pressione ENTER ou ESC", C2D2_TEXTO_CENTRALIZADO);
		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	}
	C2D2_RemoveFonte(OpenSymbol16);
	return x;
}
