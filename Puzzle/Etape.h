/*
 * Etat.h
 *
 *  Created on: 16 d�c. 2012
 *      Author:
 */

#ifndef ETAPE_H_
#define ETAPE_H_

#include "stdafx.h"

using namespace std;


#include "Mouv.h"
#include "Etat.h"


/*
 *   Classe Etape
 *Membres
 *	Etat *etat		: pointeur sur la structure Damier qui repr�sente la position des cases (cf. Damier.h)
 *	Etape *Parent	: pointeur sur l'�tat parent. Celui dont est issu cet �tat. Vaut 0 pour l'�tat initial
 *	Mouv m			: mouvement ayant fait passer de l'�tat parent � cet �tat
 *	int g			: nombre de mouvement depuis l'�tat initial
 *	int f			: heuristique f=g+Dam->h (pour �viter de recalculer f dans les boucles)
 *
 *
 *	Etat *Suivant	: pointeur sur l'�tat suivant dans les chainnages des listes LEE et LEAE
 *
 *Methodes
 *  Etpe *DerivParMouv(Mouv mv);
 *  				: cr�e un nouvel objet Etat d'apr�s un mouvement. Retourne 0 si le mouvement est impossible
 *  				: ou si le Damier obtenu est d�j� affect� � un �tat
 *
 *Membres static
 *	static Etape *LEE, *LEAE
 *					: Points de d�part des listes LEE et LEAE
 *
 *Methodes static
 *  static Etape *PopLEAE();
 *  				: d�pile la liste LEAE
 */

struct Etape {
	Etat *etat;
	Etape *Parent;
	Mouv m;
	int g, f;

	Etape();
	~Etape();

	static void clear();

	Etape *DerivParMouv(Mouv mv);

	Etape *Suivant;
	static Etape *LEE, *LEAE;
	static Etape *PopLEAE();
	void PushInLEE();
	void PushInLEAE();
	void AfficheSol(ostream &sortie);
};


#endif /* ETAPE_H_ */
