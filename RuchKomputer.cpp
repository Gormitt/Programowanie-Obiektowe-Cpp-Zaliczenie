#include "RuchKomputer.h"

RuchKomputer::RuchKomputer(Plansza* plansza, int ai, int aj) :
	Ruch(plansza, ai, aj, 0, 0) {
}

bool RuchKomputer::Wykonaj() {
	int wolnePola = 0;
	this->Alokuj_maske();
	this->Szukaj_wolnePola(this->ai, this->aj, &wolnePola);
	this->maska[this->ai][this->aj] = 0;

	int licznik = 0;
	int los = rand() % --wolnePola + 1;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (this->maska[i][j] == 2) {
				licznik++;
				if (licznik == los) {
					this->Dealokuj_maske();
					this->plansza->Set_stanPola(i, j, this->plansza->Get_stanPola(this->ai, this->aj));
					this->plansza->Set_stanPola(this->ai, this->aj, 0);

					this->plansza->Dealokuj_listeWolnych();
					this->plansza->Alokuj_listeWolnych();

					this->plansza->Wyswietl_info("komputer dokonal przeniesienia: ");
					std::cout << "(" << (char)('A' + this->ai) << ", " << this->aj + 1 << ") -> ";
					std::cout << "(" << (char)('A' + i) << ", " << j + 1 << ")\n";
					this->plansza->Wyswietl_wcisnijDowolny();

					int skasowane = plansza->Skasuj(i, j);
					this->plansza->Dodaj_punkty(skasowane);
					if (skasowane) return false;
					else return true;
				}
			}
		}
	}

	this->Dealokuj_maske();
	return false;
}

void RuchKomputer::Szukaj_wolnePola(int i, int j, int* licznik) {
	if (i < 0 || i >= this->plansza->Get_wysokosc() ||
		j < 0 || j >= this->plansza->Get_szerokosc()) return;
	else if (this->maska[i][j] != 0) return;
	else {
		(*licznik)++;
		this->maska[i][j] = 2;
		this->Szukaj_wolnePola(i - 1, j, licznik);
		this->Szukaj_wolnePola(i + 1, j, licznik);
		this->Szukaj_wolnePola(i, j - 1, licznik);
		this->Szukaj_wolnePola(i, j + 1, licznik);
	}
}