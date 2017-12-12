/*************************************************************************
Catalogue  -  R�pertoire de trajets
-------------------
d�but                : 13/11/2017
copyright            : (C) 2017 par Th�o Lorette-Froidevaux
Anatolii Gasiuk
e-mail               : theo.lorette-froidevaux@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilis�es
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
// Regroupe les donn�es n�cessaires � la cr�ation d'un trajet simple.
enum TypeTrajet {TOUS,TS,TC};

typedef struct Element
{
	Trajet *trajet;
	Element *suivant; 
	TypeTrajet type;
	
	
} Element;
// Repr�sente un �l�ment d'une liste chain�e

typedef struct
{
	Element *Tete;
} ListeChainee;
// Repr�sente le d�but d'une liste chain�e

//------------------------------------------------------------------------
// R�le de la classe <Catalogue>
// Repr�sente un ensemble de trajets, pouvant �tre agrandit, et int�gre 
// diverse foctionnalit�es de recherche. G�re les interactions avec
// l'utilisateur.
//
//------------------------------------------------------------------------

class Catalogue
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- M�thodes publiques
	void Run();
	// Mode d'emploi : Lance le programme permettant � l'utiisateur
	// d'utiliser l'application par l'interm�diaire d'une petite
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
	// Mode d'emploi : d�truit tous les trajets du catalogue puis se 
	// d�truit.
	//
	// Contrat :
	//

	//------------------------------------------------------------------ PRIVE
	private:
	
	static vector<string> split(string param, char delimiteur);


	protected:
	//----------------------------------------------------- M�thodes prot�g�es

	bool Ajouter(const char *villeDep, const char *villeArr, const char *moyenTransport);
	// Mode d'emploi : Construit et ajoute un trajet simple au catalogue
	// villeDep : la ville de d�part
	// villeArr : la ville d'arriv�e
	// moyenTransport : le moyen de transport utilis�
	// retour : bool�en indiquant si le trajet � bien �t� ajout�.
	// Contrat : V�rifie la coh�rence des informations (villeDep!=villeArr)
	//

	void Afficher() const;
	// Mode d'emploi : Affiche tous les trajets du catalogue
	//
	// Contrat :
	//

	void RechercheAvancee(const char* villeDep, const char* villeArr) const;
	// Mode d'emploi : Recherche tous les trajets pouvant correspondre 
        // � l'itini�raire demand� en combinant des trajets d�j� existants.
	//
	// Contrat :
	//

	void Recherche(const char *villeDep, const char *villeArr) const;
	// Mode d'emploi : Recherche et affiche tous les trajets dont la ville
	// de d�part est villeDep et la ville d'arriver est villeArr.
	// villeDep : la ville de d�part d�sir�e
	// villeArr : la ville d'arriv�e d�sir�e 
	// Contrat :
	//

	bool Ajouter(const UnTrajetSimple *listeTrajetSimple, unsigned int tailleListe);
	// Mode d'emploi : Construit et ajoute un trajet compos� au catalogue.
	// listeTrajetSimple : la liste des informations de chaque trajet simple
	// � ajouter.
	// tailleListe : la taille de cette liste
	// retour : bool�en indiquant si le trajet a �t� ajout�.
	// Contrat : V�rifie que pour chaque trajet simple, villeDep!=villeArr. 
	// Ne v�rifie pas que la ville d'arriv�e d'un trajet, correspond �
	// la ville de d�part du prochain trajet.
	//
	void EnregistrerCatalogue(string nomFichier, TypeTrajet);
	
	void EnregistrerCatalogue(string nomFichier, string villeDep, string villeArr="");
	
	void EnregistrerCatalogue(string nomFichier, unsigned int deb, unsigned int fin);

	
	void importer(string nomFicher, TypeTrajet type = TOUS);
	
	void importer(string nomFichier, string villeD, string villeA="");
	//----------------------------------------------------- Attributs prot�g�s
	ListeChainee listeTrajets;
	unsigned int nbTrajets;
};

//-------------------------------- Autres d�finitions d�pendantes de <Catalogue>

#endif // CATALOGUE_H

