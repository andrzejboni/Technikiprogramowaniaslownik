
#include <stdafx.h>
#include <fstream> slowa;
#include <iostream>
#include <string>
#include <conio.h>
#include <sdkddkver.h>

using namespace std;

struct SSlowo
{
	string polski;
	string angielski;
	string czesc_mowy;
	bool wypisanie;
};

struct SSlownik
{
	unsigned rozmiar;
	SSlowo *slowko;
};

void wczytaj_plik(ifstream &wczytaj, SSlownik &slownik)
{
	wczytaj >> slownik.rozmiar;

	slownik.slowko = new SSlowo[slownik.rozmiar];
	for (unsigned i = 0; i < slownik.rozmiar; i++)
	{
		wczytaj >> slownik.slowko[i].polski;
		wczytaj >> slownik.slowko[i].angielski;
		wczytaj >> slownik.slowko[i].czesc_mowy;
		slownik.slowko[i].wypisanie = 0;
	}
}

void wyszukaj_slowka(SSlownik &slownik, string wyraz_szukany)
{
	bool znaleziono = 0;

	for (unsigned i = 0; i<slownik.rozmiar; i++)
	{
		if (slownik.slowko[i].polski == wyraz_szukany)
		{
			cout << "Tlumaczenie:   " << slownik.slowko[i].angielski << endl;
			znaleziono = 1;
		}
		else if (slownik.slowko[i].angielski == wyraz_szukany)
		{
			cout << "Tlumaczenie:   " << slownik.slowko[i].polski << endl;
			znaleziono = 1;
		}
	}

	if (znaleziono == 0)
	{
		cout << "Nie znaleziono tlumaczenia" << endl;
	}
}

void wypisz_strukture(const SSlownik slownik, string twoja_czesc_mowy)
{
	cout << "Ilosc wszstkich slow w slowniku:  " << slownik.rozmiar << endl << endl;

	if (twoja_czesc_mowy == "0")
	{
		for (unsigned i = 0; i<slownik.rozmiar; i++)
		{
			cout << slownik.slowko[i].polski << " " << slownik.slowko[i].angielski << endl;;
		}
	}
	else
	{
		for (unsigned i = 0; i < slownik.rozmiar; i++)
		{
			if (slownik.slowko[i].czesc_mowy == twoja_czesc_mowy)
			{
				cout << slownik.slowko[i].polski << " " << slownik.slowko[i].angielski << endl;
			}
		}
	}
	cout << endl;
}

void wypisanie_html_calosc(ofstream &wyjscie, SSlownik slownik, string twoja_czesc_mowy)
{
	wyjscie << "<!DOCTYPE HTML>";
	wyjscie << "<html lang=" << "pl" << ">";
	wyjscie << "<head>";
	wyjscie << "<meta charset=" << "utf-8" << "/>";
	wyjscie << "<title>Slownik angielsko-polski i polsko-angielski</title>";
	wyjscie << "<meta name=" << "description" << "content=" << "Jeden z najlepszych slownikow na internecie!" << "/>";
	wyjscie << "<meta name=" << "keywords" << "content=" << "slownik,slowa" << "/>";
	wyjscie << "<meta http-equiv=" << "X-UA-Compatible" << "content=" << "IE=edge,chrome=1" << ">";
	wyjscie << "</head>";
	wyjscie << "<body><center>";
	wyjscie << "<h1><b>-----Slownik-----</b></h1>";
	wyjscie << "<b>Sprawdz rowniez: </b><a href=" << "http:/" << "/translate.google.pl/?hl=pl/" << ">Translate Google</a></br>";

	wyjscie << "<b>Spis wyrazow: </b></br>";


	if (twoja_czesc_mowy == "0")
	{
		for (unsigned i = 0; i<slownik.rozmiar; i++)
		{
			wyjscie << slownik.slowko[i].polski << " " << slownik.slowko[i].angielski << endl;
		}
	}
	else
	{
		for (unsigned i = 0; i < slownik.rozmiar; i++)
		{
			if (slownik.slowko[i].czesc_mowy == twoja_czesc_mowy)
			{
				wyjscie << slownik.slowko[i].polski << " " << slownik.slowko[i].angielski << endl;
			}
		}
	}

	wyjscie << "</center></body>";
	wyjscie << "</html>";
}


