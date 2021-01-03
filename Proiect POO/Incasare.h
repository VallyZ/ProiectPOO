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
	//Bilet bilet;
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
		//bilet = i.bilet;
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
		const_cast<int&>(this->id) = id;
		//bilet = i.bilet;
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
	//void setBilet(Bilet x) {
	//	bilet = x;
	//}
	//Bilet getBilet() {
	//	return bilet;
	//}

	void serialize() {
		ofstream f("Incasare.bin", ios::app | ios::binary);
		if (f.is_open()) {
			//int y = f.tellp();
			//cout << "Incepere fisier: " << y << endl;
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
			//y = f.tellp();
			//cout << "Final scris: " << y << endl;
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	void serialize(int x) {
		ofstream f("Incasare.bin", ios::app | ios::binary);
		if (f.is_open()) {
			//int y = f.tellp();
			//cout << "Incepere fisier: " << y << endl;
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
			//y = f.tellp();
			//cout << "Final scris: " << y << endl;
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
			//int y = f.tellp();
			//cout << "Incepere fisier: " << y << endl;
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
			//y = f.tellp();
			//cout << "Final citit: " << y << endl;
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	friend ostream& operator<<(ostream&, Incasare);
	friend istream& operator>>(istream&, Incasare&);
};

int Incasare::nrIncasari = 0;

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
