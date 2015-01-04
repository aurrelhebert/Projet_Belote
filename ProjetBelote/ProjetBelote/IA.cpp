#include "IA.h"

IA::IA()
{
}

IA::IA(Hand h, Paquet p, int atout)
{
	srand(time(NULL));

	nbCarte = h.nbCarte;
	currentHand = h;
	jeuActuel = p;
	statePli c;
	c.atout = atout;
	c.colorAsk = -1;
	cur = c;


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

int IA::minimax(int firstPlayer)
{
	return minimax(firstPlayer, 1, 0, 5);
}


	int IA::minimax(int firstPlayer, int atout, int score, int nbC)
	{
		statePli c;
		c.playerHasHand = firstPlayer;
		c.atout = atout;
		c.colorAsk = -1;
		c.currentHand = allHands[firstPlayer];
		c.nbCarte = nbC;
		c.nbPlayerPli = 0;
		c.valuePli = 0;
		c.score = score;

		if(nbC==0) {
			return score;
			cout << score << endl;
		}

		if (firstPlayer == 0 ||firstPlayer == 2)
		{
			return maxValue(c);
			//cout << nextCard <<endl;
		}
		else if(firstPlayer == 1 || firstPlayer == 3)
		{
			return minValue(c);
			//cout << nextCard <<endl;
		}
	}

	int IA::maxValuePli(statePli c)
	{
		if (c.nbPlayerPli == 4)
		{
			if (c.playerWiningPli == 0 || c.playerWiningPli == 2) 
				return minimax(c.playerWiningPli,c.atout,c.score + c.valuePli, c.nbCarte - 1);
			
			if (c.playerWiningPli == 1 || c.playerWiningPli == 3) 
				return minimax(c.playerWiningPli,c.atout,c.score, c.nbCarte - 1);
		}
		int value = - INT_MAX;

		for (int i=0; i<c.nbCarte;i++)
		{
			statePli c2 = majState(c, i);
			//TODO : gestion des hands... Maj next Joueur...
			int nextVal = IA::minValuePli(c2);
			value = max(value, nextVal);
			//c.list[i]=value;
		}  
		/* 
		int cardI = -1;

		for(int i=0; i<c.nbCarte;i++)
		{
			if(value==c.list[i] || (-value)== c.list[i] )
			{
				cardI=i;
			}
		}

		if (cardI != -1)
		{
			nextCard = c.currentHand.listHand[cardI] ;
			if (find(order.begin(), order.end(), nextCard)==order.end())
			{
				order.push_back(c.currentHand.listHand[cardI]);
			}
		}*/
		//order.push_back(c.currentHand.listHand[cardI]);
		return value;
	}


	int IA::minValuePli(statePli c)
	{
		if (c.nbPlayerPli == 4)
		{
			if (c.playerWiningPli == 0 || c.playerWiningPli == 2) 
				return minimax(c.playerWiningPli,c.atout,c.score + c.valuePli, c.nbCarte - 1);
			
			if (c.playerWiningPli == 1 || c.playerWiningPli == 3) 
				return minimax(c.playerWiningPli,c.atout,c.score, c.nbCarte - 1);
		}

		int value = INT_MAX;
		
		for (int i=0; i<c.nbCarte;i++)
		{
			statePli c2 = majState(c, i);
			//TODO : gestion des hands... Maj next Joueur...
			value = min(value, IA::maxValuePli(c2));
			//c.list[i]=value;
		}  
		//int cardI = -1;
		/*
		for(int i=0; i<c.nbCarte;i++)
		{
			if(value==c.list[i] || (-value)== c.list[i])
			{
				//cout << "ok " << i << endl;
				cardI=i;
			}

		}

		if (cardI != -1)
		{
			nextCard = c.currentHand.listHand[cardI] ;
			if (find(order.begin(), order.end(), nextCard)==order.end())
			{
				order.push_back(c.currentHand.listHand[cardI]);
			}
		}
		//order.push_back(c.currentHand.listHand[cardI]);*/
		return value;
	}

	
	IA::statePli IA::majState(statePli c, int i)
	{
		statePli c2;
		c2.atout = c.atout;
		c2.score = c.score;
		c2.nbCarte = c.nbCarte;
		c2.nbPlayerPli = c.nbPlayerPli + 1;
		c2.playerHasHand = c.playerHasHand + 1;
		if (c2.playerHasHand == 4)
			c2.playerHasHand = 0;
		c2.currentHand = allHands[c2.playerHasHand];

			if (c.colorAsk == -1)
			{
				c2.colorAsk = c.currentHand.listHand[i].getColor();
				c2.BestCard = c.currentHand.listHand[i];
				c2.playerWiningPli = c.playerHasHand;
			}
			else if(c.atout == c.currentHand.listHand[i].getColor() &&
				c.currentHand.listHand[i].getValue() > c.BestCard.getValue() || 
				c.BestCard.getColor() != c.atout &&
				c.atout == c.currentHand.listHand[i].getColor())
			{
				c2.BestCard = c.currentHand.listHand[i];
				c2.playerWiningPli = c2.playerHasHand;
			}
			
			else if(c.colorAsk == c.currentHand.listHand[i].getColor() && 
				c.BestCard.getColor() != c.atout &&
				c.currentHand.listHand[i].getValue() > c.BestCard.getValue())
			{
				c2.BestCard = c.currentHand.listHand[i];
				c2.playerWiningPli = c2.playerHasHand;
			}
			else 
			{
				c2.playerWiningPli = c.playerWiningPli;
				c2.BestCard = c.BestCard;
				c2.colorAsk = c.colorAsk;
			}

			c2.valuePli = c.currentHand.listHand[i].getValue() + c.valuePli;

			return c2;
	}

/*
Carte IA::minimax(int j)
{
	Hand h = allHands[j];
	if (cur.colorDemande == -1)
	{
		//TODO
	}
	else
	{
		if (h.hasColor(cur.colorDemande))
		{
			//TODO
		}
		else if (h.hasColor(cur.atout))
		{
			//TODO
		}
		else
		{
			//TODO
		}
	}
	Carte c;
	return c;
}
*/
/*
int IA::maxValue(state c)
{
	if(c.nbCarte == 0)
	{
		return -MAXINT;
	}
	else 
	{
		for(int i=0; i<c.nbCarte;i++)
		{
			if(c.finPli)
			{
				if(c.currentHand[i]>c.BestCard)
				{
					int v = c.valuePli+c.currentHand[i].point;
					return max(v,  );
				}
			}
		}
	}
}
*/



	int IA::maxValue(statePli c)
	{
		if (c.nbPlayerPli == 4)
		{
			if (c.playerWiningPli == 0 || c.playerWiningPli == 2) 
				return minimax(c.playerWiningPli,c.atout,c.score + c.valuePli, c.nbCarte - 1);
			
			if (c.playerWiningPli == 1 || c.playerWiningPli == 3) 
				return minimax(c.playerWiningPli,c.atout,c.score, c.nbCarte - 1);
		}
		int value = - INT_MAX;

		vector<Carte> cJ = carteAjouer(c);
		for(int i = 0; i < cJ.size(); i++)
		{
			statePli c2 = majStateCarte(c, cJ[i], i);
			int nextVal = IA::minValue(c2);
			value = max(value, nextVal);
		}
		return value;
	}

	vector<Carte> IA::carteAjouer(statePli c)
	{
		vector<Carte> vecCarte;
		
		if (vecCarte.empty())
		{
			
		}
		if (vecCarte.empty())
		{
			
		}
		return vecCarte;
	}

	IA::statePli IA::majStateCarte(statePli c, Carte carte, int i)
	{
		statePli c2;
		c2.atout = c.atout;
		c2.score = c.score;
		c2.nbCarte = c.nbCarte;
		c2.nbPlayerPli = c.nbPlayerPli + 1;
		c2.playerHasHand = c.playerHasHand + 1;
		if (c2.playerHasHand == 4)
		{
			c2.playerHasHand = 0;
		}
		c2.currentHand = allHands[c2.playerHasHand];

		if (c.colorAsk == -1)
			{
				c2.colorAsk = carte.getColor();
				c2.BestCard = carte;
				c2.playerWiningPli = c.playerHasHand;
			}
			else if(c.atout == carte.getColor() &&
				carte.getValue() > c.BestCard.getValue() || 
				c.BestCard.getColor() != c.atout &&
				c.atout == carte.getColor())
			{
				c2.BestCard = carte;
				c2.playerWiningPli = c2.playerHasHand;
			}
			
			else if(c.colorAsk == carte.getColor() && 
				c.BestCard.getColor() != c.atout &&
				carte.getValue() > c.BestCard.getValue())
			{
				c2.BestCard = carte;
				c2.playerWiningPli = c2.playerHasHand;
			}
			else 
			{
				c2.playerWiningPli = c.playerWiningPli;
				c2.BestCard = c.BestCard;
				c2.colorAsk = c.colorAsk;
			}

		c2.valuePli = carte.getValue() + c.valuePli;
			
		allHands[c2.playerHasHand].deleteCarte(i);

			return c2;
			
	}

	int IA::minValue(statePli c)
	{
		if (c.nbPlayerPli == 4)
		{
			if (c.playerWiningPli == 0 || c.playerWiningPli == 2) 
				return minimax(c.playerWiningPli,c.atout,c.score + c.valuePli, c.nbCarte - 1);
			
			if (c.playerWiningPli == 1 || c.playerWiningPli == 3) 
				return minimax(c.playerWiningPli,c.atout,c.score, c.nbCarte - 1);
		}

		int value = INT_MAX;
		
		vector<Carte> cJ = carteAjouer(c);
		for(int i = 0; i < cJ.size(); i++)
		{
			statePli c2 = majStateCarte(c, cJ[i], i);
			int nextVal = IA::maxValue(c2);
			value = min(value, nextVal);
		}
		return value;
	}