#ifndef CARTE_H
#define CARTE_H
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

/**
* @class Carte
* @brief Card of a game
* Class existing to build and use concept of Cards
* @author ahebert
* @author edauchard
**/
class Carte{
	int value; /**< Value (As, King, 8 ...) of a card */
	int color; /**< Color of card (Pique, coeur ...) */
	int point; /**< Number of point a card give in a Belote game */
	bool isAtout; /**< Is this card an atout for this game */
	int ordre; /**< Order of the card (Exemple As > 10 > 9 and 9atout > AS > 10) */

public : 
	enum color_type {COEUR, PIQUE, CARREAU, TREFLE};
	enum value_type {SEPT, HUIT, NEUF, VALET, DAME, ROI, DIX, AS};
	/**
	Simple empty constructeur
	@return new Empty card all parameters initialised at -1
	@warning use carefully
	*/
	Carte();
	/**
	Simple constructeur association a number to a value and a color
 
	@param[in]     v Value of that card
	@param[in]     c Color of that card
	@return a new card.
	*/
	Carte(int, int);
	/**
	Getter for the value of a card
	@return the value of that card
	*/
	int getValue() const;
	/**
	Getter for the color of a card
	@return the color of that card
	*/
	int getColor() const;
	/**
	Getter for the point of a card
	@return the point of that card
	*/
	int getPoint() const;
	/**
	Getter for the order of a card (this parameter help to classify card)
	For example in atout the order isn't equals to the value of the class
	@return the order of that card
	*/
	int getOrdre() const;

	/**
	Test to define if one card is > to an other one
	@param[in] c the second card
	@return true iif this card > the card given as parameter
	*/
	bool isSuperieur(Carte c);
	/**
	Used to set a Card as an Atout
	Will change the boolean of the card and the order
	@return the same card with attibutes order and isAtout modified
	*/
	void setAtout();

	/**
	Common opertor to print the card on screen
	@param[in] str the output
	@param[in] c the card we want to show
	@return the stream modified
	*/
	friend ostream & operator<<(ostream & str, Carte const & c);
	/**
	Common opertor to test the equality of 2 cards
	@param[in] lhs left card to test
	@param[in] rhs right card to test
	@return true iif lhs == rhs
	*/
	friend bool operator==(const Carte& lhs, const Carte& rhs);
	/**
	Common opertor to test < between 2 cards
	@param[in] lhs left card to test
	@param[in] rhs right card to test
	@return true iif lhs < rhs
	*/
	friend bool operator<(const Carte& lhs, const Carte& rhs);
};

#endif