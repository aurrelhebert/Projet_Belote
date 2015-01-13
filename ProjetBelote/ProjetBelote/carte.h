#ifndef CARTE_H
#define CARTE_H
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

class Carte{
	int value;
	int color;
	int point;
	bool isAtout;
	int ordre;

public : 
	enum color_type {COEUR, PIQUE, CARREAU, TREFLE};
	enum value_type {SEPT, HUIT, NEUF, VALET, DAME, ROI, DIX, AS};
	Carte();
	Carte(int, int);
	int getValue() const;
	int getColor() const;
	int getPoint() const;
	int getOrdre() const;

	bool isSuperieur(Carte c);

	void setAtout();
	friend ostream & operator<<(ostream & str, Carte const & c);
	friend bool operator==(const Carte& lhs, const Carte& rhs);
};

#endif