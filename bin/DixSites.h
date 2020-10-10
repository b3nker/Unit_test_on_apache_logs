/*************************************************************************
                           DixSites  -  description
                             -------------------
    début                : 15/01/2020
    copyright            : (C) 2020 par VERSMEE Erwan et KERMANI Benjamin
    e-mail               : erwan.versmee@insa-lyon.fr benjamin.kermani@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <DixSites> (fichier DixSites.h) ----------------
#if ! defined ( DIXSITES_H )
#define DIXSITES_H

//--------------------------------------------------- Interfaces utilisées
#include<string>
#include "Log.h"
#include <unordered_map>
#include <map>
#include <vector>

//------------------------------------------------------------------ Types
typedef unordered_map<string,int> Classement;
typedef multimap<int,string> ClassementInverse;
//------------------------------------------------------------------------
// Rôle de la classe <DixSites>
//Stocke les adresses cibles des requêtes d'un fichier log et le nombre de demandes effectué vers ces requêtes.
//Cela permet ainsi d'obtenir les dix adresses ayant le nombre le plus élevé de demande
//------------------------------------------------------------------------

class DixSites
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	void Ajouter(Log &);
	// Mode d'emploi :
	//Si la requête cible a déjà été ciblé au moins une fois, on incrémente son nombre de requête d'1, sinon on l'ajoute à la unordered_map

	void Ajouter(Log &,bool, int, bool, int);
	// Mode d'emploi :
	//Cette méthode est appelée dans le cas où l'utilisateur a entré des options : elle va comparer l'heure et l'extension de l'adresse cible avec les demandes de l'utilisateur et va ajouter le log à la unordered_map ou pas
	
	bool testVide();
	// Mode d'emploi :
	//Cette méthode permet de tester si la unordered_map est vide ou non

	void Retourner();
	// Mode d'emploi :
	//Une fois les données du fichier stocker dans la unordered_map, on inverse celle-ci grâce à cette méthode : la valeur devient la clé et la clé la valeur. On se sert ici d'une multimap pour trier les résultats et obtenir les dix adresses cibles les plus demandées

	void Afficher();
	// Mode d'emploi :
	//Affiche les résultats sur la sortie standard

//-------------------------------------------- Constructeurs - destructeur


	DixSites();
	// Mode d'emploi :
	//Ajoute au vecteur<extension> les extensions de l'adresse cible que le programme ne doit pas prendre en compte si l'utilisateur rentre l'option "-e" en ligne de commande

	virtual ~DixSites ();

//------------------------------------------------------------------ PRIVE

private:

	Classement tableau;
	ClassementInverse tableauTrie;
	vector< string > extension;
};


#endif // DIXSITES_H

