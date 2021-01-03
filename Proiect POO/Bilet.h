#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include "Incasare.h"
using namespace std;

class Bilet {
private:
	const int id = 0;
	char* nume;
	int nrPersoane;
	string* persoane;
	Cinema cinema;
	Film film;
	static int nrBilete;

public:
	Bilet() : id(++nrBilete) {
		nume = nullptr;
		nrPersoane = 0;
		persoane = nullptr;
	}

	Bilet(const char* nume, int nrPersoane, string* persoane) : id(++nrBilete) {
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			this->nume = nullptr;
		}
		if (persoane != nullptr && nrPersoane > 0) {
			this->nrPersoane = nrPersoane;
			this->persoane = new string[nrPersoane];
			for (int i = 0; i < nrPersoane; i++) {
				this->persoane[i] = persoane[i];
			}
		}
		else {
			this->nrPersoane = 0;
			this->persoane = nullptr;
		}
	}

	Bilet(const char* nume, int nrPersoane, string* persoane, int id) { //folosit in citire din binar
		const_cast<int&>(this->id) = id;
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			nume = nullptr;
		}
		if (persoane != nullptr && nrPersoane > 0) {
			this->nrPersoane = nrPersoane;
			this->persoane = new string[nrPersoane];
			for (int i = 0; i < nrPersoane; i++) {
				this->persoane[i] = persoane[i];
			}
		}
		else {
			this->nrPersoane = 0;
			this->persoane = nullptr;
		}
	}

	Bilet(const Bilet& b) : id(b.id) {
		film = b.film;
		cinema = b.cinema;
		if (b.nume != nullptr) {
			nume = new char[strlen(b.nume) + 1];
			strcpy_s(nume, strlen(b.nume) + 1, b.nume);
		}
		else {
			nume = nullptr;
		}
		if (b.persoane != nullptr && b.nrPersoane > 0) {
			nrPersoane = b.nrPersoane;
			persoane = new string[b.nrPersoane];
			for (int i = 0; i < b.nrPersoane; i++) {
				persoane[i] = b.persoane[i];
			}
		}
		else {
			nrPersoane = 0;
			persoane = nullptr;
		}
	}

	Bilet& operator=(const Bilet& b) {
		const_cast<int&>(this->id) = b.id;
		film = b.film;
		cinema = b.cinema;
		if (b.nume != nullptr) {
			nume = new char[strlen(b.nume) + 1];
			strcpy_s(nume, strlen(b.nume) + 1, b.nume);
		}
		else {
			nume = nullptr;
		}
		if (b.persoane != nullptr && b.nrPersoane > 0) {
			nrPersoane = b.nrPersoane;
			persoane = new string[b.nrPersoane];
			for (int i = 0; i < b.nrPersoane; i++) {
				persoane[i] = b.persoane[i];
			}
		}
		else {
			nrPersoane = 0;
			persoane = nullptr;
		}
		return *this;
	}

	~Bilet() {
		if (nume != nullptr) {
			delete[] nume;
		}
		if (persoane != nullptr) {
			delete[] persoane;
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
	int getNrPersoane() {
		return nrPersoane;
	}
	void setPersoane(string* x, int nrPersoane) {
		if (persoane != nullptr) {
			delete[] persoane;
		}
		if (x != nullptr && nrPersoane > 0) {
			this->nrPersoane = nrPersoane;
			persoane = new string[nrPersoane];
			for (int i = 0; i < nrPersoane; i++) {
				persoane[i] = x[i];
			}
		}
		else {
			nrPersoane = 0;
			persoane = nullptr;
		}
	}
	string* getPersoane() {
		if (persoane != nullptr) {
			string* copie = new string[nrPersoane];
			for (int i = 0; i < nrPersoane; i++) {
				copie[i] = persoane[i];
			}
			return copie;
		}
		else {
			return nullptr;
		}
	}
	void setCinema(Cinema x) {
		cinema = x;
	}
	Cinema getCinema() {
		return cinema;
	}
	void setFilm(Film x) {
		film = x;
	}
	Film getFilm() {
		return film;
	}

	void serialize1() {
		cinema.serializeBilet("Bilet.bin");
		film.serialize1Bilet("Bilet.bin");
		ofstream f("Bilet.bin", ios::app | ios::binary);
		if (f.is_open()) {
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&nrPersoane, sizeof(nrPersoane));
			int len1 = 101;
			int siguranta = 0;
			for (int i = 0; i < 4; i++) {
				if (persoane != nullptr) {
					if (persoane[i].length() != 0 && persoane[i].length() < 20 && siguranta == 0) {
						f.write((char*)&len1, sizeof(len1));
						f.write(persoane[i].c_str(), len1);
					}
					else {
						f.write((char*)&len1, sizeof(len1));
						f.write("", len1);
						siguranta = 1;
					}
				}
				else {
					f.write((char*)&len1, sizeof(len1));
					f.write("", len1);
				}
			}
			f.close();
		}
	}

	void serialize1LaLoc(int x) { // serializeaza la o anumita locatie
		cinema.serializeBiletLaLoc("Bilet.bin", x);
		film.serialize1BiletLaLoc("Bilet.bin", (x + 1062));
		fstream f("Bilet.bin", ios::out | ios::in | ios::binary);
		if (f.is_open()) {
			f.seekp((x + 1922));
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&nrPersoane, sizeof(nrPersoane));
			int len1 = 101;
			int siguranta = 0;
			for (int i = 0; i < 4; i++) {
				if (persoane != nullptr) {

					if (persoane[i].length() != 0 && persoane[i].length() < 20 && siguranta == 0) {
						f.write((char*)&len1, sizeof(len1));
						f.write(persoane[i].c_str(), len1);
					}
					else {
						f.write((char*)&len1, sizeof(len1));
						f.write("", len1);
						siguranta = 1;
					}
				}
				else {
					f.write((char*)&len1, sizeof(len1));
					f.write("", len1);
				}
			}
			f.close();
		}
	}

	void deserialize(int x) {
		fstream f("Bilet.bin", ios::in | ios::out | ios::binary);
		int cinema_id = 0;
		int cinema_id_id = 0;
		char* cinema_nume = nullptr;
		string cinema_oras = "";
		string cinema_adresa = "";
		int cinema_nrZile = 0;
		if (f.is_open()) {
			f.seekg(x);
			f.read((char*)&cinema_id, sizeof(cinema_id));
			f.read((char*)&cinema_id_id, sizeof(cinema_id_id));
			int len = 0;
			f.read((char*)&len, sizeof(len));
			char* aux = new char[len];
			f.read(aux, len);
			cinema_nume = aux;
			f.read((char*)&len, sizeof(len));
			char* aux1 = new char[len];
			f.read(aux1, len);
			cinema_oras = aux1;
			delete[] aux1;
			f.read((char*)&len, sizeof(len));
			char* aux2 = new char[len];
			f.read(aux2, len);
			cinema_adresa = aux2;
			delete[] aux2;
			f.read((char*)&cinema_nrZile, sizeof(cinema_nrZile));
			string* zi = new string[cinema_nrZile];
			for (int i = 0; i < cinema_nrZile; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				zi[i] = aux1;
			}
			for (int i = cinema_nrZile; i < 7; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
			}
			if (cinema_id_id > 0) {
				Cinema placeholder(cinema_id_id, cinema_nume, cinema_oras, cinema_adresa, cinema_nrZile, zi, cinema_id);
				if (placeholder.getCinemaId() > 0) {
					setCinema(placeholder);
				}
			}
			delete[] zi;

			int film_filmId = 0;
			int film_id = 0;
			char* film_nume = nullptr;
			float film_durata = 0;
			int film_nrZile = 0;
			float film_start = 0;
			f.read((char*)&film_filmId, sizeof(film_filmId));
			f.read((char*)&film_id, sizeof(film_id));
			len = 0;
			f.read((char*)&len, sizeof(len));
			char* aux5 = new char[len];
			f.read(aux5, len);
			film_nume = aux5;
			f.read((char*)&film_durata, sizeof(film_durata));
			f.read((char*)&film_nrZile, sizeof(film_nrZile));
			string* zi1 = new string[film_nrZile];
			for (int i = 0; i < film_nrZile; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				zi1[i] = aux1;
				delete[] aux1;
			}
			for (int i = film_nrZile; i < 7; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				delete[] aux1;
			}
			f.read((char*)&film_start, sizeof(film_start));
			if (film_id > 0) {
				Film placeHolder1(film_id, film_nume, film_durata, film_nrZile, zi1, film_start, film_filmId);
				if (placeHolder1.getFilmId() > 0) {
					setFilm(placeHolder1);
				}
			}
			delete[] zi1;
			//int y = f.tellg();
			//cout << "Locatie id: " << y << endl;

			f.read((char*)&id, sizeof(id));
			len = 0;
			f.read((char*)&len, sizeof(len));
			char* aux3 = new char[len];
			f.read(aux3, len);
			nume = aux3;
			f.read((char*)&nrPersoane, sizeof(nrPersoane));
			delete[] persoane;
			persoane = new string[nrPersoane];
			for (int i = 0; i < nrPersoane; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				persoane[i] = aux1;
				delete[] aux1;
			}
			for (int i = nrPersoane; i < 4; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				delete[] aux1;
			}
			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}

	string& operator[](int x) { //operator []
		if (x >= 0 && x < nrPersoane) {
			return persoane[x];
		}
		else {
			cout << "Insotitorul introdus nu exista." << endl;
		}
	}

	Bilet operator+(int x) {//operator + la stanga
		Bilet b = *this;
		if (x > 0) {
			if (x + b.getNrPersoane() > 4) {
				int alegere = 0;
				int h = 4 - b.getNrPersoane();
				cout << "Nu se pot introduce " << x << " insotitori.\nSe pot adauga " << h << " insotitori.\nDoresti sa adaugi cel putin 1 insotitor?\nAlegere:\n\t1)\n\t*)" << endl;
				cin >> alegere;
				if (alegere == 1) {
					int nr = 0;
					cout << "Introdu nr de insotitori doriti: " << endl;
					cin >> nr;
					string* m = new string[b.getNrPersoane() + nr];
					if (nr >= 0 && nr <= h) {
						for (int i = 0; i < b.getNrPersoane(); i++) {
							m[i] = b.getPersoane()[i];
						}
						cin.ignore(1);
						for (int i = b.getNrPersoane(); i < b.getNrPersoane() + nr; i++) {
							cout << "Nume: ";
							getline(cin, m[i]);
						}
					}
					b.setPersoane(m, b.getNrPersoane() + nr);
					return b;
				}
			}
			else {
				string* m = new string[b.getNrPersoane() + x];
					for (int i = 0; i < b.getNrPersoane(); i++) {
						m[i] = b.getPersoane()[i];
					}
					for (int i = b.getNrPersoane(); i < b.getNrPersoane() + x; i++) {
						cout << "Nume: ";
						getline(cin, m[i]);
					}
					b.setPersoane(m, b.getNrPersoane() + x);
					return b;
				}
		}
		else {
			return b;
		}
	}

	Bilet operator++() {//preincrementare
		if (nrPersoane < 4) {
			string* m = new string[nrPersoane + 1];
			for (int i = 0; i < nrPersoane; i++) {
				m[i] = persoane[i];
			}
			//cin.ignore(1);
			for (int i = nrPersoane; i < nrPersoane + 1; i++) {
				cout << "Nume: ";
				getline(cin, m[i]);
			}
			setPersoane(m, nrPersoane + 1);
			return *this;
		}
		else {
			cout << "Nr de persoane este deja maxim" << endl;
			return *this;
		}
	}

	Bilet operator++(int x) {//postincrementare
		Bilet b = *this;
		if (nrPersoane < 4) {
			string* m = new string[b.nrPersoane + 1];
			for (int i = 0; i < b.nrPersoane; i++) {
				m[i] = b.persoane[i];
			}
			//cin.ignore(1);
			for (int i = b.nrPersoane; i < b.nrPersoane + 1; i++) {
				cout << "Nume: ";
				getline(cin, m[i]);
			}
			setPersoane(m, b.nrPersoane + 1);
			return b;
		}
		else {
			cout << "Nr de persoane este deja maxim" << endl;
			return b;
		}
	}

	explicit operator int() {//cast explicit
		return id;
	}

	bool operator!() { //operator !
		return nrPersoane > 0;
	}

	friend ostream& operator<<(ostream&, Bilet);
	friend istream& operator>>(istream&, Bilet&);
	friend Bilet operator+(int, Bilet);
	friend bool operator<(const Bilet& x, const Bilet& y) {
		return x.id < y.id;
	}
	friend bool operator==(const Bilet& x, const Bilet& y) //operator==
	{
		if (x.nrPersoane == y.nrPersoane) {
			cout << "Numar de persoane egale." << endl;
			return true;
		}
		else {
			cout << "Numar de persoane inegale." << endl;
			return false;
		}
	}
};

