#pragma once
#include "Hand.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
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
	int cardsStillInGame[32]; /**< an array to resume wich card are still in game : 1 mean yes, 0 no*/
	int nbCardDeleted; /**< an integer to count how many card have been deleted*/
	int nbTour; /**< a counter to know until when the IA will established all possibility : this mean the number of turn IA play all the card of a player*/

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
	/**
	Intermediary function called inside the minimax algorithm
	@param[in] c the actual state of the game
	@return the score of the algorithm
	*/
	int minimax(state c);
	/**
	Intermediary function called inside the minimax algorithm
	@param[in] c the actual state of the game
	@return the score of the algorithm
	*/
	int maxValue(state c);
	/**
	Intermediary function called inside the minimax algorithm
	@param[in] c the actual state of the game
	@return the score of the algorithm
	*/
	int minValue(state c);

	/**
	Function used to launch and test the minimax algorithm. Here an initial state will be created. 
	This algotithm with used a prunning of the tree of possibilities using alpha and beta.
	@param[in] firstPlayer the number of the first player wich will play in the first turn
	@param[in] atout the color choosen as "Atout"
	@param[in] Hand* an array with 4 hand is needed
	@return the score of the algorithm
	*/
	int minimaxAlphaBeta(int firstPlayer, int atout, Hand *);
	/**
	Intermediary function called inside the minimax algorithm
	@param[in] c the actual state of the game
	@param[in] alpha integer with the min value saved
	@param[in] beta integer with the max value saved
	@return the score of the algorithm
	*/
	int minimax(state c, int alpha, int beta);
	/**
	Intermediary function called inside the minimax algorithm
	@param[in] c the actual state of the game
	@param[in] alpha integer with the min value saved
	@param[in] beta integer with the max value saved
	@return the score of the algorithm
	*/
	int maxValue(state c, int alpha, int beta);
	/**
	Intermediary function called inside the minimax algorithm
	@param[in] c the actual state of the game
	@param[in] alpha integer with the min value saved
	@param[in] beta integer with the max value saved
	@return the score of the algorithm
	*/
	int minValue(state c, int alpha, int beta);
	
	/**
	Intermediary function called inside the minimax algorithm used to create a new state
	@param[in] c the actual state of the game
	@param[in] i position inside the hand of the card we want to play
	@return a new state once we have play this card (from the index i)
	*/
	state majState(state c, int i);

	/**
	Intermediary function called inside the minimax algorithm, used to delete a card
	@param[in] c a card to delete
	*/
	void deleteCard(Carte c);

	/**
	This function given the Hand of a player will decide wich Card to play using minimax alpha beta algorithm
	@param[in] h the Hand of the actual player
	@param[in] atout the atout of this game
	@param[in] player the player that is the IA
	@param[in] numberCardPlayedInPli the number of card played during this turn
	@param[in] bestCard the Best Card played during this turn
	@param[in] colorAsk the color that player have to play during this turn
	@param[in] valuePli the value in a matter of points of this turn 
	@param[in] playerWining the player wining this turn
	@return the Best card to play in this situation
	*/
	Carte nextCarte(Hand, int atout, int player, int numberCardPlayedInPli, Carte bestCard, int colorAsk, int valuePli, int playerWining);
	/**
	This function given the Hand of all players will decide wich Card to play using minimax alpha beta algorithm
	@param[in] h the hands of all the players
	@param[in] atout the atout of this game
	@param[in] player the player that is the IA
	@param[in] numberCardPlayedInPli the number of card played during this turn
	@param[in] bestCard the Best Card played during this turn
	@param[in] colorAsk the color that player have to play during this turn
	@param[in] valuePli the value in a matter of points of this turn 
	@param[in] playerWining the player wining this turn
	@return the Best card to play in this situation
	*/
	Carte nextCarte(Hand*, int atout, int player, int numberCardPlayedInPli, Carte bestCard, int colorAsk, int valuePli, int playerWining);

	/**
	Intermediary function called inside next card algorithm used to create a new distribution of cards
	@param[in] h the hand of the player
	@param[in] htab new array of hand with the card of the other player assigned randomly
	@param[in] atout the atout of this game
	*/
	void distributionCards(Hand h, Hand[4], int atout);

	/**
	Function used to print on screen the game we have
	@param[in] htab an array contening the hands of all the players
	*/
	void printGame(Hand htab[4]);

	/**
	Intermediary function called to delete some cards from an array
	@param[in] c an array of card
	@param[in] lg the length to delete some cards
	*/
	void delListCard(Carte c[], int lg);

	/**
	Function used to inform us if a possible card is valid
	@param[in] h the hand of the player
	@param[in] c card we want to test
	@param[in] colorAsk color that the player have to play this turn
	@param[in] atout the atout of this game
	@param[in] bestCard best card played during this turn
	@param[in] winner the player actually wining the turn
	@param[in] actualPlayer who is actually playing
	@return true iif we can play this card
	*/
	bool isCarteValide(Hand h, Carte c, int colorAsk, int atout, Carte bestCard, int winner, int actualPartner);

	/**
	Function rending a valid card to play inside a hand
	@param[in] h the hand of the player
	@param[in] colorAsk color that the player have to play this turn
	@param[in] atout the atout of this game
	@param[in] bestCard best card played during this turn
	@param[in] winner the player actually wining the turn
	@param[in] actualPlayer who is actually playing
	@return a card that we are it respect the rules of a belote game
	*/
	Carte carteAuto(Hand h,int colorAsk,int atout, Carte bestCard,int winner,int actualPlayer);

	/**
	Function call wich will lead to let the IA decide which color took as atout
	@param[in] h the hand of the player (IA)
	@param[in] firstPlayer which player will start to play in the game
	@param[in] playerIA which player is actually the IA
	@return the color of atout taken or -1 if none of them is took
	*/
	int prendre(Hand h,int firstPlayer, int playerIA);
	/**
	Intermediary function called inside prendre algorithm
	@param[in] h the hand of the player (IA)
	@param[in] atout the atout of the future game
	@param[in] firstPlayer which player will start to play in the game
	@param[in] playerIA which player is actually the IA
	@return score of the minimax (alpha beta) algorithm
	*/
	int prendreScore(Hand h, int atout, int firstPlayer, int playerIA);
	/**
	Intermediary function called inside prendre algorithm used to create a new distribution of cards
	@param[in] h the hand of the player
	@param[in] htab new array of hand with the card of the other player assigned randomly
	@param[in] atout the atout of this game
	*/
	void distributionPrise(Hand h, Hand* htab,int atout);
	
	/**
	Simple empty constructeur
	@return new IAvDream
	@warning do not used
	*/
	IAvDream();

	/**
	Simple constructeur of an IAvDream, all parameters will be assigned
 
	@param[in]     nb number of Turn that all the possibilities will have to be evaluated indide the minimax algorithm
	@return a correct Hand
	*/
	IAvDream(int nb);
	~IAvDream(void);
};

