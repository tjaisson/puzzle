/*
 * Etat.cpp
 *
 *  Created on: 17 déc. 2012
 *      Author:
 */

#include "Etape.h"

/*
 *  Implémentation de la classe Etat
 */

Etape *Etape::LEE = NULL;
Etape *Etape::LEAE = NULL;
Etape::Etape() : Suivant(NULL){};

void Etape::clear() {
	Etape *tmpEtape = Etape::LEE;
	while (tmpEtape != NULL) {
		Etape *tmpEtape2 = tmpEtape->Suivant;
		delete tmpEtape;
		tmpEtape = tmpEtape2;
	}
	Etape::LEE = NULL;
	tmpEtape = Etape::LEAE;
	while (tmpEtape != NULL) {
		Etape *tmpEtape2 = tmpEtape->Suivant;
		delete tmpEtape;
		tmpEtape = tmpEtape2;
	}
	Etape::LEAE = NULL;
};


Etape::~Etape(){
};

Etape *Etape::DerivParMouv(Mouv mv){
	Etat *tmpEtat;
	if ( ( ( tmpEtat=etat->DerivParMouv(mv) ) == 0 ) //le mouv est impossible
			|| ( tmpEtat->ref > 0 ) ) return 0;	   //ou ce n'est pas un nouveau damier
	tmpEtat->ref++;
	Etape *tmpEtape = new Etape;
	tmpEtape->etat = tmpEtat;
	tmpEtape->Parent = this;
	tmpEtape->m = mv;
	tmpEtape->g = g+1;
	tmpEtape->f = tmpEtape->g + tmpEtape->etat->h;
	return tmpEtape;
}

Etape *Etape::PopLEAE(){
	if(LEAE == NULL) return NULL;
	Etape *tmp;
	tmp = LEAE;
	LEAE = LEAE->Suivant;
	return tmp;
};
void Etape::PushInLEE(){
	this->Suivant = LEE;
	LEE = this;
};

void Etape::PushInLEAE(){
	Etape **pItem;
	pItem=&LEAE;
	for(;;){
		if( (*pItem == NULL) || ( f < (*pItem)->f ) || ( ( f == (*pItem)->f ) && ( etat->h <= (*pItem)->etat->h ) ) ){
			Suivant = *pItem;
			*pItem = this;
			return;
		};
		pItem = &((*pItem)->Suivant);
	}
};

void Etape::AfficheSol(ostream &sortie){
	if(Parent != 0) {
		Parent->AfficheSol(sortie);
		sortie << m << endl;
	}
	sortie << etat;
};
