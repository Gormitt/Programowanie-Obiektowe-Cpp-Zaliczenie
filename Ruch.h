#pragma once
#include "Plansza.h"

class Ruch {
protected:
	Plansza* plansza;
	int ai, aj; // skad chce sie ruszyc
	int bi, bj; // gdzie chce isc
	bool czyJestDojscie;

	bool Jest_Dojscie(int** maska, int ai, int aj, int bi, int bj);
public:
	Ruch() = delete;
	Ruch(Plansza* plansza, int ai, int aj, int bi, int bj);
	virtual bool Wykonaj() = 0;
};