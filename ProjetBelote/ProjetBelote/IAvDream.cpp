#include "IAvDream.h"

#define NBTOUR 6


IAvDream::IAvDream(int nb)
{
	player = 0;
	partner = 2;
	cpt = 0;
	nbFin = 0;
	srand(time(NULL));
	nbTour = nb;
	int pos = 0;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<8; j++)
		{
			Carte c = Carte(j,i);
			cardsStillInGame[pos++] = 1;
		}
	}
	nbCardDeleted = 0;
}


IAvDream::~IAvDream(void)
{
}


int IAvDream::minimax(int firstPlayer, int atout, Hand * all)
{
	state c;
	c.playerWiningPli = firstPlayer;
	c.atout = atout;
	c.score = 0;
	c.nbCarte = 8;
	c.valuePli = 0;
	for(int i=0;i<4;i++)
		c.allHand[i] = all[i];

	nbFin = 0;

	return minimax(c);

	//TODO call min ||Max &co
}

int IAvDream::minimax(state c)
{
	if (c.nbCarte == 0)
	{
		nbFin++;
		return c.score;
	}

	c.playerHasHand = c.playerWiningPli;
	c.nbPlayerPli = 0;
	c.BestCard = Carte();
	c.valuePli = 0;
	c.colorAsk = -1;
	//c.allHand[c.playerHasHand] = c.allHand[c.playerHasHand];

	if(c.playerHasHand == player ||c.playerHasHand == partner)
	{
		return maxValue(c);
	}
	else 
	{
		return minValue(c);
	}

}

int IAvDream::maxValue(state c)
{
	if (c.nbPlayerPli == 4)
		{
			if (c.playerWiningPli == player || c.playerWiningPli == partner) 
			{	
				c.score += c.valuePli;
				c.nbCarte--;
				return minimax(c);
			}
			else
			{
				c.nbCarte--;
				return minimax(c);
			}
		}
		int value = - INT_MAX;

		if(c.colorAsk == -1 && c.nbCarte > nbTour)
		{
			for(int i = 0; i < c.allHand[c.playerHasHand].nbCarte;i++)
			{
				state c2 = majState(c, i);
				int nextVal = minValue(c2);
				value = max(value, nextVal);
			}
		}

		if(c.allHand[c.playerHasHand].hasColor(c.colorAsk) && c.colorAsk!= c.atout)
		{
			//TODO OPTI
			int posColor = c.allHand[c.playerHasHand].posColor(c.colorAsk);
			int nbColor = c.allHand[c.playerHasHand].nbColor(c.colorAsk);
			for(int i= posColor; i<(posColor + nbColor);i++)
			{
				state c2 = majState(c, i);
				int nextVal = minValue(c2);
				value = max(value, nextVal);
			}
		}
		else if(c.allHand[c.playerHasHand].hasColor(c.atout))
		{
			//Atout seulement Carte sup.
			int posColor = c.allHand[c.playerHasHand].posColor(c.atout);
			int nbColor = c.allHand[c.playerHasHand].nbColor(c.atout);
			int nbAtoutSup = 0;
			for(int i= posColor; i<(posColor + nbColor);i++)
			{
				if(c.allHand[c.playerHasHand].listHand[i].getOrdre() > c.BestCard.getOrdre() && c.BestCard.getColor() == c.atout)
				{
					state c2 = majState(c, i);
					int nextVal = minValue(c2);
					value = max(value, nextVal);
					nbAtoutSup++;
				}
				if(nbAtoutSup == 0)
				{
					state c2 = majState(c, i);
					int nextVal = minValue(c2);
					value = max(value, nextVal);
				}
			}
		} else // TODO SI NON MAITRESSE
		{	
			int posCarte = rand() %c.allHand[c.playerHasHand].nbCarte;
			state c2 = majState(c,posCarte);
			value = minValue(c2);
		}
		return value;
}

