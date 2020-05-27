#include "RuchKomputer.h"

RuchKomputer::RuchKomputer(Plansza* plansza, int ai, int aj) :
	Ruch(plansza, ai, aj, 0, 0) {
}

bool RuchKomputer::Wykonaj() {
	
	return true;
}

// dodac klase lista dynamiczna
// klasa jest templatem, ktory w zaleznosci od zaklerowanego typu przechowuje takie elementu
// klasa zawiera pola: glowa, ogon
// klasa zawiera metody: dodaj element, dealokuj liste