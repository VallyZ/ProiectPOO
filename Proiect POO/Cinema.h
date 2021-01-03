#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <set>
#include <algorithm> 
using namespace std;

class Cinema {
private:
	const int cinemaId = 0;
	int id;
	char* nume;
	string oras;
	string adresa;
	int nrZile;
	string* zi;
	static int numarCinemauri;

public:
	Cinema() : cinemaId(++numarCinemauri) {
		id = 0;
		nume = nullptr;
		oras = "";
		adresa = "";
		nrZile = 0;
		zi = nullptr;
	}

	Cinema(int id, const char* nume, string oras, string adresa, int nrZile, string* zi) :cinemaId(++numarCinemauri) {
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
		this->oras = oras;
		this->adresa = adresa;
		if ((nrZile > 0 && nrZile <= 7) && zi != nullptr) {
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
	}

	Cinema(int id, const char* nume, string oras, string adresa, int nrZile, string* zi, int cinemaId) { // folosit la citirea din binar
		const_cast<int&>(this->cinemaId) = cinemaId;
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
		this->oras = oras;
		this->adresa = adresa;
		if ((nrZile > 0 && nrZile <= 7) && zi != nullptr) {
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
	}

	Cinema(const Cinema& c) :cinemaId(c.cinemaId) {
		id = c.id;
		if (c.nume != nullptr) {
			nume = new char[strlen(c.nume) + 1];
			strcpy_s(nume, strlen(c.nume) + 1, c.nume);
		}
		else {
			nume = nullptr;
		}
		oras = c.oras;
		adresa = c.adresa;
		if ((c.nrZile > 0 && c.nrZile <= 7) && c.zi != nullptr) {
			zi = new string[c.nrZile];
			for (int i = 0; i < c.nrZile; i++) {
				zi[i] = c.zi[i];
			}
			nrZile = c.nrZile;
		}
		else {
			zi = nullptr;
			nrZile = 0;
		}
	}

	Cinema& operator=(const Cinema& c) {
		const_cast<int&>(cinemaId) = c.cinemaId;
		id = c.id;
		if (nume != nullptr) {
			delete[] nume;
		}
		if (c.nume != nullptr) {
			nume = new char[strlen(c.nume) + 1];
			strcpy_s(nume, strlen(c.nume) + 1, c.nume);
		}
		else {
			nume = nullptr;
		}
		oras = c.oras;
		adresa = c.adresa;
		if (zi != nullptr) {
			delete[] zi;
		}
		if ((c.nrZile > 0 && c.nrZile < 7) && c.zi != nullptr) {
			zi = new string[c.nrZile];
			for (int i = 0; i < c.nrZile; i++) {
				zi[i] = c.zi[i];
			}
			nrZile = c.nrZile;
		}
		else {
			zi = nullptr;
			nrZile = 0;
		}
		return *this;
	}

	~Cinema() {
		if (nume != nullptr) {
			delete[] nume;
		}
		if (zi != nullptr) {
			delete[] zi;
		}
	}
	static int getNumarCinemauri() {
		return numarCinemauri;
	}

	int getCinemaId() {
		return cinemaId;
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
		if (x != nullptr) {
			if (nume != nullptr) {
				delete[] nume;
			}
			if (strlen(x) > 0) {
				nume = new char[strlen(x) + 1];
				strcpy_s(nume, strlen(x) + 1, x);
			}
		}
		else {
			nume = nullptr;
		}
	}
	string getOras() {
		return oras;
	}
	void setOras(string x) {
		if (x.length() > 0) {
			oras = x;
		}
		else {
			oras = "'Eroare la introducerea Orasului'";
		}
	}
	string getAdresa() {
		return adresa;
	}
	void setAdresa(string x) {
		if (x.length() > 0) {
			adresa = x;
		}
		else {
			adresa = "'Eroare la introducerea Orasului'";
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
	void forteazaId(int x) {
		const_cast<int&>(cinemaId) = x;
	}

	void serialize() {
		ofstream f("Cinema.bin", ios::app | ios::binary);
		if (f.is_open()) {
			f.write((char*)&cinemaId, sizeof(cinemaId));
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&len, sizeof(len));
			f.write(oras.c_str(), len);
			f.write((char*)&len, sizeof(len));
			f.write(adresa.c_str(), len);
			f.write((char*)&nrZile, sizeof(nrZile));
			int i = 0;
			int siguranta = 0;
			for (i; i < 7; i++) {
				if (!zi[i].empty() && zi[i].length() < 9 && siguranta == 0) {
					f.write((char*)&len, sizeof(len));
					f.write(zi[i].c_str(), len);
				}
				else {
					f.write((char*)&len, sizeof(len));
					f.write("", len);
					siguranta = 1;
				}
			}
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	void serializeBilet(string x) { //  pentru a serializa in Bilet.bin
		ofstream f(x, ios::app | ios::binary);
		if (f.is_open()) {
			int y = f.tellp();
			cout << y << endl;
			f.write((char*)&cinemaId, sizeof(cinemaId));
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&len, sizeof(len));
			f.write(oras.c_str(), len);
			f.write((char*)&len, sizeof(len));
			f.write(adresa.c_str(), len);
			f.write((char*)&nrZile, sizeof(nrZile));
			int i = 0;
			int siguranta = 0;
			for (i; i < 7; i++) {
				if (!zi[i].empty() && zi[i].length() < 9 && siguranta ==0) {
					f.write((char*)&len, sizeof(len));
					f.write(zi[i].c_str(), len);
				}
				else {
					f.write((char*)&len, sizeof(len));
					f.write("", len);
					siguranta = 1;
				}
			}
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	void serializeBiletLaLoc(string x, int z) { //  pentru a serializa in Bilet.bin la o anumita locatie
		fstream f(x, ios::out | ios::in | ios::binary);
		if (f.is_open()) {
			int y = f.tellp();
			cout << y << endl;
			f.seekp(z);
			f.write((char*)&cinemaId, sizeof(cinemaId));
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&len, sizeof(len));
			f.write(oras.c_str(), len);
			f.write((char*)&len, sizeof(len));
			f.write(adresa.c_str(), len);
			f.write((char*)&nrZile, sizeof(nrZile));
			int i = 0;
			int siguranta = 0;
			for (i; i < 7; i++) {
				if (!zi[i].empty() && zi[i].length() < 9 && siguranta == 0) {
					f.write((char*)&len, sizeof(len));
					f.write(zi[i].c_str(), len);
				}
				else {
					f.write((char*)&len, sizeof(len));
					f.write("", len);
					siguranta = 1;
				}
			}
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	void serialize(int x) {
		fstream f("Cinema.bin", ios::out | ios::in | ios::binary);
		if (f.is_open()) {
			f.seekp(x);
			f.write((char*)&cinemaId, sizeof(cinemaId));
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&len, sizeof(len));
			f.write(oras.c_str(), len);
			f.write((char*)&len, sizeof(len));
			f.write(adresa.c_str(), len);
			f.write((char*)&nrZile, sizeof(nrZile));
			int i = 0;
			int siguranta = 0;
			for (i; i < 7; i++) {
				if (!zi[i].empty() && zi[i].length() < 9 && siguranta == 0) {
					f.write((char*)&len, sizeof(len));
					f.write(zi[i].c_str(), len);
				}
				else {
					f.write((char*)&len, sizeof(len));
					f.write("", len);
					siguranta = 1;
				}
			}
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}
	void deserialize(int x) {
		fstream f("Cinema.bin", ios::out | ios::in | ios::binary);
		if (f.is_open()) {
			f.seekg(x);
			f.read((char*)&cinemaId, sizeof(cinemaId));
			f.read((char*)&id, sizeof(id));
			int len = 0;
			f.read((char*)&len, sizeof(len));
			char* aux = new char[len];
			f.read(aux, len);
			nume = aux;
			
			int len1 = 0;
			f.read((char*)&len1, sizeof(len1));
			char* aux1 = new char[len1];
			f.read(aux1, len1);
			oras = aux1;
			delete[] aux1;
			int len2 = 0;
			f.read((char*)&len2, sizeof(len2));
			char* aux2 = new char[len2];
			f.read(aux2, len2);
			adresa = aux2;
			delete[] aux2;
			f.read((char*)&nrZile, sizeof(nrZile));
			delete[] zi;
			zi = new string[nrZile];
			for (int i = 0; i < nrZile; i++) {
				len = 0;
				f.read((char*)&len, sizeof(len));
				char* aux1 = new char[len];
				f.read(aux1, len);
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
			//int u = f.tellg(); // 1062
			//cout << u << endl;
			//delete[] aux;
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
	Cinema operator+(int x) {//operator + la stanga
		int z = id + x;
		if (z>0) {
			Cinema f = *this;
			f.id += x;
			return f;
		}
		else {
			cout << "Adunarea nu poate rezulta <= 0." << endl;
			return *this;
		}
	}
	Cinema operator++() {//preincrementare
			id++;
			return *this;
	}
	Cinema operator++(int x) {//postincrementare
		Cinema c = *this;
		id++;
		return c;
	}
	Cinema operator--() {//predencrementare
		if (id - 1 > 0) {
			id--;
			return *this;
		}
		else {
			cout << "Scaderea nu poate rezulta <= 0" << endl;
			return *this;
		}
	}
	Cinema operator--(int x) {//postdecrementare
		Cinema c = *this;
		if (id - 1 > 0) {
			id--;
			return c;
		}
		else {
			cout << "Scaderea nu poate rezulta <= 0" << endl;
			return c;
		}
	}
	explicit operator int() {//cast explicit
		return cinemaId;
	}
	bool operator!() { //operator !
		return nrZile > 0;
	}

	friend ostream& operator<<(ostream&, Cinema);
	friend ofstream& operator<<(ofstream&, Cinema);
	friend istream& operator>>(istream&, Cinema&);
	friend ifstream& operator>>(ifstream&, Cinema&);
	friend bool operator<(const Cinema& x,const Cinema& y){
		return x.cinemaId < y.cinemaId;
	}
	friend Cinema operator+(int, Cinema);
	friend bool operator==(const Cinema& x, const Cinema& y) //operator==
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
};

int Cinema::numarCinemauri = 0;

Cinema operator+(int x, Cinema c) {//operator + la dreapta
	int z = c.id + x;
	if (z > 0) {
		c.id += x;
		return c;
	}
	else {
		cout << "Adunarea nu poate rezulta < 0." << endl;
		return c;
	}
}

ostream& operator<<(ostream& o, Cinema c) { // cout
	o << endl;
	o << "Cinema id: " << c.cinemaId << endl;
	o << "Id: " << c.id << endl;
	if (c.nume != nullptr) {
		o << "Nume: " << c.nume << endl;
	}
	o << "Oras: " << c.oras << endl;
	o << "Adresa: " << c.adresa << endl;
	o << "Nr zile: " << c.nrZile << endl;
	if (c.zi != nullptr) {
		for (int i = 0; i < c.nrZile; i++) {
			if (i != c.nrZile -1) {
				o << c.zi[i] << ", ";
			}
			else {
				o << c.zi[i] << endl;
			}
		}
	}
	return o;
}
ofstream& operator<<(ofstream& o, Cinema c) { 
	if (o.is_open()) {
		o << c.cinemaId << endl;
		o << c.id << endl;
		if (c.nume != nullptr) {
			o << c.nume << endl;
		}
		o << c.oras << endl;
		o << c.adresa << endl;
		o << c.nrZile << endl;
		if (c.zi != nullptr) {
			for (int i = 0; i < c.nrZile; i++) {
					o << c.zi[i] << " ";
			}
		}
		o << endl;
	}
	return o;
}
istream& operator>>(istream& i, Cinema& c) { //cin
	void affArrIdC();
	affArrIdC();
	int* arrIdC();
	int* arr = arrIdC();
	int nrCinemauri();
	int max = nrCinemauri();
	int gasit = 0;
	int id;
	char* nume;
	string oras;
	string adresa;
	int nrZile;
	c.setId(0);
	//cout << "Id: ";
	//i >> id;
	//for (int i = 0; i < max; i++) {
	//	if (arr[i] == id) {
	//		gasit = 1;
	//	}
	//}
	//if (id > 0 && gasit == 0) {
	//	c.setId(id);
	//}
	//else {
	//	cout << "Eroare la introducerea id-ului." << endl;
	//	cout << "Id-ul trebuie sa fie unic si > 0." << endl;
	//	c.setId(0);
	//	gasit = 0;
	//}
	while (c.getId() == 0 && gasit == 0) {
		cout << "Id: ";
		i >> id;
		for (int i = 0; i < max; i++) {
			if (arr[i] == id) {
				gasit = 1;
			}
		}
		if (id > 0 && gasit == 0) {
			c.setId(id);
		}
		else {
			cout << "Eroare la introducerea id-ului." << endl;
			cout << "Id-ul trebuie sa fie unic si > 0." << endl;
			c.setId(0);
			gasit = 0;
		}
	}
	cout << "Nume: ";
	char buffer[101];
	i.ignore(1);
	i.getline(buffer, 100);
	c.nume = new char[strlen(buffer) + 1];
	strcpy_s(c.nume, strlen(buffer) + 1, buffer);
	cout << "Oras: ";
	i >> ws;
	getline(i, oras);
	c.setOras(oras); 
	cout << "Adresa: ";
	i >> ws;
	getline(i, adresa);
	c.setAdresa(adresa);
	cout << "Nr zile(maxim 7): ";
	i >> nrZile;
	while (nrZile <= 0 || nrZile>7) {
		cout << "Numarul de zile nu poate fi < 0 si > 7." << endl;
		cout << "Nr zile(maxim 7): ";
		i >> nrZile;
	}
	string* zi = new string[nrZile];
	for (int y = 0; y < nrZile; y++) {
		cout << "Ziua[" << y + 1 << "]: ";
		i >> zi[y];
	}
	c.setZi(zi, nrZile);
	delete[] zi;
	return i;
}
ifstream& operator>>(ifstream& i, Cinema& c) {
	if (i.is_open()) {
		int id;
		char* nume;
		string oras;
		string adresa;
		int nrZile;
		int cinemaId;
		i >> cinemaId;
		const_cast<int&>(c.cinemaId) = cinemaId;
		i >> id;
		c.setId(id);
		char buffer[101];
		i.ignore(1);
		i.getline(buffer, 100);
		c.nume = new char[strlen(buffer) + 1];
		strcpy_s(c.nume, strlen(buffer) + 1, buffer);
		getline(i, oras);
		c.setOras(oras);
		getline(i, adresa);
		c.setAdresa(adresa);
		i >> nrZile;
		if (nrZile > 0) {
			string* zi = new string[nrZile];
			for (int y = 0; y < nrZile; y++) {
				i >> zi[y];
			}
			c.setZi(zi, nrZile);
			delete[] zi;
		}
		else {
			c.nrZile = 0;
			c.zi = nullptr;
		}
		return i;
	}
}

int nrCinemauri() {
	ifstream f("Cinema.bin", ios::binary);
	if (f.is_open()) {
		f.seekg(0, ios::end);
		int x = f.tellg();
		int z = x / 1062;
		f.close();
		return z;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void ordoneazaCinemaId() {
	fstream f("Cinema.bin", ios::in | ios::out | ios::binary);
	if (f.is_open()) {
		int cinemaId = 1;
		int max = nrCinemauri();
		for (int i = 0; i < max; i++) {
			f.seekg((long long)i * 1062);
			f.write((char*)&cinemaId, sizeof(cinemaId));
			cinemaId++;
		}
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

set<Cinema> citireCinemauri() {
	ordoneazaCinemaId();
	set<Cinema> Set;
	int i = 0;
	ifstream f("Cinema.bin", ios::binary);
	if (f.is_open()) {
		int x = f.tellg();
		f.seekg(0, ios::end);
		int y = f.tellg();
		f.seekg(0, ios::beg);
		while (x != y) {
			int cinemaId = 0; int id = 0; char* nume = nullptr;
			string oras = ""; string adresa = ""; int nrZile = 0;
			//string* zi;
			f.read((char*)&cinemaId, sizeof(cinemaId));
			f.read((char*)&id, sizeof(id));
			int len = 0;
			f.read((char*)&len, sizeof(len));
			char* aux = new char[len];
			f.read(aux, len);
			nume = aux;
			//
			f.read((char*)&len, sizeof(len));
			char* aux1 = new char[len];
			f.read(aux1, len);
			oras = aux1;
			delete[] aux1;
			f.read((char*)&len, sizeof(len));
			char* aux2 = new char[len];
			f.read(aux2, len);
			adresa = aux2;
			delete[] aux2;
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
			if (id > 0) {
				Cinema placeholder(id, nume, oras, adresa, nrZile, zi, cinemaId);
				if (placeholder.getCinemaId() > 0) {
					Set.insert(placeholder);
				}
			}
			//delete[] aux;
			delete[] zi;
			x = f.tellg();
		}
		//ordoneazaCinemaId();
		f.close();
		return Set;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void afiseazaCinemauri() {
	set<Cinema> Set = citireCinemauri();
	for (set<Cinema>::iterator i = Set.begin(); i != Set.end();i++) {
		cout << *i << endl;
	}
	//cout << Film::getNumarFilme() << endl;
}

void stergeBazaDateCinema() {
	ofstream f("Cinema.bin", ios::trunc | ios::binary);
	if (f.is_open()) {
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

set<Cinema> returnCinemauri() {
	set<Cinema> Set = citireCinemauri();
	return Set;
}

//int Cinema::getNumarCinemauri() {
//	set<Cinema> Set = citireCinemauri();
//	return numarCinemauri;
//}
//
//void afiseazaNumarCinemauri() { //foloseste static int numarCinemauri in loc de calcule pe fisier(nrCinemauri()).
//	int u = Cinema::getNumarCinemauri();
//	cout << u << endl;
//}

int* arrIdCinemauri() { // return array cu id-urile cinemaurilor
	int* arrIdCinemauri = new int[nrCinemauri()];
	const int nrf = nrCinemauri();
	//int arrIdFilme[nrf];
	ifstream f("Cinema.bin", ios::binary);
	if (f.is_open()) {
		for (int i = 0; i < nrf; i++) {
			int x = 0;
			f.seekg(i * 1062);
			f.read((char*)&x, sizeof(x));
			arrIdCinemauri[i] = x;
		}
		f.close();
		return arrIdCinemauri;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

int* arrIdC() { // return array cu id-urile cinemaurilor introduse de utilizator
	int* arrId = new int[nrCinemauri()];
	const int nrf = nrCinemauri();
	//int arrIdFilme[nrf];
	ifstream f("Cinema.bin", ios::binary);
	if (f.is_open()) {
		for (int i = 0; i < nrf; i++) {
			int x = 0;
			f.seekg(i * 1062);
			f.read((char*)&x, sizeof(x));
			f.read((char*)&x, sizeof(x));
			arrId[i] = x;
		}
		f.close();
		return arrId;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void affArrIdCinemauri() {
	int* arr = arrIdCinemauri();
	cout << "Exista urmatoarele Cinemauri cu Id: " << endl;
	for (int i = 0; i < nrCinemauri(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void affArrIdC() {
	int* arr = arrIdC();
	int max = nrCinemauri();
	cout << "Exista urmatoarele Cinemauri cu Id: " << endl;
	for (int i = 0; i < max; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int locCinemaCuId() { //returneaza locatia unui film in fisier
	ifstream h("Cinema.bin", ios::binary);
	if (h.is_open()) {
		int x1 = 0;
		int locatie = 0;
		int gasit = 0;
		affArrIdCinemauri();
		cout << "Introdu id-ul cinema-ului pe care vrei sa il gasesti: " << endl;
		cin >> x1;
		for (int i = 0; i < nrCinemauri(); i++) {
			int id = 0;
			h.seekg((long long)i * 1062);
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

void afiseazaCinemaCuId() { // afiseaza un cinema existent in fisier
	int z = locCinemaCuId();
	Cinema o;
	o.deserialize(z);
	cout << o << endl;
}

Cinema returneazaCinemaCuId(int x) { // returneaza un cinema existent in fisier
	int* arr = arrIdCinemauri();
	int found = 0;
	int max = nrCinemauri();
	int i = 0;
	for (i; i < max; i++) {
		if (arr[i] == x) {
			found = 1;
		}
	}
	if (found == 1) {
		ifstream h("Cinema.bin", ios::binary);
		int locatie = 0;
		int gasit = 0;
		if (h.is_open()) {
			for (int i = 0; i < nrCinemauri(); i++) {
				int id = 0;
				h.seekg((long long)i * 1062);
				h.read((char*)&id, sizeof(id));
				if (id == x) {
					locatie = h.tellg();
					locatie -= 4;
					gasit = 1;
					break;
				}
			}
			h.close();
			if (gasit != 1) {
				cout << "Id-ul introdus nu exista." << endl;
			}
			else {
				Cinema o;
				o.deserialize(locatie);
				return o;
			}
		}
	}
	else {
		cout << "Nu exista cinema-ul cu id: " << x << "." << endl;
		Cinema b(0, "N/A", "N/A", "N/A", 0, nullptr);
		return b;
	}
}

void inlocuieCinemaCuId() { // inlocuie un cinema cu unul introdus de la tastatura
	ifstream h("Cinema.bin", ios::binary);
	if (h.is_open()) {
		int x1 = 0;
		int locatie = 0;
		int gasit = 0;
		afiseazaCinemauri();
		affArrIdCinemauri();
		int sigur = 0;
		cout << endl;
		cout << "Esti sigur ca vrei sa modifici un cinema? \nModificarea nu va avea efect pe biletele existente si va sterge baza de date a cinemaului ales." << endl;
		cout << "Alegere: \n\t1)Da\n\t*)Nu" << endl;
		cin >> sigur;
		if (sigur == 1) {
			//cout << endl;
			cout << "Introdu id-ul cinema-ului pe care vrei sa il inlocuiesti: (Cinema id: )" << endl;
			cin >> x1;
			for (int i = 0; i < 3; i++) {
				int id = 0;
				h.seekg((long long)i * 1062);
				h.read((char*)&id, sizeof(id));
				if (id == x1) {
					locatie = h.tellg();
					locatie -= 4;
					gasit = 1;
					break;
				}
			}h.close();
			if (gasit == 1) {
				Cinema test;
				test.deserialize(locatie);
				int zz = test.getId();
				string z = "cinema" + to_string(zz) + ".bin";
				remove(z.c_str());
				void introduCinema(int);
				introduCinema(locatie);
				//ordoneazaCinemaId();
				cout << "Cinema introdus cu succes." << endl;
			}
			else {
				cout << endl;
				cout << "Id-ul introdus nu a fost gasit." << endl;
			}
		}
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void stergeCinema() { // sterge un cinema din fisier
	afiseazaCinemauri();
	int x1 = 0;
	int gasit = 0;
	int max = nrCinemauri();
	affArrIdCinemauri();
	cout << endl;
	int* id = arrIdCinemauri();
	cout << "Introdu id-ul cinema-ului pe care vrei sa il stergi: (Cinema id: )" << endl;
	cin >> x1;
	Cinema p;
	for (int i = 0; i < max; i++) {
		if (x1 == id[i]) {
			gasit = 1;
		}
	}if (gasit == 1) {
		int sigur = 0;
		p = returneazaCinemaCuId(x1);
		set<Cinema> Set = citireCinemauri();
		//for (set<Cinema>::iterator i = Set.begin(); i != Set.end(); i++) {
		//	cout << *i << endl;
		//}
		cout << "Esti sigur ca vrei sa stergi cinema-ul cu Id : " << x1 << " ?\nStergerea nu va avea efect pe biletele existente si va sterge baza de date a cinemaului ales." << endl;
		cout << "\t1)Da\n\t*)Nu\nAlegere: " << endl;
		cin >> sigur;
		if (sigur == 1) {
			for (set<Cinema>::iterator i = Set.begin(); i != Set.end(); i++) {
				if (i == Set.find(p)) {
					Set.erase(i);
					cout << "Cinema sters cu succes" << endl;
					string x = "cinema";
					string u = to_string(p.getId());
					string y = ".bin";
					string z = x + u + y;
					remove(z.c_str());
					break;
				}
			}
			stergeBazaDateCinema();
			for (set<Cinema>::iterator i = Set.begin(); i != Set.end(); i++) {
				Cinema k;
				k = *i;
				k.serialize();
			}
			ordoneazaCinemaId();
		}
		else {
			cout << "Cinema-ul nu a fost sters." << endl;
		}
	}
	else {
		cout << "Id-ul introdus nu exista." << endl;
	}
}

void schimbaAtributCinema() { //modifica atributul unui cinema
	int atr = 0;
	int x1 = 0;
	int x2 = 0;
	string x3 = "";
	string x4 = "";
	int x5 = 0;
	char* nume = nullptr;
	string nume1 = "";
	x1 = locCinemaCuId();
	Cinema o;
	o.deserialize(x1);
	cout << "Modifica:\n\t1)Id\n\t2)Nume\n\t3)Oras\n\t4)Adresa\n\t5)Zile\nAlegere: ";
	cin >> atr;
	switch (atr) {
	case 1:
		cout << "Introdu noul Id: " << endl;
		cin >> x2;
		if (x2 > 0) {
			o.setId(x2);
			o.serialize(x1);
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
			o.serialize(x1);
			//delete[] nume;
			break;
		}
		else {
			cout << "Numele nu poate fi null." << endl;
			break;
		}
	case 3:
		cout << "Introdu noul Oras: " << endl;
		char buffer1[101];
		cin.ignore(1);
		cin.getline(buffer1, 100);
		//cin >> x3;
		if (strlen(buffer1) > 0) {
			o.setOras(buffer1);
			o.serialize(x1);
			break;
		}
		else {
			cout << "Orasul nu poate fi null." << endl;
			break;
		}
	case 4:
		cout << "Introdu noua Adresa: " << endl;
		char buffer2[101];
		cin.ignore(1);
		cin.getline(buffer2, 100);
		if (strlen(buffer2) > 0) {
			o.setAdresa(buffer2);
			o.serialize(x1);
			break;
		}
		else {
			cout << "Adresa nu poate fi null-a." << endl;
			break;
		}
	case 5:
		cout << "Introdu numarul de zile(maxim 7): " << endl;
		cin >> x5;
		if (x5 > 0 && x5 <= 7) {
			string* y = new string[x5];
			for (int i = 0; i < x5; i++) {
				cout << "Introdu ziua[" << i + 1 << "]: ";
				cin >> y[i];
			}
			o.setZi(y, x5);
			o.serialize(x1);
			//delete[] y;
			break;
		}
		else {
			cout << "Numarul de zile nu poate fi < 0 sau > 7.";
			break;
		}
	default:
		cout << "Alegere invalida." << endl;
	}
}

void creazaFisierLocuri(int h) {
	string x = "cinema";
	string u = to_string(h);
	string y = ".bin";
	string z = x + u + y;
	ofstream f;
	f.open(z, ios::_Noreplace);
	f.close();
}

void introduCinema() {
	Cinema c;
	cin >> c;
	if (c.getId() != 0) {
		c.serialize();
		ordoneazaCinemaId();
		creazaFisierLocuri(c.getId());
	}
	else {
		cout << "Cinemaul nu a fost introdus" << endl;
	}
}

void introduCinema(int x) { // folosit la inlocuire Cinema
	Cinema c;
	cin >> c;
	if (c.getId() != 0) {
		c.serialize(x);
		ordoneazaCinemaId();
		creazaFisierLocuri(c.getId());
	}
	else {
		cout << "Cinemaul nu a fost introdus" << endl;
	}
}