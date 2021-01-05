#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include "Bilet.h"
#include "Cinema.h"
#include "Film.h"
using namespace std;

class Incasare {
private:
	const int id = 0;
	int idBilet;
	char* nume; // numele de pe bilet
	int nr; // 1 + nrInsotitori
	int* incasare; // vector de 100 * nrInsotitori 
	static int nrIncasari;

public:
	Incasare() : id(++nrIncasari) {
		idBilet = 0;
		nume = nullptr;
		nr = 0;
		incasare = nullptr;
	}

	Incasare(int idBilet, const char* nume, int nr, int* incasare) : id(++nrIncasari) {
		this->idBilet = idBilet;
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			this->nume = nullptr;
		}
		if (nr > 0 && incasare != nullptr) {
			this->nr = nr;
			this->incasare = new int[nr];
			for (int i = 0; i < nr; i++) {
				this->incasare[i] = incasare[i];
			}
		}
		else {
			this->nr = 0;
			this->incasare = nullptr;
		}
	}

	Incasare(int idBilet, const char* nume, int nr, int* incasare, int id) {
		const_cast<int&>(this->id) = id;
		this->idBilet = idBilet;
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			this->nume = nullptr;
		}
		if (nr > 0 && incasare != nullptr) {
			this->nr = nr;
			this->incasare = new int[nr];
			for (int i = 0; i < nr; i++) {
				this->incasare[i] = incasare[i];
			}
		}
		else {
			this->nr = 0;
			this->incasare = nullptr;
		}
	}

	Incasare(const Incasare& i) :id(i.id) {
		idBilet = i.idBilet;
		if (i.nume != nullptr) {
			nume = new char[strlen(i.nume) + 1];
			strcpy_s(nume, strlen(i.nume) + 1, i.nume);
		}
		else {
			nume = nullptr;
		}
		if (i.nr > 0 && i.incasare != nullptr) {
			nr = i.nr;
			incasare = new int[i.nr];
			for (int j = 0; j < i.nr; j++) {
				incasare[j] = i.incasare[j];
			}
		}
		else {
			nr = 0;
			incasare = nullptr;
		}
	}

	Incasare& operator=(const Incasare& i) {
		const_cast<int&>(this->id) = i.id;
		idBilet = i.idBilet;
		if (i.nume != nullptr) {
			nume = new char[strlen(i.nume) + 1];
			strcpy_s(nume, strlen(i.nume) + 1, i.nume);
		}
		else {
			nume = nullptr;
		}
		if (i.nr > 0 && i.incasare != nullptr) {
			nr = i.nr;
			incasare = new int[i.nr];
			for (int j = 0; j < i.nr; j++) {
				incasare[j] = i.incasare[j];
			}
		}
		else {
			nr = 0;
			incasare = nullptr;
		}
		return *this;
	}

	~Incasare() {
		if (nume != nullptr) {
			delete[] nume;
		}
		if (incasare != nullptr) {
			delete[] incasare;
		}
	}

	int getId() {
		return id;
	}
	void forteazaId(int x) {
		if (x > 0) {
			const_cast<int&>(id) = x;
		}
	}
	int getIdBilet() {
		return idBilet;
	}
	void setIdBilet(int x) {
		if (x > 0) {
			idBilet = x;
		}
		else {
			idBilet = 0;
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
	int getNr() {
		return nr;
	}
	void setIncasare(int* incasare, int nr) {
		if (incasare != nullptr) {
			delete[] this->incasare;
		}
		if (nr > 0 && incasare != nullptr) {
			this->nr = nr;
			this->incasare = new int[nr];
			for (int i = 0; i < nr; i++) {
				this->incasare[i] = incasare[i];
			}
		}
	}
	int* getIncasare() {
		if (incasare != nullptr) {
			int* copie = new int[nr];
			for (int i = 0; i < nr; i++) {
				copie[i] = incasare[i];
			}
			return copie;
		}
		else {
			return nullptr;
		}
	}

	void serialize() {
		ofstream f("Incasare.bin", ios::app | ios::binary);
		if (f.is_open()) {
			f.write((char*)&id, sizeof(id));
			f.write((char*)&idBilet, sizeof(idBilet));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&nr, sizeof(nr));
			int siguranta = 0;
			for (int i = 0; i < 5; i++) {
				if (incasare != nullptr) {
					if (incasare[i] > 0 && siguranta == 0) {
						f.write((char*)&incasare[0], sizeof(int));
						if (i + 1 == nr) {
							siguranta = 1;
						}
					}
					else {
						int x = 0;
						f.write((char*)&x, sizeof(x));
					}
				}
			}
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	void serialize(int x) {
		ofstream f("Incasare.bin", ios::app | ios::binary);
		if (f.is_open()) {
			f.seekp(x);
			f.write((char*)&id, sizeof(id));
			f.write((char*)&idBilet, sizeof(idBilet));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&nr, sizeof(nr));
			int siguranta = 0;
			for (int i = 0; i < 5; i++) {
				if (incasare != nullptr) {
					if (incasare[i] > 0 && siguranta == 0) {
						f.write((char*)&incasare[0], sizeof(int));
						if (i + 1 == nr) {
							siguranta = 1;
						}
					}
					else {
						int x = 0;
						f.write((char*)&x, sizeof(x));
					}
				}
			}
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	void deserialize(int x) {
		fstream f("Incasare.bin", ios::out | ios::in | ios::binary);
		if (f.is_open()) {
			f.seekg(x);
			f.read((char*)&id, sizeof(id));
			f.read((char*)&idBilet, sizeof(idBilet));
			int len = 0;
			f.read((char*)&len, sizeof(len));
			char* aux = new char[len];
			f.read(aux, len);
			nume = aux;
			f.read((char*)&nr, sizeof(nr));
			delete[] incasare;
			incasare = new int[nr];
			int gol = 0;
			for (int i = 0; i < nr; i++) {
				f.read((char*)&incasare[i], sizeof(incasare[i]));
			}
			for (int j = nr; j < 5; j++) {
				f.read((char*)&gol, sizeof(gol));
			}
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	int operator[](int x) {
		if (x >= 0 && x < nr) {
			return incasare[x];
		}
		else {
			cout << "Pretul pentru insotitorul introdus nu exista" << endl;
			return 0;
		}
	}

	Incasare operator+(int x) {
		Incasare I = *this;
		cout << "Adauga extra pret pentru biletul acesta" << endl;
		if (x > 0) {
			int max = I.nr;
			for (int i = 0; i < max; i++) {
				I.incasare[i] += x;
			}
			return I;
		}
		else {
			cout << "Pretul nu poate fi <0." << endl;
			return I;
		}
	}

	Incasare operator++() {//preincrementare
		if (nr < 5) {
			int* m = new int[nr + 1];
			for (int i = 0; i < nr; i++) {
				m[i] = incasare[i];
			}
			for (int i = nr; i < nr + 1; i++) {
				m[i] = 100;
			}
			setIncasare(m, nr + 1);
			return *this;
		}
		else {
			cout << "Nr de persoane este deja maxim" << endl;
			return *this;
		}
	}

	Incasare operator++(int x) {//preincrementare
		Incasare I = *this;
		if (nr < 5) {
			int* m = new int[I.nr + 1];
			for (int i = 0; i < I.nr; i++) {
				m[i] = I.incasare[i];
			}
			for (int i = I.nr; i < I.nr + 1; i++) {
				m[i] = 100;
			}
			setIncasare(m, nr + 1);
			return I;
		}
		else {
			cout << "Nr de persoane este deja maxim" << endl;
			return I;
		}
	}

	explicit operator int() { // cast explicit
		return id;
	}

	bool operator!() { //operator !
		return nr > 0;
	}

	friend ostream& operator<<(ostream&, Incasare);
	friend istream& operator>>(istream&, Incasare&);
	friend Incasare operator+(int, Incasare);
	friend bool operator<(const Incasare& x, const Incasare& y) {
		return x.id < y.id;
	}
	friend bool operator==(const Incasare& x, const Incasare& y) //operator==
	{
		if (x.nr == y.nr) {
			cout << "Numar de incasari egale." << endl;
			return true;
		}
		else {
			cout << "Numar de incasari inegale." << endl;
			return false;
		}
	}
};

int Incasare::nrIncasari = 0;

Incasare operator+(int x, Incasare s) {
	cout << "Adauga extra pret pentru biletul acesta" << endl;
	if (x > 0) {
		int max = s.getNr();
		int* z = new int[max];
		for (int i = 0; i < max; i++) {
			z[i] = s.getIncasare()[i] + x;
		}
		s.setIncasare(z, max);
		return s;
	}
	else {
		cout << "Pretul nu poate fi <0." << endl;
		return s;
	}
}

ostream& operator<<(ostream& o, Incasare i) { // cout
	o << endl;
	o << "Id: " << i.id << endl;
	o << "Id Bilet: " << i.idBilet << endl;
	o << "Nume: " << i.nume << endl;
	o << "Nr incasari: " << i.nr << endl;
	if (i.incasare != nullptr) {
		int max = i.nr;
		for (int j = 0; j < max; j++) {
			if (j != max - 1) {
				o << i.incasare[j] << ", ";
			}
			else {
				o << i.incasare[j] << endl;
			}
		}
	}
	return o;
}

istream& operator>>(istream& i, Incasare& o) { // cin
	cout << "Id Bilet: ";
	i >> o.idBilet;
	cout << "Nume: ";
	char buffer[101];
	i.ignore(1);
	i.getline(buffer, 100);
	o.nume = new char[strlen(buffer) + 1];
	strcpy_s(o.nume, strlen(buffer) + 1, buffer);
	cout << "Nr incasari: ";
	i >> o.nr;
	while (o.nr <= 0) {
		cout << "Nr incasari nu poate fi <= 0." << endl;
		cout << "Nr incasari: ";
		i >> o.nr;
	}
	int* x = new int[o.nr];
	for (int j = 0; j < o.nr; j++) {
		cout << "Incasare[" << j + 1 << "]: ";
		i >> x[j];
	}
	o.setIncasare(x, o.nr);
	return i;
}

int nrIncasari() {
	ifstream f("Incasare.bin", ios::binary);
	if (f.is_open()) {
		f.seekg(0, ios::end);
		int x = f.tellg();
		int y = x / 137;
		f.close();
		return y;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
		return 0;
	}
}

void ordoneazaIncasari() {
	fstream f("Incasare.bin", ios::in | ios::out | ios::binary);
	if (f.is_open()) {
		int incasareId = 1;
		int max = nrIncasari();
		for (int i = 0; i < max; i++) {
			f.seekg(i * 137);
			f.write((char*)&incasareId, sizeof(incasareId));
			incasareId++;
		}
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

map<int, Incasare> returnIncasari() {
	ordoneazaIncasari();
	map<int, Incasare> I;
	Incasare i;
	int ii = 0;
	int max = nrIncasari();
	ifstream f("Incasare.bin", ios::binary);
	if (f.is_open()) {
		for (int j = 0; j < max; j++) {
			i.deserialize(j * 137);
			I[ii] = i;
			ii++;
		}
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
	return I;
}

void stergeBazaDateIncasari() {
	int alegere1 = 0;
	int alegere2 = 0;
	cout << "Sigur vrei sa stergi baza de date?" << endl;
	cout << "Alegere: \n\t1)Da\n\t*)Nu" << endl;
	cin >> alegere1;
	if (alegere1 == 1) {
		cout << "Sigur sigur vrei sa stergi baza de date?" << endl;
		cout << "Alegere: \n\t1)Da\n\t*)Nu" << endl;
		cin >> alegere2;
		if (alegere2 == 1) {
			ofstream f("Incasare.bin", ios::trunc | ios::binary);
			if (f.is_open()) {
				f.close();
			}
			else {
				cout << "Eroare la deschiderea fisierului." << endl;
			}
		}
	}
}

void stergeBazaDateIncasari(int x) {
	ofstream f("Incasare.bin", ios::trunc | ios::binary);
	if (f.is_open()) {
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void afiseazaIncasari() {
	map<int, Incasare> I = returnIncasari();
	for(int i = 0; i < I.size(); i++) {
		cout << I[i] << endl;
	}
}

int* arrIdIncasari() {
	int* arrIdIncasari = new int[nrIncasari()];
	const int max = nrIncasari();
	ifstream f("Incasare.bin", ios::binary);
	if (f.is_open()) {
		for (int i = 0; i < max; i++) {
			int x = 0;
			f.seekg(137 * i);
			f.read((char*)&x, sizeof(x));
			f.read((char*)&x, sizeof(x));
			arrIdIncasari[i] = x;
		}
		f.close();
		return arrIdIncasari;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void affArrIdIncasari() {
	int* arr = arrIdIncasari();
	cout << "Exista urmatoarele incasari cu Id: (Bilet id: )" << endl;
	for (int i = 0; i < nrIncasari(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int locIncasareCuId() { //returneaza locatia unei incasari in fisier
	ifstream h("Incasare.bin", ios::binary);
	if (h.is_open()) {
		int x1 = 0;
		int locatie = 0;
		int gasit = 0;
		affArrIdIncasari();
		cout << "Introdu id-ul incasarii pe care vrei sa o gasesti: " << endl;
		cin >> x1;
		for (int i = 0; i < nrIncasari(); i++) {
			int id = 0;
			h.seekg(137 * i);
			h.read((char*)&id, sizeof(id));
			h.read((char*)&id, sizeof(id));
			if (id == x1) {
				locatie = h.tellg();
				//locatie -= 4;
				locatie -= 8;
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

void afiseazaIncasareCuId() {
	int z = locIncasareCuId();
	Incasare i;
	i.deserialize(z);
	cout << i << endl;
}

void stergeIncasare() {
	afiseazaIncasari();
	int x1 = 0;
	int gasit = 0;
	affArrIdIncasari();
	int* id = arrIdIncasari();
	cout << "Introdu id-ul Incasarii pe care vrei sa o gasesti: (Bilet id: )" << endl;
	cin >> x1;
	for (int i = 0; i < nrIncasari(); i++) {
		if (x1 == id[i]) {
			gasit = 1;
		}
	}
	if (gasit == 1) {
		int sigur = 0;
		map<int, Incasare> I = returnIncasari();
		for (int i = 0; i < I.size(); i++) {

		}
		cout << "Esti sigur ca vrei sa stergi Incasarea cu Id: (Bilet id: )" << x1 << "?\nStergerea va rezulta si in stergerea biletului." << endl;
		cout << "\t1)Da\n\t*)Nu\nAlegere: " << endl;
		cin >> sigur;
		if (sigur == 1) {
			int siguranta = 0;
			for (int i = 0; i < I.size(); i++) {
				if (I[i].getIdBilet() == x1 && siguranta == 0) {
					I.erase(i);
					//break;
					//ordoneazaIncasari(i);
					siguranta = 1;
					i++;
					//break;
				}
				if (siguranta == 1) {
					int z = I[i].getIdBilet() - 1;
					I[i].setIdBilet(z);
				}
			}
			void stergeBilet(int);
			stergeBilet(x1);
			stergeBazaDateIncasari(0);
			for (map<int, Incasare>::iterator it = I.begin(); it != I.end(); it++) {
				it->second.serialize();
			}
			ordoneazaIncasari();
		}
		else {
			cout << "Incasarea nu a fost stearsa." << endl;
		}
	}
	else {
		cout << "Id-ul introdus nu exista." << endl;
	}
}

void stergeIncasare(int x1) { // sterge incasare cand sterge bilet
	int gasit = 0;
	int* id = arrIdIncasari();
	for (int i = 0; i < nrIncasari(); i++) {
		if (x1 == id[i]) {
			gasit = 1;
		}
	}
	if (gasit == 1) {
		int sigur = 1;
		map<int, Incasare> I = returnIncasari();
		if (sigur == 1) {
			int siguranta = 0;
			for (int i = 0; i < I.size(); i++) {
				if (I[i].getIdBilet() == x1 && siguranta == 0) {
					I.erase(i);
					//break;
					//ordoneazaIncasari(i);
					siguranta = 1;
					i++;
					//break;
				}
				if (siguranta == 1) {
					int z = I[i].getIdBilet() - 1;
					I[i].setIdBilet(z);
				}
			}
			stergeBazaDateIncasari();
			for (map<int, Incasare>::iterator it = I.begin(); it != I.end(); it++) {
				it->second.serialize();
			}
			ordoneazaIncasari();
		}
	}
	else {
		cout << "Id-ul introdus nu exista." << endl;
	}
}

int returnTotalIncasari() {
	int total = 0;
	map<int, Incasare> I = returnIncasari();
	for (int i = 0; i < I.size(); i++) {
		int x = I[i].getNr();
		for (int j = 0; j < x; j++) {
			total += I[i].getIncasare()[j];
		}
	}
	return total;
}