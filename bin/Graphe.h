/*************************************************************************
                           Graphe  -  description
                             -------------------
    début                : 22/01/2020
    copyright            : (C) 2020 par VERSMEE Erwan et KERMANI Benjamin
    e-mail               : erwan.versmee@insa-lyon.fr benjamin.kermani@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Graphe> (fichier Graphe.h) ----------------
#if ! defined ( GRAPHE_H )
#define GRAPHE_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <vector>
#include "Log.h"

//------------------------------------------------------------------ Types
typedef unordered_set<string> EnsembleAdresses;
typedef map<pair<string,string>,int> Digraph;
//------------------------------------------------------------------------
//Rôle de la classe <Graphe>
//En récupérant les données d'un log, cette classe va écrire un fichier digraph (.dot) qui permettra par la suite d'afficher une représentation graphique d'un fichier log.
//Le graphe sera composé de noeud ayant pour label le nom des adresses (cibles et référentes) et des arcs reliant ces noeuds et ayant pour label le nombre de requêtes effectué du noeud A (référent) vers le noeud B (cible). Les interactions peuvent se faire dans les deux sens.
//------------------------------------------------------------------------

class Graphe
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	void Ajouter(Log&);
	// Mode d'emploi :
	//Ajoute un log au conteneur des noeuds (unordered_set) et des arcs (map) s'il n'est pas déjà contenu dedans. Dans le deuxième cas, si la clé qu'on essaie d'ajouter existe déjà dans la map, la valeur est incrémentée de 1

	void Ajouter(Log&,bool, int, bool, int);
	// Mode d'emploi :
	//Même méthode que la première mais prend en compte les options demandées par l'utilisateur : n'ajoutera un log aux conteneurs seulement si les options sont satisfaites

	void Afficher();
	// Mode d'emploi :
	// Affiche une représentation textuelle de la map sur la sortie standard

	void EcrireDot(string);
	// Mode d'emploi :
	//Ecrit un fichier .dot en respectant rigoureusement sa syntaxe. Doit parcourir les deux conteneurs en entier pour ce faire.

//-------------------------------------------- Constructeurs - destructeur

	Graphe();
	// Mode d'emploi :
	//Ajoute au vecteur<extension> les extensions de l'adresse cible que le programme ne doit pas prendre en compte si l'utilisateur rentre l'option "-e" en ligne de commande

	virtual ~Graphe ();

//------------------------------------------------------------------ PRIVE

private:

	EnsembleAdresses adresses;
	Digraph arborescence;
	vector< string > extension;
};

#endif // GRAPHE_H
