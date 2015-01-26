#ifndef PAQUET_H
#define PAQUET_H
#include <string.h>
#include <Windows.h>
#include <iostream>
#include "carte.h"

/**
* @class Paquet
* @brief DO NOT USE
* Class resuming the 32 card of a game, not used in our current IA.
* @author ahebert
* @author edauchard
**/
class Paquet{

public:
	int jeu [32];
	int nbCarte;
	Paquet();
};

#endif