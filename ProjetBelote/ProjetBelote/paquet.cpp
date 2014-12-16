#include "paquet.h"

Paquet::Paquet()
{	
	int pos = 0;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<8; j++)
		{
			//Carte c = Carte(j,i);
			jeu[pos++] = 1;
		}
	}

}