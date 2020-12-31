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
		const_cast<int&>(this->id) = id;
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
		const_cast<int&>(id) = x;
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

	void serialize() {

		//cinema.serializeBilet("Bilet.bin");

		//film.serialize1Bilet("Bilet.bin");
		int cinema_id = cinema.getCinemaId();
		int cinema_id_id = cinema.getId();
		char* cinema_nume = new char[strlen(cinema.getNume() + 1)];
		strcpy_s(cinema_nume, strlen(cinema.getNume()) + 1, cinema.getNume());
		string cinema_oras = cinema.getOras();
		string cinema_adresa = cinema.getAdresa();
		int cinema_nrZile = cinema.getNrZile();
		string* zi = new string[cinema_nrZile];
		zi = cinema.getZi();
		//strcpy_s(cinema_nume, strlen(cinema.getNume()) + 1, cinema.getNume());
		ofstream f("Bilet.bin", ios::app | ios::binary);
		if (f.is_open()) {
			f.write((char*)&cinema_id, sizeof(cinema_id));
			f.write((char*)&cinema_id_id, sizeof(cinema_id_id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(cinema_nume, len);
			f.write((char*)&len, sizeof(len));
			f.write(cinema_oras.c_str(), len);
			f.write((char*)&len, sizeof(len));
			f.write(cinema_adresa.c_str(), len);
			f.write((char*)&cinema_nrZile, sizeof(cinema_nrZile));
			for (int i = 0; i < 7; i++) {
				//if (zi[i].length() != 0 && zi[i].length() < 9) {
				if (zi != nullptr) {
					if (zi[i].length() > 0 && zi[i].length() < 20) {
						f.write((char*)&len, sizeof(len));
						f.write(zi[i].c_str(), len);
					}
					//}
					else {
						f.write((char*)&len, sizeof(len));
						f.write("", len);
					}
				}
			}
			int y = f.tellp();
			cout << y << endl;

			int film_filmId = film.getFilmId();
			int film_id = film.getId();
			char* film_nume = new char[strlen(film.getNume() + 1)];
			strcpy_s(film_nume, strlen(film.getNume()) + 1, film.getNume());
			float film_durata = film.getDurata();
			int film_nrZile = film.getNrZile();
			string* zi1 = new string[film_nrZile];
			zi1 = film.getZi();
			float film_start = film.getStart();
			strcpy_s(film_nume, strlen(film.getNume()) + 1, film.getNume());
			f.write((char*)&film_filmId, sizeof(film_filmId));
			f.write((char*)&film_id, sizeof(film_id));
			len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(film_nume, len);
			f.write((char*)&film_durata, sizeof(film_durata));
			f.write((char*)&film_nrZile, sizeof(film_nrZile));
			int len1 = 101;
			for (int i = 0; i < 7; i++) {
				if (zi1[i].length() != 0 && zi1[i].length() < 9) {
					f.write((char*)&len1, sizeof(len1));
					f.write(zi1[i].c_str(), len1);
				}
				else {
					f.write((char*)&len1, sizeof(len1));
					f.write("", len1);
				}
			}
			f.write((char*)&film_start, sizeof(film_start));

			y = f.tellp();
			cout << y << endl;
			f.write((char*)&id, sizeof(id));
			len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&nrPersoane, sizeof(nrPersoane));
			len1 = 101;
			for (int i = 0; i < 5; i++) {
				if (persoane[i].length() != 0 && persoane[i].length() < 20) {
					f.write((char*)&len1, sizeof(len1));
					f.write(persoane[i].c_str(), len1);
				}
				else {
					f.write((char*)&len1, sizeof(len1));
					f.write("", len1);
				}
			}
			y = f.tellp();
			cout << y << endl;
			f.close();
		}
	}

	void serialize1() {

		cinema.serializeBilet("Bilet.bin");

		film.serialize1Bilet("Bilet.bin");
		ofstream f("Bilet.bin", ios::app | ios::binary);
		if (f.is_open()) {
			int y = f.tellp();
			cout << y << endl;
			f.write((char*)&id, sizeof(id));
			int len = 101;
			f.write((char*)&len, sizeof(len));
			f.write(nume, len);
			f.write((char*)&nrPersoane, sizeof(nrPersoane));
			int len1 = 101;
			for (int i = 0; i < 5; i++) {

				if (persoane != nullptr) {
					if (persoane[i].length() != 0 && persoane[i].length() < 20) {
						f.write((char*)&len1, sizeof(len1));
						f.write(persoane[i].c_str(), len1);
					}
					else {
						f.write((char*)&len1, sizeof(len1));
						f.write("", len1);
					}
				}
			}
			y = f.tellp();
			cout << y << endl;
			f.close();
		}
	}

	/*void deserialize(int x) {
		fstream f("Bilet.bin", ios::in | ios::out | ios::binary);
		int cinema_id = 0;
		int cinema_id_id = 0;
		char* cinema_nume = nullptr;
		//strcpy_s(cinema_nume, strlen(cinema.getNume()) + 1, cinema.getNume());
		string cinema_oras = "";
		string cinema_adresa = "";
		int cinema_nrZile = 0;
		//string* zi = new string[cinema_nrZile];
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
			f.read((char*)&len, sizeof(len));
			char* aux2 = new char[len];
			f.read(aux2, len);
			cinema_adresa = aux2;
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
			int y = f.tellg();
			cout << y << endl;

			int film_filmId = 0;
			int film_id = 0;
			char* film_nume = nullptr;
			//strcpy_s(film_nume, strlen(film.getNume()) + 1, film.getNume());
			float film_durata = 0;
			int film_nrZile = 0;
			//zi1 = film.getZi();
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
			//delete[] zi;
			string* zi1 = new string[film_nrZile];
			for (int i = 0; i < film_nrZile; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
				zi1[i] = aux1;
			}
			for (int i = film_nrZile; i < 7; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
			}
			f.read((char*)&film_start, sizeof(film_start));
			f.tellg();
			cout << y << endl;
			if (film_id > 0) {
				Film placeHolder1(film_id, film_nume, film_durata, film_nrZile, zi1, film_start, film_filmId);
				if (placeHolder1.getFilmId() > 0) {
					setFilm(placeHolder1);
				}
			}

			y = f.tellg();
			cout << y << endl;

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
			}
			for (int i = nrPersoane; i < 4; i++) {
				int len1 = 0;
				f.read((char*)&len1, sizeof(len1));
				char* aux1 = new char[len1];
				f.read(aux1, len1);
			}
			y = f.tellg();
			cout << y << endl;

			f.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului." << endl;
		}
	}*/

	friend ostream& operator<<(ostream&, Bilet);
	friend istream& operator>>(istream&, Bilet&);
};

int Bilet::nrBilete = 0;

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
	int j = 0;
	int max2 = returnNrFilmeDinCinema(x1);
	int x2 = 0;
	int gasit2 = 0;
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
	cout << "Nume: " << endl;
	char buffer[101];
	i.ignore(1);
	i.getline(buffer, 100);
	b.nume = new char[strlen(buffer) + 1];
	strcpy_s(b.nume, strlen(buffer) + 1, buffer);
	int z = returnLocuriLibereFilm(x1, b.film.getId());
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
	for (int y = 0; y < nrInsotitori; y++) {
		cout << "Insotitor[" << y + 1 << "]: ";
		i >> insotitori[y];
	}
	b.setPersoane(insotitori, nrInsotitori);
	return i;
}
