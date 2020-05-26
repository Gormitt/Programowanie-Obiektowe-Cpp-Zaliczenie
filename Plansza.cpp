#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Plansza.h"


Plansza::Plansza(std::string zapis) :
	siatka(NULL),
	wysokosc(WYSOKOSC),
	szerokosc(SZEROKOSC),
	skasowanie(SKASOWANIE),
	liczbaWolnych(0),
	listaWolnychGlowa(NULL),
	listaWolnychOgon(NULL) {
	this->czyWczytana = true;
	this->czyDobrzeAlokowana = this->Alokuj();

	if (this->czyDobrzeAlokowana) {
		std::ifstream plik(zapis);
		if (plik.good() && plik.is_open() && plik.peek() != std::ifstream::traits_type::eof()) {
			this->czyDobrzeWczytana = true;
			plik >> this->nick;
			plik >> this->punkty;

			for (int i = 0; i < WYSOKOSC; i++) {
				for (int j = 0; j < SZEROKOSC; j++) {
					int cyfra;
					plik >> cyfra;
					this->Set_stanPola(i, j, cyfra);
				}
			}
			plik.close();
		}
		else this->czyDobrzeWczytana = false;
	}

	this->Alokuj_listeWolnych();
}

Plansza::Plansza(std::string nick, int punkty) :
	siatka(NULL),
	wysokosc(WYSOKOSC),
	szerokosc(SZEROKOSC),
	skasowanie(SKASOWANIE),
	liczbaWolnych(0),
	nick(nick),
	punkty(punkty) {
	this->czyWczytana = false;
	this->czyDobrzeWczytana = true;
	this->czyDobrzeAlokowana = this->Alokuj();
	this->Alokuj_listeWolnych();
}

Plansza::~Plansza() {
	this->Dealokuj_listeWolnych();
	for (int i = 0; i < WYSOKOSC; i++) {
		delete this->siatka[i];
	}
	delete this->siatka;
}

bool Plansza::Alokuj() {
	this->siatka = new Pole * [WYSOKOSC];
	if (this->siatka != NULL) {
		for (int i = 0; i < WYSOKOSC; i++) {
			this->siatka[i] = new Pole[SZEROKOSC];
			if (this->siatka[i] != NULL) {
				for (int j = 0; j < SZEROKOSC; j++) {
					this->siatka[i][j].Set_i(i);
					this->siatka[i][j].Set_j(j);
					this->siatka[i][j].Set_stan(0);
				}
			}
			else return false;
		}
	}
	else return false;
	return true;
}

void Plansza::Alokuj_listeWolnych() {
	this->liczbaWolnych = this->wysokosc * this->szerokosc;
	for (int i = 0; i < WYSOKOSC; i++) {
		for (int j = 0; j < SZEROKOSC; j++) {
			if (this->siatka[i][j].Get_stan() == 0) {
				if (this->listaWolnychGlowa == NULL) {
					this->listaWolnychGlowa = new wolnePola{ &this->siatka[i][j], NULL };
					this->listaWolnychOgon = this->listaWolnychGlowa;
				}
				else {
					this->listaWolnychOgon->nast = new wolnePola{ &this->siatka[i][j], NULL };
					this->listaWolnychOgon = this->listaWolnychOgon->nast;
				}
			}
			else this->liczbaWolnych--;
		}
	}
}

void Plansza::Dealokuj_listeWolnych() {
	while (this->listaWolnychGlowa) {
		wolnePola* tmp = this->listaWolnychGlowa->nast;
		delete this->listaWolnychGlowa;
		this->listaWolnychGlowa = tmp;
		this->liczbaWolnych--;
	}
	this->listaWolnychGlowa = NULL;
	this->listaWolnychOgon = NULL;
}

bool Plansza::Dodaj_losoweKulki(int liczba) {
	liczba = (liczba > this->liczbaWolnych) ? this->liczbaWolnych : liczba;
	for (int i = 0; i < liczba; i++) {
		int wylosowane = rand() % this->liczbaWolnych + 1;
		int wartosc = rand() % 7 + 1;

		wolnePola* tmp = this->listaWolnychGlowa;
		for (int i = 0; i < wylosowane - 1; i++) {
			tmp = tmp->nast;
		}

		tmp->pole->Set_stan(wartosc);
		this->Skasuj(tmp->pole->Get_i(), tmp->pole->Get_j());

		this->Dealokuj_listeWolnych();
		this->Alokuj_listeWolnych();
	}
	if (this->liczbaWolnych == 0) return false;
	else return true;
}

