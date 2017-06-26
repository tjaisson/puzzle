/*
 * Etat.h
 *
 *  Created on: 16 déc. 2012
 *      Author:
 */

#ifndef ETAPE_H_
#define ETAPE_H_

#include "stdafx.h"

using namespace std;


#include "Mouv.h"
#include "Etat.h"


/*
 *   Classe Etat
 *Membres
 *	Damier *Dam		: pointeur sur la structure Damier qui représente la position des cases (cf. Damier.h)
 *	Etat *Parent	: pointeur sur l'état parent. Celui dont est issu cet état. Vaut 0 pour l'état initial
 *	Mouv m			: mouvement ayant fait passer de l'état parent à cet état
 *	int g			: nombre de mouvement depuis l'état initial
 *	int f			: heuristique f=g+Dam->h (pour éviter de recalculer f dans les boucles)
 *
 *
 *	Etat *Suivant	: pointeur sur l'état suivant dans les chainnages des listes LEE et LEAE
 *
 *Methodes
 *  Etat *DerivParMouv(Mouv mv);
 *  				: crée un nouvel objet Etat d'après un mouvement. Retourne 0 si le mouvement est impossible
 *  				: ou si le Damier obtenu est déjà affecté à un état
 *
 *Membres static
 *	static Etat *LEE, *LEAE
 *					: Points de départ des listes LEE et LEAE
 *
 *Methodes static
 *  static Etat *PopLEAE();
 *  				: dépile la liste LEAE
 */

struct Etape {
	Etat *etat;
	Etape *Parent;
	Mouv m;
	int g,f;

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
