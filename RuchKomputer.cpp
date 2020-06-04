#include "RuchKomputer.h"

RuchKomputer::RuchKomputer(Plansza* plansza, int ai, int aj) :
	// podczas inicjalizacji RuchuGracza trzeba zainicjalizowaæ wartosci klasy narzednej
	Ruch(plansza, ai, aj, 0, 0) {
}

bool RuchKomputer::Wykonaj() {
	// utworzenie licznika wolnych pol
	int wolnePola = 0;
	// wpisanie to pole this->maska maski dla obecnego stanu planszy
	this->Alokuj_maske();
	// rekurencyjny algorytm, ktory na masce naniesie wszystko wolneg pola DO KTORYCH ISTNIEJE DOJSCIE z pola this->ai this->aj
	this->Szukaj_wolnePola(this->ai, this->aj, &wolnePola);
	// naznaczenie na masce miejsca startowego jako 0 (niemozemy uwzglednic tego samego miejsca jako mozliwosci ruchu)
	this->maska[this->ai][this->aj] = 0;

	// licznik podczas przechodzenia przez maske, policzy kazde pole do ktrego jest dojscie
	int licznik = 0;
	// majac liczbe pol do ktorych jest dojscie generujemy to jedno do ktorego komputer dokona przestawienia
	int los = rand() % --wolnePola + 1;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			// jezeli natrafimy w masce na '2' (wolne pole, do ktorego jest dojscie od punktu startowego)
			if (this->maska[i][j] == 2) {
				// zliczamy pole
				licznik++;
				// jezeli to pole nosi taki numer, jak wylosowany numer to dokonujemy przestawienia
				if (licznik == los) {
					// dealokujemy maske bo nie jest nam potrzebna
					this->Dealokuj_maske();
					// ustawiamy stan pola docelowego na stan pola this->ai this->aj i wstawiamy zero do pola startowego
					this->plansza->Set_stanPola(i, j, this->plansza->Get_stanPola(this->ai, this->aj));
					this->plansza->Set_stanPola(this->ai, this->aj, 0);

					// dealokujemy liste wolnych pol i alokujemy ja na nowo
					this->plansza->Dealokuj_listeWolnych();
					this->plansza->Alokuj_listeWolnych();

					// informujemy o wylosowanym przeniesieniu
					this->plansza->Wyswietl_info("komputer dokonal przeniesienia: ");
					std::cout << "(" << (char)('A' + this->ai) << ", " << this->aj + 1 << ") -> ";
					std::cout << "(" << (char)('A' + i) << ", " << j + 1 << ")\n";
					this->plansza->Wyswietl_wcisnijDowolny();

					// sprawdzamy czy nastapilo skasowanie
					int skasowane = plansza->Skasuj(i, j);
					// dodajemy ew. punkty jezeli skasowanie nastapilo
					this->plansza->Dodaj_punkty(skasowane);
					// w przypadku udanego skasowania zwracamy falsz aby nie generowac w nst. ruchu kulek
					if (skasowane) return false;
					// w przypadku braku skasowania dodajey kolejne kulki
					else return true;
				}
			}
		}
	}

	// na wypadek gdyby cos poszlo nie tak, to ostatecznie dealokujemy maske i zwracamy falsz
	this->Dealokuj_maske();
	return false;
}

// rekurencyjny algorytm do poszukiwania wolnych pol, do ktorych jest dojscie z punktu o wspolrzednych i, j
void RuchKomputer::Szukaj_wolnePola(int i, int j, int* licznik) {
	// WARUNKI ZAWIJANIA REKURENCJI
	// natrafienie na pole poza plansza
	if (i < 0 || i >= this->plansza->Get_wysokosc() ||
		j < 0 || j >= this->plansza->Get_szerokosc()) return;
	// natrafienie na pole ktore: jest kulka/zostalo juz wczesniej odwiedzone
	else if (this->maska[i][j] != 0) return;
	// jezli trafiamy na wolne pole
	else {
		// dodajeme licznik wolnych pol
		(*licznik)++;
		// oznaczamy je na masce jako odwiedzone
		this->maska[i][j] = 2;
		// wywolujemy rekurencje dla kazdego sasiada danego pola
		this->Szukaj_wolnePola(i - 1, j, licznik);
		this->Szukaj_wolnePola(i + 1, j, licznik);
		this->Szukaj_wolnePola(i, j - 1, licznik);
		this->Szukaj_wolnePola(i, j + 1, licznik);
	}
}