int IAvDream::minValue(state c)
{
	if (c.nbPlayerPli == 4)
		{
			if (c.playerWiningPli == player || c.playerWiningPli == partner) 
			{	
				c.score += c.valuePli;
				c.nbCarte--;
				return minimax(c);
			}
			else
			{
				c.nbCarte--;
				return minimax(c);
			}
		}
		int value = INT_MAX;

		if(c.colorAsk == -1 && c.nbCarte > nbTour)
		{
			for(int i = 0; i < c.allHand[c.playerHasHand].nbCarte;i++)
			{
				state c2 = majState(c, i);
				int nextVal = minValue(c2);
				value = max(value, nextVal);
			}
		}

		if(c.allHand[c.playerHasHand].hasColor(c.colorAsk) && c.colorAsk!= c.atout)
		{
			//TODO OPTI
			int posColor = c.allHand[c.playerHasHand].posColor(c.colorAsk);
			int nbColor = c.allHand[c.playerHasHand].nbColor(c.colorAsk);
			for(int i= posColor; i<(posColor + nbColor);i++)
			{
				state c2 = majState(c, i);
				int nextVal = maxValue(c2);
				value = min(value, nextVal);
			}
		}
		else if(c.allHand[c.playerHasHand].hasColor(c.atout))
		{
			//Atout seulement Carte sup.
			int nbAtoutSup = 0;
			int posColor = c.allHand[c.playerHasHand].posColor(c.atout);
			int nbColor = c.allHand[c.playerHasHand].nbColor(c.atout);
			for(int i= posColor; i<(posColor + nbColor);i++)
			{
				if(c.allHand[c.playerHasHand].listHand[i].getOrdre() > c.BestCard.getOrdre() && c.BestCard.getColor() == c.atout)
				{
					state c2 = majState(c, i);
					int nextVal = maxValue(c2);
					value = min(value, nextVal);
					nbAtoutSup++;
				}
				if(nbAtoutSup == 0)
				{
					state c2 = majState(c, i);
					int nextVal = maxValue(c2);
					value = min(value, nextVal);
				}
			}
		} else // TODO SI NON MAITRESSE
		{	
			int posCarte = rand() %c.allHand[c.playerHasHand].nbCarte;
			state c2 = majState(c,posCarte);
			value = maxValue(c2);
		}
		return value;
}

//----------------------------------------------ALPHA BETA----------------

int IAvDream::minimaxAlphaBeta(int firstPlayer, int atout, Hand * all)
{
	state c;
	c.playerWiningPli = firstPlayer;
	c.atout = atout;
	c.score = 0;
	c.nbCarte = 8;
	c.valuePli = 0;
	for(int i=0;i<4;i++)
		c.allHand[i] = all[i];
	nbFin = 0;
	return minimax(c,-INT_MAX,INT_MAX);

	//TODO call min ||Max &co
}

int IAvDream::minimax(state c, int alpha, int beta)
{
	if (c.nbCarte == 0)
	{
		nbFin++;
		return c.score;
	}

	c.playerHasHand = c.playerWiningPli;
	c.nbPlayerPli = 0;
	c.BestCard = Carte();
	c.valuePli = 0;
	c.colorAsk = -1;

	if(c.playerHasHand == player ||c.playerHasHand == partner)
	{
		return maxValue(c,alpha,beta);
	}
	else 
	{
		return minValue(c,alpha,beta);
	}

}

int IAvDream::maxValue(state c, int alpha, int beta)
{
	if (c.nbPlayerPli == 4)
		{
			if (c.playerWiningPli == player || c.playerWiningPli == partner) 
			{	
				c.score += c.valuePli;
				c.nbCarte--;
				return minimax(c,alpha,beta);
			}
			else
			{
				c.nbCarte--;
				return minimax(c,alpha,beta);
			}
		}
		int value = - INT_MAX;

		if(c.colorAsk == -1 && c.nbCarte > nbTour)
		{
			for(int i = 0; i < c.allHand[c.playerHasHand].nbCarte;i++)
			{
				state c2 = majState(c, i);
				int nextVal = minValue(c2,alpha,beta);
				value = max(value, nextVal);
				if(value >= beta) 
					return value;
				alpha = max(alpha,value);
			}
		}

		if(c.allHand[c.playerHasHand].hasColor(c.colorAsk) && c.colorAsk!= c.atout)
		{
			//TODO OPTI
			int posColor = c.allHand[c.playerHasHand].posColor(c.colorAsk);
			int nbColor = c.allHand[c.playerHasHand].nbColor(c.colorAsk);
			for(int i= posColor; i<(posColor + nbColor);i++)
			{
				state c2 = majState(c, i);
				int nextVal = minValue(c2,alpha,beta);
				value = max(value, nextVal);
				if(value >= beta) 
					return value;
				alpha = max(alpha,value);
			}
		}
		else if(c.allHand[c.playerHasHand].hasColor(c.atout))
		{
			//Atout seulement Carte sup.
			int posColor = c.allHand[c.playerHasHand].posColor(c.atout);
			int nbColor = c.allHand[c.playerHasHand].nbColor(c.atout);
			int nbAtoutSup = 0;
			for(int i= posColor; i<(posColor + nbColor);i++)
			{
				if(c.allHand[c.playerHasHand].listHand[i].getOrdre() > c.BestCard.getOrdre() && c.BestCard.getColor() == c.atout)
				{
					state c2 = majState(c, i);
					int nextVal = minValue(c2,alpha,beta);
					value = max(value, nextVal);
					if(value >= beta) 
						return value;
					alpha = max(alpha,value);
					nbAtoutSup++;
				}
				if(nbAtoutSup == 0)
				{
					state c2 = majState(c, i);
					int nextVal = minValue(c2,alpha,beta);
					value = max(value, nextVal);
					if(value >= beta) 
						return value;
					alpha = max(alpha,value);
				}
			}
		} else // TODO SI NON MAITRESSE
		{	
			int posCarte = rand() %c.allHand[c.playerHasHand].nbCarte;
			state c2 = majState(c,posCarte);
			value = minValue(c2,alpha,beta);
		}
		return value;
}

