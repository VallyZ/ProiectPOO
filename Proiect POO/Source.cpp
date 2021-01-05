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
#include "Cinema.h"
using namespace std;

int a = -1;

//curata ecranul
void clear() {
	system("pause");
	system("cls");
}

void alegere() {
	cout << "Alege una din urmatoarele categorii:\n\t1)Cinema\n\t2)Film\n\t3)Consumabil\n\t4)Bilet\n\t5)Incasare\n\n\t0)Inchide program\nAlegere: ";
	cin >> a;
	while (a < 0) {
		cout << "Alegerea nu poate fi negativa.\nAlegere: ";
		cin >> a;
	}
}

int main() {

	alegere();

	while (a!=0) {
		if (a == 1) {
			//system("cls");
			int x = 0;
			cout << "Alege una din urmatoarele operatii:\n\t1)Introdu un cinema\n\t2)Afiseaza cinemauri\n\t3)Afiseaza numarul de cinemauri\n\t4)Afiseaza cinema cu Id introdus de la tastatura\n\t5)Inlocuie cinema\n\t6)Schimba atributul unui cinema\n\t7)Sterge un cinema\n\t8)Sterge baza de date a cinamului\n\n*)Apasa orice altceva pentru a iesi din acest meniu\nAlegere: ";
			int a1 = 0;
			cin >> a1;
			switch (a1) {
			case 1:
				introduCinema();
				break;
			case 2:
				afiseazaCinemauri();
				break;
			case 3:
				x = nrCinemauri();
				cout << "Numar de cinemauri: " << x << endl;
				break;
			case 4:
				afiseazaCinemaCuId();
				break;
			case 5:
				inlocuieCinemaCuId();
				break;
			case 6:
				schimbaAtributCinema();
				break;
			case 7:
				stergeCinema();
				break;
			case 8:
				stergeBazaDateCinema();
				break;
			default:
				cout << "Alegere invalida." << endl;
			}
		}
		else if (a == 2) {
			int* xx = arrIdC(); int max = nrCinemauri(); int* y1 = arrIdF(); int max2 = nrFilme();
			int alegere = 0; int gasit = 0; int gasit1 = 0; int gasit2 = 0; int gasit11 = 0; int gasit12 = 0; int gasit13 = 0;
			int alegere1 = 0; int alegere2 = 0; int alegere11 = 0; int alegere12 = 0; int alegere13 = 0;
			int x = 0;
			cout << "Alege una din urmatoarele operatii:\n\t1)Introdu un film\n\t2)Afiseaza filme\n\t3)Afiseaza numarul de filme\n\t4)Afiseaza film cu ID introdus de la tastatura\n\t5)Inlocuie film\n\t6)Schimba atributul unui film\n\t7)Sterge un film\n\t8)Sterge baza de date filme\n\t9)Introdu toate filmele in cinemauri\n\t10)Introdu toate filmele in cinemaul introdus\n\t11)Introdu un film intr-un cinema\n\t12)Arata numarul de filme din cinemaul introdus\n\t13)Afiseaza toate filmele in toate cinemaurile\n\t14)Afiseaza toate filmele din cinemaul introdus\n\t15)Sterge toate filmele din cinema\n\n*)Apasa orice altceva pentru a iesi din acest meniu\nAlegere: ";
			int a2 = 0;
			cin >> a2;
			switch (a2) {
			case 1:
				introduFilm();
				break;
			case 2:
				afiseazaFilme();
				break;
			case 3:
				x = nrFilme();
				cout << x << endl;
				break;
			case 4:
				afiseazaFilmCuId();
				break;
			case 5:
				inlocuieFilmCuId();
				break;
			case 6:
				schimbaAtributFilm();
				break;
			case 7:
				stergeFilm();
				break;
			case 8:
				stergeBazaDateFilme1();
				break;
			case 9:
				introduToateFilmeleInCinema();
				break;
			case 10:
				affArrIdC();
				cout << "Introdu cinemaul in care vrei sa adaugi toate filmele: ";
				cin >> alegere;
				for (int i = 0; i < max; i++) {
					if (xx[i] == alegere) {
						gasit = 1;
						break;
					}
				}
				if (gasit == 1) {
					introduToateFilmeleInCinemaul(alegere);
				}
				else {
					cout << "Cinemaul introdus nu exista." << endl;
				}
				break;
			case 11:
				affArrIdC();
				cout << "Introdu cinemaul dorit: ";
				cin >> alegere1;
				for (int i = 0; i < max; i++) {
					if (xx[i] == alegere1) {
						gasit1 = 1;
						break;
					}
				}
				if (gasit1 == 1) {
					affArrIdF();
					cout << "Introdu filmul dorit: ";
					cin >> alegere2;
					for (int i = 0; i < max2; i++) {
						if (y1[i] == alegere2) {
							gasit2 = 1;
							break;
						}
					}
					if (alegere2 == 1) {
						introduFilmInCinema(alegere1, alegere2);
					}
					else {
						cout << "Filmul introdus nu exista." << endl;
					}
				}
				else {
					cout << "Cinemaul introdus nu exista." << endl;
				}
				break;
			case 12:
				affArrIdC();
				cout << "Introdu cinemaul dorit: ";
				cin >> alegere11;
				for (int i = 0; i < max; i++) {
					if (xx[i] == alegere11) {
						gasit11 = 1;
						break;
					}
				}
				if (gasit11 == 1) {
					int y = returnNrFilmeDinCinema(alegere11);
					cout << y << endl;
				}
				else {
					cout << "Cinemaul introdus nu exista." << endl;
				}
				break;
			case 13:
				afiseazaToateFilmeleDinCinema();
				break;
			case 14:
				affArrIdC();
				cout << "Introdu cinemaul dorit: ";
				cin >> alegere12;
				for (int i = 0; i < max; i++) {
					if (xx[i] == alegere12) {
						gasit12 = 1;
						break;
					}
				}
				if (gasit12 == 1) {
					afiseazaFilmInCinema(alegere12);
				}else{
					cout << "Cinemaul introdus nu exista." << endl;
				}
				break;
			case 15:
				affArrIdC();
				cout << "Introdu cinemaul dorit: ";
				cin >> alegere13;
				for (int i = 0; i < max; i++) {
					if (xx[i] == alegere13) {
						gasit13 = 1;
						break;
					}
				}
				if (gasit13 == 1) {
					stergeToateFilmeleDinCinema(alegere13);
				}
				else {
					cout << "Cinemaul introdus nu exista." << endl;
				}
				break;
			default:
				cout << "Alegere invalida." << endl;
				break;
			}
		}
		else if(a==3){
			int x = 0;
			cout << "Alege una din urmatoarele operatii\n\t1)Introdu un consumabil\n\t2)Afiseaza consumabile\n\t3)Afiseaza numarul de consumabile\n\t4)Afiseaza consumabilul introdus de la tastatura\n\t5)Inlocuie un consumabil\n\t6)Schimba atributele unui consumabil\n\t7)Sterge un consumabil\n\t8)Sterge baza de date a consumabilelor\n\n*)Apasa orice altceva pentru a iesi din acest meniu\nAlegere: ";
			int a3 = 0;
			cin >> a3;
			switch (a3) {
			case 1:
				introduConsumabil();
				break;
			case 2:
				afiseazaConsumabile();
				break;
			case 3:
				x = nrConsumabile();
				cout <<"Numar de consumabile: " << x << endl;
				break;
			case 4:
				afiseazaConsumabilCuId();
				break;
			case 5:
				inlocuieConsumabilCuId();
				break;
			case 6:
				schimbaAtributConsumabil();
				break;
			case 7:
				stergeConsumabil();
				break;
			case 8:
				stergeBazaDateConsumabil();
				break;
			default:
				cout << "Alegere invalida." << endl;
				break;
			}
		}
		else if (a == 4) {
			int x = 0;
			cout << "Alege una din urmatoarele operatii:\n\t1)Introdu un bilet\n\t2)Afiseaza bilete\n\t3)Afiseaza numarul de bilete\n\t4)Afiseaza un bilet cu id-ul introdus de la tastatura\n\t5)Inlocuie un bilet\n\t6)Sterge un bilet\n\t7)Sterge baza de date a biletelor\n\n*)Apasa orice altceva pentru a iesi din acest meniu\nAlegere: ";
			int a4 = 0;
			cin >> a4;
			switch (a4) {
			case 1:
				introduBilet();
				break;
			case 2:
				afiseazaBilete();
				break;
			case 3:
				x = nrBilete();
				cout << "Numar bilete: " << x << endl;
				break;
			case 4:
				afiseazaBiletCuId();
				break;
			case 5:
				inlocuieBiletCuId();
				break;
			case 6:
				stergeBilet();
				break;
			case 7:
				stergeBazaDateBilete();
				break;
			default:
				cout << "Alegere invalida." << endl;
				break;
			}
		}
		else if (a == 5) {
		int x = 0; int y = 0;
		cout << "Alege una din urmatoarele operatiuni:\n\t1)Afiseaza incasari\n\t2)Afiseaza numarul de incasari\n\t3)Total incasari\n\t4)Afiseaza o incasare introdusa de la tastatura\n\t5)Sterge o incasare\n\t6)Sterge baza de date a incasarilor\n\n*)Apasa orice altceva pentru a iesi din acest meniu\nAlegere: ";
		int a5 = 0;
		cin >> a5;
			switch (a5) {
		case 1:
			afiseazaIncasari();
			break;
		case 2:
			x = nrIncasari();
			cout << "Numar de inasari: " << x << endl;
			break;
		case 3:
			y = returnTotalIncasari();
			cout << "Total incasari: " << y << endl;
			break;
		case 4:
			afiseazaIncasareCuId();
			break;
		case 5:
			stergeIncasare();
			break;
		case 6:
			stergeBazaDateIncasari();
			break;
		default:
			cout << "Alegere invalida." << endl;
			break;
		}
		}
		clear();
		alegere();
	}
}   