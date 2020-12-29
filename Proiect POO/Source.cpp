#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <set>
#include <algorithm> 
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
	//Film a(2, "Batman", 2.0f, 3, x, 10.00f);
	//Film b(3, "Harap Alb si cei 7 pitici", 2.0f, 4, y, 5.00f);
	//Film c(3, "Cinderella", 1.0f, 4, y, 10.00f);
	//stergeBazaDateFilme1();
	//a.serialize1();
	//b.serialize1();
	//c.serialize1();
	
	//afiseazaFilme();

	//v1[0][1] = 1;

	//resetLocuri();

	//afiseazaFilme();
	//int u = Film::getNumarFilme();
	//cout << u << endl;
	
	//afiseazaNumarFilme();
	//afiseazaFilme();
	//cout << a << endl;

	//string* p = a.getZi();
	//for (int i = 0; i < a.getNrZile(); i++) {
	//	cout << p[i] << endl;
	//}

	//afiseazalocuri();
	//resetLocuri();
	//schimbaLocuri();
	//cout << endl;
	//cout << endl;
	//afiseazalocuri();

	//float u = 12.30;
	
	//cout << fixed << setprecision(2) << u << endl;

	Cinema n(1, "Cinemagia", "Bucuresti", "Iancului 53", 4, y);
	Cinema nn(2, "Cinemagia2", "Bucuresti2", "Iancului 54", 3, x);

	//fstream o("Cinema.bin" , ios::in | ios::out | ios::trunc | ios::binary);
	//o.close();
	//n.serialize();
	//nn.serialize();

	//ordoneazaCinemaId();
	//Cinema z,l;
	//z.deserialize(2124);
	//cout << z << endl;
	//l.deserialize(3186);
	//cout << l << endl;

	//int u = nrCinemauri();
	//cout << u << endl;

	//set<Cinema> t;
	//t.insert(n);
	//t.insert(nn);
	//for (set<Cinema>::iterator i = t.begin(); i != t.end(); i++) {
	//	cout << *i << endl;
	//}

	//afiseazaCinemauri();
	//int u = nrCinemauri();
	//cout << u << endl;

	//int* u = arrIdCinemauri();
	//for (int i = 0; i < nrCinemauri(); i++) {
	//	cout << u[i] << endl;
	//}

	//affArrIdCinemauri();

	//int u = locCinemaCuId();
	//cout << u << endl;
	//afiseazaCinemaCuId();
	//inlocuieCinemaCuId();
	//afiseazaCinemauri();

	/*Cinema o;
	o = returneazaCinemaCuId(3);
	cout << o << endl;*/

	//stergeCinema();
	//schimbaAtributCinema();
	afiseazaCinemauri();
}   