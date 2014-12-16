#pragma once
#include "paquet.h"

class Hand
{
public:
	Carte listHand[8];
	int nbCarte;
	Hand();
	Hand(Carte*, int);
	~Hand(void);
};

