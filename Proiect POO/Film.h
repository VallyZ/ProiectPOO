#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include "Cinema.h"
using namespace std;

class Film {
private:
	const int filmId = 0;
	int id;
	//string nume;
	char* nume;
	float durata;
	int nrZile;
	string* zi;
	float start;//ora de incepere 12.00;
	static int numarFilme;

public:
	Film() : filmId(++numarFilme) {
		id = 0;
		//nume = "";
		nume = nullptr;
		durata = 0.0;
		nrZile = 0;
		zi = nullptr;
		start = 0.0;
	}

	Film(int id, const char* nume, float durata, int nrZile, string* zi, float start) : filmId(++numarFilme) {
		if (id > 0) {
			this->id = id;
		}
		else {
			this->id = 0;
		}
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			this->nume = nullptr;
		}
		//this->nume = nume;
		if (durata > 0) {
			this->durata = durata;
		}
		else {
			this->durata = 0;
		}
		if (nrZile > 0 && zi != nullptr) {
			this->zi = new string[nrZile];
			for (int i = 0; i < nrZile; i++) {
				this->zi[i] = zi[i];
			}
			this->nrZile = nrZile;
		}
		else {
			this->zi = nullptr;
			this->nrZile = 0;
		}
		if (start > 0) {
			this->start = start;
		}
		else {
			this->start = 0;
		}
	}

	Film(int id, const char* nume, float durata, int nrZile, string* zi, float start, int filmId) { // folosit in citire din binar
		const_cast<int&>(this->filmId) = filmId;
		if (id > 0) {
			this->id = id;
		}
		else {
			this->id = 0;
		}
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			this->nume = nullptr;
		}
		//this->nume = nume;
		if (durata > 0) {
			this->durata = durata;
		}
		else {
			this->durata = 0;
		}
		if (nrZile > 0 && zi != nullptr) {
			this->zi = new string[nrZile];
			for (int i = 0; i < nrZile; i++) {
				this->zi[i] = zi[i];
			}
			this->nrZile = nrZile;
		}
		else {
			this->zi = nullptr;
			this->nrZile = 0;
		}
		if (start > 0) {
			this->start = start;
		}
		else {
			this->start = 0;
		}
	}

	Film(const Film& f) : filmId(f.filmId) {
		id = f.id;
		if (f.nume != nullptr) {
			this->nume = new char[strlen(f.nume) + 1];
			strcpy_s(this->nume, strlen(f.nume) + 1, f.nume);
		}
		else {
			this->nume = nullptr;
		}
		//nume = f.nume;
		durata = f.durata;
		if (f.nrZile > 0 && f.zi != nullptr) {
			zi = new string[f.nrZile];
			for (int i = 0; i < f.nrZile; i++) {
				zi[i] = f.zi[i];
			}
			nrZile = f.nrZile;
		}
		else {
			zi = nullptr;
			nrZile = 0;
		}
		start = f.start;
	}

	Film& operator=(const Film& f) {
		const_cast<int&>(filmId) = f.filmId;
		id = f.id;
		/*if (nume != nullptr) {
			delete[] nume;
		}*/
		if (f.nume != nullptr) {
			this->nume = new char[strlen(f.nume) + 1];
			strcpy_s(this->nume, strlen(f.nume) + 1, f.nume);
		}
		else {
			this->nume = nullptr;
		}
		//nume = f.nume;
		durata = f.durata;
		if (zi != nullptr) {
			delete[] zi;
		}
		if (f.nrZile > 0 && f.zi != nullptr) {
			zi = new string[f.nrZile];
			for (int i = 0; i < f.nrZile; i++) {
				zi[i] = f.zi[i];
			}
			nrZile = f.nrZile;
		}
		else {
			zi = nullptr;
			nrZile = 0;
		}
		start = f.start;
		return *this;
	}

	~Film() {
		if (nume != nullptr) {
			delete[] nume;
		}
		if (zi != nullptr) {
			//cout << this->getNume() << endl;
			delete[] zi;
		}
	}
	static int getNumarFilme(); //metoda definita in afara clasei.

	int getFilmId() {
		return filmId;
	}
	int getId() {
		return id;
	}
	void setId(int x) {
		if (x > 0) {
			id = x;
		}
		else {
			id = 0;
		}
	}
	char* getNume() {
		return nume;
	}
	void setNume(const char* x) {
		if (strlen(x) > 0) {
			strcpy_s(nume, strlen(x) + 1, x);
		}
		else {
			nume = nullptr;
		}
	}
	float getDurata() {
		return durata;
	}
	void setDurata(float x) {
		if (x > 0) {
			durata = x;
		}
		else {
			durata = 0;
		}
	}
	int getNrZile() {
		return nrZile;
	}
	void setZi(string* x, int zile) {
		if (zi != nullptr) {
			delete[] zi;
		}
		if (x != nullptr && zile > 0) {
			nrZile = zile;
			zi = new string[zile];
			for (int i = 0; i < nrZile; i++) {
				zi[i] = x[i];
			}
		}
		else {
			nrZile = 0;
			zi = nullptr;
		}
	}
	string* getZi() {
		if (zi != nullptr) {
			string* copie = new string[nrZile];
			for (int i = 0; i < nrZile; i++) {
				copie[i] = zi[i];
			}
			return copie;
		}
		else {
			return nullptr;
		}
	}

	float getStart() {
		return start;
	}
	void setStart(float x) {
		if (x > 0) {
			start = x;
		}
		else {
			start = 0;
		}
	}
	void forteazaId(int x) {
		const_cast<int&>(filmId) = x;
	}

	void serialize1() { // Scrie in fisier binar un obiect.
		ofstream f("Film1.bin", ios::app | ios::binary);
		if (f.is_open()) {
			int y = f.tellp();
			cout << y << endl;
			f.write((char*)&filmId, sizeof(filmId));
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&durata, sizeof(durata));
			f.write((char*)&nrZile, sizeof(nrZile));
			int len1 = 101;
			for (int i = 0; i < 7; i++) {
				if (zi[i].length() != 0 && zi[i].length() < 9) {
					f.write((char*)&len1, sizeof(len1));
					f.write(zi[i].c_str(), len1);
				}
				else {
					f.write((char*)&len1, sizeof(len1));
					f.write("", len1);
				}
			}
			f.write((char*)&start, sizeof(start));
			y = f.tellp();
			cout << y << endl;
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}
	void serialize1Bilet(string z) { // pentru a serializa in Bilet
		ofstream f(z, ios::app | ios::binary);
		if (f.is_open()) {
			int y = f.tellp();
			cout << y << endl;
			f.write((char*)&filmId, sizeof(filmId));
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&durata, sizeof(durata));
			f.write((char*)&nrZile, sizeof(nrZile));
			int len1 = 101;
			int siguranta = 0;
			for (int i = 0; i < 7; i++) {
				if (zi != nullptr) {
					if (zi[i].length() != 0 && zi[i].length() < 9 && siguranta == 0) {
						f.write((char*)&len1, sizeof(len1));
						f.write(zi[i].c_str(), len1);
					}
					else {
						f.write((char*)&len1, sizeof(len1));
						f.write("", len1);
						siguranta = 1;
					}
				}
			}
			f.write((char*)&start, sizeof(start));
			//delete[]
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}
	void serialize1BiletLaLoc(string z, int x) { // pentru a serializa in Bilet
		fstream f(z, ios::out | ios::in | ios::binary);
		if (f.is_open()) {
			int y = f.tellp();
			cout << y << endl;
			f.seekp(x);
			f.write((char*)&filmId, sizeof(filmId));
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&durata, sizeof(durata));
			f.write((char*)&nrZile, sizeof(nrZile));
			int len1 = 101;
			int siguranta = 0;
			for (int i = 0; i < 7; i++) {
				if (zi != nullptr) {
					if (zi[i].length() != 0 && zi[i].length() < 9 && siguranta == 0) {
						f.write((char*)&len1, sizeof(len1));
						f.write(zi[i].c_str(), len1);
					}
					else {
						f.write((char*)&len1, sizeof(len1));
						f.write("", len1);
						siguranta = 1;
					}
				}
			}
			f.write((char*)&start, sizeof(start));
			//delete[]
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}
	void serialize1(int x) { // Scrie in fisier binar la o anumita locatie
		fstream f("Film1.bin", ios::out | ios::in | ios::binary);
		if (f.is_open()) {
			f.seekp(x);
			f.write((char*)&filmId, sizeof(filmId));
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&durata, sizeof(durata));
			f.write((char*)&nrZile, sizeof(nrZile));
			int len1 = 101;
			int siguranta = 0;
			for (int i = 0; i < 7; i++) {
				if (zi != nullptr) {
					if (zi[i].length() != 0 && zi[i].length() < 9 && siguranta == 0) {
						f.write((char*)&len1, sizeof(len1));
						f.write(zi[i].c_str(), len1);
					}
					else {
						f.write((char*)&len1, sizeof(len1));
						f.write("", len1);
						siguranta = 1;
					}
				}
			}
			f.write((char*)&start, sizeof(start));
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	void deserialize1(int x) { //afiseaza un obiect de la o anumita locatie
		fstream f("Film1.bin", ios::out | ios::in | ios::binary);
		if (f.is_open()) {
			f.seekg(x);
			int y = f.tellg();
			cout << y << endl;
			f.read((char*)&filmId, sizeof(filmId));
			f.read((char*)&id, sizeof(id));
			int len = 0;
			f.read((char*)&len, sizeof(len));
			char* aux = new char[len];
			f.read(aux, len);
			nume = aux;
			f.read((char*)&durata, sizeof(durata));
			f.read((char*)&nrZile, sizeof(nrZile));
			delete[] zi;
			zi = new string[nrZile];
			//string* zi1 = new string[nrZile];
			for (int i = 0; i < nrZile; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				zi[i] = aux1;
				delete[] aux1;
			}
			for (int i = nrZile; i < 7; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				delete[] aux1;
			}
			f.read((char*)&start, sizeof(start));
			//delete[] aux;
			y = f.tellg();
			cout << y << endl;
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	string& operator[](int x) { //operator []
		if (x >= 0 && x < nrZile) {
			return zi[x];
		}
		else {
			cout << "Ziua introdusa nu exista." << endl;
		}
	}

	Film operator+(float x) {//operator + la stanga
		float z = 24 - start;
		if (x >= 0 && x <= z) {
			Film f = *this;
			f.start += x;
			return f;
		}
		else {
			cout << "Adunarea excede ora 24" << endl;
			return *this;
		}
	}

	Film operator++() {//preincrementare
		if (start + 1 < 25) {
			this->start++;
			return *this;
		}
		else {
			cout << "Adunarea excede ora 24" << endl;
			return *this;
		}
	}

	Film operator++(int i) {//postincrementare
		if (start + 1 < 25) {
			Film f = *this;
			this->start++;
			return f;
		}
		else {
			cout << "Adunarea excede ora 24" << endl;
			Film f = *this;
			return f;
		}
	}

	Film operator--() {//predencrementare
		if (start - 1 > 0) {
			this->start--;
			return *this;
		}
		else {
			cout << "Scaderea excede ora 0" << endl;
			return *this;
		}
	}

	Film operator--(int i) {//postdecrementare
		if (start - 1 > 0) {
			Film f = *this;
			this->start--;
			return f;
		}
		else {
			cout << "Scaderea excede ora 0" << endl;
			Film f = *this;
			return f;
		}
	}

	explicit operator int() {//cast explicit
		return filmId;
	}

	bool operator!() { //operator !
		return nrZile > 0;
	}

	friend ostream& operator<<(ostream&, Film);
	friend ofstream& operator<<(ofstream&, Film);
	friend istream& operator>>(istream&, Film&);
	friend ifstream& operator>>(ifstream&, Film&);
	friend Film operator+(float, Film);
	friend bool operator<=(const Film& x, const Film& y) //operator<
	{
		if (x.filmId <= y.filmId) {
			cout << "1<=2" << endl;
			return x.filmId < y.filmId;
			//return true;
		}
		else {
			return x.filmId >= y.filmId;
			//return false;
		}
	}
	friend bool operator<(const Film& x, const Film& y) {
		return x.filmId < y.filmId;
	}
	friend bool operator==(const Film& x, const Film& y) //operator==
	{
		if (x.nrZile == y.nrZile) {
			cout << "Numar de zile egale." << endl;
			return true;
		}
		else {
			cout << "Numar de zile inegale." << endl;
			return false;
		}
	}
	//////////////////////////////////FA SETTERE PENTRU TOATE ATRIBUTELE////////////////////////
};


Film operator+(float x, Film f) {//operator + la dreapta
	float z = 24 - f.start;
	if (x >= 0 && x <= z) {
		//Film f = *this;
		f.start = f.start + x;
		return f;
	}
	else {
		cout << "Adunarea excede ora 24" << endl;
		return f;

	}
}

ostream& operator<<(ostream& o, Film f) { //cout
	o << endl;
	o << "Film id: " << f.filmId << endl;
	o << "Id: " << f.getId() << endl;
	if (f.nume != nullptr) {
		o << "Nume: " << f.getNume() << endl;
	}
	o << "Durata: " << fixed << setprecision(2) << f.getDurata() << endl;
	o << "Nr zile: " << f.getNrZile() << endl;
	if (f.zi != nullptr) {
		for (int i = 0; i < f.getNrZile(); i++) {
			if (i != f.getNrZile() - 1) {
				o << f.zi[i] << ", ";
			}
			else {
				o << f.zi[i] << endl;
			}
		}
	}
	o << "Ora de inceput: " << fixed << setprecision(2) << f.getStart() << endl;
	return o;
}

ofstream& operator<<(ofstream& of, Film f) {
	if (of.is_open()) {
		of << f.filmId << endl;
		of << f.id << endl;
		if (f.nume != nullptr) {
			of << f.nume << endl;
		}
		of << f.durata << endl;
		of << f.nrZile << endl;
		if (f.zi != nullptr) {
			for (int i = 0; i < f.nrZile; i++) {
				of << f.zi[i] << " ";
			}
		}
		of << endl;
		of << f.start << endl;
	}
	return of;
}

istream& operator>>(istream& i, Film& f) { //cin
	void affArrIdF();
	affArrIdF();
	int* arrIdF();
	int* arr = arrIdF();
	int nrFilme();
	int max = nrFilme();
	//cout << max << endl;
	int gasit = 0;
	int id;
	char* nume;
	float durata;
	int nrZile = 0;
	float start;
	cout << "Id: ";
	i >> id;
	for (int i = 0; i < max; i++) {
		if (arr[i] == id) {
			gasit = 1;
		}
	}
	if (id > 0 && gasit == 0) {
		f.setId(id);
		
	}
	else {
		cout << "Eroare la introducerea id-ului." << endl;
		cout << "Id-ul trebuie sa fie unic si > 0." << endl;
		f.setId(0);
	}
	cout << "Nume: ";
	char buffer[101];
	i.ignore(1);
	i.getline(buffer, 100);
	f.nume = new char[strlen(buffer) + 1];
	strcpy_s(f.nume, strlen(buffer) + 1, buffer);
	cout << "Durata: ";
	i >> durata;
	if (durata > 0) {
		f.setDurata(durata);
	}
	else {
		f.setDurata(0);
	}
	cout << "Nr zile(maxim 7): ";
	i >> nrZile;
	while (nrZile < 0 && nrZile>7) {
		cout << "Numarul de zile nu poate fi < 0 si > 7." << endl;
		cout << "Nr zile(maxim 7): ";
		i >> nrZile;
	}
	string* zi = new string[nrZile];
	//cout << "Zile:";
	for (int y = 0; y < nrZile; y++) {
		cout << "Ziua[" << y + 1 << "]: ";
		i >> zi[y];
	}
	f.setZi(zi, nrZile);
	cout << "Ora de inceput: ";
	i >> start;
	if (start >= 0) {
		f.setStart(start);
	}
	else {
		f.setStart(0);
	}

	return i;
}

ifstream& operator>>(ifstream& i, Film& f) {
	if (i.is_open()) {
		int id;
		char* nume;
		float durata;
		int nrZile;
		float start;
		int filmId;
		i >> filmId;
		const_cast<int&>(f.filmId) = filmId;
		i >> id;
		f.setId(id);
		//i >> ws;
		//getline(i, nume);
		//f.setNume(nume);
		char buffer[101];
		i.clear();
		i.ignore(2);
		i.getline(buffer, 100);
		f.nume = new char[strlen(buffer) + 1];
		strcpy_s(f.nume, strlen(buffer) + 1, buffer);
		i >> durata;
		f.setDurata(durata);
		i >> nrZile;
		if (nrZile > 0) {
			string* zi = new string[nrZile];
			for (int y = 0; y < nrZile; y++) {
				i >> zi[y];
			}
			f.setZi(zi, nrZile);
		}
		else {
			f.nrZile = 0;
			f.zi = nullptr;
		}
		i >> start;
		f.setStart(start);
		return i;
	}
}

int Film::numarFilme = 0;


int nrFilme() {
	ifstream f("Film1.bin", ios::binary);
	if (f.is_open()) {
		f.seekg(0, ios::end);
		int x = f.tellg();
		int z = x / 860;
		f.close();
		return z;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
		return 0;
	}
}

void ordoneazaFilmId() {
	fstream f("Film1.bin", ios::in | ios::out | ios::binary);
	if (f.is_open()) {
		int filmId = 1;
		for (int i = 0; i < nrFilme(); i++) {
			f.seekg(i * 860);
			f.write((char*)&filmId, sizeof(filmId));
			filmId++;
		}
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

map<int, Film> citireFilme() { // afiseaza toate filmele din fisier
	map<int, Film> Map;
	int i = 0;
	ifstream f("Film1.bin", ios::binary);
	if (f.is_open()) {
		int x = f.tellg();
		f.seekg(0, ios::end);
		int y = f.tellg();
		f.seekg(0, ios::beg);
		while (x != y) {
			int filmId = 0; int id = 0; int nrZile = 0;
			char* nume = nullptr;
			float durata = 0; float start = 0;
			f.read((char*)&filmId, sizeof(filmId));
			f.read((char*)&id, sizeof(id));
			int len = 0;
			f.read((char*)&len, sizeof(len));
			char* aux = new char[len];
			f.read(aux, len);
			nume = aux;
			
			f.read((char*)&durata, sizeof(durata));
			f.read((char*)&nrZile, sizeof(nrZile));
			string* zi = new string[nrZile];
			for (int i = 0; i < nrZile; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				zi[i] = aux1;
				delete[] aux1;
			}
			for (int i = nrZile; i < 7; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				delete[] aux1;
			}
			f.read((char*)&start, sizeof(start));
			if (id > 0) {
				Film placeHolder(id, nume, durata, nrZile, zi, start, filmId);
				if (placeHolder.getFilmId() > 0) {
					Map[i] = placeHolder;
					i++;
				}
			}
			x = f.tellg();
			//delete[] aux;
			delete[] zi;
		}
		return Map;
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void stergeBazaDateFilme1() {
	ofstream f("Film1.bin", ios::trunc | ios::binary);
	if (f.is_open()) {
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

map<int, Film> returnFilme() {
	map<int, Film>Map1 = citireFilme();
	return Map1;
}

void afiseazaFilme() {
	map<int, Film>Map1 = citireFilme();
	for (int i = 0; i < Map1.size(); i++) {
		cout << Map1[i] << endl;
	}
	//cout << Film::getNumarFilme() << endl;
}
int Film::getNumarFilme() {
	map<int, Film>Map1 = citireFilme();
	return numarFilme;
}

void afiseazaNumarFilme() { //foloseste static int numarFilme in loc de calcule pe fisier(nrFilme()).
	int u = Film::getNumarFilme();
	cout << u << endl;
}

int* returnAtrLoc() { // creaza vector cu locatiile fiecarui atribut al clasei Film
	ifstream f("Film1.bin", ios::binary);
	if (f.is_open()) {
		int filmId = 0; int id = 0; int nrZile = 0;
		char* nume = nullptr;
		float durata = 0; float start = 0;
		int locFilmId = 0; int locId = 0; int locNume = 0; int locDurata = 0; int locNrZile = 0; int locZi[] = { 0,0,0,0,0,0,0 }; int locStart = 0;
		locFilmId = f.tellg();
		f.read((char*)&filmId, sizeof(filmId));
		locId = f.tellg();
		f.read((char*)&id, sizeof(id));
		locNume = f.tellg();
		int len = 0;
		f.read((char*)&len, sizeof(len));
		char* aux = new char[len];
		f.read(aux, len);
		nume = aux;
		//delete[] aux;
		locDurata = f.tellg();
		f.read((char*)&durata, sizeof(durata));
		locNrZile = f.tellg();
		f.read((char*)&nrZile, sizeof(nrZile));
		string* zi = new string[nrZile];
		for (int i = 0; i < nrZile; i++) {
			int len1 = 0;
			locZi[i] = f.tellg();
			f.read((char*)&len1, sizeof(len1));
			char* aux1 = new char[len1];
			f.read(aux1, len1);
			zi[i] = aux1;
			delete[] aux1;
		}
		for (int i = nrZile; i < 7; i++) {
			int len1 = 0;
			locZi[i] = f.tellg();
			f.read((char*)&len1, sizeof(len1));
			char* aux1 = new char[len1];
			f.read(aux1, len1);
			delete[] aux1;
		}
		locStart = f.tellg();
		f.read((char*)&start, sizeof(start));
		static int returnDate[] = { locFilmId, locId, locNume, locDurata, locNrZile, locZi[0], locZi[1], locZi[2], locZi[3], locZi[4], locZi[5], locZi[6], locStart };
		delete[] zi;
		f.close();
		return returnDate;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

int* arrIdFilme() { // return array cu id-urile filmelor
	int* arrIdFilme = new int[nrFilme()];
	const int nrf = nrFilme();
	//int arrIdFilme[nrf];
	ifstream f("Film1.bin", ios::binary);
	if (f.is_open()) {
		for (int i = 0; i < nrf; i++) {
			int x = 0;
			f.seekg(i * 860);
			f.read((char*)&x, sizeof(x));
			arrIdFilme[i] = x;
		}
		f.close();
		return arrIdFilme;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

int* arrIdF() { // return array cu id-urile introduse de la tastatura
	int* arrIdFilme = new int[nrFilme()];
	const int nrf = nrFilme();
	//int arrIdFilme[nrf];
	ifstream f("Film1.bin", ios::binary);
	if (f.is_open()) {
		for (int i = 0; i < nrf; i++) {
			int x = 0;
			f.seekg(i * 860);
			f.read((char*)&x, sizeof(x));
			f.read((char*)&x, sizeof(x));
			arrIdFilme[i] = x;
		}
		f.close();
		return arrIdFilme;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void affArrIdFilme() {
	int* arr = arrIdFilme();
	cout << "Exista urmatoarele filme cu Id: " << endl;
	for (int i = 0; i < nrFilme(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void affArrIdF() {
	int* arr = arrIdF();
	cout << "Exista urmatoarele filme cu Id: " << endl;
	for (int i = 0; i < nrFilme(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int locFilmCuId() { //returneaza locatia unui film in fisier
	ifstream h("Film1.bin", ios::binary);
	if (h.is_open()) {
		int x1 = 0;
		int locatie = 0;
		int gasit = 0;
		affArrIdFilme();
		cout << "Introdu id-ul filmului pe care vrei sa il gasesti: " << endl;
		cin >> x1;
		for (int i = 0; i < nrFilme(); i++) {
			int id = 0;
			h.seekg((long long)i * 860);
			h.read((char*)&id, sizeof(id));
			if (id == x1) {
				locatie = h.tellg();
				locatie -= 4;
				gasit = 1;
				break;
			}
		}h.close();
		if (gasit != 1) {
			cout << "Id-ul introdus nu exista." << endl;
		}
		else {
			return locatie;
		}
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void afiseazaFilmCuId() { // afiseaza un film existent in fisier
	int z = locFilmCuId();
	Film o;
	o.deserialize1(z);
	cout << o << endl;
}

void inlocuieFilmCuId() { // inlocuie un film cu unul introdus de la tastatura
	ifstream h("Film1.bin", ios::binary);
	if (h.is_open()) {
		int x1 = 0;
		int locatie = 0;
		int gasit = 0;
		affArrIdFilme();
		//cout << endl;
		cout << "Introdu id-ul filmului pe care vrei sa il inlocuiesti: " << endl;
		cin >> x1;
		for (int i = 0; i < 3; i++) {
			int id = 0;
			h.seekg((long long)i * 860);
			h.read((char*)&id, sizeof(id));
			if (id == x1) {
				locatie = h.tellg();
				locatie -= 4;
				gasit = 1;
				break;
			}
		}h.close();
		if (gasit == 1) {
			Film nou;
			cin >> nou;
			nou.serialize1(locatie);
			ordoneazaFilmId();
			cout << "Film introdus cu succes." << endl;
		}
		else {
			cout << endl;
			cout << "Id-ul introdus nu a fost gasit." << endl;
		}
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void stergeFilm() { // sterge un film din fisier
	afiseazaFilme();
	int x1 = 0;
	int gasit = 0;
	affArrIdFilme();
	cout << endl;
	int* id = arrIdFilme();
	cout << "Introdu id-ul filmului pe care vrei sa il stergi: (Film id: )" << endl;
	cin >> x1;
	for (int i = 0; i < nrFilme(); i++) {
		if (x1 == id[i]) {
			gasit = 1;
		}
	}if (gasit == 1) {
		int sigur = 0;
		map<int, Film>Map = returnFilme();
		for (int i = 0; i < Map.size(); i++) {
			cout << Map[i] << endl;
		}
		cout << "Esti sigur ca vrei sa stergi filmul cu Id : " << x1 << " ?" << endl;
		cout << "\t1)Da\n\t*)Nu\nAlegere: " << endl;
		cin >> sigur;
		if (sigur == 1) {
			for (int i = 0; i < Map.size(); i++) {
				if (Map[i].getFilmId() == x1) {
					void stergeFilmDinCinema(int h, int g); // sterge filmul g din fisierul cinemaul h
					int* arr = arrIdC();
					int max = nrCinemauri();
					cout << "Gasit" << endl;
					for (int j = 0; j < max; j++) {
						stergeFilmDinCinema(arr[j], Map[i].getId());
					}
					Map.erase(i);

					break;
				}
			}
			stergeBazaDateFilme1();
			for (map<int, Film>::iterator it = Map.begin(); it != Map.end(); it++) {
				it->second.serialize1();
			}
			ordoneazaFilmId();
		}
		else {
			cout << "Filmul nu a fost sters." << endl;
		}
	}
	else {
		cout << "Id-ul introdus nu exista." << endl;
	}
}

void schimbaAtributFilm() { //modifica atributul unui film
	int atr = 0;
	int x1 = 0;
	int x2 = 0;
	float x3 = 0;
	int x4 = 0;
	float x5 = 0;
	char* nume = nullptr;
	string nume1 = "";
	x1 = locFilmCuId();
	Film o;
	o.deserialize1(x1);
	cout << "Modifica:\n\t1)Id\n\t2)Nume\n\t3)Durata\n\t4)Zile\n\t5)Ora de incepere\nAlegere: ";
	cin >> atr;
	switch (atr) {
	case 1:
		cout << "Introdu noul Id: " << endl;
		cin >> x2;
		if (x2 > 0) {
			o.setId(x2);
			o.serialize1(x1);
			break;
		}
		else {
			cout << "Id-ul nu poate fi < 0." << endl;
			break;
		}
	case 2:
		cout << "Introdu noul Nume: " << endl;
		char buffer[101];
		cin.ignore(1);
		cin.getline(buffer, 100);
		nume = new char[strlen(buffer) + 1];
		strcpy_s(nume, strlen(buffer) + 1, buffer);
		if (strlen(nume) > 0) {
			o.setNume(nume);
			o.serialize1(x1);
			//delete[] nume;
			break;
		}
		else {
			cout << "Numele nu poate fi null." << endl;
			break;
		}
	case 3:
		cout << "Introdu noua Durata: " << endl;
		cin >> x3;
		if (x3 > 0) {
			o.setDurata(x3);
			o.serialize1(x1);
			break;
		}
		else {
			cout << "Durata nu poate fi < 0." << endl;
			break;
		}
	case 4:
		cout << "Introdu numarul de zile(maxim 7): " << endl;
		cin >> x4;
		if (x4 > 0 && x4 <= 7) {
			string* y = new string[x4];
			for (int i = 0; i < x4; i++) {
				cout << "Introdu ziua[" << i + 1 << "]: ";
				cin >> y[i];
			}
			o.setZi(y, x4);
			o.serialize1(x1);
			//delete[]y;
			break;
		}
		else {
			cout << "Numarul de zile nu poate fi < 0 sau > 7.";
			break;
		}
	case 5:
		cout << "Introdu noua Ora de start: " << endl;
		cin >> x5;
		if (x5 > 0 && x5 <= 24) {
			o.setStart(x5);
			o.serialize1(x1);
			break;
		}
		else {
			cout << "Ora de inceput nu poate fi < 0 sau > 24.";
			break;
		}
	default:
		cout << "Alegere invalida." << endl;
	}
}

void introduFilmInCinema(int h, int b) { // introdu filmul cu id b in cinemaul h
	int* arr = arrIdF();
	int* arr3 = arrIdC();
	int max3 = nrCinemauri();
	int gasit = 0;
	int gasit2 = 0;
	int gasit3 = 0;
	int max = nrFilme();
	for (int i = 0; i < max; i++) {
		if (arr[i] == b) {
			gasit = 1;
			break;
		}
	}
	if (gasit == 1) {
		int* returnFilmeDinCinema(int);
		int returnNrFilmeDinCinema(int);
		int* arr2 = returnFilmeDinCinema(h);
		int max2 = returnNrFilmeDinCinema(h);
		for (int i = 0; i < max2; i++) {
			if (arr2[i] == b) {
				gasit2 = 1;
				cout << "Filmul cu id: " << b <<" exista deja in cinemaul: "<< h << "." << endl;
				break;
			}
		}
		if (gasit2 == 0) {
			for (int i = 0; i < max3; i++) {
				if (arr3[i] == h) {
					gasit3 = 1;
					break;
				}
			}if (gasit3 == 1) {
				int loc = 50;
				string x, y, z;
				x = "cinema";
				y = ".bin";
				z = x + to_string(h) + y;
				ofstream f(z, ios::app | ios::binary | ios::_Nocreate );
				if (f.is_open()) {
					f.write((char*)&b, sizeof(b));
					f.write((char*)&loc, sizeof(loc));
					f.close();
				}
			}
			else {
				cout << "Eroare la deschiderea fisierului.(nu este creat)" << endl;
			}
		}
	}
	else {
		cout << "Id-ul introdus nu exista." << endl;
	}
}

int* returnFilmeDinCinema(int h){// returneaza vector de id-uri de filme din cinemaul h 
	int* ret = new int[100];
	int i = 0;
	string x, y, z;
	x = "cinema";
	y = ".bin";
	z = x + to_string(h) + y;
	fstream f(z, ios::in | ios::out | ios::binary);
	if (f.is_open()) {
		int x1 = f.tellg();
		f.seekg(0, ios::end);
		int x2 = f.tellg();
		f.seekg(0, ios::beg);
		while (x1 != x2) {
			int x3 = 0;
			int x4 = 0;
			f.read((char*)&x3, sizeof(x3));
			f.read((char*)&x4, sizeof(x4));
			ret[i] = x3;
			i++;
			x1 = f.tellg();
		}
		f.close();
	}
	return ret;
}

int returnNrFilmeDinCinema(int h) { // returneaza numarul de filme din cinemaul h
	int ret = 0;
	int i = 0;
	string x, y, z;
	x = "cinema";
	y = ".bin";
	z = x + to_string(h) + y;
	fstream f(z, ios::in | ios::out | ios::binary);
	if (f.is_open()) {
		int x1 = f.tellg();
		f.seekg(0, ios::end);
		int x2 = f.tellg();
		ret = x2 / 8;
		f.close();
	}
	return ret;
}

void introduToateFilmeleInCinema() { // introdu toate filmele in toate cinemaurile
	int* z = arrIdC();
	int* zz = arrIdF();
	for (int i = 0; i < nrCinemauri(); i++) {
		for (int j = 0; j < nrFilme(); j++) {
			introduFilmInCinema(z[i], zz[j]);
		}
	}
}

void introduToateFilmeleInCinemaul(int h) { // introdu toate filmele in cinemaul h
	int* z = arrIdC();
	int* zz = arrIdF();
	for (int i = 0; i < nrCinemauri(); i++) {
		for (int j = 0; j < nrFilme(); j++) {
			if (z[i] == h) {
				introduFilmInCinema(z[i], zz[j]);
			}
		}
	}
}

void afiseazaFilmInCinema(int h) { // afiseaza id-ul si numarul de locuri libere din cinemaul h
	int id = 0;
	int loc = 0;
	string x, y, z;
	x = "cinema";
	y = ".bin";
	z = x + to_string(h) + y;
	fstream f(z, ios::in | ios::out | ios::binary);
	if (f.is_open()) {
		int x1 = f.tellg();
		f.seekg(0, ios::end);
		int x2 = f.tellg();
		f.seekg(0, ios::beg);
		cout << endl;
		cout << endl;
		cout << "Cinema: " << h << endl;
		while (x1 != x2) {
			f.read((char*)&id, sizeof(id));
			f.read((char*)&loc, sizeof(loc));
			cout << endl;
			cout << "Id film: " << id << endl;
			cout << "Locuri libere: " << loc << endl;
			//int k = f.tellp();
			//cout << k << endl;
			x1 = f.tellg();
		}
		f.close();
	}
}

void afiseazaToateFilmeleDinCinema() { // afiseaza toate filmele din toate cinemaurile
	int* z = arrIdC();
	for (int i = 0; i < nrCinemauri(); i++) {
		afiseazaFilmInCinema(z[i]);
	}
}

void stergeFilmDinCinema(int h, int g) { // sterge filmul g din fisierul cinemaul h
	if (h > 0) {
		string x, y, z;
		x = "cinema";
		y = ".bin";
		z = x + to_string(h) + y;
		int x3 = 0;
		int x4 = 0;
		map<int, int>Map;
		fstream f(z, ios::in | ios::out | ios::binary);
		if (f.is_open()) {
			int x1 = f.tellg();
			f.seekg(0, ios::end);
			int x2 = f.tellg();
			f.seekg(0, ios::beg);
			while (x1 != x2) {
				f.read((char*)&x3, sizeof(x3));
				f.read((char*)&x4, sizeof(x4));
				if (x3 != g) {
					Map[x3] = x4;
				}
				x1 = f.tellg();
			}
			f.close();
		}
		remove(z.c_str());
		creazaFisierLocuri(h);
		fstream ff(z, ios::in | ios::out | ios::binary);
		for (map<int, int>::iterator it = Map.begin(); it != Map.end(); it++) {
			ff.write((char*)&it->first, sizeof(it->first));
			ff.write((char*)&it->second, sizeof(it->second));
		}
		ff.close();
	}
}

void introduFilm() {
	Film p;
	cin >> p;
	if (p.getId() != 0) {
		p.serialize1();
		ordoneazaFilmId();
	}
	else {
		cout << "Filmul nu a fost introdus." << endl;
	}
}

void stergeToateFilmeleDinCinema(int h) {
	int* arr = arrIdF();
	int max = nrFilme();
	for (int i = 0; i < max; i++) {
		stergeFilmDinCinema(h, arr[i]);
	}
	cout << "Toate filmele din cinemaul " << h << " au fost sterse." << endl;
}

int returnLocuriLibereFilm(int h, int g) {
	string x, y, z;
	x = "cinema";
	y = ".bin";
	z = x + to_string(h) + y;
	int x3 = 0;
	int x4 = 0;
	ifstream f(z, ios::binary);
	if (f.is_open()) {
		int x1 = f.tellg();
		f.seekg(0, ios::end);
		int x2 = f.tellg();
		f.seekg(0, ios::beg);
		while (x1 != x2) {
			f.read((char*)&x3, sizeof(x3));
			f.read((char*)&x4, sizeof(x4));
			if (x3 == g) {
				return x4;
			}
			x1 = f.tellg();
		}
		return 0;
		f.close();
	}
}