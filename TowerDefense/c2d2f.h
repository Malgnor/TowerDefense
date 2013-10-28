#ifndef _C2D2F_H_
#define _C2D2F_H_

#include <c2d2/chien2d2.h>

#include <string>

using namespace std;

bool stringInput(string& x);
bool stringFInput(string& x, char* txt = "", char* sufixo = "", char* prefixo = "");
string stringFInput(char* txt = "", char* sufixo = "", char* prefixo = "");

void dRetangulo(int x, int y, int largura, int altura, char* cor);
void dRetanguloPintado(int x, int y, int largura, int altura, char* cor);
void dRetanguloPintadoAlfa(int x, int y, int largura, int altura, char* cor, unsigned char alfa);

void dLinha(int x, int y, int largura, int altura, char* cor);

void dCirculo(int xcentro, int ycentro, int raio, char* cor);
void dCirculoPintado(int xcentro, int ycentro, int raio, char* cor);

void dElipse(int xcentro, int ycentro, int va, int vb, char* cor);
void dElipsePintada(int xcentro, int ycentro, int va, int vb, char* cor);
#endif