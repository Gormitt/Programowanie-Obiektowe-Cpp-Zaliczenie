#include "Ruch.h"

Ruch::Ruch(Plansza* plansza, int ai, int aj, int bi, int bj) :
	// inicjalizacja parametrow ruchu
	plansza(plansza),
	ai(ai),
	aj(aj),
	bi(bi),
	bj(bj),
	maska(NULL) {

	// alokacja maski planszy
	// maska to kopia planszy, ktora nie rozroznia koloru kulek (1 to kulka 0 to wolne pole)
	this->Alokuj_maske();
	// wywolanie rekurencyjnego algorytmu, ktory sprawdza czy pomiedzy punktem startowym a punktem docelowym jest przejscie
	this->czyJestDojscie = this->Jest_Dojscie(ai, aj, bi, bj);
	// dealokacja maski
	this->Dealokuj_maske();
}

bool Ruch::Jest_Dojscie(int ai, int aj, int bi, int bj) {
	// WARUNKI ZAWIJANIA REKURENCJI
	// wyjscie poza plansze
	if (ai < 0 || ai >= this->plansza->Get_wysokosc() || aj < 0 || aj >= this->plansza->Get_szerokosc()) return false;
	// natrafienie na docelowe pole zwraca prawde
	else if (ai == bi && aj == bj) return true;
	// natrafienie na pole zajete lub odwiedzone zwraca falsz
	else if (this->maska[ai][aj] == 1) return false;
	else {
		// natrafienie na wolne pole oznacza je w masce jako odwiedzone
		this->maska[ai][aj] = 1;
		// to skomplikowane i bardzo rozbudowane wyrazenie logiczne spowoduje, ze jezeli chociazby jedna rekurencja zwroci prawde
		// to cale to wyrazenie bedzie prawda, jezeli natomiast kazda rekurencja zwroci falsz, tzn. ze nie ma dojscia pomiedzy punktami
		// i calosc to bedzie false
		// wyrazenie logiczne to wywolanie rekurencji dla kazdego sasiada pola w ktorym obecnie znajduje sie stereowanie ta metoda
		return this->Jest_Dojscie(ai, aj - 1, bi, bj) ||
			this->Jest_Dojscie(ai, aj + 1, bi, bj) ||
			this->Jest_Dojscie(ai - 1, aj, bi, bj) ||
			this->Jest_Dojscie(ai + 1, aj, bi, bj);
	}
}

// alokacja kopii planszy ktora nie rozrownia kolorw
// 0 - pole jest wolne
// 1 - pole jest zajete
void Ruch::Alokuj_maske() {
	int wysokosc = this->plansza->Get_wysokosc();
	int szerokosc = this->plansza->Get_szerokosc();
	this->maska = new int* [wysokosc];
	if (this->maska != NULL) {
		for (int k = 0; k < wysokosc; k++) {
			this->maska[k] = new int[szerokosc];
			if (this->maska[k] != NULL) {
				for (int l = 0; l < szerokosc; l++) {
					this->maska[k][l] = (this->plansza->Get_stanPola(k, l) == 0) ? 0 : 1;
				}
			}
		}
	}
	this->maska[this->ai][this->aj] = 0;
}

void Ruch::Dealokuj_maske() {
	for (int k = 0; k < this->plansza->Get_wysokosc(); k++) {
		delete this->maska[k];
	}
	delete[] this->maska;
}