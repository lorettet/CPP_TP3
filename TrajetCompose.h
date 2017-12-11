/*************************************************************************
                           TrajetCompose  -  Trajet composé de sous-trajets
                             -------------------
    début                : 13/11/2017
    copyright            : (C) 2017 par Théo Lorette-Froidevaux
			   Anatolii Gasiuk
    e-mail               : theo.lorette-froidevaux@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
// Représente un trajet composé d'un ou de plusieurs objets de type Trajet.
//
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Afficher() const;
    // Mode d'emploi : Affiche les informations sur le trajet, incluant
    // toutes les escales.
    //
    // Contrat :
    //

    const char* getVilleArrivee() const;
    // Mode d'emploi : Renvoie la ville de départ.
    //
    // Contrat :
    //

    const char* getVilleDepart() const;
    // Mode d'emploi : Renvoie le terminus du trajet.
    //
    // Contrat :
    //

    TrajetCompose* Copy() const;
    // Mode d'emploi : Renvoie une copie du TrajetCompose
    // 
    // Contrat :
    //

	void Sauvegarder(ofstream & p, bool infoOnly=false);

//-------------------------------------------- Constructeurs - destructeur
    TrajetCompose( Trajet** trajets, unsigned int nb);
    // Mode d'emploi : Construit un trajet composé à partir de la liste de
    // trajets passée en paramètre. 
    // 
    // Contrat : Aucune vérification n'est effectué sur les données entrantes.
    //

    virtual ~TrajetCompose ( );
    // Mode d'emploi : Détruit chaque trajet puis se détruit.
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	Trajet** listeTrajets;
	const unsigned int nbTrajets;
};

//-------------------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TRAJETCOMPOSE_H

