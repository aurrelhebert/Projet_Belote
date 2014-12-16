#ifndef PAQUET_H
#define PAQUET_H
#include <string.h>
#include <Windows.h>
#include <iostream>
#include "carte.h"

class Paquet{

public:
	int jeu [32];
	int nbCarte;
	Paquet();
};

#endif