#include <Windows.h>
#include <iostream>
#include "carte.h"
#include "paquet.h"
#include <string>
#include "Hand.h"
#include "IA.h"
#include "IAvDream.h"

using namespace std;


void playGame(Hand htab[4],IAvDream monIA)
{	
	int player, nbCardPlayed, carteJoue, colorPlay;
	Carte bCard;
	for(int nbTour = 1; nbTour < 9; nbTour++)
	{
		cout << "Tour " << nbTour << endl;
		monIA.printGame(htab);
		cout << "choisir joueur" << endl;
		cin >> player;
		Carte c [4];
		for (int i=0; i <4; i++)
		{	
			cout <<"joueur " << player << " ,i = " << i << endl;
			if (player == 0 && i == 0)
			{
				bCard = monIA.nextCarte(htab[player],1,player,0,Carte(),-1,0);
				cout << bCard << endl;
				c[i] = bCard;
				htab[player].deleteCarte(bCard);
			}
			else if(i == 0)
			{
				cout << "Joue quoi ? " << endl;
				cin >> carteJoue;
				bCard=htab[player].listHand[carteJoue];
				colorPlay = bCard.getColor();
				cout << bCard << endl;
				c[i] = bCard;
				htab[player].deleteCarte(bCard);
			}
			else if (player == 0)
			{
				Carte cardToPlay = monIA.nextCarte(htab[0],1,player,i,bCard,colorPlay,0);
				cout << "Superieur " << cardToPlay << " ? " << endl;
				bool sup;
				cin >> sup;
				if (sup)
				{
					bCard=htab[player].listHand[carteJoue];
				}
				c[i]= cardToPlay;
				htab[player].deleteCarte(cardToPlay);
			}
			else {
				cout << "Joue quoi ? " << endl;
				cin >> carteJoue;
				Carte tmp = htab[player].listHand[carteJoue];
				cout << "Superieur " << tmp << " ? " <<endl;
				bool sup;
				cin >> sup;
				if (sup)
				{
					bCard=htab[player].listHand[carteJoue];
				}
				c[i] = tmp;
				htab[player].deleteCarte(tmp);
			}
			player = (player +1)%4;
		}
		monIA.delListCard(c, 4);
		monIA.nbTour--;
	}
	cout << "Si vous lisez ce message, c'est que le jeu n'a pas planté :) " << endl;
}


int main()  {
	
	srand(time(NULL));

	/*Paquet p = Paquet();
	int point = 0;

	Carte tas [8];
	for(int i=0;i<8; i++)
	{
		Carte c = Carte(Carte::AS-i,Carte::PIQUE);
		c.setAtout();
		cout << c.getPoint() << endl;
		tas[i]= c;
	}
	Hand h = Hand(tas, sizeof(tas)/sizeof(Carte));
	h.triAtout(Carte::PIQUE);*/


	IAvDream monIADream = IAvDream(6);
	Hand tabHand[4];
	//tabHand[0] = h;

	/*Carte tas2 [8];
	for(int i=0;i<8; i++)
	{
		Carte c = Carte(Carte::AS-i,Carte::CARREAU);
		tas2[i]= c;
	}
	Hand h2 = Hand(tas2, sizeof(tas2)/sizeof(Carte));
	h2.triAtout(Carte::PIQUE);
	tabHand[1] = h2;

	Carte tas3 [8];
	for(int i=0;i<8; i++)
	{
		Carte c = Carte(Carte::AS-i,Carte::COEUR);
		tas3[i]= c;
	}
	Hand h3 = Hand(tas3, sizeof(tas3)/sizeof(Carte));
	h3.triAtout(Carte::PIQUE);
	tabHand[2] = h3;

	Carte tas4 [8];
	for(int i=0;i<8; i++)
	{
		Carte c = Carte(Carte::AS-i,Carte::TREFLE);
		tas4[i]= c;
	}
	Hand h4 = Hand(tas4, sizeof(tas4)/sizeof(Carte));
	h4.triAtout(Carte::PIQUE);
	tabHand[3] = h4;*/



	//cout << monIADream.minimax(0, 1, tabHand) << endl;
	
	vector<Carte> cartesRestantes;

	for(int i=0; i<4; i++)
	{
		for(int j=0; j<8; j++)
		{
			Carte c = Carte(j,i);
			cartesRestantes.push_back(c);
		}
	}

	for(int i = 0; i < 4; i++)
	{
		Carte newHand[8];
		for(int j = 0; j < 8; j++)
		{
			int posCarte = rand() %cartesRestantes.size();
			Carte tmp = cartesRestantes[posCarte];
			if (tmp.getColor() == Carte::PIQUE)
			{	
				tmp.setAtout();
			}
			newHand[j] = tmp;
			cartesRestantes.erase(cartesRestantes.begin() + posCarte);
		}
		tabHand[i] = Hand(newHand,8);
		tabHand[i].triAtout(Carte::PIQUE);
	}

	
	/*cout << "Alpha Beta : " << monIADream.minimaxAlphaBeta(0, 1, tabHand) << endl;
	cout << "Nb Coup : "<< monIADream.nbFin << endl;

	cout << "Retour de Carte : " << monIADream.nextCarte(tabHand[0], 1, 2, 0, Carte(), -1, 0) << endl;
	cout << "Nb Coup : "<< monIADream.nbFin << endl;*/

	playGame(tabHand,monIADream);
	
	while(1);
	return 0;
}