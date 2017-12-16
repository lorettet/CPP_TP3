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

	string villeDep;
	string villeArr;
	string moyenTransport;
	string commande;
	string test;
	string nomFichier="Sauvegarde.txt";
	string borneInf;
	string borneSup;
	bool ecraseFichier = true;
	while (true)
	{
		cout << "\t\t\t\tVoici la liste de commandes: " << endl << endl;
		cout << "\t\t\t\t 1 - Afficher la liste de trajets" << endl;
		cout << "\t\t\t\t 2 - Entrer un trajet simple" << endl;
		cout << "\t\t\t\t 3 - Entrer un trajet composé" << endl;
		cout << "\t\t\t\t 4 - Rechercher un trajet" << endl;
		cout << "\t\t\t\t 5 - Recherche avancée de trajet" << endl;
		cout << "\t\t\t\t 6 - Sauvegarder"  << endl;
		cout << "\t\t\t\t 7 - Lecture"  << endl << endl;

		cout << "\t\t\t\t 8 - Quitter l'application" << endl << endl;

		cin >> commande;
		switch (atoi(commande.c_str()))
		{
		case 1:
			this->Afficher();
			break;

		case 2:
			cout << "Veuillez entrer la ville de départ" << endl;
			cin.ignore();
			getline(cin, villeDep);
			cout << "Veuillez entrer la ville d'arrivée" << endl;
			getline(cin, villeArr);
			cout << "Veuillez entrer le moyen de transport" << endl;
			getline(cin, moyenTransport);

			if (Ajouter(villeDep.c_str(), villeArr.c_str(), moyenTransport.c_str()))
				cout << "Trajet ajouté avec succès!" << endl;
			else
				cout << "Erreur lors de l'ajout du trajet... :(" << endl;
			break;

		case 3:
		{
			cout << "Veuillez rentrer le nombre de trajets simples avec leur moyen de transport" << endl;
			string nombreTrajets;
			cin.ignore();
			getline(cin, nombreTrajets);
			int nbrTrajets = atoi(nombreTrajets.c_str());
			if (nbrTrajets == 0)
			{
				cout << "La saisi n'est pas valide." << endl;
				break;
			}
			UnTrajetSimple* liste = new UnTrajetSimple[nbrTrajets];
			cout << "Veuillez rentrer la ville de départ" << endl;
			getline(cin,villeDep);
			for (int i(0); i<nbrTrajets; i++)
			{
				cout << "Veuillez rentrer la ville d'arrivée de Trajet "<<i+1 << endl;
				getline(cin, villeArr);
				cout << "Veuillez rentrer le moyen de transport de Trajet " << i + 1 << endl;
				getline(cin , moyenTransport);
				cout << endl << endl;

				liste[i].villeDep = new char[20];
				liste[i].villeArr = new char[20];
				liste[i].moyenTransport = new char[20];

				strcpy(liste[i].villeDep, villeDep.c_str());

				strcpy(liste[i].villeArr, villeArr.c_str());

				strcpy(liste[i].moyenTransport, moyenTransport.c_str());

				villeDep= villeArr;
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

		case 4:
			cout << "Veuillez entrer la ville de départ" << endl;
			cin.ignore();
			getline(cin , villeDep);
			cout << "Veuillez entrer la ville d'arrivée" << endl;
			getline(cin , villeArr);
			this->Recherche(villeDep.c_str(), villeArr.c_str());
			break;

		case 5:
			cout << "Veuillez entrer la ville de départ" << endl;
			cin.ignore();
			getline(cin, villeDep);
			cout << "Veuillez entrer la ville d'arrivée" << endl;
			getline(cin, villeArr);
			this->RechercheAvancee(villeDep.c_str(), villeArr.c_str());
			break;
		
		case 6:
			
			cout << "Veuillez entrer le nom de fichier de destination" << endl;
			cin.ignore();
			getline(cin , nomFichier);
			{ifstream testExistence(nomFichier);
				if (!testExistence.fail())
				{
					bool passePas = true;
					while (passePas)
					{
						cout << "Un fichier avec ce nom existe déjà" << endl;
						cout << "\t\t 1 - Ecraser le fichier existant" << endl;
						cout << "\t\t 2 - Sauvegarder à la suite" << endl << endl;

						string testFichier;
						cin >> testFichier;
						switch (atoi(testFichier.c_str()))
						{
						case 1:
						{
							ecraseFichier = true; 
							passePas = false;
						}
						break;

						case 2:
						{
							ecraseFichier = false;
							passePas = false;
						}
						break;
						default:
							cout << "Commande non valide" << endl;
							break;

						}
					}


				}
			}
			
			
			cout << "\t\t Liste de commandes: " << endl << endl;
			cout << "\t\t 1 - Enregistrer tous les trajets" << endl;
			cout << "\t\t 2 - Enregistrer celon le type de trajet" << endl;
			cout << "\t\t 3 - Enregistrer celon la ville de départ" << endl;
			cout << "\t\t 4 - Enregistrer celon la ville d'arrivée" << endl;
			cout << "\t\t 5 - Enregistrer celon la ville de départ et la ville d'arrivée" << endl;
			cout << "\t\t 6 - Enregistrer un intervalle de trajet" << endl << endl;

			
			cin >> test;

			switch (atoi(test.c_str()))
			{
				case 1:
					EnregistrerCatalogue(ecraseFichier,nomFichier);
					break;
				case 2:
					cout << "\t Liste de commandes: " << endl << endl;
					cout << "\t 1 - Enregistrer les trajets simples" << endl;
					cout << "\t 2 - Enregistrer les trajets composés" << endl << endl;
					cin >> test;
					switch (atoi(test.c_str()))
					{
						case 1:
							EnregistrerCatalogue(ecraseFichier, nomFichier, TS);
							break;
						case 2:
							EnregistrerCatalogue(ecraseFichier, nomFichier, TC);
							break;
					}
					break;
				case 3:
					cout << "Veuillez entrer la ville de départ. "<<endl;
					cin.ignore();
					getline(cin , villeDep);
					EnregistrerCatalogue(ecraseFichier, nomFichier, villeDep);
					break;

				case 4:
					cout << "Veuillez entrer la ville d'arrivées " << endl;
					cin.ignore();
					getline(cin , villeArr);
					EnregistrerCatalogue(ecraseFichier, nomFichier, "",villeArr);
					break;
				case 5:
					cout << "Veuillez entrer la ville de départ " << endl;
					cin.ignore();
					getline(cin , villeDep);
					cout << "Veuillez entrer la ville d'arrivées " << endl;
					cin.ignore();
					getline(cin , villeArr);
					EnregistrerCatalogue(ecraseFichier, nomFichier, villeDep, villeArr);
					break;
				case 6:
					cout << "Veuillez entrer la borne inferieure " << endl;
					cin >> borneInf;
					cout << "Veuillez entrer la borne supérieure " << endl;
					cin >> borneSup;
					
					EnregistrerCatalogue(ecraseFichier, nomFichier, atoi(borneInf.c_str()), atoi(borneSup.c_str()));
					break;
				default:
					cout << "Commande non valide" << endl;
					break;

			}

			break;

		case 7:
			
			cout << "Veuillez entrer le nom de fichier source" << endl;
			cin.ignore();
			getline(cin , nomFichier);
			{
				ifstream lecture(nomFichier);
				if (lecture.fail())
				{
					cout << "erreur, fichier n'existe pas." << endl;
					break;

				}
			}
			cout << endl << "\t\t Liste de commandes: " << endl << endl ;
			cout<< "\t\t 1 - Importer tous les trajets" << endl;
			cout << "\t\t 2 - Importer celon le type de trajet" << endl;
			cout << "\t\t 3 - Importer celon la ville de départ" << endl;
			cout << "\t\t 4 - Importer celon la ville d'arrivée" << endl;
			cout << "\t\t 5 - Importer celon la ville de départ et la ville d'arrivée" << endl;
			cout << "\t\t 6 - Importer un intervalle de trajet" << endl << endl;
			
			cin >> test;

			switch (atoi(test.c_str()))
			{
				case 1:
					importer(nomFichier);
					break;
				case 2:
					cout << "\t Liste de commandes: " << endl << endl;
					cout << "\t 1 - Importer les trajets simples" << endl;
					cout << "\t 2 - Importer les trajets composés" << endl << endl;
					cin >> test;
					switch (atoi(test.c_str()))
					{
						case 1:
							importer( nomFichier, TS);
							break;
						case 2:
							importer(nomFichier, TC);
							break;
						default:
							cout << "Commande non valide" << endl;
							break;
					}
					break;

				case 3:
					cout << "Veuillez entrer la ville de départ. " << endl;
					cin.ignore();
					getline(cin , villeDep);
					importer(nomFichier, villeDep);
					break;

				case 4:
					cout << "Veuillez entrer la ville d'arrivées " << endl;
					cin.ignore();
					getline(cin , villeArr);
					importer(nomFichier, "", villeArr);
					break;
				case 5:
					cout << "Veuillez entrer la ville de départ " << endl;
					cin.ignore();
					getline(cin, villeDep);
					cout << "Veuillez entrer la ville d'arrivées " << endl;
					getline(cin, villeArr);
					importer(nomFichier, villeDep, villeArr);
					break;
				case 6:
					cout << "Veuillez entrer la borne inferieure " << endl;
					cin >> borneInf;
					cout << "Veuillez entrer la borne supérieure " << endl;
					cin >> borneSup;
					importer(nomFichier, atoi(borneInf.c_str()), atoi(borneSup.c_str()));
					break;
				default:
					cout << "Commande non valide" << endl;
					break;

			}


			break;

		case 8:
			return;
		default:
			cout << "Commande non valide" << endl;
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
			
			
			while (strcmp(test->trajet->getVilleArrivee(), villeArr) !=0 || strcmp(newPtr->trajet->getVilleArrivee(), villeArr) != 0) // on parcourt toute la liste pour faire le lien ville depart= ville arrivé
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

void Catalogue::EnregistrerCatalogue(bool ecraseTest, string nomFichier, TypeTrajet type)
{
	unsigned int trajetDeFichiers = 0;
	if (!ecraseTest)
	{
		ifstream lecture(nomFichier, ios::in);
		lecture >> trajetDeFichiers;

	}
	ofstream flux(nomFichier, (ecraseTest) ? ios::out : ios::app);
	if (ecraseTest)
	{
		flux << "          " << endl;
	}
	unsigned int nbTrajetsAjoutes = trajetDeFichiers;
	for(Element *elem = listeTrajets.Tete;elem!=NULL;elem=elem->suivant)
	{
		if(elem->type==type || type==TOUS)
		{	
			elem->trajet->Sauvegarder(flux);
			nbTrajetsAjoutes++;
		}
	}
	flux.close();
	ofstream flux2(nomFichier, std::ios::in | ios::ate);
	flux2.seekp(ios::beg);
	flux2 << nbTrajetsAjoutes;
	flux2.close();
}

void Catalogue::EnregistrerCatalogue(bool ecraseTest, string nomFichier, string villeDep, string villeArr)
{
	unsigned int trajetDeFichiers = 0;
	if (!ecraseTest)
	{
		ifstream lecture(nomFichier, ios::in);
		lecture >> trajetDeFichiers;

	}
	ofstream flux(nomFichier, (ecraseTest) ? ios::out : ios::app);
	if (ecraseTest)
	{
		flux << "          " << endl;
	}
	unsigned int nbTrajetsAjoutes = trajetDeFichiers;
	for(Element *elem = listeTrajets.Tete;elem!=NULL;elem=elem->suivant)
	{
		int villeDepEgale = strcmp(villeDep.c_str(),elem->trajet->getVilleDepart());
		int villeArrEgale = strcmp(villeArr.c_str(),elem->trajet->getVilleArrivee());
		
		if(villeDep=="" && villeArr=="")
		{
				elem->trajet->Sauvegarder(flux);
				nbTrajetsAjoutes++;
		}
		else if(villeDepEgale ==0 && villeArr=="")
		{
				elem->trajet->Sauvegarder(flux);
				nbTrajetsAjoutes++;
		}
		else if(villeArrEgale==0 && villeDep=="")
		{
				elem->trajet->Sauvegarder(flux);
				nbTrajetsAjoutes++;
		}
		else if(villeArrEgale==0 && villeDepEgale==0)
		{
				elem->trajet->Sauvegarder(flux);
				nbTrajetsAjoutes++;
		}
	}
	flux.close();
	ofstream flux2(nomFichier, std::ios::in | ios::ate);
	flux2.seekp(ios::beg);
	flux2 << nbTrajetsAjoutes;
	flux2.close();
}

void Catalogue::EnregistrerCatalogue(bool ecraseTest, string nomFichier, unsigned int deb, unsigned int fin)
{
	if(!(fin>=deb&&fin<=nbTrajets)||deb==0||fin==0)
	{
		cout<<"Erreur d'intervalle"<<endl;
		return;
	}
	
	unsigned int trajetDeFichiers = 0;
	if (!ecraseTest)
	{
		ifstream lecture(nomFichier, ios::in);
		lecture >> trajetDeFichiers;

	}
	ofstream flux(nomFichier, (ecraseTest)?ios::out:ios::app);
	if (ecraseTest)
	{
		flux << "          " << endl;
	}
	unsigned int nbTrajetsAjoutes = trajetDeFichiers;
	unsigned int compteur=1;
	Element *elem = listeTrajets.Tete;
	for (elem; compteur != deb; elem = elem->suivant, compteur++);
	
	for(elem;compteur!=fin+1;elem=elem->suivant,compteur++)
	{
		elem->trajet->Sauvegarder(flux);
		nbTrajetsAjoutes++;
	}
	flux.close();
	ofstream flux2(nomFichier, std::ios::in | ios::ate);
	flux2.seekp(ios::beg);
	flux2 << nbTrajetsAjoutes;
	flux2.close();
	
}


void Catalogue::importer(string nomFichier,TypeTrajet type)
{
	ifstream fluxLecture(nomFichier, ios::in);
	
	string meta;
	vector<string> splitRes;
	unsigned int nbTrajetsEnreg;
	string strNbrTrajets;
	getline(fluxLecture, strNbrTrajets);
	nbTrajetsEnreg = atoi(strNbrTrajets.c_str());
	
	if(nbTrajetsEnreg==0) // si aucun trajet n'a été enregistrer, on sort
		return;

	while(getline(fluxLecture, meta))
	{
		string ligne;
		string villeD;
		string villeA;
		string transport;
		
		unsigned int metaNbTrajets;
		
		splitRes = split(meta,';');
		metaNbTrajets=atoi(splitRes[0].c_str());
		
		if(metaNbTrajets==1)
		{
			if(!(type==TOUS||type==TS))
			{
				getline(fluxLecture,ligne);
			}
			else
			{
				getline(fluxLecture, ligne);
				splitRes = split(ligne,';');
				villeD = splitRes[0];
				villeA = splitRes[1];
				transport = splitRes[2];
				Ajouter(villeD.c_str(),villeA.c_str(),transport.c_str());
			}
		}
		else
		{
			if(!(type==TOUS||type==TC))
			{
				for(unsigned int k=0;k<metaNbTrajets;k++)
				{
					getline(fluxLecture, ligne);
				}

			}
			else
			{
				UnTrajetSimple *lesTrajets=new UnTrajetSimple[metaNbTrajets];
				for(unsigned int k=0;k<metaNbTrajets;k++)
				{
					getline(fluxLecture, ligne);
					splitRes = split(ligne,';');
					villeD = splitRes[0];
					villeA = splitRes[1];
					transport = splitRes[2];
					lesTrajets[k].villeDep=new char[villeD.size()+1];
					lesTrajets[k].villeArr=new char[villeA.size()+1];
					lesTrajets[k].moyenTransport=new char[transport.size()+1];
					
					strcpy(lesTrajets[k].villeDep,villeD.c_str());
					strcpy(lesTrajets[k].villeArr,villeA.c_str());
					strcpy(lesTrajets[k].moyenTransport,transport.c_str());
				}
				Ajouter(lesTrajets,metaNbTrajets);
				for (unsigned int k(0); k<metaNbTrajets; k++)
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

void Catalogue::importer(string nomFichier, string villeD, string villeA)
{
	fstream fluxLecture(nomFichier, ios::in);
	string meta;
	vector<string> splitRes;
	unsigned int nbTrajetsEnreg;
	string strNbrTrajets;
	getline(fluxLecture, strNbrTrajets);
	nbTrajetsEnreg = atoi(strNbrTrajets.c_str());
	
	if(nbTrajetsEnreg==0) // si aucun trajet n'a été enregistrer, on sort
		return;

	while(getline(fluxLecture, meta))
	{
		string ligne;
		string transport;
		string villeDep;
		string villeArr;
		
		unsigned int metaNbTrajets;
		string metaVilleDep;
		string metaVilleArr;
		
		splitRes = split(meta,';');
		metaNbTrajets=stoi(splitRes[0]);
		metaVilleDep=splitRes[1];
		metaVilleArr=splitRes[2];
		
		
		if(metaNbTrajets==1)
		{
			if((metaVilleArr==villeA && villeD=="") || (metaVilleDep==villeD && villeA=="") || (metaVilleDep==villeD && metaVilleArr==villeA)||(villeA==""&& villeD==""))
			{
				getline(fluxLecture, ligne);
				splitRes = split(ligne,';');
				villeDep = splitRes[0];
				villeArr = splitRes[1];
				transport = splitRes[2];
				Ajouter(villeDep.c_str(),villeArr.c_str(),transport.c_str());
			}
			else
			{
				getline(fluxLecture, ligne);
			}
			
			
		}
		else
		{
			if((metaVilleArr==villeA && villeD=="") || (metaVilleDep==villeD && villeA=="") || (metaVilleDep==villeD && metaVilleArr==villeA)||(villeA==""&& villeD==""))
			{
				UnTrajetSimple *lesTrajets=new UnTrajetSimple[metaNbTrajets];
				for(unsigned int k=0;k<metaNbTrajets;k++)
				{
					getline(fluxLecture, ligne);
					splitRes = split(ligne,';');
					villeDep = splitRes[0];
					villeArr = splitRes[1];
					transport = splitRes[2];
					lesTrajets[k].villeDep=new char[villeDep.size()+1];
					lesTrajets[k].villeArr=new char[villeArr.size()+1];
					lesTrajets[k].moyenTransport=new char[transport.size()+1];
					
					strcpy(lesTrajets[k].villeDep,villeDep.c_str());
					strcpy(lesTrajets[k].villeArr,villeArr.c_str());
					strcpy(lesTrajets[k].moyenTransport,transport.c_str());
				}
				Ajouter(lesTrajets,metaNbTrajets);
				for (unsigned int k(0); k<metaNbTrajets; k++)
				{
					delete[] lesTrajets[k].villeDep;
					delete[] lesTrajets[k].villeArr;
					delete[] lesTrajets[k].moyenTransport;
				}
				delete [] lesTrajets;
			}
			
			else
			{
				for(unsigned int k=0;k<metaNbTrajets;k++)
				{
					getline(fluxLecture, ligne);
				}
			}				
			
		}
	}
}

void Catalogue::importer(string nomFichier, unsigned int deb, unsigned int fin)
{
	if (!(fin >= deb&&fin <= nbTrajets) || deb == 0 || fin == 0)
	{
		cout << "Erreur d'intervalle" << endl;
		return;
	}
	
	fstream fluxLecture(nomFichier, ios::in);
	string meta;
	vector<string> splitRes;
	unsigned int nbTrajetsEnreg;
	string strNbrTrajets;
	getline(fluxLecture, strNbrTrajets);
	nbTrajetsEnreg = atoi(strNbrTrajets.c_str());
	unsigned int compteur = 1;

	if (nbTrajetsEnreg == 0) // si aucun trajet n'a été enregistrer, on sort
		return;

	else if (nbTrajetsEnreg < fin)
	{
		cout << "erreur: l'intervalle saisi depasse la limite du fichier" << endl;
		return;
	}

	while (compteur!=deb)
	{
		getline(fluxLecture, meta);
		string ligne;
		unsigned int metaNbTrajets;

		splitRes = split(meta, ';');
		metaNbTrajets = atoi(splitRes[0].c_str());
		


		if (metaNbTrajets == 1)
		{
			getline(fluxLecture, ligne);
		}
		else
		{
			for (unsigned int k = 0; k<metaNbTrajets; k++)
			{
				getline(fluxLecture, ligne);
			}
		}

		compteur++;
	}

	while ( compteur!=fin+1)
	{
		getline(fluxLecture, meta); 
		string ligne;
		string transport;

		unsigned int metaNbTrajets;
		string villeD;
		string villeA;

		splitRes = split(meta, ';');
		metaNbTrajets = stoi(splitRes[0]);


		if (metaNbTrajets == 1)
		{
			
			getline(fluxLecture, ligne);
			splitRes = split(ligne, ';');
			villeD = splitRes[0];
			villeA = splitRes[1];
			transport = splitRes[2];
			Ajouter(villeD.c_str(), villeA.c_str(), transport.c_str());
			


		}
		else
		{
			
			UnTrajetSimple *lesTrajets = new UnTrajetSimple[metaNbTrajets];
			for (unsigned int k = 0; k<metaNbTrajets; k++)
			{
				getline(fluxLecture, ligne);
				splitRes = split(ligne, ';');
				villeD = splitRes[0]; 
				villeA = splitRes[1];
				transport = splitRes[2];
				lesTrajets[k].villeDep = new char[villeD.size()+1];
				lesTrajets[k].villeArr = new char[villeA.size()+1];
				lesTrajets[k].moyenTransport = new char[transport.size()+1];

				strcpy(lesTrajets[k].villeDep, villeD.c_str());
				strcpy(lesTrajets[k].villeArr, villeA.c_str());
				strcpy(lesTrajets[k].moyenTransport, transport.c_str());
			}
			Ajouter(lesTrajets, metaNbTrajets);
			for (unsigned int k(0); k<metaNbTrajets; k++)
			{
				delete[] lesTrajets[k].villeDep;
				delete[] lesTrajets[k].villeArr;
				delete[] lesTrajets[k].moyenTransport;
			}
			delete[] lesTrajets;
			

		}
		compteur++;
	}
}



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

vector<string> Catalogue::split(string param, char delimiteur)
{
	size_t pos;
	string token;
	vector<string> result;
	while ((pos = param.find(delimiteur)) != std::string::npos)
	{
		token = param.substr(0, pos);
		result.push_back(token);
		param.erase(0, pos+1);
	}
	result.push_back(param);
	return result;
}

