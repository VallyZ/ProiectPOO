#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
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
	}

	Film(int id, const char* nume, float durata, int nrZile, string* zi, float start, int filmId) { // folosit in citire din binar
		const_cast<int&>(this->filmId) = filmId;
		if (id > 0) {
			this->id = id;
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
	}

	Film(const Film& f) : filmId(f.filmId) {
		id = f.id;
		if (nume != nullptr) {
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
		if (zi != nullptr) {
			//cout << this->getNume() << endl;
			delete[] zi;
		}
		if (nume != nullptr) {
			delete[] nume;
		}
	}

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
	/*
	string* showZi() {
		if (zi != nullptr) {
			string* copie = new string[nrZile];
			copie = this->getZi();
			cout << "Zile: " << endl;
			for (int i = 0; i < nrZile; i++) {
				if (i != nrZile - 1) {
					cout << copie[i] << ", ";
				}
				else {
					cout << copie[i] << endl;
				}
			}
		}
		return 0;
	}
	*/
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
	/*
		void serialize() { // Scrie in fisier binar un obiect.
			ofstream f("Film.bin", ios::app | ios::binary);
			//f.seekp(0, ios::end);
			cout << f.tellp() << endl;
			f.write((char*)&filmId, sizeof(filmId));
			f.write((char*)&id, sizeof(id));
			int len = nume.length() + 1;
			f.write((char*)&len, sizeof(len));
			f.write(nume.c_str(), len);
			f.write((char*)&durata, sizeof(durata));
			f.write((char*)&nrZile, sizeof(nrZile));
			for (int i = 0; i < nrZile; i++) {
				f.write((char*)&zi[i], sizeof(zi[i]));
			}
			f.write((char*)&start, sizeof(start));
			cout << f.tellp() << endl;
			f.close();
		}
		*/
	void serialize1() { // Scrie in fisier binar un obiect.
		ofstream f("Film1.bin", ios::app | ios::binary);
		if (f.is_open()) {
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
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}
	/*
	void deserialize() {
		ifstream f("Film.bin", ios::binary);
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
		string* zi1 = new string[nrZile];
		for (int i = 0; i < nrZile; i++) {
			f.read((char*)&zi1[i], sizeof(zi1[i])); //ca sa functioneze are nevoie sa stearga ceva alocat.
			zi[i] = zi1[i];
		}
		f.read((char*)&start, sizeof(start));
		f.close();
	}*/
	void deserialize1(int x) { //afiseaza un obiect de la o anumita locatie
		fstream f("Film1.bin", ios::out | ios::in | ios::binary);
		if (f.is_open()) {
			f.seekg(x);
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
			string* zi1 = new string[nrZile];
			for (int i = 0; i < nrZile; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				zi[i] = aux1;
			}
			for (int i = nrZile; i < 7; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
			}
			f.read((char*)&start, sizeof(start));
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


	/*
	void getAll() {
		cout << "Id: " << getId() << endl;
		cout << "Nume: " << getNume() << endl;
		cout << "Durata: " << getDurata() << endl;
		cout << "Nr zile: " << getNrZile() << endl;
		cout << showZi() << endl;
		//cout << "Zi: " << getZi() << endl;
		cout << "Ora de inceput: " << getStart() << endl;
	}
	*/

	friend ostream& operator<<(ostream&, Film);
	friend ofstream& operator<<(ofstream&, Film);
	friend istream& operator>>(istream&, Film&);
	friend ifstream& operator>>(ifstream&, Film&);
	friend Film operator+(float, Film);
	friend bool operator<=(const Film& x, const Film& y) //operator<
	{
		if (x.filmId <= y.filmId) {
			cout << "1<=2" << endl;
			return true;
		}
		else {
			cout << "2<=1" << endl;
			return false;
		}
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
	o << "Durata: " << f.getDurata() << endl;
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
	o << "Ora de inceput: " << f.getStart() << endl;
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

/// //////////////////////////// FLOAT NU APARE CU .00/////////////////////////////////////////

istream& operator>>(istream& i, Film& f) { //cin
	int id;
	char* nume;
	float durata;
	int nrZile = 0;
	float start;
	cout << "Id: ";
	i >> id;
	f.setId(id);
	cout << "Nume: ";
	char buffer[101];
	i.ignore(1);
	i.getline(buffer, 100);
	f.nume = new char[strlen(buffer) + 1];
	strcpy_s(f.nume, strlen(buffer) + 1, buffer);
	cout << "Durata: ";
	i >> durata;
	f.setDurata(durata);
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
	f.setStart(start);
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