SSlownik wczytaj_slowko(SSlownik &slownik)
{
	SSlownik nowy_slownik;

	nowy_slownik.rozmiar = slownik.rozmiar + 1;

	nowy_slownik.slowko = new SSlowo[nowy_slownik.rozmiar];

	for (unsigned i = 0; i < slownik.rozmiar; i++)
	{
		nowy_slownik.slowko[i] = slownik.slowko[i];
	}

	cout << "Podaj polski: ";
	cin >> nowy_slownik.slowko[nowy_slownik.rozmiar - 1].polski;

	cout << "Podaj angielski: ";
	cin >> nowy_slownik.slowko[nowy_slownik.rozmiar - 1].angielski;

	cout << "Podaj czesc mowy: ";
	cin >> nowy_slownik.slowko[nowy_slownik.rozmiar - 1].czesc_mowy;

	ofstream plik("slowa.txt");

	if (plik.good() == false)
	{
		cout << "Plik nie istnieje!";
		// exit(0);
	}

	plik << nowy_slownik.rozmiar << endl;

	for (unsigned i = 0; i < nowy_slownik.rozmiar; i++)
	{
		plik << nowy_slownik.slowko[i].polski << " " << nowy_slownik.slowko[i].angielski << " " << nowy_slownik.slowko[i].czesc_mowy << endl;
	}

	plik.close();

	




	return nowy_slownik;
}


int main()
{
	SSlownik slowniczek;

	ifstream od("slowa.txt");

	if (od.good() == false)
	{
		cout << "Plik nie istnieje!";
		//exit(0);
	}

	wczytaj_plik(od, slowniczek);
	od.close();

	string szukany;
	char wybor;
	bool koniec = 0;

	while (koniec == 0)
	{
		cout << "1. Slownik" << endl;
		cout << "2. Dodaj do slownika" << endl;
		cout << "3. Pokaz slownik" << endl;
		cout << "4. Wygenerowanie strony" << endl;
		cout << "5. Exit" << endl;

		cin >> wybor;
		switch (wybor)
		{
		case '1':
		{
			cout << "Szukany wyraz: ";
			cin >> szukany;

			wyszukaj_slowka(slowniczek, szukany);

			break;
		}
		case '2':
		{
			slowniczek = wczytaj_slowko(slowniczek);
		}
		case '3':
		{
			cout << endl;
			cout << "-----SLOWNIK-----" << endl;
			cout << endl;

			char wybor1;

			cout << "w - caly slownik" << endl << "r - rzeczowniki" << endl << "c - czasowniki" << endl << "p - przymiotniki" << endl;
			cin >> wybor1;
			switch (wybor1)
			{
			case 'c':
			{
				wypisz_strukture(slowniczek, "czasownik");
				break;
			}
			case 'a':
			{
				wypisz_strukture(slowniczek, "0");
				break;
			}
			case 'r':
			{
				wypisz_strukture(slowniczek, "rzeczownik");
				break;
			}
			case 'p':
			{
				wypisz_strukture(slowniczek, "przymiotnik");
				break;
			}
			}

			cout << endl;
			break;
		}

		case '4':
		{
			char wyborek;

			ofstream html("strona.html");

			if (html.good() == false)
			{
				cout << "Plik nie istnieje!";
				exit(0);
			}
			cout << "w - caly slownik" << endl << "r - rzeczowniki" << endl << "c - czasowniki" << endl << "p - przymiotniki" << endl;
			cin >> wyborek;
			switch (wyborek)
			{
			case 'c':
			{
				wypisanie_html_calosc(html, slowniczek, "czasownik");
				break;
			}
			case 'w':
			{
				wypisanie_html_calosc(html, slowniczek, "0");
				break;
			}
			case 'r':
			{
				wypisanie_html_calosc(html, slowniczek, "rzeczownik");
				break;
			}
			case 'p':
			{
				wypisanie_html_calosc(html, slowniczek, "przymiotnik");
				break;
			}
			}
			html.close();
			cout << endl;
			break;
		}

		case '5':
		{
			koniec = 1;
			break;
		}


		default: cout << "Wcisnieto niewlasciwy klawisz" << endl;
		}
	}


	delete[] slowniczek.slowko;

	system("PAUSE");
	return 0;
}