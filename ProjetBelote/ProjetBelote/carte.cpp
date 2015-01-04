#include "carte.h"
#include <string>

Carte::Carte()
{
	value = -1;
	color = -1;
	point = -1;
	isAtout = false;
}

Carte::Carte(int v, int c)
{
	value = v;
	color = c;
	isAtout = false;
	switch(v)
	{
	case SEPT:
	case HUIT:
	case NEUF:
		{
			point = 0;
			break;
		}
	case VALET:
		{
			point = 2;
			break;
		}
	case DAME:
		{
			point = 3;
			break;
		}
	case ROI:
		{
			point = 4;
			break;
		}
	case DIX:
		{
			point = 10;
			break;
		}
	case AS:
		{
			point = 11;
		}
	}
}

int Carte::getValue() const
{	
	return value;
}


int Carte::getColor() const
{	
	return color;
}

int Carte::getPoint() const
{	
	return point;
}
void Carte::setAtout()
{
	isAtout = true;
	if(value == VALET) point = 20;
	else if(value == NEUF) point = 14;
}

bool operator==(const Carte& lhs, const Carte& rhs) 
{
    return lhs.getValue() == rhs.getValue() && lhs.getColor() == rhs.getColor();
}

ostream& operator<<(ostream & str, Carte const & c)
{
	str << "Carte : ";
	switch(c.getValue())
	{
	case Carte::SEPT:
		{
		str << "Sept ";
		break;
		}
	case Carte::HUIT:
		{
		str << "Huit ";
		break;
		}
	case Carte::NEUF:
		{
			str << "Neuf ";
		break;
		}
	case Carte::VALET:
		{
			str << "Valet ";
		break;
		}
	case Carte::DAME:
		{
			str << "Dame ";
		break;
		}
	case Carte::ROI:
		{
			str << "Roi ";
		break;
		}
	case Carte::DIX:
		{
			str << "Dix ";
		break;
		}
	case Carte::AS:
		{
			str << "As ";
		break;
		}
	}
	switch(c.getColor())
	{
	case Carte::COEUR:
		{
		str << "Coeur";
		break;
		}
	case Carte::PIQUE:
		{
		str << "Pique ";
		break;
		}
	case Carte::CARREAU:
		{
			str << "Carreau ";
		break;
		}
	case Carte::TREFLE:
		{
			str << "Trefle ";
		break;
		}
	}
	return str;
}