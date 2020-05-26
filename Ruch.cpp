#include "Ruch.h"

Ruch::Ruch(Plansza* plansza, int ai, int aj, int bi, int bj) :
	plansza(plansza),
	ai(ai),
	aj(aj),
	bi(bi),
	bj(bj) {

	int wysokosc = plansza->Get_wysokosc();
	int szerokosc = plansza->Get_szerokosc();
	int** maska = new int* [wysokosc];
	if (maska != NULL) {
		for (int k = 0; k < wysokosc; k++) {
			maska[k] = new int[szerokosc];
			if (maska[k] != NULL) {
				for (int l = 0; l < szerokosc; l++) {
					maska[k][l] = (this->plansza->Get_stanPola(k, l) == 0) ? 0 : 1;
				}
			}
		}
	}
	maska[ai][aj] = 0;

	this->czyJestDojscie = this->Jest_Dojscie(maska, ai, aj, bi, bj);

	for (int k = 0; k < wysokosc; k++) {
		delete maska[k];
	}
	delete[] maska;
}

bool Ruch::Jest_Dojscie(int** maska, int ai, int aj, int bi, int bj) {
	if (ai < 0 || ai >= plansza->Get_wysokosc() || aj < 0 || aj >= plansza->Get_szerokosc()) return false;
	else if (ai == bi && aj == bj) return true;
	else if (maska[ai][aj] == 1) return false;
	else {
		maska[ai][aj] = 1;
		return this->Jest_Dojscie(maska, ai, aj - 1, bi, bj) ||
			this->Jest_Dojscie(maska, ai, aj + 1, bi, bj) ||
			this->Jest_Dojscie(maska, ai - 1, aj, bi, bj) ||
			this->Jest_Dojscie(maska, ai + 1, aj, bi, bj);
	}
}