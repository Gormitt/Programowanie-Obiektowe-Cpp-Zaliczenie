#pragma once
#include "Ui.h"

class Pole : public Ui {
private:
	int i;
	int j;
	int stan;
public:
	Pole();

	void Wyswietl();
	
	// set
	void Set_i(int i);
	void Set_j(int j);
	void Set_stan(int stan);

	// get
	int Get_i();
	int Get_j();
	int Get_stan();
};