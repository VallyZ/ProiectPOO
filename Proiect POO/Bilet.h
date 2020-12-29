#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
using namespace std;

class Bilet {
private:
	const int id = 0;
	string nume;
	int id_film;
	float pret;
	//int rand;
	//int loc;
	static int nrBilete;

public:
	Bilet() : id(++nrBilete) {
		pret = 0.0;
		//rand = 0;
		//loc = 0;
	}

	Bilet(float pret, int rand, int loc) : id(++nrBilete) {

	}
};

int Bilet::nrBilete = 0;