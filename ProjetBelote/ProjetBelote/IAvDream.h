#pragma once
#include "Hand.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>

/**
* @class IAvDream
* @brief the rule the game will follow
* AI of the game and the special strategy the computer will used to play.
* @author ahebert
* @author edauchard
**/
class IAvDream
{
public:
	int player; /**< the id of the main player in this round. It will be the player we want to maximise his score*/
	Hand h; /**< the hand of the main player*/
	int partner; /**< the partner of the main player*/
	int nbFin; /**< a counter to know how many operation where done*/
	int cpt; /**< a counter to know how many operation where done*/
	int cardsStillInGame[32];
	int nbCardDeleted;
	int nbTour;

	struct state //< the state that we will transmit and used inside the algo
	{
		int nbPlayerPli; //< Number of player that played during the turn (Pli)
		int playerHasHand; //<Player having the hand
		int playerWiningPli; //<Player wining it
		Carte BestCard; //< Best Card played until now
		int colorAsk; //< Color that the player have to play
		int atout; //< Strongest Color of this game 
		Hand currentHand; //<Hand of the actual player
		Hand allHand[4]; //< an array where all the hand of the actual state are
		int nbCarte; //< Number of card that actual player still have in hand
		int valuePli; //< Value of this Pli
		int score; //< the score of the game at this state
	};

	/**
	Function used to launch and test the minimax algorithm. Here an initial state will be created.
	@param[in] firstPlayer the number of the first player wich will play in the first turn
	@param[in] atout the color choosen as "Atout"
	@param[in] Hand* an array with 4 hand is needed
	@return the score of the algorithm
	*/
	int minimax(int firstPlayer, int atout, Hand *);
	int minimax(state c);
	int maxValue(state c);
	int minValue(state c);
	int minimaxAlphaBeta(int firstPlayer, int atout, Hand *);
	int minimax(state c, int alpha, int beta);
	int maxValue(state c, int alpha, int beta);
	Carte nextCarte(Hand, int atout, int player, int numberCardPlayedInPli, Carte bestCard, int colorAsk, int valuePli);
	int minValue(state c, int alpha, int beta);
	state majState(state c, int i);

	void deleteCard(Carte c);

	void distributionCards(Hand h, Hand[4], int atout);
	void printGame(Hand htab[4]);

	void delListCard(Carte c[], int lg);
	bool isCarteValide(Hand h, Carte c, int colorAsk, int atout, Carte bestCard);

	IAvDream(int nb);
	~IAvDream(void);
};

