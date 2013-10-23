#include "c2d2f.h"

bool stringInput( string& x ){
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	bool m = false;
	m = teclas[C2D2_LSHIFT].ativo || teclas[C2D2_RSHIFT].ativo ? true : false;
	if(teclas[C2D2_A].pressionado)
		x+= m ? "A" : "a";
	if(teclas[C2D2_B].pressionado)
		x+= m ? "B" : "b";
	if(teclas[C2D2_C].pressionado)
		x+= m ? "C" : "c";
	if(teclas[C2D2_D].pressionado)
		x+= m ? "D" : "d";
	if(teclas[C2D2_E].pressionado)
		x+= m ? "E" : "e";
	if(teclas[C2D2_F].pressionado)
		x+= m ? "F" : "f";
	if(teclas[C2D2_G].pressionado)
		x+= m ? "G" : "g";
	if(teclas[C2D2_H].pressionado)
		x+= m ? "H" : "h";
	if(teclas[C2D2_I].pressionado)
		x+= m ? "I" : "i";
	if(teclas[C2D2_J].pressionado)
		x+= m ? "J" : "j";
	if(teclas[C2D2_K].pressionado)
		x+= m ? "K" : "k";
	if(teclas[C2D2_L].pressionado)
		x+= m ? "L" : "l";
	if(teclas[C2D2_M].pressionado)
		x+= m ? "M" : "m";
	if(teclas[C2D2_N].pressionado)
		x+= m ? "N" : "n";
	if(teclas[C2D2_O].pressionado)
		x+= m ? "O" : "o";
	if(teclas[C2D2_P].pressionado)
		x+= m ? "P" : "p";
	if(teclas[C2D2_Q].pressionado)
		x+= m ? "Q" : "q";
	if(teclas[C2D2_R].pressionado)
		x+= m ? "R" : "r";
	if(teclas[C2D2_S].pressionado)
		x+= m ? "S" : "s";
	if(teclas[C2D2_T].pressionado)
		x+= m ? "T" : "t";
	if(teclas[C2D2_U].pressionado)
		x+= m ? "U" : "u";
	if(teclas[C2D2_V].pressionado)
		x+= m ? "V" : "v";
	if(teclas[C2D2_W].pressionado)
		x+= m ? "W" : "w";
	if(teclas[C2D2_X].pressionado)
		x+= m ? "X" : "x";
	if(teclas[C2D2_Y].pressionado)
		x+= m ? "Y" : "y";
	if(teclas[C2D2_Z].pressionado)
		x+= m ? "Z" : "z";
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
	if(teclas[C2D2_ESPACO].pressionado)
		m ? !x.empty() ? x.pop_back() : 0 : x+=" ";
	return true;
}

bool stringFInput( string& x, char* txt)
{
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	bool m = false;
	int OpenSymbol16 = C2D2_CarregaFonte("imgs/OpenSymbol16.bmp", 16);
	C2D2_Sincroniza(C2D2_FPS_PADRAO);
	while(true){
		C2D2_LimpaTela();
		teclas = C2D2_PegaTeclas();
		if(teclas[C2D2_ENTER].pressionado || teclas[C2D2_ESC].pressionado || teclas[C2D2_ENCERRA].pressionado)
			break;
		stringInput(x);
		C2D2_DesenhaTexto(OpenSymbol16, 400, 280, txt, C2D2_TEXTO_CENTRALIZADO);
		C2D2_DesenhaTexto(OpenSymbol16, 400, 300, x.c_str(), C2D2_TEXTO_CENTRALIZADO);
		C2D2_DesenhaTexto(OpenSymbol16, 400, 320, "Shift + Espa�o = Apaga um caracter", C2D2_TEXTO_CENTRALIZADO);
		C2D2_DesenhaTexto(OpenSymbol16, 400, 340, "Pressione ENTER ou ESC para confimar", C2D2_TEXTO_CENTRALIZADO);
		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	}
	C2D2_RemoveFonte(OpenSymbol16);
	return true;
}

std::string stringFInput( char* txt )
{
	string x = "";
	return stringFInput(x, txt); ? x : "";
}
