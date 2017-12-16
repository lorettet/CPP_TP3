/*************************************************************************
                           Trajet  -  Classe abstraite
                             -------------------
    début                : 13/11/2017
    copyright            : (C) 2017 par Théo Lorette-Froidevaux
			   Anatolii Gasiuk
    e-mail               : theo.lorette-froidevaux@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H ) 
#define TRAJET_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
// Contient les méthodes de base devant être implémentées dans des classes
// représentant des trajets.
//
//------------------------------------------------------------------------

class Trajet
{

//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


    virtual void Afficher() const = 0;
    // Mode d'emploi : Affiche les caractéristiques du trajet
    //
    // Contrat :
    //
	
    virtual const char* getVilleDepart() const =0;
    // Mode d'emploi : Renvoie la ville de départ du trajet
    //
    // Contrat :
    //

    virtual const char* getVilleArrivee() const =0;
    // Mode d'emploi : Renvoie le terminus du trajet
    //
    // Contrat :
    //
    
    virtual Trajet* Copy() const = 0;
    // Mode d'emploi : Renvoie une copie du trajet
    //
    // Contrat : 
    //

	virtual void Sauvegarder(ofstream &p, bool infoOnly=false) = 0;


	
//-------------------------------------------- Constructeurs - destructeur
    
    virtual ~Trajet ( ){}
    // Mode d'emploi :
    //
    // Contrat :
    //
	
//----------------------------------------------------------------- PROTECTED

protected:
//----------------------------------------------------- Méthodes protégées

};

#endif // TRAJET_H

