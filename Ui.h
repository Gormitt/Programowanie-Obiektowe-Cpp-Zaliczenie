#pragma once
#include <iostream>

class Ui {
protected:
	// wielkosci poszczegolnych menu
	int wielkosc_menu;
	int wielkosc_menuZapisy;
	int wielkosc_menuWyjscie;
	int wielkosc_menuCzyZapisac;

	// id kolorow
	int id_kolorSzary;
	int id_kolorNiebieski;
	int id_kolorZielony;
	int id_kolorBlekitny;
	int id_kolorCzerwony;
	int id_kolorRozowy;
	int id_kolorZolty;
	int id_kolorBialy;

	// ust. kolor + wyswietlanie prefixow do wizualizowania przekazu
	void Ustaw_kolor(int id);
	void Wyswietl_prefixError();
	void Wyswietl_prefixInfo();
	void Wyswietl_prefixWybierz();
	void Wyswietl_prefixHint();
public:
	Ui();

	void Wyczysc_ekran();
	std::string Pobierz_nick();

	// wyswietl <bledy>
	void Wyswietl_error(std::string tekst);
	void Wyswietl_info(std::string tekst);
	void Wyswietl_hint(std::string tekst);
	// wyswietl <menu>
	void Wyswietl_menu();
	void Wyswietl_menuZapisy();
	void Wyswietl_jakGrac();
	void Wyswietl_menuWyjscie();
	void Wyswietl_menuCzyZapisac();
	// wyswietl
	void Wyswietl_tytul();
	void Wyswietl_wcisnijDowolny();

	// get
	int Get_wielkoscMenu();
	int Get_wielkoscMenuZapisy();
	int Get_wielkoscMenuWyjscie();
	int Get_wielkoscMenuCzyZapisac();
	
	// szablony
	template <class T>
	T Pobierz_wybor(T min, T max) {
		T wpis;
		bool pierwsza = true;
		do {
			if (pierwsza) {
				pierwsza = false;
				this->Wyswietl_prefixWybierz();
				std::cout << " podaj wybor " << "<" << min << ", " << max << "> : ";
			}
			else {
				this->Wyswietl_error("nie ma takiej opcji, prosze sprobuj ponownie: ");
			}
			while (true) {
				std::cin >> wpis;
				if (!std::cin.good() || getchar() != '\n') {
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
					this->Wyswietl_error("niepoprawny format, prosze sprobuj ponownie: ");
				}
				else break;
			}
		} while (wpis < min || wpis > max);
		return wpis;
	}
};