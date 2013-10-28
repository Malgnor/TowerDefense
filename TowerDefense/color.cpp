#include "color.h"

#include <fstream>
#include <string>

using namespace std;

/*
	Tabela de cores:
	http://www.imagemagick.org/script/color.php

	snow 	snow 	rgb( 255 , 250 , 250 ) 	#FFFAFA
	snow 255 250 250
	snow 1 0.980392 0.980392

	ifstream ifile("rawCor.txt");
	ofstream ofile("cores_uchar.txt");
	unsigned int rgb[3];
	string cor;
	string buffer;
	while(!ifile.eof()){
	ifile >> cor >> buffer >> buffer >> rgb[0] >> buffer >> rgb[1] >> buffer >> rgb[2] >> buffer >> buffer;
	ofile << cor << "= " << rgb[0] << " " << rgb[1] << " " << rgb[2] << endl;
	}
	ifile.close();
	ofile.close();

	
	ifstream ifile("cores_uchar.txt");
	ofstream ofile("cores_double.txt");
	unsigned int rgb[3];
	string cor;
	string buffer;
	while(!ifile.eof()){
		ifile >> cor >> rgb[0] >> rgb[1] >> rgb[2];
		ofile << cor << " " << (double)(rgb[0]/255.0) << " " << (double)(rgb[1]/255.0) << " " << (double)(rgb[2]/255.0) << endl;
	}
	ifile.close();
	ofile.close();
*/

void openCorDouble(double r[3], char* cor){
	ifstream ifile("cores_double.txt");
	if(ifile.is_open()){
		string c = "";
		while(!ifile.eof()){
			ifile >> c >> r[0] >> r[1] >> r[2];
			if(c == cor)
				break;
		}
	}
	ifile.close();
}

void openCor(unsigned int r[3], char* cor){
	ifstream ifile("cores_uchar.txt");
	if(ifile.is_open()){
		string c = "";
		while(!ifile.eof()){
			ifile >> c >> r[0] >> r[1] >> r[2];
			if(c == cor)
				break;
		}
	}
	ifile.close();
}

double getCorDoubleR(char* cor){
	double r[3];
	openCorDouble(r, cor);
	return r[0];
}

double getCorDoubleG(char* cor){
	double r[3];
	openCorDouble(r, cor);
	return r[1];
}

double getCorDoubleB(char* cor){
	double r[3];
	openCorDouble(r, cor);
	return r[2];
}

unsigned int getCorR(char* cor){
	unsigned int r[3];
	openCor(r, cor);
	return r[0];
}

unsigned int getCorG(char* cor){
	unsigned int r[3];
	openCor(r, cor);
	return r[1];
}

unsigned int getCorB(char* cor){
	unsigned int r[3];
	openCor(r, cor);
	return r[2];
}