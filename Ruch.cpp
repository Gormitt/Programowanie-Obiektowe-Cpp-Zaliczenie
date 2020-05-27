#include "Ruch.h"

Ruch::Ruch(Plansza* plansza, int ai, int aj, int bi, int bj) :
	plansza(plansza),
	ai(ai),
	aj(aj),
	bi(bi),
	bj(bj),
	maska(NULL) {

	this->Alokuj_maske();
	this->czyJestDojscie = this->Jest_Dojscie(ai, aj, bi, bj);
	this->Dealokuj_maske();
}

bool Ruch::Jest_Dojscie(int ai, int aj, int bi, int bj) {
	if (ai < 0 || ai >= this->plansza->Get_wysokosc() || aj < 0 || aj >= this->plansza->Get_szerokosc()) return false;
	else if (ai == bi && aj == bj) return true;
	else if (this->maska[ai][aj] == 1) return false;
	else {
		this->maska[ai][aj] = 1;
		return this->Jest_Dojscie(ai, aj - 1, bi, bj) ||
			this->Jest_Dojscie(ai, aj + 1, bi, bj) ||
			this->Jest_Dojscie(ai - 1, aj, bi, bj) ||
			this->Jest_Dojscie(ai + 1, aj, bi, bj);
	}
}

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