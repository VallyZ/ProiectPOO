#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
//#include <vector>
using namespace std;



class Film {
private:
	const int filmId = 0;
	int id;
	string nume;
	float durata;
	int nrZile;
	string* zi;
	float start;//ora de incepere 12.00;
	static int numarFilme;

public:
	Film() : filmId(++numarFilme) {
		id = 0;
		nume = "";
		durata = 0.0;
		nrZile = 0;
		zi = nullptr;
		start = 0.0;
	}

	Film(int id, string nume, float durata, int nrZile, string* zi, float start) : filmId(++numarFilme) {
		if (id > 0) {
			this->id = id;
		}
		this->nume = nume;
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
	Film(int id, string nume, float durata, int nrZile, string* zi, float start, int filmId) { // folosit in citire din binar
		const_cast<int&>(this->filmId) = filmId;
		if (id > 0) {
			this->id = id;
		}
		this->nume = nume;
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
		nume = f.nume;
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
		nume = f.nume;
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
	string getNume() {
		return nume;
	}
	void setNume(string x) {
		if (x.length() > 0) {
			nume = x;
		}
		else {
			nume = "";
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
		//f.seekp(0, ios::end);
		cout << f.tellp() << endl;
		f.write((char*)&filmId, sizeof(filmId));
		f.write((char*)&id, sizeof(id));
		int len = 101;
		f.write((char*)&len, sizeof(len));
		f.write(nume.c_str(), len);
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
				f.write("",len1);
			}
			
		}
		f.write((char*)&start, sizeof(start));
		cout << f.tellp() << endl;
		f.close();
	}
	void serialize1(int x) { // Scrie in fisier binar un obiect.
		fstream f("Film1.bin", ios::out | ios::in | ios::binary);
		f.seekp(x);
		cout << f.tellp() << endl;
		f.write((char*)&filmId, sizeof(filmId));
		f.write((char*)&id, sizeof(id));
		int len = 101;
		f.write((char*)&len, sizeof(len));
		f.write(nume.c_str(), len);
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
		cout << f.tellp() << endl;
		f.close();
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
	void deserialize1(int x) {
		fstream f("Film1.bin", ios::out | ios::in | ios::binary);
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


ostream& operator<<(ostream& o, Film f) {
	o << endl;
	o << "Film id: " << f.filmId << endl;
	o << "Id: " << f.getId() << endl;
	o << "Nume: " << f.getNume() << endl;
	o << "Durata: " << f.getDurata() << endl;
	o << "Nr zile: " << f.getNrZile() << endl;
	if (f.zi != nullptr) {
		for (int i = 0; i < f.getNrZile(); i++) {
			if (i != f.getNrZile() - 1 ) {
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
		of << f.nume << endl;
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

istream& operator>>(istream& i, Film& f) {
	int id;
	string nume;
	float durata;
	int nrZile;
	float start;
	//int filmId;
	cout << "Id: ";
	//i >> filmId;
	i >> id;
	f.setId(id);
	cout << "Nume: ";
	i >> ws;
	getline(i, nume);
	f.setNume(nume);
	cout << "Durata: ";
	i >> durata;
	f.setDurata(durata);
	cout << "Nr zile: ";
	i >> nrZile;
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
		string nume;
		float durata;
		int nrZile;
		float start;
		int filmId;
		i >> filmId;
		const_cast<int&>(f.filmId) = filmId;
		i >> id;
		f.setId(id);
		i >> ws;
		getline(i, nume);
		f.setNume(nume);
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

class Consumabil {
private:
	int id;
	string nume;
	string um;
	int cant;

public:
	Consumabil() {
		id = 0;
		nume = "";
		um = "";
		cant = 0;
	}
};

class Istoric {
private:
	int id;
};

class Incasare {
private:
	float inc_bilet;
	float inc_consum;
	float total;

public:
	Incasare() {
		inc_bilet = 0;
		inc_consum = 0;
		total = 0;
	}
};

class Cinema {
private:
	int id;
	string nume;
	string adresa;

public:
	Cinema() {
		id = 0;
		nume = "";
		adresa = "";
	}
};

void arataFilme() {
	ifstream g("FilmTEXT.txt");
	Film n;
	std::map<int, Film> Map;
	for (int i = 0; i < 10; i++) {
		g >> n;
		if (n.getFilmId() >= 0) {
			Map[i] = n;
			cout << Map[i];
		}
	}
}
/*
map<int,Film> citire() {
	std::map<int, Film> Map;
	int i = 0;
	ifstream f("Film.bin", ios::binary);
	int x = f.tellg();
	f.seekg(0, ios::end);
	int y = f.tellg();
	f.seekg(0, ios::beg);
	while (x != y) {
	int filmId = 0; int id = 0; int nrZile = 0;
	string nume = "";
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
	string *zi = new string[nrZile];
	for (int i = 0; i < nrZile; i++) {
		f.read((char*)&zi[i], sizeof(zi[i]));
	}
	f.read((char*)&start, sizeof(start));
	if(id > 0) {
		Film placeHolder(id, nume, durata, nrZile, zi, start, filmId);
		if (placeHolder.getFilmId() > 0) {
			Map[i] = placeHolder;
			i++;
		}
	}
	x = f.tellg();
	}
	return Map;
	f.close();
}
*/
map<int, Film> citire1() { // afiseaza toate filmele din fisier
	std::map<int, Film> Map;
	int i = 0;
	ifstream f("Film1.bin", ios::binary);
	int x = f.tellg();
	f.seekg(0, ios::end);
	int y = f.tellg();
	f.seekg(0, ios::beg);
	while (x != y) {
		int filmId = 0; int id = 0; int nrZile = 0;
		string nume = "";
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
		}
		for (int i = nrZile; i < 7; i++) {
			int len1 = 0;
			f.read((char*)&len1, sizeof(len1));
			char* aux1 = new char[len1];
			f.read(aux1, len1);
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
	}
	return Map;
	f.close();
}

int* returnAtrLoc() { // creaza vector cu locatiile fiecarui atribut al clasei Film
	ifstream f("Film1.bin", ios::binary);
	int filmId = 0; int id = 0; int nrZile = 0;
	string nume = "";
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
	}
	for (int i = nrZile; i < 7; i++) {
		int len1 = 0;
		locZi[i] = f.tellg();
		f.read((char*)&len1, sizeof(len1));
		char* aux1 = new char[len1];
		f.read(aux1, len1);
	}
	locStart = f.tellg();
	f.read((char*)&start, sizeof(start));
	static int returnDate[] = { locFilmId, locId, locNume, locDurata, locNrZile, locZi[0], locZi[1], locZi[2], locZi[3], locZi[4], locZi[5], locZi[6], locStart };
	f.close();
	return returnDate;
}

int nrFilme() {
	ifstream f("Film1.bin", ios::binary);
	f.seekg(0, ios::end);
	int x = f.tellg();
	int z = x / 860;
	f.close();
	return z;
}

int* arrIdFilme() { // return array cu id-urile filmelor
	int* arrIdFilme = new int[nrFilme()];
	const int nrf = nrFilme();
	//int arrIdFilme[nrf];
	ifstream f("Film1.bin", ios::binary);
	for (int i = 0; i < nrf; i++) {
		int x = 0;
		f.seekg(i * 860);
		f.read((char*)&x, sizeof(x));
		arrIdFilme[i] = x;
	}
	f.close();
	return arrIdFilme;
}

int locFilmCuId() {
	ifstream h("Film1.bin", ios::binary);
	int x1 = 0;
	int locatie = 0;
	int gasit = 0;
	int* arr = arrIdFilme();
	cout << "Exista urmatoarele filme cu Id: " << endl;
	for (int i = 0; i < nrFilme(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
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
		cout << "Id-ul introdus nu exista" << endl;
	}
	else {
		return locatie;
	}
}

void afiseazaFilmCuId() {
	//if (x > 0) {
		int z = locFilmCuId();
		int* ret = returnAtrLoc();
		Film o;
		o.deserialize1(z);
		cout << o << endl;
		/*
		ifstream f("Film1.bin", ios::binary);
		int filmId = 0; int id = 0; int nrZile = 0;
		string nume = "";
		float durata = 0; float start = 0;
		f.seekg(ret[0]);
		f.read((char*)&filmId, sizeof(filmId));
		f.seekg(ret[1]);
		f.read((char*)&id, sizeof(id));
		int len = 0;
		f.seekg(ret[2]);
		f.read((char*)&len, sizeof(len));
		char* aux = new char[len];
		f.read(aux, len);
		nume = aux;
		f.seekg(ret[3]);
		f.read((char*)&durata, sizeof(durata));
		f.seekg(ret[4]);
		f.read((char*)&nrZile, sizeof(nrZile));
		string* zi = new string[nrZile];
		for (int i = 0; i < nrZile; i++) {
			int len1 = 0;
			f.seekg(ret[5 + i]);
			f.read((char*)&len1, sizeof(len1));
			char* aux1 = new char[len1];
			f.read(aux1, len1);
			zi[i] = aux1;
		}
		for (int i = nrZile; i < 7; i++) {
			int len1 = 0;
			f.seekg(ret[5 + nrZile]);
			f.read((char*)&len1, sizeof(len1));
			char* aux1 = new char[len1];
			f.read(aux1, len1);
		}
		f.seekg(ret[12]);
		f.read((char*)&start, sizeof(start));
		f.close();
		cout << filmId << endl;
		cout << id << endl;
		cout << nume << endl;
		cout << durata << endl;
		cout << nrZile << endl;
		cout << start << endl;
		for (int i = 0; i < 7; i++) {
			if (zi[i].length() != 0 && zi[i].length() < 9) {
				cout << zi[i] << endl;
			}
		}
		cout << start << endl;
	}
	else {
		cout << "Nu exista filmul cu id: " << x << endl;
	}*/
	//}
}
/*
void stergeBazaDateFilme() {
	ofstream f("Film.bin", ios::trunc | ios::binary);
	f.close();
}
*/
void stergeBazaDateFilme1() {
	ofstream f("Film1.bin", ios::trunc | ios::binary);
	f.close();
}
map<int,Film> afiseazaFilme() {
	map<int, Film>Map1 = citire1();
	for (int i = 0; i < Map1.size(); i++) {
		cout << Map1[i] << endl;
	}
	return Map1;
}

int main() {
	/*
	//////////////////////////////////////TESTE CLASA FILM////////////////////////////////
	string x[] = { "Luni", "Marti", "Joiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii" };
	string y[] = { "Luni", "Marti" };
	Film c(1, "Uganda in action", 2.0f, 2, y, 10.00f);
	Film d(2, "Venezuela", 2.0f, 3, x, 10.00f);

	ofstream f;
	f.open("FilmTEXT.txt");
	f << a;
	f << c;
	f << d;
	//f << a;
	//f << a;
	f.close();


	Film o, k, z;
	//g >> n;
	//g >> o;
	//g >> o;
	//g >> o;
	//cout << n;
	//cout << o;
	//cout << o;
	//cout << o;

	//c.serialize();
	a.serialize();
	ifstream g("FilmTEXT.txt");
	Film n;
	std::map<int, Film> Map;
	/*for (int i = 0; i < 10; i++) {
		g >> n;
		if (n.getFilmId() >= 0) {
			Map[i] = n;
			cout << Map[i];
		}
	}*/
	
	//int i = 0;
	//g >> n;
	//while (n.getFilmId() >= 0) {
	//	Map[i] = n;
	//	cout << Map[i];
	//	i++;
	//	g >> n;
	//}*/
	
	string x[] = { "Luni", "Sambata", "Duminica" };
	string y[] = { "Luni", "Sambata", "Duminica", "Sambata" };
	Film a(2, "Batman", 2.0f, 3, x, 10.00f);
	Film b(3, "Harap Alb si cei 7 pitici", 2.0f, 4, y, 5.00f);
	Film c(3, "Cinderella", 1.0f, 4, y, 10.00f);
	//stergeBazaDateFilme1();
	//a.serialize1();
	//b.serialize1();
	//map<int,Film>Map1 = citire();

	//for (int i = 0; i < Map1.size(); i++) {
	//	cout << Map1[i] << endl;
	//}

	//a.serialize1();
//	Film e;
	//e.deserialize1();
	//cout << e << endl;
	
/*
	ifstream f("Film1.bin", ios::binary);
	int id = 0;
	int id1 = 0;
	int len = 0;
	string r = "";
	f.seekg(0, ios::beg);
	int p = f.tellg();
	cout << p << endl;
	f.read((char*)&id, sizeof(id));
	f.read((char*)&id1, sizeof(id1));
	f.read((char*)&len, sizeof(len));
	char* aux = new char[len];
	f.read(aux, len);
	r = aux;
	cout << "Id film: " << id << endl;
	cout << "Nume: " << r << endl;
	f.seekg(0, ios::end);
	int u = f.tellg();
	cout << u << endl;
	//int z = u / 2;
	//cout << "Marime obiect: " << z << endl;
	f.seekg(1*860);
	f.read((char*)&id, sizeof(id));
	f.read((char*)&id1, sizeof(id1));
	f.read((char*)&len, sizeof(len));
	char* aux1 = new char[len];
	f.read(aux1, len);
	r = aux1;
	cout << "Id film: " << id << endl;
	cout << "Nume: " << r << endl;
	f.seekg(2*860);
	f.read((char*)&id, sizeof(id));
	f.read((char*)&id1, sizeof(id1));
	f.read((char*)&len, sizeof(len));
	char* aux2 = new char[len];
	f.read(aux2, len);
	r = aux2;
	cout << "Id film: " << id << endl;
	cout << "Nume: " << r << endl;
	f.seekg(3*860);
	f.read((char*)&id, sizeof(id));
	f.read((char*)&id1, sizeof(id1));
	f.read((char*)&len, sizeof(len));
	char* aux3 = new char[len];
	f.read(aux3, len);
	r = aux3;
	cout << "Id film: " << id << endl;
	cout << "Nume: " << r << endl;
	f.close();
	*/
	/*
	afiseazaFilme();

	ifstream h("Film1.bin", ios::binary);
	int x1 = 0;
	int locatie = 0;
	int gasit = 0;
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
		c.serialize1(locatie);
	}
	afiseazaFilme();
	*/
	afiseazaFilmCuId();

	//int* ret = returnAtrLoc();
	//for (int i = 0; i < 13; i++) {
	//	cout << ret[i] << endl;
	//}
	//cout << ret[12] << endl;

	//int* ret = arrIdFilme();
	//for (int i = 0; i < nrFilme(); i++) {
	//	cout << ret[i] << endl;
	//}
	//int h = locFilmCuId();
	//cout << h << endl;
	
	

	//ifstream f("Film1.bin", ios::binary);
	//int filmId = 0; int id = 0; int nrZile = 0;
	//string nume = "";
	//float durata = 0; float start = 0;
	//f.seekg(ret[0]);
	//f.read((char*)&filmId, sizeof(filmId));
	//f.seekg(ret[1]);
	//f.read((char*)&id, sizeof(id));
	//int len = 0;
	//f.seekg(ret[2]);
	//f.read((char*)&len, sizeof(len));
	//char* aux = new char[len];
	//f.read(aux, len);
	//nume = aux;
	//f.seekg(ret[3]);
	//f.read((char*)&durata, sizeof(durata));
	//f.seekg(ret[4]);
	//f.read((char*)&nrZile, sizeof(nrZile));
	//string* zi = new string[nrZile];
	//for (int i = 0; i < nrZile; i++) {
	//	int len1 = 0;
	//	f.seekg(ret[5+i]);
	//	f.read((char*)&len1, sizeof(len1));
	//	char* aux1 = new char[len1];
	//	f.read(aux1, len1);
	//	zi[i] = aux1;
	//}
	//for (int i = nrZile; i < 7; i++) {
	//	int len1 = 0;
	//	f.seekg(ret[5+nrZile]);
	//	f.read((char*)&len1, sizeof(len1));
	//	char* aux1 = new char[len1];
	//	f.read(aux1, len1);
	//}
	//f.seekg(ret[12]);
	//f.read((char*)&start, sizeof(start));
	//f.close();
	//cout << filmId << endl;
	//cout << id << endl;
	//cout << nume << endl;
	//cout << durata << endl;
	//cout << nrZile << endl;
	//cout << start << endl;
	//for (int i = 0; i < 7; i++) {
	//	if (zi[i].length() != 0 && zi[i].length() < 9) {
	//		cout << zi[i] << endl;
	//	}
	//}
	//cout << start << endl;

	//cout << endl;

	//int m = 860;
	//ifstream q("Film1.bin", ios::binary);
	//filmId = 0; id = 0; nrZile = 0;
	//nume = "";
	//durata = 0; start = 0;
	//q.seekg(ret[0] + m);
	//q.read((char*)&filmId, sizeof(filmId));
	//q.seekg(ret[1] + m);
	//q.read((char*)&id, sizeof(id));
	//len = 0;
	//q.seekg(ret[2] + m);
	//q.read((char*)&len, sizeof(len));
	//delete[] aux;
	//aux = new char[len];
	//q.read(aux, len);
	//nume = aux;
	//q.seekg(ret[3] + m);
	//q.read((char*)&durata, sizeof(durata));
	//q.seekg(ret[4] + m);
	//q.read((char*)&nrZile, sizeof(nrZile));
	//delete[] zi;
	//zi = new string[nrZile];
	//for (int i = 0; i < nrZile; i++) {
	//	int len1 = 0;
	//	q.seekg(ret[5 + i] + m);
	//	q.read((char*)&len1, sizeof(len1));
	//	char* aux1 = new char[len1];
	//	q.read(aux1, len1);
	//	zi[i] = aux1;
	//}
	//for (int i = nrZile; i < 7; i++) {
	//	int len1 = 0;
	//	q.seekg(ret[5 + nrZile] + m);
	//	q.read((char*)&len1, sizeof(len1));
	//	char* aux1 = new char[len1];
	//	q.read(aux1, len1);
	//}
	//q.seekg(ret[12] + m);
	//q.read((char*)&start, sizeof(start));
	//q.close();
	//cout << filmId << endl;
	//cout << id << endl;
	//cout << nume << endl;
	//cout << durata << endl;
	//cout << nrZile << endl;
	//cout << start << endl;
	//for (int i = 0; i < 7; i++) {
	//	if (zi[i].length() != 0 && zi[i].length() < 9) {
	//		cout << zi[i] << endl;
	//	}
	//}
	//cout << start << endl;

	//afiseazaFilme();

	//string zi = a[12];//operator []
	//cout << zi << endl;
	//cout << a << endl;
	////a = 15 + a;
	//cout << a << endl;
//	a = a + 2;
//	cout << a << endl;
//	a = a + 1;
//	cout << a << endl;
//	a = 1 + a;
//	cout << a << endl;

	//a = ++a;
	//cout << a << endl;
	//a = a++;
	//cout << a << endl;
	//a = --a;
	//cout << a << endl;
	//a = a--;
	//cout << a << endl;

	//int ok = (int)b; //cast explicit
	//cout << ok << endl;
	//b <= a;
	//if (!a) {
	//	cout << "Are zile" << endl;
	//}
	//else {
	//	cout << "Nu are zile" << endl;
	//}

	//a == b;

}   