#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include "Ui.h"

Ui::Ui() :
	// wielkosci poszczegolnych menu
	wielkosc_menu		(4),
	wielkosc_menuZapisy	(5),
	wielkosc_menuWyjscie(2),
	wielkosc_menuCzyZapisac(2),
	// id kolorow
	id_kolorSzary		(8),
	id_kolorNiebieski	(9),
	id_kolorZielony		(10),
	id_kolorBlekitny	(11),
	id_kolorCzerwony	(12),
	id_kolorRozowy		(13),
	id_kolorZolty		(14),
	id_kolorBialy		(15) {
}

// metody PROTECTED

void Ui::Ustaw_kolor(int id) {
	HANDLE konsola = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(konsola, id);
}

void Ui::Wyswietl_prefixError() {
	this->Ustaw_kolor(this->id_kolorCzerwony);
	std::cout << "(!) error";
	this->Ustaw_kolor(this->id_kolorBialy);
}

void Ui::Wyswietl_prefixInfo() {
	this->Ustaw_kolor(this->id_kolorZolty);
	std::cout << "(i) info";
	this->Ustaw_kolor(this->id_kolorBialy);
}

void Ui::Wyswietl_prefixWybierz() {
	this->Ustaw_kolor(this->id_kolorZielony);
	std::cout << "($) wybierz";
	this->Ustaw_kolor(this->id_kolorBialy);
}

void Ui::Wyswietl_prefixHint() {
	this->Ustaw_kolor(this->id_kolorNiebieski);
	std::cout << "(H) hint";
	this->Ustaw_kolor(this->id_kolorBialy);
}

// metody PUBLIC

void Ui::Wyczysc_ekran() {
	system("cls");
}

std::string Ui::Pobierz_nick() {
	this->Wyswietl_prefixWybierz();
	std::string nick;
	std::cout << " podaj nick: ";
	while (true) {
		std::cin >> nick;
		if (!std::cin.good() || getchar() != '\n') {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			this->Wyswietl_error("niepoprawny format, prosze sprobuj ponownie: ");
		}
		else return nick;
	}
}

void Ui::Wyswietl_error(std::string tekst) {
	this->Wyswietl_prefixError();
	std::cout << " - " << tekst;
}

void Ui::Wyswietl_info(std::string tekst) {
	this->Wyswietl_prefixInfo();
	std::cout << " - " << tekst;
}

void Ui::Wyswietl_hint(std::string tekst) {
	this->Wyswietl_prefixHint();
	std::cout << " - " << tekst;
}

// * folder musi zawierac poprawny plik "tytul.txt"
void Ui::Wyswietl_tytul() {
	std::ifstream plik("tytul.txt");
	std::cout << plik.rdbuf();
	plik.close();
}

void Ui::Wyswietl_menu() {
	std::cout << "\t1. Nowa Gra" << std::endl;
	std::cout << "\t2. Wczytaj zapis" << std::endl;
	std::cout << "\t3. Jak grac" << std::endl;
	std::cout << "\t4. Wyjdz" << std::endl << std::endl;
}

void Ui::Wyswietl_menuZapisy() {
	std::cout << "\t>>  Zapisy  <<" << std::endl;
	std::cout << "\t-- zapis  1. --" << std::endl;
	std::cout << "\t-- zapis  2. --" << std::endl;
	std::cout << "\t-- zapis  3. --" << std::endl;
	std::cout << "\t-- zapis  4. --" << std::endl;
	std::cout << "\t <powrot - 5.>" << std::endl << std::endl;
}

// * folder musi zawierac poprawny plik "jak_grac.txt"
void Ui::Wyswietl_jakGrac() {
	std::ifstream plik("jak_grac.txt");
	std::cout << plik.rdbuf();
	plik.close();
}

void Ui::Wyswietl_menuWyjscie() {
	std::cout << ">> Czy na pewno chcesz wyjsc? <<" << std::endl;
	std::cout << "\t-- 1. tak --" << std::endl;
	std::cout << "\t-- 2. nie --" << std::endl;
}

void Ui::Wyswietl_menuCzyZapisac() {
	std::cout << ">> Czy chcesz zapisac gre? <<" << std::endl;
	std::cout << "\t-- 1. tak --" << std::endl;
	std::cout << "\t-- 2. nie --" << std::endl;
}

void Ui::Wyswietl_wcisnijDowolny() {
	this->Wyswietl_info("wcisnij dowolny klawisz aby kontynuowac..");
	char tmp = _getch();
}

// get
int Ui::Get_wielkoscMenu() { return this->wielkosc_menu; }
int Ui::Get_wielkoscMenuZapisy() { return this->wielkosc_menuZapisy; }
int Ui::Get_wielkoscMenuWyjscie() { return this->wielkosc_menuWyjscie; }
int Ui::Get_wielkoscMenuCzyZapisac() { return this->wielkosc_menuCzyZapisac; }