int IAvDream::minValue(state c, int alpha, int beta)
{
	if (c.nbPlayerPli == 4)
		{
			if (c.playerWiningPli == player || c.playerWiningPli == partner) 
			{	
				c.score += c.valuePli;
				c.nbCarte--;
				return minimax(c,alpha,beta);
			}
			else
			{
				c.nbCarte--;
				return minimax(c,alpha,beta);
			}
		}
		int value = INT_MAX;

		if(c.colorAsk == -1 && c.nbCarte > nbTour)
		{
			for(int i = 0; i < c.allHand[c.playerHasHand].nbCarte;i++)
			{
				state c2 = majState(c, i);
				int nextVal = minValue(c2,alpha,beta);
				value = max(value, nextVal);
				if(value <= alpha) 
					return value;
				beta = min(beta,value);
			}
		}

		if(c.allHand[c.playerHasHand].hasColor(c.colorAsk) && c.colorAsk!= c.atout)
		{
			//TODO OPTI
			int posColor = c.allHand[c.playerHasHand].posColor(c.colorAsk);
			int nbColor = c.allHand[c.playerHasHand].nbColor(c.colorAsk);
			for(int i= posColor; i<(posColor + nbColor);i++)
			{
				state c2 = majState(c, i);
				int nextVal = maxValue(c2,alpha,beta);
				value = min(value, nextVal);
				if(value <= alpha) 
					return value;
				beta = min(beta,value);
			}
		}
		else if(c.allHand[c.playerHasHand].hasColor(c.atout))
		{
			//Atout seulement Carte sup.
			int nbAtoutSup = 0;
			int posColor = c.allHand[c.playerHasHand].posColor(c.atout);
			int nbColor = c.allHand[c.playerHasHand].nbColor(c.atout);
			for(int i= posColor; i<(posColor + nbColor);i++)
			{
				if(c.allHand[c.playerHasHand].listHand[i].getOrdre() > c.BestCard.getOrdre() && c.BestCard.getColor() == c.atout)
				{
					state c2 = majState(c, i);
					int nextVal = maxValue(c2,alpha,beta);
					value = min(value, nextVal);
					if(value <= alpha) 
						return value;
					beta = min(beta,value);
					nbAtoutSup++;
				}
				if(nbAtoutSup == 0)
				{
					state c2 = majState(c, i);
					int nextVal = maxValue(c2,alpha,beta);
					value = min(value, nextVal);
					if(value <= alpha) 
						return value;
					beta = min(beta,value);
				}
			}
		} else // TODO SI NON MAITRESSE
		{	
			int posCarte = rand() %c.allHand[c.playerHasHand].nbCarte;
			state c2 = majState(c,posCarte);
			value = maxValue(c2,alpha,beta);
		}
		return value;
}

//--------------------------------------------

IAvDream::state IAvDream::majState(state c, int i)
	{
		cpt++;
		state c2;
		c2.atout = c.atout;
		c2.score = c.score;
		c2.nbCarte = c.nbCarte;
		
		
		for (int i =0; i<4;i++)
			c2.allHand[i] = c.allHand[i];

			if (c.colorAsk == -1)
			{
				c2.colorAsk = c.allHand[c.playerHasHand].listHand[i].getColor();
				c2.BestCard = c.allHand[c.playerHasHand].listHand[i];
				c2.playerWiningPli = c.playerHasHand;
			}
			else if((c.atout == c.allHand[c.playerHasHand].listHand[i].getColor() &&
				c.allHand[c.playerHasHand].listHand[i].getOrdre() > c.BestCard.getOrdre() &&
				c.BestCard.getColor() == c.atout )|| (
				c.BestCard.getColor() != c.atout &&
				c.atout == c.allHand[c.playerHasHand].listHand[i].getColor()))
			{
				c2.BestCard = c.allHand[c.playerHasHand].listHand[i];
				c2.playerWiningPli = c.playerHasHand;
				c2.colorAsk = c.colorAsk;
			}
			
			else if(c.colorAsk == c.allHand[c.playerHasHand].listHand[i].getColor() && 
				c.BestCard.getColor() != c.atout &&
				c.allHand[c.playerHasHand].listHand[i].getOrdre() > c.BestCard.getOrdre())
			{
				c2.BestCard = c.allHand[c.playerHasHand].listHand[i];
				c2.playerWiningPli = c.playerHasHand;
				c2.colorAsk = c.colorAsk;
			}
			else 
			{
				c2.playerWiningPli = c.playerWiningPli;
				c2.BestCard = c.BestCard;
				c2.colorAsk = c.colorAsk;
			}

		c2.valuePli = c.allHand[c.playerHasHand].listHand[i].getPoint() + c.valuePli;
		c2.allHand[c.playerHasHand].deleteCarte(i);
		c2.playerHasHand = (c.playerHasHand + 1)%4;
		c2.nbPlayerPli = c.nbPlayerPli + 1;
			return c2;
	}


