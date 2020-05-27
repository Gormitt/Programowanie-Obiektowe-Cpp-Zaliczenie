#include <iostream>
#include <string>
#include "Kontroler.h"
#include "RuchGracz.h"
#include "RuchKomputer.h"

Kontroler::Kontroler() :
	ui(Ui()),
	plansza(NULL),
	programTrwa(true),
	graTrwa(false),
	czyDodawacKulki(true),
	czyPrzerwana(false),
	liczbaWstawianych(LICZBA_WSTAWIANYCH) {
}

void Kontroler::Start() {
	while (this->programTrwa) {
		this->ui.Wyczysc_ekran();
		this->ui.Wyswietl_tytul();
		this->ui.Wyswietl_menu();

		int wybor = this->ui.Pobierz_wybor<int>(1, this->ui.Get_wielkoscMenu());
		// uzytkownik wybiera opcje "nowa gra"
		if (wybor == 1) {
			this->Opcje_nowaGra();
			while (this->graTrwa) this->Petla_gry();
			this->ZakonczGre();
		}
		// uzytkownik wybiera opcje "wczytaj gre"
		else if (wybor == 2) {
			this->Opcja_wczytajGre();
			while (this->graTrwa) this->Petla_gry();
			this->ZakonczGre();
		}
		// uzytkownik wybiera opcje "jak grac?"
		else if (wybor == 3) this->Opcja_jakGrac();
		// uzytkownik wybiera opcje "wyjdz"
		else if (wybor == 4) this->Opcja_wyjdz();
	}
}

void Kontroler::Petla_gry() {
	this->ui.Wyczysc_ekran();
	this->plansza->Wyswietl();
	bool czyKontynuowac = this->Pobierz_ruch();
	if (czyKontynuowac == false) {
		this->graTrwa = false;
		this->czyPrzerwana = true;
	}
	else if (this->czyDodawacKulki) this->graTrwa = this->plansza->Dodaj_losoweKulki(this->liczbaWstawianych);
}

void Kontroler::Opcje_nowaGra() {
	this->ui.Wyczysc_ekran();
	this->plansza = new Plansza(this->ui.Pobierz_nick(), 0);
	if (this->plansza->Get_czyDobrzeAlokowana()) this->graTrwa = true;
	else {
		this->graTrwa = false;
		ui.Wyswietl_error("blad podczas alokacji pamieci na plansze\n");
		ui.Wyswietl_wcisnijDowolny();
	}
	plansza->Dodaj_losoweKulki(liczbaWstawianych);
}

void Kontroler::Opcja_wczytajGre() {
	this->ui.Wyczysc_ekran();
	this->ui.Wyswietl_menuZapisy();
	int wybor = this->ui.Pobierz_wybor<int>(1, this->ui.Get_wielkoscMenuZapisy());

	if (wybor == 5) return;
	else this->plansza = new Plansza("zapis_" + std::to_string(wybor) + ".txt");
	if (this->plansza->Get_czyDobrzeAlokowana() && this->plansza->Get_czyDobrzeWczytana()) this->graTrwa = true;
	else {
		this->graTrwa = false;
		if (!this->plansza->Get_czyDobrzeAlokowana()) this->ui.Wyswietl_error("blad podczas alokacji pamieci na plansze\n");
		if (!this->plansza->Get_czyDobrzeWczytana()) this->ui.Wyswietl_error("blad podczas otwarcia zapisu [nie istnieje/jest pusty]\n");
		this->ui.Wyswietl_wcisnijDowolny();
	}
}

void Kontroler::Opcja_jakGrac() {
	this->ui.Wyczysc_ekran();
	this->ui.Wyswietl_jakGrac();
	this->ui.Wyswietl_wcisnijDowolny();
}

void Kontroler::Opcja_wyjdz() {
	this->ui.Wyczysc_ekran();
	this->ui.Wyswietl_menuWyjscie();
	int wybor = this->ui.Pobierz_wybor<int>(1, this->ui.Get_wielkoscMenuWyjscie());
	if (wybor == 1) this->programTrwa = false;
}

