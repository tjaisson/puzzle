/*
 * Mouv.h
 *
 *  Created on: 16 déc. 2012
 *      Author:
 */

#ifndef MOUV_H_
#define MOUV_H_

#include "stdafx.h"

using namespace std;

enum Mouv {NORD=0, EST=1, SUD=2, OUEST=3, RIEN};

extern inline Mouv operator-(Mouv m);
extern inline Mouv operator++(Mouv& m, int);
extern inline ostream& operator<<(ostream &sortie, Mouv m);

#endif /* MOUV_H_ */
