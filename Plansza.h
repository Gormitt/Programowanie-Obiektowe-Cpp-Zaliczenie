#pragma once
#include "Ui.h"
#include "Pole.h"

#define WYSOKOSC 9
#define SZEROKOSC 9
#define SKASOWANIE 5

struct wolnePola {
	Pole* pole;
	wolnePola* nast;
};

class Plansza : public Ui {
protected:
	// do planszy
	Pole** siatka;
	int wysokosc;
	int szerokosc;
	int skasowanie;
	int liczbaWolnych;
	// walidacja bledow
	bool czyWczytana;
	bool czyDobrzeAlokowana;
	bool czyDobrzeWczytana;
	// do gry 
	std::string nick;
	int punkty;
	// lista dynamiczna wolnych pol
	wolnePola* listaWolnychGlowa;
	wolnePola* listaWolnychOgon;
public:
	Plansza() = delete;
	Plansza(std::string zapis);
	Plansza(std::string imie, int punkty);
	~Plansza();
	
	bool Alokuj();
	void Alokuj_listeWolnych();
	void Dealokuj_listeWolnych();
	bool Dodaj_losoweKulki(int liczba);
	void Wyswietl();
	void Dodaj_punkty(int punkty);
	int Skasuj(int i, int j);
	bool Zapisz(std::string zapis);
	
	// set
	void Set_stanPola(int i, int j, int stan);
	void Set_czyWczytana(bool stan);
	
	// get
	int Get_wysokosc();
	int Get_szerokosc();
	int Get_stanPola(int i, int j);
	int Get_punkty();
	std::string Get_nick();
	bool Get_czyWczytana();
	bool Get_czyDobrzeAlokowana();
	bool Get_czyDobrzeWczytana();
};