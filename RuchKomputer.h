#pragma once
#include "Ruch.h"

class RuchKomputer : public Ruch {
public:
	RuchKomputer(Plansza* plansza, int ai, int aj);
	virtual bool Wykonaj();
	void Szukaj_wolnePola(int i, int j, int* licznik);
};

