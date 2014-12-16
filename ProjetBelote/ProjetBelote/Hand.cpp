#include "Hand.h"

Hand::Hand()
{
}

Hand::Hand(Carte* c, int nb)
{
	nbCarte = nb;
	for (int i=0; i<nbCarte; i++)
	{
		listHand[i]=c[i];
	}
}


Hand::~Hand(void)
{
}