void Plansza::Wyswietl() {
	std::cout << "    ";
	for (int i = 0; i < SZEROKOSC; i++) std::cout << i + 1 << " ";
	this->Ustaw_kolor(id_kolorBlekitny);
	std::cout << "\t\tnick: ";
	this->Ustaw_kolor(id_kolorBialy);
	std::cout << this->nick;
	std::cout << "\twolne pola: " << this->liczbaWolnych << std::endl;

	std::cout << "  ";
	for (int i = 0; i < SZEROKOSC + 2; i++) std::cout << "+ ";
	this->Ustaw_kolor(id_kolorRozowy);
	std::cout << "\tpunkty: ";
	this->Ustaw_kolor(id_kolorBialy);
	std::cout << this->punkty << std::endl;

	for (int i = 0; i < WYSOKOSC; i++) {
		std::cout << (char)('A' + i) << " + ";
		for (int j = 0; j < SZEROKOSC; j++) {
			this->siatka[i][j].Wyswietl();
		}
		std::cout << "+ " << std::endl;
	}

	std::cout << "  ";
	for (int i = 0; i < SZEROKOSC + 2; i++) std::cout << "+ ";
	std::cout << std::endl;
}

void Plansza::Dodaj_punkty(int punkty) {
	this->punkty += punkty;
}

int Plansza::Skasuj(int i, int j) {
	int tmp = this->siatka[i][j].Get_stan();
	int startPozioma = 0, dlPozioma = 0, maxPozioma = 0;
	int startPionowa = 0, dlPionowa = 0, maxPionowa = 0;
	for (int k = 0; k < this->szerokosc; k++) {
		if (this->siatka[i][k].Get_stan() == tmp) {
			dlPozioma++;
			if (dlPozioma > maxPozioma) {
				maxPozioma = dlPozioma;
				startPozioma = k - dlPozioma + 1;
			}
		}
		else dlPozioma = 0;

		if (this->siatka[k][j].Get_stan() == tmp) {
			dlPionowa++;
			if (dlPionowa > maxPionowa) {
				maxPionowa = dlPionowa;
				startPionowa = k - dlPionowa + 1;
			}
		}
		else dlPionowa = 0;
	}
	
	int punkty = 0;
	if (maxPozioma >= SKASOWANIE) {
		for (int k = 0; k < maxPozioma; k++) this->siatka[i][startPozioma + k].Set_stan(0);
		punkty += maxPozioma;
	}
	if (maxPionowa >= SKASOWANIE) {
		for (int k = 0; k < maxPionowa; k++) this->siatka[startPionowa + k][j].Set_stan(0);
		punkty += maxPionowa;
	}

	if (maxPozioma >= SKASOWANIE || maxPionowa >= SKASOWANIE) {
		this->Dealokuj_listeWolnych();
		this->Alokuj_listeWolnych();
	}

	return punkty;
}

bool Plansza::Zapisz(std::string zapis) {
	std::ofstream plik(zapis);
	if (plik.good() && plik.is_open()) {
		plik << this->nick << " " << this->punkty << std::endl;
		for (int i = 0; i < this->wysokosc; i++) {
			for (int j = 0; j < this->szerokosc; j++) {
				plik << this->siatka[i][j].Get_stan() << " ";
			}
			plik << std::endl;
		}
		plik.close();
		return true;
	}
	else return false;
}

// set
void Plansza::Set_stanPola(int i, int j, int stan) { this->siatka[i][j].Set_stan(stan); }
void Plansza::Set_czyWczytana(bool stan) { this->czyWczytana = stan; }

// get
int Plansza::Get_wysokosc() { return this->wysokosc; }
int Plansza::Get_szerokosc() { return this->szerokosc; }
int Plansza::Get_stanPola(int i, int j) { return this->siatka[i][j].Get_stan(); }
int Plansza::Get_punkty() { return this->punkty; }
std::string Plansza::Get_nick() { return this->nick; }
bool Plansza::Get_czyWczytana() { return this->czyWczytana; }
bool Plansza::Get_czyDobrzeAlokowana() { return this->czyDobrzeAlokowana; }
bool Plansza::Get_czyDobrzeWczytana() { return this->czyDobrzeWczytana; }