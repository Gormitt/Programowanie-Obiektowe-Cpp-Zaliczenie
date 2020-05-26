#include <iostream>
#include "Pole.h"

Pole::Pole() :
	i(0),
	j(0),
	stan(0) {
}

void Pole::Wyswietl() {
	this->Ustaw_kolor(this->stan + this->id_kolorSzary - 1);
	if (this->stan != 0) std::cout << (char)(254) << " ";
	else std::cout << "  ";
	this->Ustaw_kolor(this->id_kolorBialy);
}

// set
void Pole::Set_i(int i) { this->i = i; }
void Pole::Set_j(int j) { this->j = j; }
void Pole::Set_stan(int stan) { this->stan = stan; }

// get
int Pole::Get_i() { return this->i; }
int Pole::Get_j() { return this->j; }
int Pole::Get_stan() { return this->stan; }