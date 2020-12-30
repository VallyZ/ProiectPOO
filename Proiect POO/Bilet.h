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
	Film film;
	//int id_film;
	//float pret;
	//int rand;
	//int loc;
	static int nrBilete;

public:
	Bilet() : id(++nrBilete) {
		nume = "Necunoscut";
		//pret = 0.0;
		//rand = 0;
		//loc = 0;
	}

	Bilet(string nume) : id(++nrBilete) {
		this->nume = nume;
	}

	void setFilm(Film x) {
		film = x;
	}
	Film getFilm() {
		return film;
	}

	friend ostream& operator<<(ostream&, Bilet);
};

int Bilet::nrBilete = 0;

map<int, Film>retFilme() {
	map<int, Film>Map1 = returnFilme();
	return Map1;
}

ostream& operator<<(ostream& o, Bilet b) {
	//o << (Film)b;
	//cout << endl;
	o << b.nume;
	cout << endl;
	o << b.film;
	return o;
}