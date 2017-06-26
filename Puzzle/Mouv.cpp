/*
 * Mouv.cpp
 *
 *  Created on: 16 déc. 2012
 *      Author:
 */

#include "Mouv.h"

Mouv operator-(Mouv m) {
	switch(m)
	{
	case NORD: return SUD;
	case EST: return OUEST;
	case SUD: return NORD;
	case OUEST: return EST;
	default: return RIEN;
	}
};

Mouv operator++(Mouv& m, int) {
	int temp = m;
	return m = static_cast<Mouv> (++temp);
};

ostream& operator<<(ostream &sortie, Mouv m){
	switch(m)
	{
	case NORD: return sortie << "NORD";
	case EST: return sortie << "EST";
	case SUD: return sortie << "SUD";
	case OUEST: return sortie << "OUEST";
	default: return sortie << "RIEN";
	}
};

