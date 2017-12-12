/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : theo.lorette-froidevaux@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void TrajetSimple::Afficher() const
// Algorithe : 
//
{
	cout << "De " << villeDepart << " à " << villeArrivee << " en " << moyenTransport << endl;
}

const char* TrajetSimple::getVilleArrivee() const
// Algorithme : 
//
{
	return villeArrivee;
}

const char* TrajetSimple::getVilleDepart() const
// Algorithme : 
//
{
	return villeDepart;
} 

Trajet* TrajetSimple::Copy() const
// Algorithme : 
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie virtuel de <TrajetSimple>" << endl;
#endif
	return new TrajetSimple(villeDepart,villeArrivee,moyenTransport);
}

void TrajetSimple::Sauvegarder(ofstream &p, bool infoOnly)
{
	
	if(!infoOnly)
	{
		p<<"1;"<<villeDepart<<";"<<villeArrivee<<endl;
	}
	p<<villeDepart<<";"<<villeArrivee<<";"<<moyenTransport<<endl;
		
}


//-------------------------------------------- Constructeurs - destructeur

TrajetSimple::TrajetSimple(const char *villeDep, const char *villeArr, const char *moyenTransp)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
	char* newVilleDepart = new char[strlen(villeDep)+1];
	strcpy(newVilleDepart,villeDep);
	villeDepart = newVilleDepart;

	char* newVilleArrivee = new char[strlen(villeArr)+1];
	strcpy(newVilleArrivee,villeArr);
	villeArrivee = newVilleArrivee;

	char* newMoyenTransport = new char[strlen(moyenTransp)+1];
	strcpy(newMoyenTransport,moyenTransp);
	moyenTransport = newMoyenTransport;

} //----- Fin de TrajetSimple (constructeur de copie)

TrajetSimple::~TrajetSimple ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
	delete [] villeDepart;
	delete [] villeArrivee;
	delete [] moyenTransport;
} //----- Fin de ~TrajetSimple


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

