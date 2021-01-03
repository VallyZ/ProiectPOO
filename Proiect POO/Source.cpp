#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <set>
#include <algorithm> 
#include <list>
#include <stdio.h>
#include "Film.h"
#include "Bilet.h"
#include "Consumabil.h"
#include "Incasare.h"
#include "Istoric.h"
#include "Cinema.h"
using namespace std;

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



void stergeBazaDateFilme() {
	ofstream f("Film.bin", ios::trunc | ios::binary);
	f.close();
}

/*
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

int main() {
	
	//////////////////////////////////////TESTE CLASA FILM////////////////////////////////
	string x[] = { "Luni", "Sambata", "Duminica" };
	string y[] = { "Luni", "Sambata", "Duminica", "Sambata" };
	Film a(2, "Batman", 2.0f, 3, x, 10.00f);
	//Film b(3, "Harap Alb si cei 7 pitici", 2.0f, 4, y, 5.00f);
	////Film c(3, "Cinderella", 1.0f, 4, y, 10.00f);
	////stergeBazaDateFilme1();
	////a.serialize1();
	////b.serialize1();
	////c.serialize1();

	//Cinema n(1, "Cinemagia", "Bucuresti", "Iancului 53", 4, y);
	////Cinema nn(2, "Cinemagia2", "Bucuresti2", "Iancului 54", 3, x);

	////stergeBazaDateCinema();
	////n.serialize();
	////nn.serialize();

	////schimbaAtributCinema();
	////

	////Consumabil u(1, "Cola", "ml", 3, x);
	////Consumabil uu(2, "Fanta", "ml", 0, nullptr);
	////cout << a.getZi()[1] << endl;

	//string var[] = { "Gigel", "Tudor"};
	//string var1[] = { "Gigel Mihai", "Tudor Daniel", "Andrei" };
	//string var2[] = { "Gigel Mihai", "Tudorache", "Andrei Savu Dan" };
	//string var3[] = { "Gigel Mihai" };
	//string var4[] = { "Gigel Mihai", "Gogu" , "Tudorache", "Andrei Savu Dan" };
	//Bilet p("Vali4", 3, var1);
	//Bilet pp("Vali3 Mailat", 4, var4);
	//Bilet ppp("Vali2 Eugen Mihai", 3, var2);
	//Bilet pppp("Vali1", 2, var);
	//Bilet ppppp("Valentin", 1, var3);
	//Bilet pppppp("Vali", 0, nullptr);
	////p.setFilm(a);
	////p.setCinema(n);
	//////cout << p << endl;
	////p.serialize1();
	////pp.setFilm(a);
	////pp.setCinema(n);
	////pp.serialize1();
	////ppp.setFilm(a);
	////ppp.setCinema(n);
	////ppp.serialize1();
	////pppp.setFilm(a);
	////pppp.setCinema(n);
	////pppp.serialize1();
	////ppppp.setFilm(a);
	////ppppp.setCinema(n);
	////ppppp.serialize1();
	////pppppp.setFilm(a);
	////pppppp.setCinema(n);
	////pppppp.serialize1();
	//
	////cout << p.getFilm().getNume() << endl;
	////cout << p.getFilm() << endl;
	////map<int, Film> map1 = retFilme();
	////p.setFilm(map1[1]);
	////cout << p.getFilm() << endl;
	////stergeCinema();
	////introduCinema();
	//Bilet i;
	////cin >> i;
	////i.serialize1();
	////i.deserialize(0);
	////cout << i << endl;
	////i.deserialize(2455);
	////cout << i << endl;
	////i.deserialize(4910);
	////cout << i << endl;
	////i.deserialize(7365);
	////cout << i << endl;
	////i.deserialize(9820);
	////cout << i << endl;
	////i.deserialize(12275);
	////cout << i << endl;
	////i.getCinema().serializeBilet("Bilet.bin");
	////i.getFilm().serialize1Bilet("Bilet.bin");
	////i.serialize1();
	////cout << i << endl;
	////i.deserialize(0);
	////Bilet g;
	////g.deserialize(0);
	////cout << g << endl;

	////afiseazaCinemaCuId();
	////ordoneazaBiletId();
	////i.deserialize();
	////i.serialize();
	////afiseazaFilme();
	////afiseazaFilmInCinema(1);
	////stergeFilmDinCinema(1, 3);
	////afiseazaFilmInCinema(1);

	////Film u;
	////cin >> u;
	////u.serialize1();
	//////u.deserialize1(0);
	////cout << u << endl;
	////stergeBazaDateBilete();
	//int z = nrBilete();
	//cout << z << endl;
	//ordoneazaBiletId();
	//map<int, Bilet> v = citireBilete();

	//scadeLocuriLibere(2, 3, 1);
	//introduBilet();
	//afiseazaFilmInCinema(2);

	//Bilet l;
	//l = pp++;
	//cout << l << endl;

	//cout << !pp << endl;



/*
	char* nume1 = nullptr;
	int nr1 = 0;
	string* arr = nullptr;

	char buffer[101];
	//cin.ignore(1);
	cout << "Nume: ";
	cin.getline(buffer, 100);
	nume1 = new char[strlen(buffer) + 1];
	strcpy_s(nume1, strlen(buffer) + 1, buffer);
	cout << "Nr: ";
	cin >> nr1;
	arr = new string[nr1];
	cin.ignore(1);
	for (int i = 0; i < nr1; i++) {
		//cin >> ws;
		cout << "Persoana: ";
		getline(cin, arr[i]);
	}

	cout << nume1 << endl;
	cout << nr1 << endl;
	for (int i = 0; i < nr1; i++) {
		cout << arr[i] << endl;
	}
	ofstream f("Test.bin", ios::app, ios:: binary);
	if (f.is_open()) {

		int len = 101;
		f.write((char*)&len, sizeof(len));
		f.write(nume1, len);

		f.write((char*)&nr1, sizeof(nr1));

		for (int i = 0; i < nr1; i++) {
			f.write((char*)&len, sizeof(len));
			f.write(arr[i].c_str(), len);
			f.write("\0", sizeof(char));
		}
		f.close();
	}

	char* nume2 = nullptr;
	int nr2 = 0;
	string* arr2 = nullptr;

	fstream g("Test.bin", ios::in | ios::out | ios::binary);
	if (g.is_open()) {
		int len = 0;
		g.read((char*)&len, sizeof(len));
		char* aux = new char[len];
		g.read(aux, len);
		nume2 = aux;

		g.read((char*)&nr2, sizeof(nr2));

		arr2 = new string[nr2];
		for (int i = 0; i < nr2; i++) {
			len = 0;
			g.read((char*)&len, sizeof(len));
			char* aux1 = new char[len];
			g.read(aux1, len);
			//arr2[i] = aux1;
			getline(g, arr2[i], '\0');
		}
		g.close();
	}
	cout << nume2 << endl;
	cout << nr2 << endl;
	for (int i = 0; i < nr2; i++) {
		cout << arr2[i] << endl;
	}

	remove("Test.bin");

	*/
}   