Carte IAvDream::nextCarte(Hand h, int atout, int playerActive, int numberCardPlayedInPli, Carte bestCard, int colorAsk, int valuePli)
{
	nbFin = 0;
	Hand htab[4];

	distributionCards(h, htab, atout);
	//printGame(htab);
	int max = 0;
	int index = 0;
	bool hasAtoutSup = false;
	if(h.hasColor(atout))
	{
		if (h.listHand[h.posColor(atout)].getOrdre() > bestCard.getOrdre())
		{
			hasAtoutSup = true;
		}
	}
	for (int i=0; i<h.nbCarte;i++)
	{
		
		state c;
		c.playerWiningPli = playerActive;
		c.atout = atout;
		c.nbCarte = h.nbCarte;
	
	//TODO gestion Hand To del
		for(int i=0;i<4;i++)
			c.allHand[(i+playerActive)%4] = htab[i];
		
		c.playerHasHand = playerActive;
		c.nbPlayerPli = numberCardPlayedInPli;
		c.colorAsk = colorAsk;
		c.BestCard = bestCard;
		c.valuePli = valuePli;
	
		c.score = 0;
		if (colorAsk == -1 || 
			colorAsk == h.listHand[i].getColor() && colorAsk != atout ||
			bestCard.getColor() == atout && hasAtoutSup && h.listHand[i].getOrdre() > bestCard.getOrdre() && (h.hasColor(colorAsk) == false || colorAsk == atout)||
			bestCard.getColor() == atout && h.listHand[i].getColor() == atout && !hasAtoutSup && (h.hasColor(colorAsk) == false || colorAsk == atout) ||
			h.hasColor(colorAsk)==false && h.hasColor(atout) == false)
		
		{
			c = majState(c, i);
			if(c.playerHasHand == player ||c.playerHasHand == partner)
			{
				int value = maxValue(c,-INT_MAX, INT_MAX);
				if(value>max)
				{
					max = value;
					index = i;
				}
			}
			else 
			{
				int value = minValue(c,-INT_MAX, INT_MAX);
				if(value>max)
				{
					max = value;
					index = i;
				}
			}
		}
		
	}
	cout << "Score : " << max << endl;
	return h.listHand[index];
}

void IAvDream::deleteCard(Carte c)
{
	int pos = c.getColor()*8 + c.getValue();
	cardsStillInGame[pos] = 0;
	nbCardDeleted++;
}


void IAvDream::distributionCards(Hand h, Hand htab[4], int atout)
{
	htab[0] = h;
	int pos = 0;
	vector<Carte> listeRestante;

	for (int i=0; i<h.nbCarte;i++)
	{
		Carte tmp = h.listHand[i];
		deleteCard(tmp);
	}
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			//int posCarte = rand() % 32 - nbCardDeleted;
			if (cardsStillInGame[pos++] == 1)
			{
				Carte c(j,i);
				listeRestante.push_back(c);
			}
		}
	}

	for(int i = 1; i < 4; i++)
	{
		Carte newHand[8];
		for(int j = 0; j < h.nbCarte; j++)
		{
			int posCarte = rand() %listeRestante.size();
			Carte tmp = listeRestante[posCarte];
			if (tmp.getColor() == atout)
			{	
				tmp.setAtout();
			}
			newHand[j] = tmp;
			listeRestante.erase(listeRestante.begin() + posCarte);
		}
		htab[i] = Hand(newHand,h.nbCarte);
		htab[i].triAtout(atout);
	}
}



void IAvDream::printGame(Hand htab[4]){
	for(int i = 0; i< 4; i++)
	{
		cout << "Hand " << i << " --------------" << endl;
		for(int j = 0; j< htab[i].nbCarte; j++)
		{
			cout << "Carte " << j << " : " << htab[i].listHand[j] << " " << htab[i].listHand[j].getPoint() << endl;
		}
	}
}

void IAvDream::delListCard(Carte cards[], int lg)
{
	for(int i=0; i <lg; i++)
	{
		deleteCard(cards[i]);
	}
}