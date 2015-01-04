#ifndef CARTE_H
#define CARTE_H
#include <string.h>
#include <Windows.h>
#include <iostream>

using namespace std;

class Carte{
	int value;
	int color;
	int point;
	bool isAtout;

public : 
	enum color_type {COEUR, PIQUE, CARREAU, TREFLE};
	enum value_type {SEPT, HUIT, NEUF, VALET, DAME, ROI, DIX, AS};
	Carte();
	Carte(int, int);
	int getValue() const;
	int getColor() const;
	int getPoint() const;

	void setAtout();
	friend ostream & operator<<(ostream & str, Carte const & c);
	friend bool operator==(const Carte& lhs, const Carte& rhs);
};

#endif