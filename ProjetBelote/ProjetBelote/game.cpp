#include <Windows.h>
#include <iostream>
#include "carte.h"
#include "paquet.h"
#include <string>
#include "Hand.h"
#include "IA.h"

using namespace std;
int main()  {

	Paquet p = Paquet();

	Carte tas [8];
	for(int i=0;i<8; i++)
	{
		Carte c = Carte(Carte::AS-i,Carte::PIQUE);
		tas[i]= c;
		p.jeu[i+Carte::PIQUE* 8] = 0;
	}
	Hand h = Hand(tas, sizeof(tas)/sizeof(Carte));
	IA monIA = IA(h,p);	
	for(int i = 0; i< 4; i++)
	{
		cout << "Hand " << i << " --------------" << endl;
		for(int j = 0; j<8; j++)
		{
			//cout << "Carte " << j << " : " << monIA.allHands[i].listHand[j].getValue() << monIA.allHands[i].listHand[j].getColor() << endl;
			cout << "Carte " << j << " : " << monIA.allHands[i].listHand[j] << endl;
		}
	}
	while(1);
	return 0;
}