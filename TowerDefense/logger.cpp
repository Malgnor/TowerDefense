#include "logger.h"
#include <c2d2\chien2d2.h>
#include <stdio.h>

using namespace std;

void addToLog(char* txt){
	ofstream oFile("logs/log.log", ios_base::app);
	oFile << C2D2_TempoSistema() << ":" << txt << endl;
	oFile.close();
}

void addToLog(char* txt, int var){
	ofstream oFile("logs/log.log", ios_base::app);
	oFile << C2D2_TempoSistema() << ":" << txt << "=" << var << endl;
	oFile.close();
}

void addToLog(char* txt, unsigned int var){
	ofstream oFile("logs/log.log", ios_base::app);
	oFile << C2D2_TempoSistema() << ":" << txt << "=" << var << endl;
	oFile.close();
}

void addToLog(char* txt, float var){
	ofstream oFile("logs/log.log", ios_base::app);
	oFile << C2D2_TempoSistema() << ":" << txt << "=" << var << endl;
	oFile.close();
}

void addToLog(char* txt, double var){
	ofstream oFile("logs/log.log", ios_base::app);
	oFile << C2D2_TempoSistema() << ":" << txt << "=" << var << endl;
	oFile.close();
}

void addToLog(char* txt, char var){
	ofstream oFile("logs/log.log", ios_base::app);
	oFile << C2D2_TempoSistema() << ":" << txt << "=" << var << endl;
	oFile.close();
}

void addToLog(char* txt, char* var){
	ofstream oFile("logs/log.log", ios_base::app);
	oFile << C2D2_TempoSistema() << ":" << txt << "=" << var << endl;
	oFile.close();
}

void addToLog(char* txt, string var){
	ofstream oFile("logs/log.log", ios_base::app);
	oFile << C2D2_TempoSistema() << ":" << txt << "=" << var.c_str() << endl;
	oFile.close();
}

void addToLog(char* txt, time_t var){
	ofstream oFile("logs/log.log", ios_base::app);
	oFile << C2D2_TempoSistema() << ":" << txt << "=" << var << endl;
	oFile.close();
}

