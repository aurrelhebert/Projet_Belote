#include "IAvDream.h"

#define NBTOUR 6
#define NBMAX 5

using namespace std;

IAvDream::IAvDream()
{
}

IAvDream::IAvDream(int nb)
{
	player = 0;
	partner = 2;
	cpt = 0;
	nbFin = 0;
	//srand(time(NULL));
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
				if(c.nbCarte == 1)
					c.score += 10;
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
				if(c.nbCarte == 1)
					c.score += 10;
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
		
		
		for (int k =0; k<4;k++)
			c2.allHand[k] = c.allHand[k];

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


Carte IAvDream::nextCarte(Hand h, int atout, int playerActive, int numberCardPlayedInPli, Carte bestCard, int colorAsk, int valuePli, int playerWining)
{
	nbFin = 0;
	Hand htab[4];

	distributionCards(h, htab, atout);
	player=playerWining;
	partner=(playerWining+2)%4;
	//printGame(htab);
	int max = -1;
	int index = 0;
	int hasAtoutSup = false;
	
	if(h.hasAtoutSup(bestCard.getOrdre(),atout))
		hasAtoutSup = true;
	
	for (int i=0; i<h.nbCarte;i++)
	{
		
		state c;
		c.playerWiningPli = playerWining;
		c.atout = atout;
		c.nbCarte = h.nbCarte;
	
	//TODO gestion Hand To del
		for(int k=0;k<4;k++)
			c.allHand[(k+playerActive)%4] = htab[k];
		
		c.playerHasHand = playerActive;
		c.nbPlayerPli = numberCardPlayedInPli;
		c.colorAsk = colorAsk;
		c.BestCard = bestCard;
		c.valuePli = valuePli;
	
		c.score = 0;

		if(isCarteValide(h, h.listHand[i], colorAsk, atout, bestCard,playerWining,playerActive))
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
	//cout << "Score : " << max << endl;
	return h.listHand[index];
}
Carte IAvDream::nextCarte(Hand* htab, int atout, int playerActive, int numberCardPlayedInPli, Carte bestCard, int colorAsk, int valuePli, int playerWining)
{
	nbFin = 0;
	Hand h = htab[playerActive];

	//distributionCards(h, htab, atout);
	player=playerActive;
	partner=(playerActive+2)%4;
	
	//cout << player << partner <<endl;
	//printGame(htab);
	int max = -1;
	int index = 0;
	bool hasAtoutSup = false;
	if(h.hasAtoutSup(bestCard.getOrdre(),atout))
		hasAtoutSup = true;
	
	for (int i=0; i<h.nbCarte;i++)
	{
		
		state c;
		c.playerWiningPli = playerWining;
		c.atout = atout;
		c.nbCarte = h.nbCarte;
	
	//TODO gestion Hand To del
		for(int k=0;k<4;k++)
			c.allHand[(k+playerActive)%4] = htab[k];
		
		c.playerHasHand = playerActive;
		c.nbPlayerPli = numberCardPlayedInPli;
		c.colorAsk = colorAsk;
		c.BestCard = bestCard;
		c.valuePli = valuePli;
	
		c.score = 0;
		
		if(isCarteValide(h, h.listHand[i], colorAsk, atout, bestCard,playerWining, playerActive))
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
	//cout << "Score : " << max << endl;
	//cout << player << partner <<endl;
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
		Carte newHand[9];
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
	cout << setfill('-');
	cout << setw(13) << " Joueur 0 " << setw(5) << " + ";
	cout << setw(13) << " Joueur 1 " << setw(5) << " + ";
	cout << setw(13) << " Joueur 2 " << setw(5) << " + ";
	cout << setw(13) << " Joueur 3 " << setw(5) << " + " << endl;
	cout << setfill(' ');

	for(int j = 0; j< htab[0].nbCarte; j++)
	{
		//cout << "Carte " << j << " : " << htab[i].listHand[j] << " " << htab[i].listHand[j].getPoint() << endl;
		cout << j << " " << htab[0].listHand[j] << setw(2) << "| ";
		cout << j << " " << htab[1].listHand[j] << setw(2) << "| ";
		cout << j << " " << htab[2].listHand[j] << setw(2) << "| ";
		cout << j << " " << htab[3].listHand[j] << setw(2) << "| " << endl;
	}
	cout << setfill('-');
	cout << setw(71) << "" << endl;
	cout << setfill(' ');
}

void IAvDream::delListCard(Carte cards[], int lg)
{
	for(int i=0; i <lg; i++)
	{
		deleteCard(cards[i]);
	}
}


bool IAvDream::isCarteValide(Hand h, Carte c, int colorAsk, int atout, Carte bestCard,int winner, int actualPartner)
{
	actualPartner = (actualPartner + 2)%4;
	bool valide = false;
	if(colorAsk == -1)
		valide = true;
	else if(colorAsk != atout)
	{
		//Si carte est de la couleur demand�e ou si main ne contient pas cette couleur ni de l'atout
		if(c.getColor() == colorAsk || (h.hasColor(colorAsk) == false && h.hasColor(atout) == false))
			valide = true;
		//Si main ne contient pas couleur demandee, et ma carte est de l'atout
		else if(h.hasColor(colorAsk) == false && c.getColor() == atout)
		{
			//Si bestCard n'est pas en atout ou si elle est d'ordre inf�rieur � la carte propos�e
			if(bestCard.getColor() != atout || c.getOrdre() > bestCard.getOrdre() || h.hasAtoutSup(bestCard.getOrdre(),atout) == false )
				valide = true;
		}
		else if(winner == actualPartner && h.hasColor(colorAsk) == false)
				valide = true;
		//Autres cas � false par d�faut
	}
	else
	{
		//Si main ne contient pas d'atout
		if(h.hasColor(colorAsk) == false)
			valide = true;
		//Si carte est de l'atout et de valeur sup�rieure � la bestCard
		else if(c.getColor() == colorAsk && (c.getOrdre() > bestCard.getOrdre() || h.hasAtoutSup(bestCard.getOrdre(), atout) == false))
			valide = true;
		//Autres cas � false par d�faut
	}
	return valide;
}

Carte IAvDream::carteAuto(Hand h,int colorAsk,int atout, Carte bestCard,int winner,int actualPlayer)
{
	for(int i = 0; i < h.nbCarte; i++)
	{
		if(isCarteValide(h,h.listHand[i],colorAsk,atout,bestCard,winner,actualPlayer))
		{
			return h.listHand[i];
		}
	}
	cout << "Erreur : pas de carte valide (derniere carte retournee par defaut" << endl;
	return h.listHand[h.nbCarte-1];
}

int IAvDream::prendre(Hand h,int firstPlayer, int playerIA)
{
	Carte firstCarte = h.listHand[5];
	int value = -1;
	int atoutPris = -1;
	for(int i = 0; i < 4; i++)
	{
		Hand hTmp;
		Carte tabCarte[8];
		for (int k = 0; k<h.nbCarte; k++)
		{
			tabCarte[k] = Carte(h.listHand[k].getValue(),h.listHand[k].getColor());
		}
		hTmp = Hand(tabCarte,h.nbCarte);
		hTmp.setAtout(i);
		int score = prendreScore(hTmp,i,firstPlayer,playerIA);
		if(score > value)
		{
			value = score;
			atoutPris = i;
		}
	}
		return atoutPris;
}


int IAvDream::prendreScore(Hand h, int atout, int firstPlayer, int playerIA)
{
	Hand htab[4];

	//distributionCards(h, htab, atout);
	distributionPrise(h,htab,atout);
	
	player=playerIA;
	partner=(playerIA+2)%4;

	int score = minimaxAlphaBeta(firstPlayer, atout,htab);
	if (score > 130)
		return score;
	else 
		return -1;
}

void IAvDream::distributionPrise(Hand h, Hand* htab,int atout)
{
	vector<Carte> listeRestante;
	int stillInGame[32];
	int nbDel = 0;
	int cptPos = 0;
	for(int i = 0; i < 32; i++)
	{
		stillInGame[i] = 1;
	}
	for(int i=0; i<h.nbCarte;i++)
	{
		int pos = h.listHand[i].getColor()*8 + h.listHand[i].getValue();
		stillInGame[pos] = 0;
		nbDel ++;
	}
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(stillInGame[cptPos] == 1)
			{
				Carte c(j,i);
				listeRestante.push_back(c);
			}
			cptPos++;
		}
	}
	for(int i = 0; i < 4; i++)
	{
		Carte newHand[9];
		if(i == 0) //TODO change playerIA
		{
			for(int k = 0; k < h.nbCarte; k++)
			{
				newHand[k] = h.listHand[k];
			}
		}
		else
		{
			for(int j = 0; j < h.nbCarte; j++)
			{
				int posCarte = rand() %listeRestante.size();
				Carte tmp = listeRestante[posCarte];
				newHand[j] = tmp;
				listeRestante.erase(listeRestante.begin() + posCarte);
			}
		}
		htab[i] = Hand(newHand,h.nbCarte);
		htab[i].setAtout(atout);
		htab[i].triAtout(atout);
	}
}
