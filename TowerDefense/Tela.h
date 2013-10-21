#pragma once

class Tela
{
	public:
		virtual Tela* proximaTela() = 0;

		virtual void inicializar() = 0;		
		virtual void atualizar() = 0;
		virtual void desenhar() = 0;
		virtual void finalizar() = 0;

		//Toda classe virtual tem que ter, 
		//OBRIGATORIAMENTE um destrutor virtual
		virtual ~Tela() {}
};