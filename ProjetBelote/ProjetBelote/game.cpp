#include <Windows.h>
#include <iostream>
#include <iomanip>
#include "carte.h"
#include "paquet.h"
#include <string>
#include "Hand.h"
#include "IA.h"
#include "IAvDream.h"
#include "ConsoleColor.h"

using namespace std;


void playGame(Hand htab[4],IAvDream monIA)
{	
	int player, nbCardPlayed, carteJoue, colorPlay, winner, scorePli, scoreA, scoreB;
	cout << "Belote : nouveau jeu" << endl;
	cout << "Choisir le joueur qui commence la partie (0 - 3) : ";
	cin >> player;
	int atout = 1;
	scoreA = 0;
	scoreB = 0;
	Carte bCard;
	for(int nbTour = 1; nbTour < 9; nbTour++)
	{
		cout << setfill('-');
		cout << setw(71) << "" << endl;
		cout << setfill(' ');
		cout << ".... Tour " << nbTour << " ...." << endl;
		monIA.printGame(htab);
		Carte c [4];
		scorePli = 0;
		bool valide;
		
		for (int i=0; i <4; i++)
		{	
			valide = false;
			if(i == 0 || i == 2) cout << blue <<".... Joueur " << player << ", (" << i+1 << "/4) ...." <<endl;
			else cout << yellow <<".... Joueur " << player << ", (" << i+1 << "/4) ...." <<endl;
			if (player == 0 && i == 0)
			{
				winner = player;
				bCard = monIA.nextCarte(htab[player],atout,player,0,Carte(),-1,0,winner);
				cout << "La carte jouee est : " << bCard << endl;
				scorePli += bCard.getPoint();
				c[i] = bCard;
				htab[player].deleteCarte(bCard);
				colorPlay = bCard.getColor();
			}
			else if(i == 0)
			{
				cout << "Joue quoi ? ";
				cin >> carteJoue;

				if(carteJoue < htab[player].nbCarte)
				{
					Carte tmp=htab[player].listHand[carteJoue];

					valide = monIA.isCarteValide(htab[player],tmp,-1,atout,bCard);
					while(!valide)
					{
						cout << "Carte non acceptee selon les regles du jeu ! " << endl;
						cout << "Joue quoi ? ";
						cin >> carteJoue;
						tmp=htab[player].listHand[carteJoue];
						winner = player;
						valide = monIA.isCarteValide(htab[player],tmp,-1,atout,bCard);
					}
					bCard = tmp;
				}
				else
				{
					bCard = monIA.carteAuto(htab[player],-1,atout,bCard);
				}

				colorPlay = bCard.getColor();
				cout << "La carte jouee est : " << bCard << endl;
				scorePli += bCard.getPoint();
				c[i] = bCard;
				htab[player].deleteCarte(bCard);
			}
			else if (player == 0)
			{
				Carte cardToPlay = monIA.nextCarte(htab[0],atout,player,i,bCard,colorPlay,0,winner);
				cout << "La carte jouee est : " << cardToPlay << endl;
				scorePli += cardToPlay.getPoint();
				bool sup;
				sup = cardToPlay.isSuperieur(bCard);
				cout << cardToPlay << "est superieur a " << bCard << " ? => " << sup <<endl;
				if (sup)
				{
					bCard=htab[player].listHand[carteJoue];
					winner = player;
				}
				c[i]= cardToPlay;
				htab[player].deleteCarte(cardToPlay);
			}
			else {
				cout << "Joue quoi ? ";
				cin >> carteJoue;
				Carte tmp;

				if(carteJoue < htab[player].nbCarte)
				{
					tmp = htab[player].listHand[carteJoue];

					valide = monIA.isCarteValide(htab[player],tmp,colorPlay,atout,bCard);
					while(!valide)
					{
						cout << "Carte non acceptee selon les regles du jeu ! " << endl;
						cout << "Joue quoi ? ";
						cin >> carteJoue;
						tmp=htab[player].listHand[carteJoue];

						valide = monIA.isCarteValide(htab[player],tmp,colorPlay,atout,bCard);
					}
				}
				else
				{
					tmp = monIA.carteAuto(htab[player],colorPlay,atout,bCard);
				}


				cout << "La carte jouee est : " << tmp << endl;
				scorePli += tmp.getPoint();
				bool sup;
				sup = tmp.isSuperieur(bCard);
				cout << tmp << "est superieur a " << bCard << " ? => " << sup <<endl;
				if (sup)
				{
					bCard=htab[player].listHand[carteJoue];
					winner = player;
				}
				c[i] = tmp;
				htab[player].deleteCarte(tmp);
			}
			player = (player +1)%4;
		}
		monIA.delListCard(c, 4);
		monIA.nbTour--;
		cout << white << "Le gagnant du pli est : Joueur " << winner << " - Score du pli : " << scorePli << endl;
		if(winner == 0 || winner == 2) scoreA += scorePli;
		else scoreB += scorePli;
		player = winner;
	}
	cout << "La partie est terminee" << endl;
	if(scoreA > scoreB)
		cout << "Les gagnants sont les Joueurs 0 et 2, avec un score final de " << scoreA << " points" << endl;
	else
		cout << "Les gagnants sont les Joueurs 1 et 3, avec un score final de " << scoreB << " points" << endl;
	cout << "Si vous lisez ce message, c'est que le jeu n'a pas plante :) " << endl;
}


int main()  {
	//cout << "Affichage test" << endl;
	//cout << setw(6) << "Huit" << setw(6) << "Coeur" << endl;
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