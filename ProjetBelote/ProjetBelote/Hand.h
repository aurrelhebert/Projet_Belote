#pragma once
#include "paquet.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>

/**
* @class Hand
* @brief hand of a user
* Class used to assure wich are card a user Control
* @author ahebert
* @author edauchard
**/
class Hand
{
public:
	Carte listHand[8]; /**< Array of all the card possessed in 1 hand */
	int nbCarte; /**< number of card possessed */
	int posPique; /**< where is the first "Pique" */
	int posCoeur; /**< where is the first "Coeur" */
	int posCarreau; /**< where is the first "Carreau" */
	int posTrefle; /**< where is the first "Trefle" */
	int nbPique; /**< number of card of type "Pique" */
	int nbCoeur; /**< number of card of type "Coeur" */
	int nbCarreau; /**< number of card of type "Carreau" */
	int nbTrefle; /**< number of card of type "Trefle" */

	/**
	Simple empty constructeur.
	@return new Hand.
	@warning do not used
	*/
	Hand();
	/**
	Simple constructeur, the array will be classified by the color.
 
	@param[in]     c Array of card.
	@param[in]     nb number of card in the hand.
	@return a correct Hand.
	*/
	Hand(Carte*, int);

	/**
	Function used to destroy a card, using the index (the position of the card) given in param. Rebuilt the hand without this card.
 
	@param[in]     index position of the card we want to delete.
	*/
	void deleteCarte(int index);

	/**
	Delete the card given in parameter from the hand.
 
	@param[in]     c the card we want to delete.
	*/
	void deleteCarte(Carte c);
	~Hand(void);

	/**
	Getter to the position of a color
	@param[in] color is the number of the color we want to access
	@return the position in the array of the first card of this color
	*/
	int posColor(int color);

	/**
	Test a hand to know if it possessed a given color.
	@param[in] c the color we want to know if it belong to the hand.
	@return boolean yes if this hand has the color
	*/
	bool hasColor(int c);

	/**
	Test a hand to know if it possessed a better asset than the best one in game.
	@param[in] ordre the order of the best asset in game.
	@return boolean yes if this hand has a bette asset
	*/
	bool hasAtoutSup(int ordre, int atout);

	/**
	Getter used to get the number of card of a given color in the hand
	@param[in] c the color we want to access.
	@return number of card from this color in the hand
	*/
	int Hand::nbColor(int c);

	/**
	Function used to sort the card that are "Atout"

	@param[in] color give the color "Atout"
	*/
	void triAtout(int color);


	void setAtout(int atout);

private:
	/**
	Function used to sort the array of the hand

	@param[in] tableau[] the array to sort
	@param[in] longueur the length of the array
	*/
	void triABulle(Carte tableau[], int longueur);

};

