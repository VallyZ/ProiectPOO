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

void stergeBazaDateFilme() {
	ofstream f("Film.bin", ios::trunc | ios::binary);
	f.close();
}

int main() {
	//string x[] = { "Luni", "Sambata", "Duminica" };
	//string y[] = { "Luni", "Sambata", "Duminica", "Sambata" };
	//Film a(2, "Batman", 2.0f, 3, x, 10.00f);
	//Film b(3, "Harap Alb si cei 7 pitici", 2.0f, 4, y, 5.00f);
	////Film c(3, "Cinderella", 1.0f, 4, y, 10.00f);

	//Cinema n(1, "Cinemagia", "Bucuresti", "Iancului 53", 4, y);
	////Cinema nn(2, "Cinemagia2", "Bucuresti2", "Iancului 54", 3, x);

	//string var[] = { "Gigel", "Tudor"};
	//string var1[] = { "Gigel Mihai", "Tudor Daniel", "Andrei" };
	//string var2[] = { "Gigel Mihai", "Tudorache", "Andrei Savu Dan" };
	//string var3[] = { "Gigel Mihai" };
	//string var4[] = { "Gigel Mihai", "Gogu" , "Tudorache", "Andrei Savu Dan" };
	//Bilet p("Vali4", 3, var1);

	//Incasare i;
	//cin >> i;
	//i.serialize();

	Incasare ii;
	ii.deserialize(0);
	ii = ++ii;
	cout << ii;


	//affArrIdBilete();
	//afiseazaIncasari();
	//stergeBilet();
	////stergeIncasare();
	//afiseazaBilete();
	//afiseazaIncasari();

	

}   