bool Kontroler::Pobierz_ruch() {
	int ai, aj, bi, bj;

	this->ui.Wyswietl_info("aby przerwac napisz ");
	std::cout << (char)('A' + this->plansza->Get_wysokosc()) << std::endl;
	while (true) {
		this->ui.Wyswietl_info("podaj symbol rzedu i nr. kolumny kulki do przeniesienia\n");
		ai = this->ui.Pobierz_wybor<char>('A', 'A' + this->plansza->Get_wysokosc()) - 'A';
		if (ai == this->plansza->Get_wysokosc()) return false;

		aj = this->ui.Pobierz_wybor<int>(1, this->plansza->Get_szerokosc()) - 1;

		if (this->plansza->Get_stanPola(ai, aj) == 0) {
			this->ui.Wyswietl_error("wybrane pole jest puste\n");
			continue;
		}
		if (!this->CzyJestWyjscie(ai, aj)) {
			this->ui.Wyswietl_error("z tego pola nie da sie wyjsc\n");
			continue;
		}
		break;
	}

	this->ui.Wyswietl_info("aby komputer uzupelnij ten ruch napisz ");
	std::cout << (char)('A' + this->plansza->Get_wysokosc()) << std::endl;
	while (true) {
		this->ui.Wyswietl_info("podaj symbol rzedu i nr. kolumny docelowego pola\n");
		bi = this->ui.Pobierz_wybor<char>('A', 'A' + this->plansza->Get_wysokosc()) - 'A';
		if (bi == this->plansza->Get_wysokosc()) {
			Ruch* ruch = new RuchKomputer(this->plansza, ai, aj);
			this->czyDodawacKulki = ruch->Wykonaj();
			delete ruch;
			return true;
		}

		bj = this->ui.Pobierz_wybor<int>(1, this->plansza->Get_szerokosc()) - 1;

		if (this->plansza->Get_stanPola(bi, bj) != 0) {
			this->ui.Wyswietl_error("wybrane pole jest zajete\n");
			continue;
		}
		break;
	}

	Ruch* ruch = new RuchGracz(this->plansza, ai, aj, bi, bj);
	this->czyDodawacKulki = ruch->Wykonaj();
	delete ruch;

	return true;
}

bool Kontroler::CzyJestWyjscie(int i, int j) {
	if (i - 1 >= 0 && this->plansza->Get_stanPola(i - 1, j) == 0) return true;
	if (i + 1 < this->plansza->Get_wysokosc() && this->plansza->Get_stanPola(i + 1, j) == 0) return true;
	if (j - 1 >= 0 && this->plansza->Get_stanPola(i, j - 1) == 0) return true;
	if (j + 1 < this->plansza->Get_szerokosc() && this->plansza->Get_stanPola(i, j + 1) == 0) return true;
	return false;
}

void Kontroler::ZakonczGre() {
	this->ui.Wyczysc_ekran();
	std::cout << ">>  Koniec gry  <<" << std::endl << std::endl;
	std::cout << "\tnick: \t" << this->plansza->Get_nick() << std::endl;
	std::cout << "\tpunkty:\t" << this->plansza->Get_punkty() << std::endl << std::endl;

	if (this->czyPrzerwana) {
		this->ui.Wyswietl_menuCzyZapisac();
		int wybor = this->ui.Pobierz_wybor<int>(1, this->ui.Get_wielkoscMenuCzyZapisac());
		if (wybor == 1) {
			this->ui.Wyczysc_ekran();
			this->ui.Wyswietl_menuZapisy();
			wybor = this->ui.Pobierz_wybor<int>(1, this->ui.Get_wielkoscMenuZapisy());
			if (wybor == 5) this->ui.Wyswietl_info("nie zapisano gry\n");
			else if (this->plansza->Zapisz("zapis_" + std::to_string(wybor) + ".txt")) this->ui.Wyswietl_info("poprawnie zapisano gre\n");
			else this->ui.Wyswietl_error("blad podczas zapisywania gry\n");
		}
		else {
			this->ui.Wyswietl_info("nie zapisano gry\n");
		}
	}
	this->ui.Wyswietl_wcisnijDowolny();
	delete this->plansza;
}