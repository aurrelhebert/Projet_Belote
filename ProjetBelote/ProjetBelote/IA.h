#pragma once
#include "Hand.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

class IA
{
public:
	Hand currentHand;
	Paquet jeuActuel;
	vector<Carte> cartesRestantes;
	int nbCarte;
	Hand allHands[4];

	IA();
	IA(Hand,Paquet);
	~IA(void);

	Carte minimax();
};

