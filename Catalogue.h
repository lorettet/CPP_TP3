/*************************************************************************
Catalogue  -  Répertoire de trajets
-------------------
début                : 13/11/2017
copyright            : (C) 2017 par Théo Lorette-Froidevaux
Anatolii Gasiuk
e-mail               : theo.lorette-froidevaux@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include <string>
#include <vector>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef struct
{
	char *villeDep;
	char *villeArr;
	char *moyenTransport;

} UnTrajetSimple;
// Regroupe les données nécessaires à la création d'un trajet simple.
enum TypeTrajet {TOUS,TS,TC};

typedef struct Element
{
	Trajet *trajet;
	Element *suivant; 
	TypeTrajet type;
	
	
} Element;
// Représente un élément d'une liste chainée

typedef struct
{
	Element *Tete;
} ListeChainee;
// Représente le début d'une liste chainée

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
// Représente un ensemble de trajets, pouvant être agrandit, et intègre 
// diverse foctionnalitées de recherche. Gère les interactions avec
// l'utilisateur.
//
//------------------------------------------------------------------------

class Catalogue
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Méthodes publiques
	void Run();
	// Mode d'emploi : Lance le programme permettant à l'utiisateur
	// d'utiliser l'application par l'intermédiaire d'une petite
	// interface dans la console.
	//
	// Contrat :
	//

	//-------------------------------------------- Constructeurs - destructeur
	Catalogue();
	// Mode d'emploi : Construit un Catalogue vide
	//
	// Contrat :
	//

	virtual ~Catalogue();
	// Mode d'emploi : détruit tous les trajets du catalogue puis se 
	// détruit.
	//
	// Contrat :
	//

	//------------------------------------------------------------------ PRIVE
	private:
	
	static vector<string> split(string param, char delimiteur);


	protected:
	//----------------------------------------------------- Méthodes protégées

	bool Ajouter(const char *villeDep, const char *villeArr, const char *moyenTransport);
	// Mode d'emploi : Construit et ajoute un trajet simple au catalogue
	// villeDep : la ville de départ
	// villeArr : la ville d'arrivée
	// moyenTransport : le moyen de transport utilisé
	// retour : booléen indiquant si le trajet à bien été ajouté.
	// Contrat : Vérifie la cohérence des informations (villeDep!=villeArr)
	//

	void Afficher() const;
	// Mode d'emploi : Affiche tous les trajets du catalogue
	//
	// Contrat :
	//

	void RechercheAvancee(const char* villeDep, const char* villeArr) const;
	// Mode d'emploi : Recherche tous les trajets pouvant correspondre 
        // à l'itiniéraire demandé en combinant des trajets déjà existants.
	//
	// Contrat :
	//

	void Recherche(const char *villeDep, const char *villeArr) const;
	// Mode d'emploi : Recherche et affiche tous les trajets dont la ville
	// de départ est villeDep et la ville d'arriver est villeArr.
	// villeDep : la ville de départ désirée
	// villeArr : la ville d'arrivée désirée 
	// Contrat :
	//

	bool Ajouter(const UnTrajetSimple *listeTrajetSimple, unsigned int tailleListe);
	// Mode d'emploi : Construit et ajoute un trajet composé au catalogue.
	// listeTrajetSimple : la liste des informations de chaque trajet simple
	// à ajouter.
	// tailleListe : la taille de cette liste
	// retour : booléen indiquant si le trajet a été ajouté.
	// Contrat : Vérifie que pour chaque trajet simple, villeDep!=villeArr. 
	// Ne vérifie pas que la ville d'arrivée d'un trajet, correspond à
	// la ville de départ du prochain trajet.
	//
	void EnregistrerCatalogue(string nomFichier, TypeTrajet);
	
	void EnregistrerCatalogue(string nomFichier, string villeDep, string villeArr="");
	
	void EnregistrerCatalogue(string nomFichier, unsigned int deb, unsigned int fin);

	
	void importer(string nomFicher, TypeTrajet type = TOUS);
	
	void importer(string nomFichier, string villeD, string villeA="");
	//----------------------------------------------------- Attributs protégés
	ListeChainee listeTrajets;
	unsigned int nbTrajets;
};

//-------------------------------- Autres définitions dépendantes de <Catalogue>

#endif // CATALOGUE_H