int Bilet::nrBilete = 0;

Bilet operator+(int x, Bilet b) {
	if (x > 0) {
		if (x + b.getNrPersoane() > 4) {
			int alegere = 0;
			int h = 4 - b.getNrPersoane();
			cout << "Nu se pot introduce " << x << " insotitori.\nSe pot adauga " << h << " insotitori.\nDoresti sa adaugi cel putin 1 insotitor?\nAlegere:\n\t1)\n\t*)" << endl;
			cin >> alegere;
			if (alegere == 1) {
				int nr = 0;
				cout << "Introdu nr de insotitori doriti: " << endl;
				cin >> nr;
				string* m = new string[b.getNrPersoane() + nr];
				if (nr >= 0 && nr <= h) {
					for (int i = 0; i < b.getNrPersoane(); i++) {
						m[i] = b.getPersoane()[i];
					}
					cin.ignore(1);
					for (int i = b.getNrPersoane(); i < b.getNrPersoane() + nr; i++) {
						cout << "Nume: ";
						getline(cin, m[i]);
					}
				}
				b.setPersoane(m, b.getNrPersoane() + nr);
				return b;
			}
		}
		else {
			string* m = new string[b.getNrPersoane() + x];
			for (int i = 0; i < b.getNrPersoane(); i++) {
				m[i] = b.getPersoane()[i];
			}
			for (int i = b.getNrPersoane(); i < b.getNrPersoane() + x; i++) {
				cout << "Nume: ";
				getline(cin, m[i]);
			}
			b.setPersoane(m, b.getNrPersoane() + x);
			return b;
		}
	}
	else {
		return b;
	}
}

