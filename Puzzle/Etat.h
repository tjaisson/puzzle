/*
 * Damier.h
 *
 *  Created on: 16 d�c. 2012
 *      Author:
 */

#ifndef ETAT_H_
#define ETAT_H_

#include "stdafx.h"

using namespace std;

#include "Mouv.h"

/*
 *****************************************
 *             Classe Etat             *
 *****************************************
 *
 * Le damier est repr�sent� en interne par une cha�ne AZT
 *     E # C
 *     B D A    ->    "E#CBDA"
 *
 * L'emplacement de la case vide est indiqu� par cCV et lCv
 *
 * Cette structure int�gre les pointeurs n�cessaires � la constitution d�un index
 * � base d'arbre :
 *      Index : pointeur static sur la racine de l'arbre
 *      g, d : pointeurs vers les branches g et d dans l'arbre
 */

struct Etat {
	static int n;	//nb colonnes
	static int m;	//nb lignes
	static int strSize;  // sera �gal � n*m+1 pour ne pas le recalculer

	static Etat *Index;
    Etat *g,*d;
    static void clear();
    static void init(istream &entree);

    Etat *DerivParMouv(Mouv mv);

    char *Str;
    int cCV, lCV, iCV;
    int h;
    int ref;
    Etat();
    ~Etat();
};

/*
 *  Surcharge des op�rateurs de flot
 *  ********************************
 */
extern ostream& operator<<(ostream &sortie, Etat* D);

#endif /* ETAT_H_ */
