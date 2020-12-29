#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include "Film.h"
using namespace std;


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
/*s
void arataFilme() {
	ifstream g("FilmTEXT.txt");
	if (g.is_open()) {
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
	else {
		cout << "Eroare la deschiderea fisierului." << endl;
	}
}*/
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

map<int, Film> citire1() { // afiseaza toate filmele din fisier
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
	map<int, Film>Map1 = citire1();
	return Map1;
}

void afiseazaFilme() {
	map<int, Film>Map1 = citire1();
	for (int i = 0; i < Map1.size(); i++) {
		cout << Map1[i] << endl;
	}
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
			f.seekg((long long)i * 860);
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
	}else {
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
	int x1 = 0;
	int gasit = 0;
	affArrIdFilme();
	cout << endl;
	int* id = arrIdFilme();
	cout << "Introdu id-ul filmului pe care vrei sa il inlocuiesti: " << endl;
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
					cout << "Gasit" << endl;
					Map.erase(i);
					break;
				}
			}
			stergeBazaDateFilme1();
			for (map<int, Film>::iterator it = Map.begin(); it != Map.end(); it++) {
				it->second.serialize1();
			}
			ordoneazaFilmId();
		}else {
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

/*
void stergeBazaDateFilme() {
	ofstream f("Film.bin", ios::trunc | ios::binary);
	f.close();
}
*/

void resetLocuri() {
	vector<vector<int>> v1;
	vector<int> v2;
	int sizeV1 = 5;
	int sizeV2 = 10;
	v1.resize(sizeV1);
	v2.resize(sizeV2);
	for (int j = 0; j < v2.size(); j++) {
		v2[j] = 1;
	}
	for (int i = 0; i < v1.size(); i++) {
		v1[i] = v2;
	}
	fstream o("Locuri.bin", ios::in | ios::out | ios::binary);
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v2.size(); j++) {
			o.write((char*)&v1[i][j], sizeof(v1[i][j]));
		}
	}
	o.close();

	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v2.size(); j++) {
			cout << v1[i][j] << " ";
		}
		cout << endl;
	}
}

void afiseazalocuri() {
	vector<vector<int>> v3;
	vector<int> v4;
	int sizeV3 = 5;
	int sizeV4 = 10;
	v3.resize(sizeV3);
	v4.resize(sizeV4);
	fstream p("Locuri.bin", ios::in | ios::out | ios::binary);
	for (int j = 0; j < v3.size(); j++) {
		for (int i = 0; i < v4.size(); i++) {
			p.read((char*)&v4[i], sizeof(v4[i]));
		}
		v3[j] = v4;
	}
	p.close();

	for (int i = 0; i < v3.size(); i++) {
		for (int j = 0; j < v4.size(); j++) {
			cout << v3[i][j] << " ";
		}
		cout << endl;
	}
}

vector<vector<int>> returnLocuri() {
	vector<vector<int>> v3;
	vector<int> v4;
	v3.resize(5);
	v4.resize(10);
	fstream p("Locuri.bin", ios::in | ios::out | ios::binary);
	for (int j = 0; j < v3.size(); j++) {
		for (int i = 0; i < v4.size(); i++) {
			p.read((char*)&v4[i], sizeof(v4[i]));
		}
		v3[j] = v4;
	}
	p.close();
	return v3;
}

void schimbaLocuri() {
	cout << "Introdu randul dorit(1-5): " << endl;
	int q1 = 0;
	cin >> q1;
	cout << "Introdu locul dorit(1-10): " << endl;
	int q2 = 0;
	cin >> q2;
	if ((q1 > 0 && q1 <= 5) && (q2 > 0 && q2 <= 10)) {
		vector<vector<int>> temp = returnLocuri();
		temp[q1 - 1][q2 - 1] = 2;
		fstream o("Locuri.bin", ios::in | ios::out | ios::binary);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				o.write((char*)&temp[i][j], sizeof(temp[i][j]));
			}
		}
		o.close();
	}
	else {
		cout << "Randul si locul dorit nu exista." << endl;
	}

	/*
	vector<vector<int>> v3;
	vector<int> v4;
	int sizeV3 = 5;
	int sizeV4 = 10;
	v3.resize(sizeV3);
	v4.resize(sizeV4);
	cout << "Introdu randul dorit(1-5): " << endl;
	int q1 = 0;
	cin >> q1;
	cout << "Introdu locul dorit(1-10): " << endl;
	int q2 = 0;
	cin >> q2;
	int placeholder = 0;
	int ocupat = 2;
	fstream k("Locuri.bin", ios::in | ios::out | ios::binary);
	for (int i = 0; i < v3.size(); i++) {
		for (int j = 0; j < v4.size(); j++) {
			k.read((char*)&placeholder, sizeof(placeholder));
			if (i == q1 - 1 && j == q2 - 1) {
				//int x = k.tellg();
				//k.read((char*)&placeholder, sizeof(placeholder));
				//k.seekp(x);
				k.write((char*)&ocupat, sizeof(ocupat));
				//break;
			}
		}
	}
	k.close();
	*/
}

int main() {
	
	//////////////////////////////////////TESTE CLASA FILM////////////////////////////////
	string x[] = { "Luni", "Sambata", "Duminica" };
	string y[] = { "Luni", "Sambata", "Duminica", "Sambata" };
	Film a(2, "Batman", 2.0f, 3, x, 10.00f);
	Film b(3, "Harap Alb si cei 7 pitici", 2.0f, 4, y, 5.00f);
	Film c(3, "Cinderella", 1.0f, 4, y, 10.00f);
	//stergeBazaDateFilme1();
	//a.serialize1();
	//b.serialize1();
	//c.serialize1();
	
	//afiseazaFilme();

	//v1[0][1] = 1;

	//resetLocuri();

	//afiseazaFilme();

	cout << a << endl;

	//afiseazalocuri();
	//resetLocuri();
	//schimbaLocuri();
	//cout << endl;
	//cout << endl;
	//afiseazalocuri();

}   