map<int, Film>retFilme() {
	map<int, Film>Map1 = returnFilme();
	return Map1;
}

ostream& operator<<(ostream& o, Bilet b) { // cout
	o << endl;
	o << "Cinema:\n\tId: " << b.cinema.getId() << endl;
	if (b.cinema.getNume() != nullptr) {
		o << "\tNume: " << b.cinema.getNume() << endl;
	}
	o << "\tOras: " << b.cinema.getOras() << endl;
	o << "\tAdresa: " << b.cinema.getAdresa() << endl;
	o << "\tNr zile: " << b.cinema.getNrZile() << endl;
	o << "\tZile: ";
	if (b.cinema.getZi() != nullptr) {
		int max = b.cinema.getNrZile();
		for (int i = 0; i < max; i++) {
			if (i != max - 1) {
				o << b.cinema.getZi()[i] << ", ";
			}
			else {
				o << b.cinema.getZi()[i] << endl;
			}
		}
	}
	o << endl;
	o << "Film:\n\tId: " << b.film.getId() << endl;
	if (b.film.getNume() != nullptr) {
		o << "\tNume: " << b.film.getNume() << endl;
	}
	o << "\tDurata: " << b.film.getDurata() << endl;
	o << "\tNr zile:" << b.film.getNrZile() << endl;
	o << "\tZile: ";
	if (b.film.getZi() != nullptr) {
		int max = b.film.getNrZile();
		for (int i = 0; i < max; i++) {
			if (i != max - 1) {
				o << b.film.getZi()[i] << ", ";
			}
			else {
				o << b.film.getZi()[i] << endl;
			}
		}
	}
	o << "\tOra de inceput: " << b.film.getStart() << endl;
	o << endl;
	o << "Id: " << b.id << endl;
	if (b.nume != nullptr) {
		o << "Nume: " << b.nume << endl;
	}
	o << "Nr insotitori: " << b.nrPersoane << endl;
	if (b.persoane != nullptr) {
		for (int i = 0; i < b.nrPersoane; i++) {
			if (i != b.nrPersoane - 1) {
				o << b.persoane[i] << ", ";
			}
			else {
				o << b.persoane[i] << endl;
			}
		}
	}
	return o;
}

