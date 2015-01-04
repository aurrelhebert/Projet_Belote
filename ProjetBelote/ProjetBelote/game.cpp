#include <Windows.h>
#include <iostream>
#include "carte.h"
#include "paquet.h"
#include <string>
#include "Hand.h"
#include "IA.h"
#include "IAvDream.h"

using namespace std;
int main()  {
	
	srand(time(NULL));

	Paquet p = Paquet();
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
	IA monIA = IA(h,p, Carte::CARREAU);	
	for(int i = 0; i< 4; i++)
	{
		cout << "Hand " << i << " --------------" << endl;
		for(int j = 0; j<8; j++)
		{
			//cout << "Carte " << j << " : " << monIA.allHands[i].listHand[j].getValue() << monIA.allHands[i].listHand[j].getColor() << endl;
			cout << "Carte " << j << " : " << monIA.allHands[i].listHand[j] << endl;
		}
	}
	//cout << monIA.minimax(0) << endl;
	IAvDream monIADream = IAvDream();
	Hand tabHand[4];
	tabHand[0] = h;

	Carte tas2 [8];
	for(int i=0;i<8; i++)
	{
		Carte c = Carte(Carte::AS-i,Carte::CARREAU);
		tas2[i]= c;
	}
	Hand h2 = Hand(tas2, sizeof(tas2)/sizeof(Carte));
	tabHand[1] = h2;

	Carte tas3 [8];
	for(int i=0;i<8; i++)
	{
		Carte c = Carte(Carte::AS-i,Carte::COEUR);
		tas3[i]= c;
	}
	Hand h3 = Hand(tas3, sizeof(tas3)/sizeof(Carte));
	tabHand[2] = h3;

	Carte tas4 [8];
	for(int i=0;i<8; i++)
	{
		Carte c = Carte(Carte::AS-i,Carte::TREFLE);
		tas4[i]= c;
	}
	Hand h4 = Hand(tas4, sizeof(tas4)/sizeof(Carte));
	tabHand[3] = h4;



	cout << monIADream.minimax(0, 1, tabHand) << endl;
	
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
	}

	for(int i = 0; i< 4; i++)
	{
		cout << "Hand " << i << " --------------" << endl;
		for(int j = 0; j<8; j++)
		{
			//cout << "Carte " << j << " : " << monIA.allHands[i].listHand[j].getValue() << monIA.allHands[i].listHand[j].getColor() << endl;
			cout << "Carte " << j << " : " << tabHand[i].listHand[j] << " " << tabHand[i].listHand[j].getPoint() << endl;
			point += tabHand[i].listHand[j].getPoint();
		}
	}
	cout << "Total : " << point << endl;
	cout << monIADream.minimax(0, 1, tabHand) << endl;
	while(1);
	return 0;
}