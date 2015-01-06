#pragma once
#include "paquet.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>

class Hand
{
public:
	Carte listHand[8];
	int nbCarte;
	int posPique;
	int posCoeur;
	int posCarreau;
	int posTrefle;
	int nbPique;
	int nbCoeur;
	int nbCarreau;
	int nbTrefle;


	Hand();
	Hand(Carte*, int);
	void deleteCarte(int index);
	void deleteCarte(Carte c);
	~Hand(void);

	int posColor(int color);
	bool hasColor(int c);
	int Hand::nbColor(int c);
	void triAtout(int color);

private:
	void triABulle(Carte tableau[], int longueur);

};