istream& operator>>(istream& i , Bilet& b) { // cin
	int* arr = arrIdCinemauri();
	int max = nrCinemauri();
	int x1 = 0;
	int gasit = 0;
	cout << "Selecteaza unul din urmatoarele cinemauri: " << endl;
	afiseazaCinemauri();
	cout << endl;
	while (gasit == 0) {
		cout << "Alege id-ul cinemaului dorit: (Cinema id: )" << endl;
		i >> x1;
		for (int i = 0; i < max; i++) {
			if (arr[i] == x1) {
				gasit = 1;
				break;
			}
		}
		if (gasit == 1) {
			b.setCinema(returneazaCinemaCuId(x1));
		}
		else {
			cout << "Id-ul introdus nu exista." << endl;
		}
	}
	int* arr2 = returnFilmeDinCinema(x1);
	if (arr2[0] > 0) {
		int j = 0;
		int max2 = returnNrFilmeDinCinema(x1);
		int x2 = 0;
		int gasit2 = 0;
		int locFilm = 0;
		cout << "Selecteaza unul din urmatoarele filme care ruleaza la cinemaul cu id: " << x1 << "." << endl;
		map<int, Film> Map = returnFilme();
		map<int, Film> Map2;
		int u = 0;
		for (map<int, Film>::iterator i = Map.begin(); i != Map.end(); i++) {
			for (int j = 0; j < max2; j++) {
				if (i->second.getId() == arr2[j]) {
					cout << i->second << endl;
					Map2[u] = i->second;
					u++;
				}
			}
		}
		while (gasit2 == 0) {
			cout << "Alege id-ul filmului dorit: (Film id: )" << endl;
			i >> x2;
			for (map<int, Film>::iterator i = Map2.begin(); i != Map2.end(); i++) {
				if (i->second.getFilmId() == x2) {
					b.setFilm(i->second);
					gasit2 = 1;
				}
			}
		}
		u = returnLocuriLibereFilm(x1, b.film.getId());
		if (u >= 1) {
			cout << "Nume: " << endl;
			char buffer[101];
			i.ignore(1);
			i.getline(buffer, 100);
			b.nume = new char[strlen(buffer) + 1];
			strcpy_s(b.nume, strlen(buffer) + 1, buffer);
			int z = returnLocuriLibereFilm(x1, b.film.getId()) - 1;
			int z1 = 0;
			if (z > 4) {
				z1 = 4;
			}
			if (z >= 0 && z <= 4) {
				z1 = z;
			}
			cout << z << endl;
			cout << "Numar de insotitori: " << "(max: " << z1 << ")" << endl;
			int nrInsotitori = -1;
			i >> nrInsotitori;
			while (nrInsotitori < 0 && nrInsotitori > z1) {
				cout << "Numarul de insotitori nu poate fi negativ." << endl;
				i >> nrInsotitori;
			}
			string* insotitori = new string[nrInsotitori];
			i.ignore(1);
			for (int y = 0; y < nrInsotitori; y++) {
				cout << "Insotitor[" << y + 1 << "]: ";
				getline(i, insotitori[y]);
			}
			b.setPersoane(insotitori, nrInsotitori);
			scadeLocuriLibere(x1, b.film.getId(), nrInsotitori + 1);
			delete[] insotitori;
			return i;
		}
		else {
			cout << "Nu mai sunt locuri libere la film." << endl;
			return i;
		}
		
	}
	else {
		cout << "Cinemaul nu are filme." << endl;
	}
}

