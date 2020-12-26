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
	//vector <Film> aa;
	static int numarFilme;

public:
	Film() : filmId(++numarFilme) {
		id = 0;
		nume = "";
		durata = 0.0;
		nrZile = 0;
		zi = nullptr;
		start = 0.0;

		//aa.resize(1, *this);
		//aa.push_back(*this);
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
			//this->zi = new string[sizeof(zi) / sizeof(zi[0])];
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
			//this->zi = new string[sizeof(zi) / sizeof(zi[0])];
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

	//////////////////////////////////FA SETTERE PENTRU TOATE ATRIBUTELE////////////////////////
};

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

void stergeBazaDateFilme() {
	ofstream f("Film.bin", ios::trunc | ios::binary);
	f.close();
}

//merge?

int main() {
	/*
	//////////////////////////////////////TESTE CLASA FILM////////////////////////////////
	string x[] = { "Luni", "Marti", "Joiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii" };
	string y[] = { "Luni", "Marti" };
	//cout << x->length() << endl;
	//cout << sizeof(x[0]) << endl;
	//cout << sizeof(x[1]) << endl;
	//cout << sizeof(x[2]) << endl;
	//cout << sizeof(x) / sizeof(x[0]) << endl;

	//Film z;

	Film a(1, "Venom", 2.0f, 3, x, 10.00f);
	//cout << a;
	//a.setZi(y, 2);
	//cout << a;
	//cout << z;
	//Film b = a;
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
	Film a(2, "Batman", 2.0f, 3, x, 10.00f);
	a.serialize();
	a.serialize();
	map<int,Film>Map1 = citire();

	for (int i = 0; i < Map1.size(); i++) {
		cout << Map1[i] << endl;
	}


	//cout << endl;
	//cout << Map.size() << endl;
	
	//Film e;// , u;
	//e.deserialize();
	//cout << e << endl;
//	u.deserialize();
	//cout << u << endl;
	//arataFilme();

	//cout << sizeof(u) << endl;

	/*
	fstream p("Film.bin", ios::_Nocreate | ios::binary | ios::in);
	p.seekg(0, ios::beg);
	//cout << p.tellp() << endl;
	int oo = 0;
	p.read((char*)&oo, sizeof(int));
	p.close();
	cout << "id: " << oo << endl;

	fstream w("Film.bin", ios::_Nocreate | ios::binary | ios::in);
	w.seekg(907);
	int ok = 0;
	w.read((char*)&ok, sizeof(int));
	w.close();
	cout << "id: " << ok << endl;
	*/

	//fstream xz("Film.bin", ios::_Nocreate | ios::binary | ios::in);
	////nrart((xz.open("Film.bin"),ios::binary), sizeof(Film));
	//xz.seekg(0, ios::beg);
	//xz.tellg();
	//cout << xz.tellg() << endl;
	//xz.seekg(0, ios::end);
	//xz.tellg();
	//cout << xz.tellg() << endl;
	//cout << xz.tellg() / sizeof(Film) << endl;
	//xz.seekg(0, ios::beg);
	////cout << xz.tellg() << endl;
	//xz.close();
	
	/*string x[] = { "Luni", "Marti", "Joi" };
	cout << sizeof(x) / sizeof(x[1]) << endl;
	ofstream f("test.bin", ios::binary);
	for (int i = 0; i < 3; i++) {
		f.write((char*)&x[i], sizeof(x[i]));
	}
	f.close();

	ifstream g("test.bin", ios::binary);
	//string y[] = { "","","" };
	string* y = new string[3];
	for (int i = 0; i < 3; i++) {

		g.read((char*)&y[i], sizeof(y[i]));
		//int len = 0;
		//g.read((char*)&len, sizeof(len));
		//char* aux = new char[len];
		//g.read(aux, len);
		//y[i] = aux;
		//cout << y[i] << endl;


	}
	//delete[] y;
	for (int i = 0; i < 3; i++) {
		cout << y[i] << endl;
	}
	g.close();*/


	//cin >> z;
	//ofstream f;
	//f.open("FilmTEXT.txt");
	//f << z;
	//f.close();
	//FILE* P;
	//int size = sizeof(float);
	//float start = 0;
	//fstream q("FilmTEXT.txt", ios::_Nocreate | ios::in);
	//cout << "Delpasament in fisier: " << q.tellg() << endl;
	//q.seekg(0, ios::end);
	//cout << "Delpasament in fisier: " << q.tellg() << endl;
	//cout << "Delpasament in fisier: " << q.tellg() /sizeof(a) << endl;
	//q.read((char*)&start, size);
	//cout << start << endl;
	//fopen_s(&P, "FilmTEXT.txt", "r");
	//cout << nrart(P, a);
	//cout << sizeof(Film) << endl;
	//cout << sizeof(a) << endl;
	//cout << sizeof(c) << endl;




}