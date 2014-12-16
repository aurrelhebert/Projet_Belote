#include "IA.h"

IA::IA()
{
}

IA::IA(Hand h, Paquet p)
{
	srand(time(NULL));

	nbCarte = h.nbCarte;
	currentHand = h;
	jeuActuel = p;

	int pos = 0;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<8; j++)
		{
			if(p.jeu[pos])
			{
				Carte c = Carte(j,i);
				cartesRestantes.push_back(c);
			}
			pos++;
		}
	}


	allHands[0] = currentHand;
	for(int i = 1; i < 4; i++)
	{
		Carte newHand[8];
		for(int j = 0; j < nbCarte; j++)
		{
			int posCarte = rand() %cartesRestantes.size();
			Carte tmp = cartesRestantes[posCarte];
			newHand[j] = tmp;
			cartesRestantes.erase(cartesRestantes.begin() + posCarte);
		}
		allHands[i] = Hand(newHand,nbCarte);
	}
}


IA::~IA(void)
{
}


Carte IA::minimax()
{
	Carte c;
	return c;
}