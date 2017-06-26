/*
 * Damier.cpp
 *
 *  Created on: 16 déc. 2012
 *      Author:
 */

#include "Etat.h"

/*
 * Implémentation de la classe Etat
 */
	int Etat::n = 0;
	int Etat::m = 0;
	int Etat::strSize;
	Etat *Etat::Index = NULL;

    void Etat::clear(){
    	if (Index != NULL) delete Index;
    	Index = NULL;
    };

    Etat::Etat() :g(0),d(0),ref(0){};
    Etat::~Etat() {
    	delete Str;
    	if(g != NULL) delete g;
    	if(d != NULL) delete d;
    };

    Etat *Etat::DerivParMouv(Mouv mv){
    	int     tmplCV = lCV,
    			tmpcCV = cCV,
    			tmpiCV;

    	switch(mv) {
    	 case NORD:
    		 tmplCV--;
    		 if(tmplCV < 0) return NULL; //Mouv impossible
    		 tmpiCV = iCV - n;
    		 break;
    	 case EST:
    		 tmpcCV++;
    		 if(tmpcCV >= n) return NULL; //Mouv impossible
    		 tmpiCV = iCV + 1;
    		 break;
    	 case SUD:
    		 tmplCV++;
    		 if(tmplCV >= m) return NULL; //Mouv impossible
    		 tmpiCV = iCV + n;
    		 break;
    	 case OUEST:
    		 tmpcCV--;
    		 if(tmpcCV < 0) return NULL; //Mouv impossible
    		 tmpiCV = iCV - 1;
    		 break;
    	 default: return this;
    	}
    	char *tmpStr;
    	tmpStr = new char[strSize];
    	memcpy(tmpStr,Str,strSize);
    	tmpStr[tmpiCV]=Str[iCV];
    	tmpStr[iCV]=Str[tmpiCV];

    	Etat **pItem;
    	pItem = &Index;
    	int comp;
    	for(;;){
    		if(*pItem == NULL){
    			*pItem = new Etat;
    			(*pItem)->Str = tmpStr;
    	    	(*pItem)->cCV = tmpcCV;
    	    	(*pItem)->lCV = tmplCV;
    	    	(*pItem)->iCV = tmpiCV;

    	    	switch(mv) {
    	    	 case NORD:
    	    		 if( ( (tmpStr[iCV]-'A')/n) >= lCV ) (*pItem)->h = h - 1;
    	    		 else  (*pItem)->h = h + 1;
   	    			 return *pItem;
    	    	 case EST:
    	    		 if( ( (tmpStr[iCV]-'A')%n) <= cCV ) (*pItem)->h = h - 1;
    	    		 else  (*pItem)->h = h + 1;
   	    			 return *pItem;
    	    	 case SUD:
    	    		 if( ( (tmpStr[iCV]-'A')/n) <= lCV ) (*pItem)->h = h - 1;
    	    		 else  (*pItem)->h = h + 1;
   	    			 return *pItem;
    	    	 case OUEST:
    	    		 if( ( (tmpStr[iCV]-'A')%n) >= cCV ) (*pItem)->h = h - 1;
    	    		 else  (*pItem)->h = h + 1;
   	    			 return *pItem;
    	    	}
    		}
    		comp = strcmp((*pItem)->Str,tmpStr);
    		if(comp == 0){
    			delete tmpStr;
    			return *pItem;
    		}
    		if(comp > 0) pItem = &((*pItem)->g);
    		else  pItem = &((*pItem)->d);
    	};
   };

ostream& operator<<(ostream &sortie, Etat* D){
	int i,j,k;
	for(j=0;j<D->m;j++){
		sortie << " ";
		k=j*D->n;
		for(i=0;i<D->n;i++) sortie << " " << D->Str[k+i];
		sortie << endl;
	}
	return sortie;
};



void Etat::init(istream &entree){
	clear();
	entree >> m >> n;
	strSize = n*m+1;
	Index = new Etat;
	Index->Str = new char[strSize];
	Index->h = 0;
	int i = 0,l,c;
	char tmp;
	for(l=0;l<m;l++)
	for(c=0;c<n;c++) {
		entree >> tmp;
		Index->Str[i]=tmp;
		if(tmp == '#'){
			Index->cCV=i%n; // devrait être égal à c
			Index->lCV=i/n; // devrait être égal à l
			Index->iCV=i;
		} else {
			Index->h = Index->h + abs( ((tmp-'A')%n) - c);
			Index->h = Index->h + abs( ((tmp-'A')/n) - l);
		}
		i++;
	}
	Index->Str[i] = '\0';
};

