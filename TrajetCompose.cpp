/*************************************************************************
                           TrajetCompose  -  Trajet composé de sous-trajets
                             -------------------
    début                : 13/11/2017
    copyright            : (C) 2017 par Théo Lorette-Froidevaux
			   Anatolii Gasiuk
    e-mail               : theo.lorette-froidevaux@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void TrajetCompose::Afficher() const
// Algorithme : 
//
{
	for(unsigned int i = 0; i<nbTrajets-1; i++)
	{
		listeTrajets[i]->Afficher();
		cout << " - ";
	}
	listeTrajets[nbTrajets-1]->Afficher();
}

const char* TrajetCompose::getVilleArrivee() const
{
	return listeTrajets[nbTrajets-1]->getVilleArrivee();
}

const char* TrajetCompose::getVilleDepart() const
{
	return listeTrajets[0]->getVilleDepart();
} 

TrajetCompose* TrajetCompose::Copy() const
{
// Algorithme : Copie chaque trajet et renvoie un nouveau trajet composé.
//
#ifdef MAP
    cout << "Appel au constructeur de copie virtuel <TrajetCompose>" << endl;
#endif
	Trajet** lesTrajets = new Trajet*[nbTrajets];
	for(unsigned int i = 0; i<nbTrajets; i++)
	{
		lesTrajets[i] = listeTrajets[i]->Copy();
	}
	return new TrajetCompose(lesTrajets,nbTrajets);
} 

void TrajetCompose::Sauvegarder(ofstream & p, bool infoOnly)
{
	 if(!infoOnly)
	 {
		p<<nbTrajets<<";"<<getVilleDepart()<<";"<<getVilleArrivee()<<endl;
	 }
	 for(unsigned int i(0); i<nbTrajets;i++)
	 {
		 listeTrajets[i]->Sauvegarder(p,true);
	 }
}

//-------------------------------------------- Constructeurs - destructeur
TrajetCompose::TrajetCompose ( Trajet** trajets, unsigned int nb ) : nbTrajets(nb)
{
// Algorithme : 
//
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
	listeTrajets = new Trajet*[nb];
	for(unsigned int i = 0; i < nb; i++)
	{
		listeTrajets[i] = trajets[i]->Copy();
	}
} // ------ Fin de TrajetCompose


TrajetCompose::~TrajetCompose ( )
{
// Algorithme :
//
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
	for(unsigned int i = 0; i<nbTrajets; i++)
	{
		delete listeTrajets[i];
	}
	delete [] listeTrajets;
} //----- Fin de ~TrajetCompose


//------------------------------------------------------------------ PROTECTED

//----------------------------------------------------- Méthodes protégées

