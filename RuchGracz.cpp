#include "RuchGracz.h"

RuchGracz::RuchGracz(Plansza* plansza, int ai, int aj, int bi, int bj) :
	Ruch(plansza, ai, aj, bi, bj) {
}

bool RuchGracz::Wykonaj() {
	if (this->czyJestDojscie) {
		this->plansza->Set_stanPola(bi, bj, this->plansza->Get_stanPola(ai, aj));
		this->plansza->Set_stanPola(ai, aj, 0);

		this->plansza->Dealokuj_listeWolnych();
		this->plansza->Alokuj_listeWolnych();

		int skasowane = plansza->Skasuj(bi, bj);
		this->plansza->Dodaj_punkty(skasowane);
		if (skasowane) return false;
		else return true;
	}
	else {
		this->plansza->Wyswietl_error("przesuniecie niemozliwe z powodu braku dojscia\n");
		this->plansza->Wyswietl_wcisnijDowolny();
		return false;
	}
}