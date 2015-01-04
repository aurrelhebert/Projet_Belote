#pragma once
#include "Hand.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

class IA
{
public:
	Hand currentHand;
	Paquet jeuActuel;
	vector<Carte> cartesRestantes;
	int nbCarte;
	Carte nextCard;
	vector<Carte> order;
	Hand allHands[4];
	IA();
	IA(Hand,Paquet,int);
	~IA(void);

	struct statePli
	{
		int nbPlayerPli; // Number of player that played during the turn (Pli)
		int playerHasHand; //Player having the hand
		int playerWiningPli; //Player wining it
		Carte BestCard; // Best Card played until now
		int colorAsk; // Color that the player have to play
		int atout; // Strongest Color of this game 
		Hand currentHand; //Hand of the actual player
		int nbCarte; // Number of card that actual player still have in hand
		int valuePli; // Value of this Pli
		int list[8];
		int score;
	};
	statePli cur;

	struct stateCur
	{
		int score;
	};
	
	int minimax(int firstPlayer);
	int minimax(int firstPlayer, int atout, int score, int nbC);
	int maxValuePli(statePli c);
	int minValuePli(statePli c);
	int maxValue(statePli c);
	int minValue(statePli c);

private:
	statePli majState(statePli c, int index);
	vector<Carte> carteAjouer(statePli c);
	statePli majStateCarte(statePli c, Carte carte, int i);
};

