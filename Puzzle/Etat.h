/*
 * Damier.h
 *
 *  Created on: 16 déc. 2012
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
 * Le damier est représenté en interne par une chaîne AZT
 *     E # C
 *     B D A    ->    "E#CBDA"
 *
 * L'emplacement de la case vide est indiqué par cCV et lCv
 *
 * Cette structure intègre les pointeurs nécessaires à la constitution d’un index
 * à base d'arbre :
 *      Index : pointeur static sur la racine de l'arbre
 *      g, d : pointeurs vers les branches g et d dans l'arbre
 */

struct Etat {
	static int n;	//nb colonnes
	static int m;	//nb lignes
	static int strSize;  // sera égal à n*m+1 pour ne pas le recalculer

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
 *  Surcharge des opérateurs de flot
 *  ********************************
 */
extern ostream& operator<<(ostream &sortie, Etat* D);

#endif /* ETAT_H_ */
