#ifndef _C2D2F_H_
#define _C2D2F_H_

#include <c2d2/chien2d2.h>

#include <string>

using namespace std;

bool stringInput(string& x);
bool stringFInput(string& x, char* txt = "", char* sufixo = "", char* prefixo = "");
string stringFInput(char* txt = "", char* sufixo = "", char* prefixo = "");

#endif