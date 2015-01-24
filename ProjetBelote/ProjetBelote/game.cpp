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
#include <map>

using namespace std;

#define NBFORIA 20

void setAtout(Carte tab[4][8], int atout)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			Carte tmp = tab[i][j];
			if (tab[i][j].getColor() == atout)
			{	
				tab[i][j].setAtout();
			}
		}
	}
}

int assetManagement(Carte tab[4][8], IAvDream monIA, int player, Carte firstCarte, int playerIA)
{
	Carte tabTmp [4][8];
	Hand tabHand[4];
	for (int i = 0; i<4; i++)
		for(int j = 0; j <8; j++)
			tabTmp[i][j] = tab[i][j];

	setAtout(tabTmp, firstCarte.getColor());
	for (int i=0; i<4; i++)
	{
		tabHand[i] = Hand(tabTmp[i],5);
	}

	bool prendre = monIA.prendre(tabHand[playerIA], firstCarte.getColor(), player, 0);
	cout << prendre << endl;
	if (prendre)
	{
		return firstCarte.getColor();
	}
	else 
	{
		return 1;
	}
}

void playGame(Hand htab[4],IAvDream monIA, int player, int atoutGame)
{	
	int nbCardPlayed, carteJoue, colorPlay, winner, scorePli, scoreA, scoreB;
	winner = -1;
	int atout = atoutGame;
	scoreA = 0;
	scoreB = 0;
	Carte bCard;
	for(int nbTour = 1; nbTour < 9; nbTour++)
	{
		if (nbTour==3)
		{
			monIA.nbTour = 0;
		}
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
				Carte resIa[NBFORIA];
				IAvDream tabIa[NBFORIA];
#pragma omp parallel for
				for (int iForIa = 0; iForIa <NBFORIA; iForIa++)
				{
					srand(iForIa);
					tabIa[iForIa] = IAvDream(monIA.nbTour);
					resIa[iForIa] = tabIa[iForIa].nextCarte(htab[player],atout,player,0,Carte(),-1,0,winner);
					//cout << iForIa << ": " << resIa[iForIa] << endl;
				}
				map<Carte, int> m;
				
				for (int iForIa = 0; iForIa <NBFORIA; iForIa++)
				{
					Carte tmp = resIa[iForIa];
					if(m.find(tmp).operator==(m.end()))
					{
						m[tmp]=0;
					} 
					m[tmp]++;
				}
				int max = -1;
				Carte tmpForIa;
				for (std::map<Carte, int>::iterator it = m.begin(); it != m.end(); ++it)
				{
					//cout << it->first << it->second <<endl;
					if (it->second > max)
					{
						tmpForIa = it->first;
						max = it->second;
					}
				}
				bCard = tmpForIa;
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

					valide = monIA.isCarteValide(htab[player],tmp,-1,atout,bCard,winner,player);
					while(!valide)
					{
						cout << "Carte non acceptee selon les regles du jeu ! " << endl;
						cout << "Joue quoi ? ";
						cin >> carteJoue;
						tmp=htab[player].listHand[carteJoue];
						valide = monIA.isCarteValide(htab[player],tmp,-1,atout,bCard,winner,player);
					}
					bCard = tmp;
					winner = player;
				}
				else
				{
					bCard = monIA.carteAuto(htab[player],-1,atout,bCard,winner,player);
				}

				colorPlay = bCard.getColor();
				cout << "La carte jouee est : " << bCard << endl;
				scorePli += bCard.getPoint();
				c[i] = bCard;
				htab[player].deleteCarte(bCard);
			}
			else if (player == 0)
			{
				Carte resIa[NBFORIA];
				IAvDream tabIa[NBFORIA];
#pragma omp parallel for
				for (int iForIa = 0; iForIa <NBFORIA; iForIa++)
				{
					srand(iForIa);
					tabIa[iForIa] = IAvDream(monIA.nbTour);
					resIa[iForIa] = tabIa[iForIa].nextCarte(htab,atout,player,i,bCard,colorPlay,0,winner);
					//cout << iForIa << ": " << resIa[iForIa] << endl;
				}
				map<Carte, int> m;
				
				for (int iForIa = 0; iForIa <NBFORIA; iForIa++)
				{
					Carte tmp = resIa[iForIa];
					if(m.find(tmp).operator==(m.end()))
					{
						m[tmp]=0;
					} 
					m[tmp]++;
				}
				int max = -1;
				Carte cardToPlay;
				for (std::map<Carte, int>::iterator it = m.begin(); it != m.end(); ++it)
				{
					//cout << it->first << it->second <<endl;
					if (it->second > max)
					{
						cardToPlay = it->first;
						max = it->second;
					}
				}

				//Carte cardToPlay = monIA.nextCarte(htab,atout,player,i,bCard,colorPlay,0,winner);

				//cout << "Part: " <<  monIA.partner << "play: " << monIA.partner << endl;
				cout << "La carte jouee est : " << cardToPlay << endl;
				scorePli += cardToPlay.getPoint();
				bool sup;
				sup = cardToPlay.isSuperieur(bCard);
				cout << cardToPlay << "est superieur a " << bCard << " ? => " << sup <<endl;
				if (sup)
				{
					bCard=cardToPlay;
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

					valide = monIA.isCarteValide(htab[player],tmp,colorPlay,atout,bCard,winner,player);
					while(!valide)
					{
						cout << "Carte non acceptee selon les regles du jeu ! " << endl;
						cout << "Joue quoi ? ";
						cin >> carteJoue;
						tmp=htab[player].listHand[carteJoue];
						
						cout << tmp << endl;
						valide = monIA.isCarteValide(htab[player],tmp,colorPlay,atout,bCard,winner,player);
					}
				}
				else
				{
					tmp = monIA.carteAuto(htab[player],colorPlay,atout,bCard,winner,player);
				}


				cout << "La carte jouee est : " << tmp << endl;
				scorePli += tmp.getPoint();
				bool sup;
				sup = tmp.isSuperieur(bCard);
				cout << tmp << "est superieur a " << bCard << " ? => " << sup <<endl;
				if (sup)
				{
					bCard=tmp;
					winner = player;
				}
				c[i] = tmp;
				htab[player].deleteCarte(tmp);
			}
			player = (player +1)%4;
		}
		monIA.delListCard(c, 4);
		if(nbTour < 4) 
			monIA.nbTour--;
		if(nbTour == 8) 
			scorePli +=10;
		cout << white << "Le gagnant du pli est : Joueur " << winner << " - Score du pli : " << scorePli << endl;
		if(winner == 0 || winner == 2) 
			scoreA += scorePli;
		else 
			scoreB += scorePli;
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
	int atoutGame = 1;
	int playerIA = 0;
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
	
	Carte tabCarte [4][8];
	for(int i = 0; i < 4; i++)
	{
		Carte newHand[8];
		for(int j = 0; j < 5; j++)
		{
			int posCarte = rand() %cartesRestantes.size();
			Carte tmp = cartesRestantes[posCarte];
			tabCarte[i][j]= tmp;
			newHand[j] = tmp;
			cartesRestantes.erase(cartesRestantes.begin() + posCarte);
		}
		tabHand[i] = Hand(newHand,5);
		tabHand[i].triAtout(atoutGame);
	}

	
	/*cout << "Alpha Beta : " << monIADream.minimaxAlphaBeta(0, 1, tabHand) << endl;
	cout << "Nb Coup : "<< monIADream.nbFin << endl;

	cout << "Retour de Carte : " << monIADream.nextCarte(tabHand[0], 1, 2, 0, Carte(), -1, 0) << endl;
	cout << "Nb Coup : "<< monIADream.nbFin << endl;*/

	int player;
	cout << "Belote : nouveau jeu" << endl;
	cout << "Choisir le joueur qui commence la partie (0 - 3) : ";
	cin >> player;
	
	monIADream.printGame(tabHand);

	int posCarteForAtout = rand() %cartesRestantes.size();
	Carte tmpForAtout = cartesRestantes[posCarteForAtout];
	
	cout << tmpForAtout << endl;

	atoutGame = assetManagement(tabCarte, monIADream, player, tmpForAtout, playerIA);

	cout << atoutGame << endl;

	setAtout(tabCarte, atoutGame);
	for(int i = 0; i < 4; i++)
	{
		Carte* newHand = tabCarte[i];
		for(int j = 5; j < 8; j++)
		{
			Carte tmp;
			int posCarte;
			if (i == player && j == 5)
			{
				tmp = tmpForAtout;
				posCarte = posCarteForAtout;
			}
			else 
			{
				posCarte = rand() %cartesRestantes.size();
				tmp = cartesRestantes[posCarte];
			}
			if (tmp.getColor() == atoutGame)
			{	
				tmp.setAtout();
			}
			newHand[j] = tmp;
			cartesRestantes.erase(cartesRestantes.begin() + posCarte);
		}
		tabHand[i] = Hand(newHand,8);
		tabHand[i].triAtout(atoutGame);
	}

	playGame(tabHand,monIADream, player, atoutGame);
	
	while(1);
	return 0;
}