int nrBilete() {
	ifstream f("Bilet.bin", ios::binary);
	if (f.is_open()) {
		f.seekg(0, ios::end);
		int x = f.tellg();
		int z = x / 2455;
		f.close();
		return z;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
		return 0;
	}
}

void ordoneazaBiletId() {
	fstream f("Bilet.bin", ios::in | ios::out | ios::binary);
	if (f.is_open()) {
		int biletId = 1;
		for (int i = 0; i < nrBilete(); i++) {
			f.seekg((1922*(i+1))+(533*i)); //1922 locatia id, 533 marime bilet fara cinema si film
			f.write((char*)&biletId, sizeof(biletId));
			biletId++;
		}
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

map<int, Bilet> returnBilete() {
	map<int, Bilet> B;
	Bilet b;
	int i = 0;
	int max = nrBilete();
	ifstream f("Bilet.bin", ios::binary);
	if (f.is_open()) {
		for (int j = 0; j < max; j++) {
			b.deserialize(j * 2455);
			B[i] = b;
			i++;
		}
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
	return B;
}

void stergeBazaDateBilete() {
	ofstream f("Bilet.bin", ios::trunc | ios::binary);
	if (f.is_open()) {
		f.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void afiseazaBilete() {
	map<int, Bilet> B = returnBilete();
	for (int i = 0; i < B.size(); i++) {
		cout << B[i] << endl;
	}
}

int* arrIdBilete() {
	int* arrIdBilete = new int[nrBilete()];
	const int max = nrBilete();
	ifstream f("Bilet.bin", ios::binary);
	if (f.is_open()) {
		for (int i = 0; i < max; i++) {
			int x = 0;
			f.seekg((1922 * (i + 1)) + (533 * i));
			f.read((char*)&x, sizeof(x));
			arrIdBilete[i] = x;
		}
		f.close();
		return arrIdBilete;
	}
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}

void affArrIdBilete() {
	int* arr = arrIdBilete();
	cout << "Exista urmatoarele bilete cu Id: " << endl;
	for (int i = 0; i < nrBilete(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int locBiletCuId() { //returneaza locatia unui bilet in fisier
	ifstream h("Bilet.bin", ios::binary);
	if (h.is_open()) {
		int x1 = 0;
		int locatie = 0;
		int gasit = 0;
		affArrIdBilete();
		cout << "Introdu id-ul biletului pe care vrei sa il gasesti: " << endl;
		cin >> x1;
		for (int i = 0; i < nrBilete(); i++) {
			int id = 0;
			h.seekg((1922 * (i + 1)) + (533 * i));
			h.read((char*)&id, sizeof(id));
			if (id == x1) {
				locatie = h.tellg();
				locatie -= 4;
				locatie -= 1922;
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

void afiseazaBiletCuId() {
	int z = locBiletCuId();
	Bilet b;
	b.deserialize(z);
	cout << b << endl;
}

void inlocuieBiletCuId() {
	int x = locBiletCuId();
	if (x < 100000) {
		Bilet b;
		cin >> b;
		b.serialize1LaLoc(x);
		ordoneazaBiletId();
		cout << "Bilet modificat cu succes" << endl;
	}
}

void stergeBilet() {
	afiseazaBilete();
	int x1 = 0;
	int gasit = 0;
	affArrIdBilete();
	cout << endl;
	int* id = arrIdBilete();
	cout << "Introdu id-ul Biletului pe care vrei sa il stergi: " << endl;
	cin >> x1;
	for (int i = 0; i < nrBilete(); i++) {
		if (x1 == id[i]) {
			gasit = 1;
		}
	}if (gasit == 1) {
		int sigur = 0;
		map<int, Bilet>B = returnBilete();
		for (int i = 0; i < B.size(); i++) {
			//cout << B[i] << endl;
		}
		cout << "Esti sigur ca vrei sa stergi biletul cu Id : " << x1 << " ?" << endl;
		cout << "\t1)Da\n\t*)Nu\nAlegere: " << endl;
		cin >> sigur;
		if (sigur == 1) {
			for (int i = 0; i < B.size(); i++) {
				if (B[i].getId() == x1) {
					scadeLocuriLibere(B[i].getCinema().getId(),B[i].getFilm().getId(),-(B[i].getNrPersoane()+1));
					B.erase(i);
					break;
				}
			}
			stergeBazaDateBilete();
			for (map<int, Bilet>::iterator it = B.begin(); it != B.end(); it++) {
				it->second.serialize1();
			}
			ordoneazaBiletId();
		}
		else {
			cout << "Biletul nu a fost sters." << endl;
		}
	}
	else {
		cout << "Id-ul introdus nu exista." << endl;
	}
}

void introduBilet() {
	Bilet b;
	cin >> b;
	//string z = b.getNume();
	if (b.getNume()!=nullptr) {
		b.serialize1();
		ordoneazaBiletId();
		//void introduSiSerializeazaBilet(Bilet);
		//introduSiSerializeazaBilet(b);
		int* x = new int[b.getNrPersoane() + 1];
		for (int j = 0; j < b.getNrPersoane() + 1; j++) {
			x[j] = 100;
		}
		Incasare i(nrBilete(), b.getNume(), b.getNrPersoane() + 1, x);
		//cout << i << endl;
		i.serialize();
	}
	else {
		cout << "Biletul nu a fost introdus." << endl;
	}
}