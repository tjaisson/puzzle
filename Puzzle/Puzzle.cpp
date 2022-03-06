// Puzzle.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Mouv.h"
#include "Etat.h"
#include "Etape.h"

using namespace std;

void AfficheSol(ostream &s, Etape &e) {
	s << "Damier : " << e.etat->m << " lignes, " << e.etat->n << " colonnes" << endl;
	s << "solution en " << e.g << " mouvements" << endl;
	e.AfficheSol(s);
};

void AffichePasSol(ostream &s) {
	s << "Le puzzle n'a pas de solution" << endl;
};

int main2() {
	ifstream fin;
	fin.open("..\\Puzzle\\damier.txt");
	Etat::init(fin);
	fin.close();

	Etape *tmpEtape = new Etape;
	tmpEtape->etat = Etat::Index;
	tmpEtape->etat->ref++;
	tmpEtape->Parent = NULL;
	tmpEtape->g = 0;
	tmpEtape->f = tmpEtape->etat->h;
	tmpEtape->m = RIEN;
	tmpEtape->PushInLEAE();

	bool SolTrouv = false;
	Mouv mv, mContr;
	Etape *EtapeCourante;
	while ((EtapeCourante = Etape::PopLEAE()) != NULL) {
		EtapeCourante->PushInLEE();
		if (EtapeCourante->etat->h == 0) {
			SolTrouv = true;
			break;
		}
		else {
			mContr = -EtapeCourante->m;
			for (mv = NORD; mv <= OUEST; mv++) {
				if ((mv != mContr) && ((tmpEtape = EtapeCourante->DerivParMouv(mv)) != NULL)) {
					tmpEtape->PushInLEAE();
				}
			}
		}
	}
	if (SolTrouv) {
		AfficheSol(cout, *EtapeCourante);
	}
	else {
		AffichePasSol(cout);
	}
	Etape::clear();
	Etat::clear();
	return 0;
}


int main()
{
    return main2();
}
