#pragma once
#include "Plansza.h"

#define LICZBA_WSTAWIANYCH 3

class Kontroler {
private:
	Ui ui;
	Plansza* plansza;
	bool programTrwa;
	bool graTrwa;
	bool czyDodawacKulki;
	bool czyPrzerwana;
	int liczbaWstawianych;

	void Petla_gry();
	void Opcje_nowaGra();
	void Opcja_wczytajGre();
	void Opcja_jakGrac();
	void Opcja_wyjdz();
	bool Pobierz_ruch();
	bool CzyJestWyjscie(int i, int j);
	void ZakonczGre();
public:
	Kontroler();
	void Start();
};