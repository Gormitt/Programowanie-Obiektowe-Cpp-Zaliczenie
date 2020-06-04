#include "RuchGracz.h"

RuchGracz::RuchGracz(Plansza* plansza, int ai, int aj, int bi, int bj) :
	// inicjalizujemy pola nadrzedne
	Ruch(plansza, ai, aj, bi, bj) {
}

bool RuchGracz::Wykonaj() {
	// jezeli istnieje dojscie do pozadanego przez gracza pola
	if (this->czyJestDojscie) {
		// dokonujemy przestawienia
		this->plansza->Set_stanPola(bi, bj, this->plansza->Get_stanPola(ai, aj));
		this->plansza->Set_stanPola(ai, aj, 0);

		// uaktualniamy dynamiczna liste wolnych pol
		this->plansza->Dealokuj_listeWolnych();
		this->plansza->Alokuj_listeWolnych();

		// spradzamy czy nastapilo skasowanie
		int skasowane = plansza->Skasuj(bi, bj);
		// dodjemy potencjale punkty
		this->plansza->Dodaj_punkty(skasowane);
		// w przypadku skasowania czegokolwiek nie dodajemy kolejnych kulek
		if (skasowane) return false;
		// w przypadku braku skasowania dodajemy kolejne kulki
		else return true;
	}
	// jezeli nie to informujemy o bledzie i zwracamy falsz, aby nie dolosowywac kolejnych kulek
	else {
		this->plansza->Wyswietl_error("przesuniecie niemozliwe z powodu braku dojscia\n");
		this->plansza->Wyswietl_wcisnijDowolny();
		return false;
	}
}