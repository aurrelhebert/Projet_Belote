#pragma once
#include "Hand.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>

class IAvDream
{
public:
	int player;
	Hand h;
	int partner;
	int nbFin;
	int cpt;

	struct state
	{
		int nbPlayerPli; // Number of player that played during the turn (Pli)
		int playerHasHand; //Player having the hand
		int playerWiningPli; //Player wining it
		Carte BestCard; // Best Card played until now
		int colorAsk; // Color that the player have to play
		int atout; // Strongest Color of this game 
		Hand currentHand; //Hand of the actual player
		Hand allHand[4];
		int nbCarte; // Number of card that actual player still have in hand
		int valuePli; // Value of this Pli
		int score;
	};


	int minimax(int firstPlayer, int atout, Hand *);
	int minimax(state c);
	int maxValue(state c);
	int minValue(state c);
	int minimaxAlphaBeta(int firstPlayer, int atout, Hand *);
	int minimax(state c, int alpha, int beta);
	int maxValue(state c, int alpha, int beta);
	Carte nextCarte(Hand *, int atout, vector<Carte> cartesRestantes, int player, int numberCardPlayedInPli, Carte bestCard, int colorAsk, int valuePli);
	int minValue(state c, int alpha, int beta);
	state majState(state c, int i);
	IAvDream(void);
	~IAvDream(void);
};

