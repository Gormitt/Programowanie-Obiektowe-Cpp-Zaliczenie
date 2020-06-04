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

// glowna funkcja w calym  programie, zawiera petle, ktora obsluguje menu glowne
void Kontroler::Start() {
	while (this->programTrwa) {
		this->ui.Wyczysc_ekran();
		this->ui.Wyswietl_tytul();
		this->ui.Wyswietl_menu();

		// pobranie od uzytkownika opcji
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

// metoda petla gry obsluguje tylko to co dzieje sie na ekranie podczas rozgrywki
void Kontroler::Petla_gry() {
	// rozpoczynamy od wyczyszczenia ekranu
	this->ui.Wyczysc_ekran(); 
	// nastepnie wyswietlamy plansze
	this->plansza->Wyswietl(); 
	// pobieramy ruch
	bool czyKontynuowac = this->Pobierz_ruch(); 
	// w przypadku checi przerwania, ustawiamy zmienne sterujace
	if (czyKontynuowac == false) { 
		// ta zmienna sterujaca sprawi ze nie bedzie kolejnego obrotu petli z gra
		this->graTrwa = false; 
		// ta zmienna sterujaca sprawi ze kontroler wie ze ten koniec gry jest spowodowany przerwaniem, a nie zapelnieniem planszy
		this->czyPrzerwana = true; 
	}
	// w przypadku kontynuacji sprawdzamy czy powinnismy dodac kulki, jak tak to dodajemy
	else if (this->czyDodawacKulki) this->graTrwa = this->plansza->Dodaj_losoweKulki(this->liczbaWstawianych); 
}

void Kontroler::Opcje_nowaGra() {
	// rozpoczynamy od wyczyszczenia ekrany
	this->ui.Wyczysc_ekran();
	// pobieramy od uzytkownika jego nick i alokujemy plansze
	this->plansza = new Plansza(this->ui.Pobierz_nick(), 0);
	// jezeli poprawnie zaalokowano plansze to ustawiamy sterowanie na rozpoczecie gry i dodajemy pierwsze kulki
	if (this->plansza->Get_czyDobrzeAlokowana()) {
		this->graTrwa = true;
		plansza->Dodaj_losoweKulki(liczbaWstawianych);
	}
	// w przeciwnym przypadku informujemy o bledzie alokacji
	else {
		this->graTrwa = false;
		ui.Wyswietl_error("blad podczas alokacji pamieci na plansze\n");
		ui.Wyswietl_wcisnijDowolny();
	}
}

void Kontroler::Opcja_wczytajGre() {
	// rozpoczynamy od wyczyszczenia ekranu
	this->ui.Wyczysc_ekran();
	// wyswietlenie menu zapisow do wyboru
	this->ui.Wyswietl_menuZapisy();
	// pobranie numeru zapisu
	int wybor = this->ui.Pobierz_wybor<int>(1, this->ui.Get_wielkoscMenuZapisy());

	// jezeli uzytkownik wybral opcje wroc to nie wczytujemy gry
	if (wybor == 5) {
		this->graTrwa = false;
		return;
	}
	// jezeli uzytkownik podal zapis to tworzymy jego pelna nazwe i wczytujemy plansze z pliku
	else this->plansza = new Plansza("zapis_" + std::to_string(wybor) + ".txt");

	// jezeli komputer poprawnie zaalokuje pamiec i wczyta plansze z pliku to ustawiamy sterowanie na rozpoczecie gry
	if (this->plansza->Get_czyDobrzeAlokowana() && this->plansza->Get_czyDobrzeWczytana()) this->graTrwa = true;
	// w przeciwnym przypadku informujemy o bledzie i nie rozpoczynamy gry
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

// zwraca true jezeli wola uzytkownika jest dalsza gra
// zwraca false jezeli wola uzytkownika jest zakoczenie gry
bool Kontroler::Pobierz_ruch() {
	int ai, aj, bi, bj;

	// poinformowanie uzytkownika o mozliwosci wyjscia
	this->ui.Wyswietl_info("aby przerwac napisz ");
	std::cout << (char)('A' + this->plansza->Get_wysokosc()) << std::endl;
	// petla dziala tak dlugo az uzytkownik poda poprawne wspolrzedne kulki do przeniesienia lub zechce skonczyc
	while (true) {
		this->ui.Wyswietl_info("podaj symbol rzedu i nr. kolumny kulki do przeniesienia\n");
		ai = this->ui.Pobierz_wybor<char>('A', 'A' + this->plansza->Get_wysokosc()) - 'A';
		// w przypadku checi zakonczenia programu
		if (ai == this->plansza->Get_wysokosc()) return false;

		aj = this->ui.Pobierz_wybor<int>(1, this->plansza->Get_szerokosc()) - 1;

		// jezeli pole jest puste to powtarzamy wczytanie
		if (this->plansza->Get_stanPola(ai, aj) == 0) {
			this->ui.Wyswietl_error("wybrane pole jest puste\n");
			continue;
		}
		// jezeli z danego pola nie mozna wyjsc to powtarzamy ruch
		if (!this->CzyJestWyjscie(ai, aj)) {
			this->ui.Wyswietl_error("z tego pola nie da sie wyjsc\n");
			continue;
		}
		break;
	}

	// poinformowanie o mozliwosci dopelnienian ruchu przez komputer
	this->ui.Wyswietl_info("aby komputer uzupelnij ten ruch napisz ");
	std::cout << (char)('A' + this->plansza->Get_wysokosc()) << std::endl;
	// petla dziala tak dlugo az uzytkownik poprawnie poda pole na kotre przemieszczamy kulke, albo zdecyduje aby komputer dokonczyl za niego ruch
	while (true) {
		this->ui.Wyswietl_info("podaj symbol rzedu i nr. kolumny docelowego pola\n");
		bi = this->ui.Pobierz_wybor<char>('A', 'A' + this->plansza->Get_wysokosc()) - 'A';
		// w przypadku checi dopelnienia ruchu
		if (bi == this->plansza->Get_wysokosc()) {
			// tworzymy instancje klasy RuchKomputer dzieki czemu wskaznik typu Ruch staje sie polimorficzny
			Ruch* ruch = new RuchKomputer(this->plansza, ai, aj);
			// wykonujemy ruch i od razu badamy czy nastapilo skasowanie 
			// jezeli nastapilo to wpisujemy do zmiennej falsz, dzieki czemu w nastepnej turze nie bedzie dodawania
			this->czyDodawacKulki = ruch->Wykonaj();
			delete ruch;
			return true;
		}

		bj = this->ui.Pobierz_wybor<int>(1, this->plansza->Get_szerokosc()) - 1;
		
		// jezeli miejsce docelowe jest zajete to ponawiamy wczytywanie
		if (this->plansza->Get_stanPola(bi, bj) != 0) {
			this->ui.Wyswietl_error("wybrane pole jest zajete\n");
			continue;
		}
		break;
	}

	// po zakonczeniu wczytywania tworzymy instancje klasy RuchGracz dzieki czemu wskaznik typu Ruch staje sie polimorficzny
	Ruch* ruch = new RuchGracz(this->plansza, ai, aj, bi, bj);
	// wykonujemy ruch i od razu badamy czy nastapilo skasowanie 
	// jezeli nastapilo to wpisujemy do zmiennej falsz, dzieki czemu w nastepnej turze nie bedzie dodawania
	// jezeli ruch sie nie uda (z komputerem tego problemu nie ma bo komputer zawsze poprawnie wykona ruch) to do zmiennej tez idzie falsz, tak aby nie dodawac kulek po nieudanym ruchu
	// jezeli skasowanie nie nastapilo to do zmiennej trafia prawda, dzieki czemu w nastepnej turze nastapi dolosowanie
	this->czyDodawacKulki = ruch->Wykonaj();
	delete ruch;

	// po wykonanym ruchu zwracamy prawde, tzn. uzytkownik nie ma woli zakonczenia gry
	return true;
}

// funkcja zwraca prawde jezeli z danego pola jest wyjscie
// funkcja zwraca falsz jezeli z danego pola nie ma wyjscia
bool Kontroler::CzyJestWyjscie(int i, int j) {
	if (i - 1 >= 0 && this->plansza->Get_stanPola(i - 1, j) == 0) return true;
	if (i + 1 < this->plansza->Get_wysokosc() && this->plansza->Get_stanPola(i + 1, j) == 0) return true;
	if (j - 1 >= 0 && this->plansza->Get_stanPola(i, j - 1) == 0) return true;
	if (j + 1 < this->plansza->Get_szerokosc() && this->plansza->Get_stanPola(i, j + 1) == 0) return true;
	return false;
}

void Kontroler::ZakonczGre() {
	// jezeli gra sie nie rozpoczela to plansza nie zostala alokowana, stad wniosek ze jezeli w this->plansza jest wartosc NULL to gra nie istnieje i nie ma czego konczyc
	if (this->plansza != NULL) {
		// wyswietlenie podsumowania gry
		this->ui.Wyczysc_ekran();
		std::cout << ">>  Koniec gry  <<" << std::endl << std::endl;
		std::cout << "\tnick: \t" << this->plansza->Get_nick() << std::endl;
		std::cout << "\tpunkty:\t" << this->plansza->Get_punkty() << std::endl << std::endl;

		// jezeli gra zostala przerwana z woli uzytkownika to znaczy ze mozna ja bylo kontynuowac i jest sens jej zapisania
		if (this->czyPrzerwana) {
			// wyswietlenie zapytania czy zapisac
			this->ui.Wyswietl_menuCzyZapisac();
			int wybor = this->ui.Pobierz_wybor<int>(1, this->ui.Get_wielkoscMenuCzyZapisac());
			// tak
			if (wybor == 1) {
				// wyswietlenie menu zapisow i pobranie numeru
				this->ui.Wyczysc_ekran();
				this->ui.Wyswietl_menuZapisy();
				wybor = this->ui.Pobierz_wybor<int>(1, this->ui.Get_wielkoscMenuZapisy());
				// jezeli uzytkownik sie jednak rozmysli to nie zapisujemy
				if (wybor == 5) this->ui.Wyswietl_info("nie zapisano gry\n");
				// w przeciwnym razie zapisujemy plansze do pliku i jak sie to uda to informujemy uzytkownika
				else if (this->plansza->Zapisz("zapis_" + std::to_string(wybor) + ".txt")) this->ui.Wyswietl_info("poprawnie zapisano gre\n");
				// w przypadku blednego zapisu tez informuje o tym uzytkownika odpowiednim bledem
				else this->ui.Wyswietl_error("blad podczas zapisywania gry\n");
			}
			// nie
			else {
				this->ui.Wyswietl_info("nie zapisano gry\n");
			}
		}
		// aby komunikaty nie zniknely to dodajemy mechanizm - wcisnij dowolny aby kontynuowac
		this->ui.Wyswietl_wcisnijDowolny();
		// dealokujemy plansze
		delete this->plansza;
	}
}