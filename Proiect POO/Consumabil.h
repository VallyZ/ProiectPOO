#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

class Consumabil {
private:
	const int consumabilId = 0;
	int id;
	char* nume;
	string um;
	//int cant;
	int nrTopinguri;
	string* toping;
	static int numarConsumabile;

public:
	Consumabil() : consumabilId(++numarConsumabile) {
		id = 0;
		nume = nullptr;
		um = "";
		nrTopinguri = 0;
		toping = nullptr;
	}

	Consumabil(int id, const char* nume, string um, int nrTopinguri, string* toping) : consumabilId(++numarConsumabile) {
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
		this->um = um;
		if (nrTopinguri > 0 && toping != nullptr) {
			this->nrTopinguri = nrTopinguri;
			this->toping = new string[nrTopinguri];
			for (int i = 0; i < nrTopinguri; i++) {
				this->toping[i] = toping[i];
			}
		}
		else {
			this->nrTopinguri = 0;
			this->toping = nullptr;
		}
	}
	Consumabil(int id, const char* nume, string um, int nrTopinguri, string* toping, int consumabilId) {// folosit la citirea din binar
		const_cast<int&>(this->consumabilId) = consumabilId;
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
		this->um = um;
		if (nrTopinguri > 0 && toping != nullptr) {
			this->nrTopinguri = nrTopinguri;
			this->toping = new string[nrTopinguri];
			for (int i = 0; i < nrTopinguri; i++) {
				this->toping[i] = toping[i];
			}
		}
		else {
			this->nrTopinguri = 0;
			this->toping = nullptr;
		}
	}
	Consumabil(const Consumabil& c) : consumabilId(c.consumabilId) {
		id = c.id;
		if (c.nume != nullptr) {
			nume = new char[strlen(c.nume) + 1];
			strcpy_s(nume, strlen(c.nume) + 1, c.nume);
		}
		else {
			nume = nullptr;
		}
		um = c.um;
		if (c.nrTopinguri > 0 && c.toping != nullptr) {
			nrTopinguri = c.nrTopinguri;
			toping = new string[c.nrTopinguri];
			for (int i = 0; i < c.nrTopinguri; i++) {
				toping[i] = c.toping[i];
			}
		}
		else {
			nrTopinguri = 0;
			toping = nullptr;
		}
	}
	Consumabil& operator=(const Consumabil& c) {
		const_cast<int&>(this->consumabilId) = c.consumabilId;
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
		um = c.um;
		if (toping != nullptr) {
			delete[] toping;
		}
		if (c.nrTopinguri > 0 && c.toping != nullptr) {
			nrTopinguri = c.nrTopinguri;
			toping = new string[c.nrTopinguri];
			for (int i = 0; i < c.nrTopinguri; i++) {
				toping[i] = c.toping[i];
			}
		}
		else {
			nrTopinguri = 0;
			toping = nullptr;
		}
		return *this;
	}
	~Consumabil() {
		if (nume != nullptr) {
			delete[] nume;
		}
		if (toping != nullptr) {
			delete[] toping;
		}
	}
	static int getNumarConsumabile() {//////////////static int getNumarConsumabile();//////////////////////////////////////////////////////////
		return numarConsumabile;
	}
	int getConsumabilId() {
		return consumabilId;
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
	string getUm() {
		return um;
	}
	void setUm(string x) {
		if (x.length() > 0) {
			um = x;
		}
		else {
			um = "'Eroare la introducerea Unitatii de masura'";
		}
	}
	int getNrTopinguri() {
		return nrTopinguri;
	}
	void setToping(string* x, int topinguri) {
		if (toping != nullptr) {
			delete[] toping;
		}
		if (x != nullptr && topinguri > 0) {
			nrTopinguri = topinguri;
			toping = new string[topinguri];
			for (int i = 0; i < topinguri; i++) {
				toping[i] = x[i];
			}
		}
		else {
			nrTopinguri = 0;
			toping = nullptr;
		}
	}
	string* getZi() {
		if (toping != nullptr) {
			string* copie = new string[nrTopinguri];
			for (int i = 0; i < nrTopinguri; i++) {
				copie[i] = toping[i];
			}
			return copie;
		}
		else {
			return nullptr;
		}
	}
	void forteazaId(int x) {
		const_cast<int&>(consumabilId) = x;
	} 

	void serialize() {
		ofstream f("Consumabil.bin", ios::app | ios::binary);
		if (f.is_open()) {
			f.write((char*)&consumabilId, sizeof(consumabilId));
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&len, sizeof(len));
			f.write(um.c_str(), len);
			f.write((char*)&nrTopinguri, sizeof(nrTopinguri));
			for (int i = 0; i < 5; i++) {
				if (toping != nullptr) {
					if (toping[i].length() < 20) {
						f.write((char*)&len, sizeof(len));
						f.write(toping[i].c_str(), len);
					}
					else {
						f.write((char*)&len, sizeof(len));
						f.write("", len);
					}
				}
				else {
					f.write((char*)&len, sizeof(len));
					f.write("", len);
				}
			}
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}
	void serialize(int x) {
		fstream f("Consumabil.bin", ios::in | ios::out | ios::binary);
		if (f.is_open()) {
			f.seekp(x);
			f.write((char*)&consumabilId, sizeof(consumabilId));
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&len, sizeof(len));
			f.write(um.c_str(), len);
			f.write((char*)&nrTopinguri, sizeof(nrTopinguri));
			for (int i = 0; i < 5; i++) {
				if (toping != nullptr) {
					if (toping[i].length() < 20) {
						f.write((char*)&len, sizeof(len));
						f.write(toping[i].c_str(), len);
					}
					else {
						f.write((char*)&len, sizeof(len));
						f.write("", len);
					}
				}
				else {
					f.write((char*)&len, sizeof(len));
					f.write("", len);
				}
			}
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}
	void deserialize(int x) {
		fstream f("Consumabil.bin", ios::in | ios::out | ios::binary);
		if (f.is_open()) {
			f.seekg(x);
			f.read((char*)&consumabilId, sizeof(consumabilId));
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
			um = aux1;
			f.read((char*)&nrTopinguri, sizeof(nrTopinguri));
			delete[] toping;
			toping = new string[nrTopinguri];
			if (nrTopinguri == 0) {
				toping = nullptr;
			}
			for (int i = 0; i < nrTopinguri; i++) {
				len = 0;
				f.read((char*)&len, sizeof(len));
				char* aux1 = new char[len];
				f.read(aux1, len);
				toping[i] = aux1;
			}
			for (int i = nrTopinguri; i < 5; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
			}
			//int y = f.tellg();// 747
			//cout << y << endl;
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	string& operator[](int x) { //operator []
		if (x >= 0 && x < nrTopinguri) {
			return toping[x];
		}
		else {
			cout << "Topingul introdus nu exista." << endl;
		}
	}

	Consumabil operator+(int x) {//operator + la stanga
		int z = id + x;
		if (z > 0) {
			Consumabil f = *this;
			f.id += x;
			return f;
		}
		else {
			cout << "Adunarea nu poate rezulta <= 0." << endl;
			return *this;
		}
	}

	Consumabil operator++() {//preincrementare
		id++;
		return *this;
	}

	Consumabil operator++(int x) {//postincrementare
		Consumabil c = *this;
		id++;
		return c;
	}
	Consumabil operator--() {//predencrementare
		if (id - 1 > 0) {
			id--;
			return *this;
		}
		else {
			cout << "Scaderea nu poate rezulta <= 0" << endl;
			return *this;
		}
	}
	Consumabil operator--(int x) {//postdecrementare
		Consumabil c = *this;
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
		return consumabilId;
	}
	bool operator!() { //operator !
		return nrTopinguri > 0;
	}


	friend ostream& operator<<(ostream&, Consumabil);
	friend ofstream& operator<<(ofstream&, Consumabil);
	friend istream& operator>>(istream&, Consumabil&);
	friend ifstream& operator>>(ifstream&, Consumabil&);
	friend bool operator<(const Consumabil& x, const Consumabil& y) {
		return x.consumabilId < y.consumabilId;
	}
	friend Consumabil operator+(int, Consumabil);
	friend bool operator==(const Consumabil& x, const Consumabil& y) //operator==
	{
		if (x.nrTopinguri == y.nrTopinguri) {
			cout << "Numar de topinguri egale." << endl;
			return true;
		}
		else {
			cout << "Numar de topinguri inegale." << endl;
			return false;
		}
	}

};

int Consumabil::numarConsumabile = 0;

Consumabil operator+(int x, Consumabil c) {//operator + la dreapta
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

ostream& operator<<(ostream& o, Consumabil c) { // cout
	o << endl;
	o << "Consumabil id: " << c.consumabilId << endl;
	o << "Id: " << c.id << endl;
	if (c.nume != nullptr) {
		o << "Nume: " << c.nume << endl;
	}
	o << "Unitate de masura: " << c.um << endl;
	o << "Nr topinguri: " << c.nrTopinguri << endl;
	if (c.toping != nullptr) {
		for (int i = 0; i < c.nrTopinguri; i++) {
			if (i != c.nrTopinguri - 1) {
				o << c.toping[i] << ", ";
			}
			else {
				o << c.toping[i] << endl;
			}
		}
	}
	return o;
}
ofstream& operator<<(ofstream& o, Consumabil c) {
	if (o.is_open()) {
		o << endl;
		o << c.consumabilId << endl;
		o << c.id << endl;
		if (c.nume != nullptr) {
			o << c.nume << endl;
		}
		o << c.um << endl;
		o << c.nrTopinguri << endl;
		if (c.toping != nullptr) {
			for (int i = 0; i < c.nrTopinguri; i++) {
				o << c.toping[i] << " ";
			}
		}
		o << endl;
	}
	return o;
}
istream& operator>>(istream& i, Consumabil& c) { //cin
	int id;
	char* nume;
	string um;
	int nrTopinguri;
	cout << "Id: ";
	i >> id;
	if (id > 0) {
		c.setId(id);
	}
	else {
		c.setId(0);
	}
	cout << "Nume: ";
	char buffer[101];
	i.ignore(1);
	i.getline(buffer, 100);
	c.nume = new char[strlen(buffer) + 1];
	strcpy_s(c.nume, strlen(buffer) + 1, buffer);
	cout << "Unitate de masura: ";
	i >> ws;
	getline(i, um);
	c.setUm(um);
	cout << "Nr topinguri(maxim 5): ";
	i >> nrTopinguri;
	while (nrTopinguri < 0 && nrTopinguri>5) {
		cout << "Numarul de topinguri nu poate fi < 0 si > 5." << endl;
		cout << "Nr zile(maxim 5): ";
		i >> nrTopinguri;
	}
	string* toping = new string[nrTopinguri];
	for (int y = 0; y < nrTopinguri; y++) {
		cout << "Toping[" << y + 1 << "]: ";
		i >> toping[y];
	}
	c.setToping(toping, nrTopinguri);
	return i;
}
ifstream& operator>>(ifstream& i, Consumabil& c) {
	if (i.is_open()) {
		int id;
		char* nume;
		string um;
		int nrTopinguri;
		int consumabilId;
		i >> consumabilId;
		const_cast<int&>(c.consumabilId) = consumabilId;
		i >> id;
		c.setId(id);
		char buffer[101];
		i.ignore(1);
		i.getline(buffer, 100);
		c.nume = new char[strlen(buffer) + 1];
		strcpy_s(c.nume, strlen(buffer) + 1, buffer);
		getline(i, um);
		c.setUm(um);
		i >> nrTopinguri;
		if (nrTopinguri > 0) {
			string* toping = new string[nrTopinguri];
			for (int y = 0; y < nrTopinguri; y++) {
				i >> toping[y];
			}
			c.setToping(toping, nrTopinguri);
		}
		else {
			c.nrTopinguri = 0;
			c.toping = nullptr;
		}
		return i;
	}
}

int nrConsumabile() {
	ifstream f("Consumabil.bin", ios::binary);
	if (f.is_open()) {
		f.seekg(0, ios::end);
		int x = f.tellg();
		int z = x / 747;
		f.close();
		return z;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void ordoneazaConsumabilId() {
	fstream f("Consumabil.bin", ios::in | ios::out | ios::binary);
	if (f.is_open()) {
		int consumabilId = 1;
		int max = nrConsumabile();
		for (int i = 0; i < max; i++) {
			f.seekg(i * 747);
			f.write((char*)&consumabilId, sizeof(consumabilId));
			consumabilId++;
		}
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

list<Consumabil> citireConsumabile() {
	ordoneazaConsumabilId();
	list<Consumabil> List;
	int i = 0;
	ifstream f("Consumabil.bin", ios::binary);
	if (f.is_open()) {
		int x = f.tellg();
		f.seekg(0, ios::end);
		int y = f.tellg();
		f.seekg(0, ios::beg);
		while (x != y) {
			int consumabilId = 0; int id = 0; char* nume = nullptr;
			string um = ""; int nrTopinguri = 0;
			//string* zi;
			f.read((char*)&consumabilId, sizeof(consumabilId));
			f.read((char*)&id, sizeof(id));
			int len = 0;
			f.read((char*)&len, sizeof(len));
			char* aux = new char[len];
			f.read(aux, len);
			nume = aux;
			f.read((char*)&len, sizeof(len));
			char* aux1 = new char[len];
			f.read(aux1, len);
			um = aux1;
			f.read((char*)&nrTopinguri, sizeof(nrTopinguri));
			string* toping = new string[nrTopinguri];
			if (nrTopinguri == 0) {
				toping = nullptr;
			}
			for (int i = 0; i < nrTopinguri; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				toping[i] = aux1;
			}
			for (int i = nrTopinguri; i < 5; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
			}
			if (id > 0) {
				Consumabil placeholder(id, nume, um, nrTopinguri, toping, consumabilId);
				if (placeholder.getConsumabilId() > 0) {
					List.push_back(placeholder);
				}
			}
			x = f.tellg();
		}
		f.close();
		return List;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void afiseazaConsumabile() {
	list<Consumabil> l = citireConsumabile();
	for (list<Consumabil>::iterator i = l.begin(); i != l.end(); i++) {
		cout << *i << endl;
	}
}

void stergeBazaDateConsumabil() {
	ofstream f("Consumabil.bin", ios::trunc | ios::binary);
	if (f.is_open()) {
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

list<Consumabil> returnConsumabile() {
	list<Consumabil> List = citireConsumabile();
	return List;
}

int* arrIdConsumabile() { // return array cu id-urile consumabilelor
	int* citireConsumabile = new int[nrConsumabile()];
	const int nrf = nrConsumabile();
	//int arrIdFilme[nrf];
	ifstream f("Consumabil.bin", ios::binary);
	if (f.is_open()) {
		for (int i = 0; i < nrf; i++) {
			int x = 0;
			f.seekg((long long)i * 747);
			f.read((char*)&x, sizeof(x));
			citireConsumabile[i] = x;
		}
		f.close();
		return citireConsumabile;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void affArrIdConsumabile() {
	int* arr = arrIdConsumabile();
	cout << "Exista urmatoarele Consumabile cu Id: " << endl;
	for (int i = 0; i < nrConsumabile(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int locConsumabilCuId() { //returneaza locatia unui film in fisier
	ifstream h("Consumabil.bin", ios::binary);
	if (h.is_open()) {
		int x1 = 0;
		int locatie = 0;
		int gasit = 0;
		affArrIdConsumabile();
		cout << "Introdu id-ul consumabil-ului pe care vrei sa il gasesti: " << endl;
		cin >> x1;
		for (int i = 0; i < nrConsumabile(); i++) {
			int id = 0;
			h.seekg((long long)i * 747);
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

void afiseazaConsumabilCuId() { // afiseaza un consumabil existent in fisier
	int z = locConsumabilCuId();
	Consumabil o;
	o.deserialize(z);
	cout << o << endl;
}

Consumabil returneazaConsumabilCuId(int x) { // returneaza un consumabil existent in fisier
	int* arr = arrIdConsumabile();
	int found = 0;
	int max = nrConsumabile();
	int i = 0;
	for (i; i < max; i++) {
		if (arr[i] == x) {
			found = 1;
		}
	}
	if (found == 1) {
		ifstream h("Consumabil.bin", ios::binary);
		int locatie = 0;
		int gasit = 0;
		if (h.is_open()) {
			for (int i = 0; i < nrConsumabile(); i++) {
				int id = 0;
				h.seekg((long long)i * 747);
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
				Consumabil o;
				o.deserialize(locatie);
				return o;
			}
		}
	}
	else {
		cout << "Nu exista consumabilul-ul cu id: " << x << "." << endl;
		Consumabil b(0,"N/A","N/A",0,nullptr);
		return b;
	}
}

void inlocuieConsumabilCuId() { // inlocuie un consumabil cu unul introdus de la tastatura
	ifstream h("Consumabil.bin", ios::binary);
	if (h.is_open()) {
		int x1 = 0;
		int locatie = 0;
		int gasit = 0;
		affArrIdConsumabile();
		//cout << endl;
		cout << "Introdu id-ul consumabil-ului pe care vrei sa il inlocuiesti: " << endl;
		cin >> x1;
		for (int i = 0; i < 3; i++) {
			int id = 0;
			h.seekg((long long)i * 747);
			h.read((char*)&id, sizeof(id));
			if (id == x1) {
				locatie = h.tellg();
				locatie -= 4;
				gasit = 1;
				break;
			}
		}h.close();
		if (gasit == 1) {
			Consumabil nou;
			cin >> nou;
			nou.serialize(locatie);
			ordoneazaConsumabilId();
			cout << "Consumabil introdus cu succes." << endl;
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

void stergeConsumabil() { // sterge un cinema din fisier
	int x1 = 0;
	int gasit = 0;
	int max = nrConsumabile();
	affArrIdConsumabile();
	cout << endl;
	int* id = arrIdConsumabile();
	cout << "Introdu id-ul consumabil-ului pe care vrei sa il stergi: " << endl;
	cin >> x1;
	Consumabil p;
	for (int i = 0; i < max; i++) {
		if (x1 == id[i]) {
			gasit = 1;
		}
	}
	if (gasit == 1) {
		int sigur = 0;
		p = returneazaConsumabilCuId(x1);
		list<Consumabil> List = citireConsumabile();
		cout << "Esti sigur ca vrei sa stergi consumabil-ul cu Id : " << x1 << " ?" << endl;
		cout << "\t1)Da\n\t*)Nu\nAlegere: " << endl;
		cin >> sigur;
		if (sigur == 1) {
			//list<Consumabil>::iterator i;
			//List.remove_if(i == find(List.begin(), List.end(), p);
			Consumabil l;
			
			for (list<Consumabil>::iterator i = List.begin(); i != List.end(); i++) {
				l = *i;
				//cout << l << endl;
				if (l.getConsumabilId() == x1) {
					cout << "Consumabil sters cu succes" << endl;
					List.erase(i);
					break;
				}
			}
			stergeBazaDateConsumabil();
			Consumabil k;
			for (list<Consumabil>::iterator i = List.begin(); i != List.end(); i++) {
				
				k = *i;
				k.serialize();
			}
			ordoneazaConsumabilId();
		}
		else {
			cout << "Consumabil-ul nu a fost sters." << endl;
		}
	}
	else {
		cout << "Id-ul introdus nu exista." << endl;
	}
}

void schimbaAtributConsumabil() { //modifica atributul unui consumabil
	int atr = 0;
	int x1 = 0;
	int x2 = 0;
	string x3 = "";
	int x5 = 0;
	char* nume = nullptr;
	string nume1 = "";
	x1 = locConsumabilCuId();
	Consumabil o;
	o.deserialize(x1);
	cout << "Modifica:\n\t1)Id\n\t2)Nume\n\t3)Unitate de masura\n\t4)Toping\nAlegere: ";
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
			break;
		}
		else {
			cout << "Numele nu poate fi null." << endl;
			break;
		}
	case 3:
		cout << "Introdu noua Unitate de masura: " << endl;
		char buffer1[101];
		cin.ignore(1);
		cin.getline(buffer1, 100);
		//cin >> x3;
		if (strlen(buffer1) > 0) {
			o.setUm(buffer1);
			o.serialize(x1);
			break;
		}
		else {
			cout << "Orasul nu poate fi null." << endl;
			break;
		}
	case 4:
		cout << "Introdu numarul de topinguri(maxim 5): " << endl;
		cin >> x5;
		if (x5 == 0) {
			o.setToping(nullptr, 0);
			o.serialize(x1);
			break;
		}
		if (x5 > 0 && x5 <= 5) {
			string* y = new string[x5];
			for (int i = 0; i < x5; i++) {
				cout << "Introdu topigul[" << i + 1 << "]: ";
				cin >> y[i];
			}
			o.setToping(y, x5);
			o.serialize(x1);
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