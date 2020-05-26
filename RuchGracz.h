#pragma once
#include "Ruch.h"

class RuchGracz : public Ruch {
public:
	RuchGracz(Plansza* plamsza, int ai, int aj, int bi, int bj);
	virtual bool Wykonaj();
};