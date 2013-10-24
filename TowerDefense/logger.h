#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "globalDef.h"
#include <fstream>

void addToLog(char* txt);
void addToLog(char* txt, int var);
void addToLog(char* txt, unsigned int var);
void addToLog(char* txt, float var);
void addToLog(char* txt, double var);
void addToLog(char* txt, char var);
void addToLog(char* txt, char* var);
void addToLog(char* txt, std::string var);
void addToLog(char* txt, time_t var);

#endif