/*************************************************************************
Catalogue  -  description
-------------------
début                : 13/11/2017
copyright            : (C) 2017 par Théo Lorette-Froidevaux
Anatolii Gasiuk
e-mail               : theo.lorette-froidevaux@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
//------------------------------------------------------ Include personnel
#include "Catalogue.h"

//------------------------------------------------------------- Constantes
#define TAILLE_BUFFER_CLAVIER 20
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool Catalogue::Ajouter(const char *villeDep, const char *villeArr, const char *moyenTransport)
// Algorithme : Créer un objet TrajetSimple et l'ajoute dans la liste chainée
//
{
	if (strcmp(villeDep, villeArr) == 0)
		return false;

	Element* ptr = new Element;
	ptr->trajet = new TrajetSimple(villeDep, villeArr, moyenTransport);
	ptr->suivant = NULL;
	ptr->type=TS;
	if (listeTrajets.Tete == NULL)
	{
		listeTrajets.Tete = ptr;
		nbTrajets++;
		return true;
	}
	Element* ptrRech = listeTrajets.Tete;
	while (ptrRech->suivant != NULL)
	{
		ptrRech = ptrRech->suivant;
	}
	ptrRech->suivant = ptr;
	nbTrajets++;
	return true;
}

bool Catalogue::Ajouter(const UnTrajetSimple *listeTrajetSimple, unsigned int tailleListe)
// Algorithme : pour chaque membre de la liste de UnTrajetSimple, créer l'objet TrajetSimple
// associé. Créer l'objet TrajetCompose à partir des objets TrajetSimple et enfin l'ajoute à
// la liste chainée.
{
	for (unsigned int i = 0; i<tailleListe; i++)
	{
		if (strcmp(listeTrajetSimple[i].villeDep, listeTrajetSimple[i].villeArr) == 0)
			return false;
	}

	Trajet** lesTrajets = new Trajet*[tailleListe];
	for (unsigned int i = 0; i<tailleListe; i++)
	{
		lesTrajets[i] = new TrajetSimple(listeTrajetSimple[i].villeDep, listeTrajetSimple[i].villeArr, listeTrajetSimple[i].moyenTransport);
	}
	Element* elem = new Element;
	elem->suivant = NULL;
	elem->trajet = new TrajetCompose(lesTrajets, tailleListe);
	elem->type=TC;
	Element* ptr = listeTrajets.Tete;
	if (ptr == NULL)
	{
		listeTrajets.Tete = elem;
	}
	else {
		while (ptr->suivant != NULL)
			ptr = ptr->suivant;
		ptr->suivant = elem;
	}
	for (unsigned int i = 0; i<tailleListe; i++)
	{
		delete lesTrajets[i];
	}
	delete[] lesTrajets;
	nbTrajets++;
	return true;
}

void Catalogue::Afficher() const
// Algorithme : Pour chaque trajet de la liste chainée, affiche le trajet.
//
{
	if (listeTrajets.Tete == NULL)
	{
		cout << "Aucun trajet planifié" << endl;
		return;
	}
	Element* ptr = listeTrajets.Tete;
	int i = 1;
	while (ptr != NULL)
	{
		cout << "- Trajet " << i++ << " ------------------------------------------" << endl;
		ptr->trajet->Afficher();
		ptr = ptr->suivant;
	}
}



void Catalogue::Run()
// Algorithme : Affiche la liste d'instructions possible, puis exécute l'instruction en fonction
// des données entrées par l'utilisateur. Se processus est répété tant que l'utiisateur ne quitte
// pas l'application.
//
{
	cout << "\t\t\t Bonjour, bienvenue dans le GPS de Timtim." << endl << endl;
	cout << "#####################################################################################" << endl;
	cout << "#########               #    #   ######   ##               #   #   ######   #########" << endl;
	cout << "#########               #    #    ####    ##               #   #    ####    #########" << endl;
	cout << "###############   #######    #   # ## #   ########   #######   #   # ## #   #########" << endl;
	cout << "###############   #######    #   ##  ##   ########   #######   #   ##  ##   #########" << endl;
	cout << "###############   #######    #   ######   ########   #######   #   ######   #########" << endl;
	cout << "###############   #######    #   ######   ########   #######   #   ######   #########" << endl;
	cout << "###############   #######    #   ######   ########   #######   #   ######   #########" << endl;
	cout << "#####################################################################################" << endl << endl;

	char villeDep[TAILLE_BUFFER_CLAVIER];
	char villeArr[TAILLE_BUFFER_CLAVIER];
	char moyenTransport[TAILLE_BUFFER_CLAVIER];
	int commande;
	while (true)
	{
		cout << "\t\t\t\tVoici la liste de commandes: " << endl << endl;
		cout << "\t\t\t\t 0 - Afficher la liste de trajets" << endl;
		cout << "\t\t\t\t 1 - Entrer un trajet simple" << endl;
		cout << "\t\t\t\t 2 - Entrer un trajet composé" << endl;
		cout << "\t\t\t\t 3 - Rechercher un trajet" << endl;
		cout << "\t\t\t\t 4 - Recherche avancée de trajet" << endl << endl;
		cout << "\t\t\t\t 5 - Quitter l'application" << endl << endl;
		cout << "\t\t\t\t 6 - Sauvegarder" << endl << endl;
		cout << "\t\t\t\t 7 - Lecture" << endl << endl;

		cin >> commande;
		switch (commande)
		{
		case 0:
			this->Afficher();
			break;

		case 1:
			cout << "Veuillez entrer la ville de départ, la ville d'arrivée et le transport correspondant : " << endl;
			cin >> villeDep;
			cin >> villeArr;
			cin >> moyenTransport;

			if (Ajouter(villeDep, villeArr, moyenTransport))
				cout << "Trajet ajouté avec succès!" << endl;
			else
				cout << "Erreur lors de l'ajout du trajet... :(" << endl;
			break;

		case 2:
		{
			cout << "Veuillez rentrer le nombre de trajets simples avec leur moyen de transport" << endl;
			int nbrTrajets;
			cin >> nbrTrajets;
			UnTrajetSimple* liste = new UnTrajetSimple[nbrTrajets];
			cin >> villeDep;
			for (int i(0); i<nbrTrajets; i++)
			{
				cin >> villeArr;
				cin >> moyenTransport;

				liste[i].villeDep = new char[20];
				liste[i].villeArr = new char[20];
				liste[i].moyenTransport = new char[20];

				strcpy(liste[i].villeDep, villeDep);

				strcpy(liste[i].villeArr, villeArr);

				strcpy(liste[i].moyenTransport, moyenTransport);

				strcpy(villeDep, villeArr);
			}
			if (Ajouter(liste, nbrTrajets))
				cout << "Trajet ajouté avec succès!" << endl;
			else
				cout << "Erreur lors de l'ajout du trajet... :(" << endl;

			for (int i(0); i<nbrTrajets; i++)
			{
				delete[] liste[i].villeDep;
				delete[] liste[i].villeArr;
				delete[] liste[i].moyenTransport;
			}
			delete[] liste;
		}
		break;

		case 3:
			cout << "Veuillez entrer la ville de départ et la ville d'arrivée : " << endl;

			cin >> villeDep;
			cin >> villeArr;
			this->Recherche(villeDep, villeArr);
			break;

		case 4:
			cout << "Veuillez entrer la ville de départ et la ville d'arrivée : " << endl;
			cin >> villeDep;
			cin >> villeArr;
			this->RechercheAvancee(villeDep, villeArr);
			break;

		case 5:
			return;
		case 6:
			EnregistrerCatalogue(TOUS);
			break;
		case 7:
			importer("Sauvegarde.txt", TC);
			break;
		}
	}

}

void Catalogue::Recherche(const char *villeDep, const char *villeArr) const
// Algorithme : pour chaque trajet de la liste, on l'affiche uniquement si ses
// villes de départ et d'arrivée correspondent aux paramètres.
{
	bool test = false;
	Element *ptrRech = listeTrajets.Tete;
	unsigned int compteur = 0;
	while (ptrRech != NULL)
	{
		if (strcmp(ptrRech->trajet->getVilleDepart(), villeDep) == 0)
		{
			if (strcmp(ptrRech->trajet->getVilleArrivee(), villeArr) == 0)
			{
				if (!test)
				{
					cout << "Liste des trajets proposés: " << endl;
					test = true;
				}
				cout << "- Trajet " << ++compteur << " ------------------------------------------" << endl;
				ptrRech->trajet->Afficher();
			}
		}
		ptrRech = ptrRech->suivant;
	}
	if (!test)
	{
		cout << "Aucun trajet ne correspond à votre recherche: " << villeDep << " -> " << villeArr << endl;
	}
}

void Catalogue::RechercheAvancee(const char*villeDep, const char*villeArr) const 
// Algorithme : pour chaque trajet de la liste, on test si la ville de départ correspond à celle d'un trajet
// on stocke le trajet trouvé dans une nouvelle liste de trajet et on reitere le procéde pour la ville de 
// depart de trajet
//si avant la fin de la liste on arrive sur un trajet dont la ville de depart correspond à ville voulu
// on affiche la liste, sinon on la vide et on reitere.
{
	Element *ptr = listeTrajets.Tete;
	Element *test = listeTrajets.Tete;
	
	int compteur = 0;
	while (ptr!= NULL)	// on parcour la liste de trajet pour trouver le premier trajet avec ville de depart voulu
	{

		if (strcmp(ptr->trajet->getVilleDepart(), villeDep) == 0)
		{


			Element *newPtr = new Element;
			Element *newTete;
			test = listeTrajets.Tete;

			newPtr->trajet = ptr->trajet;
			newPtr->suivant = NULL;


			newTete = newPtr;
			
			
			while (strcmp(test->trajet->getVilleArrivee(), villeArr) !=0 ) // on parcourt toute la liste pour faire le lien ville depart= ville arrivé
			{	

				

				test = test->suivant;
				if (test == NULL) // si on arrive à la fin sans resultat voulu, on efface la liste newPtr
				{
					Element* ptrParcourt = newTete;
					while (ptrParcourt != NULL)
					{
						Element* tmp = ptrParcourt->suivant;
						delete ptrParcourt;
						ptrParcourt = tmp;

					}
					break;
				}
				
				else
					if (strcmp(test->trajet->getVilleDepart(), newPtr->trajet->getVilleArrivee()) == 0)
					{
						Element *elem=new Element;
						elem->trajet = test->trajet;
						elem->suivant = NULL;
						newPtr->suivant = elem;
						newPtr = newPtr->suivant;
					
					}

			}
			if (strcmp(newPtr->trajet->getVilleArrivee(), villeArr) == 0) // si le resultat est correct, on l'affiche
			{
				compteur++;

				cout << "    Trajet  " <<compteur<<" :"<< endl;
				newPtr = newTete;
				while (newPtr!=NULL)
				{
					newPtr->trajet->Afficher();
					newPtr = newPtr->suivant;
				}

				
			}
			Element* ptrParcourt = newTete;
			while (ptrParcourt != NULL)
			{
				Element* tmp = ptrParcourt->suivant;
				delete ptrParcourt;
				ptrParcourt = tmp;

			}
			
			
		}
		

		ptr = ptr->suivant;
	}
	if (compteur == 0)
	{
		cout << "Désolé, votre recherche n'a pas donné de resultat" << endl;
	}



}

void Catalogue::EnregistrerCatalogue(TypeTrajet type)
{
	ofstream flux("Sauvegarde.txt", ios::app);
	for(Element *elem = listeTrajets.Tete;elem!=NULL;elem=elem->suivant)
	{
		if(elem->type==type || type==TOUS)
		{	
		
			elem->trajet->Sauvegarder(flux);
		}
	}
	flux.close();
}



void Catalogue::importer(string nomFichier,TypeTrajet type)
{
	ifstream fluxLecture(nomFichier, ios::in);
	unsigned int i;

	while(fluxLecture>>i)
	{
		string ligne;
		string villeD;
		string villeA;
		string transport;
		
		if(i==1)
		{
			if(!(type==TOUS||type==TS))
			{
				fluxLecture>>ligne;
			}
			else
			{
				fluxLecture>>ligne;
				int pos=ligne.find(';');
				villeD=ligne.substr(0,pos);
				ligne.erase(0,pos+1);
				pos=ligne.find(';');
				villeA=ligne.substr(0,pos);
				ligne.erase(0,pos+1);
				transport=ligne;
				Ajouter(villeD.c_str(),villeA.c_str(),transport.c_str()); 
			}
		}
		else
		{
			if(!(type==TOUS||type==TC))
			{
				for(unsigned int k(0);k<i;k++)
				{
					fluxLecture>>ligne;
				}

			}
			else
			{
				UnTrajetSimple *lesTrajets=new UnTrajetSimple[i];
				for(unsigned int k(0);k<i;k++)
				{
					fluxLecture>>ligne;
					int pos=ligne.find(';');
					villeD=ligne.substr(0,pos);
					ligne.erase(0,pos+1);
					pos=ligne.find(';');
					villeA=ligne.substr(0,pos);
					ligne.erase(0,pos+1);
					transport=ligne;
					lesTrajets[k].villeDep=new char[villeD.size()];
					lesTrajets[k].villeArr=new char[villeA.size()];
					lesTrajets[k].moyenTransport=new char[transport.size()];
					
					strcpy(lesTrajets[k].villeDep,villeD.c_str());
					strcpy(lesTrajets[k].villeArr,villeA.c_str());
					strcpy(lesTrajets[k].moyenTransport,transport.c_str());
				}
				Ajouter(lesTrajets,i);
				for (int k(0); k<i; k++)
				{
					delete[] lesTrajets[k].villeDep;
					delete[] lesTrajets[k].villeArr;
					delete[] lesTrajets[k].moyenTransport;
				}
				delete [] lesTrajets;
			}				
			
		}
	}
}

void Catalogue::importer(string nomFichier, string villeA, string villeD);

Catalogue::Catalogue():nbTrajets(0)
{
#ifdef MAP
	cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
	listeTrajets.Tete = NULL;
	
} //----- Fin de Catalogue


Catalogue::~Catalogue()
{
#ifdef MAP
	cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
	Element* ptr = listeTrajets.Tete;
	while (ptr != NULL)
	{
		delete ptr->trajet;
		Element* tmp = ptr;
		ptr = ptr->suivant;
		delete tmp;
	}
} //----- Fin de ~Catalogue


  //------------------------------------------------------------------ PRIVE

  //----------------------------------------------------- Méthodes protégées

