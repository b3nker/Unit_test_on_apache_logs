/*************************************************************************
                           Graphe -  description
                             -------------------
    début                : 22/01/2020
    copyright            : (C) 2020 par VERSMEE Erwan et KERMANI Benjamin
    e-mail               : erwan.versmee@insa-lyon.fr benjamin.kermani@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Graphe> (fichier Graphe.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
//------------------------------------------------------ Include personnel
#include "Graphe.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Graphe::Ajouter(Log& l)
{
	string adrCible = l.getRenseignements().adresseCible;
	string adrRef = l.getRenseignements().adresseReferant;
	// On ne souhaite pas garder dans notre graphe ce type d'adresse
	if((!adrCible.empty() && adrCible != "-") && (!adrRef.empty() && adrRef != "-"))
	{

		// Insère dans notre table de hachage les différents noeuds si ils ne sont pas déjà présents
		adresses.insert(l.getRenseignements().adresseCible);
		adresses.insert(l.getRenseignements().adresseReferant);
		
		//Ajout dans la map
		pair<string,string> p(l.getRenseignements().adresseReferant,l.getRenseignements().adresseCible);
		if(arborescence.find(p)==arborescence.end())
		{
			arborescence.insert(make_pair(p,1));
		}
		else
		{
			Digraph::iterator it = arborescence.find(p);
			it->second=it->second +1;	
		}
	}
}//----- Ajouter

void Graphe::Ajouter(Log& l,bool tempsSouhaite, int heureSouhaitee, bool noExtens, int statutRecherche)
{
	vector<string>::iterator it;
	bool est_absent = true;
	int heure = l.getRenseignements().heure;
	int statut = l.getRenseignements().statut;
	string ext = l.getRenseignements().extension;

	for(it = extension.begin(); it != extension.end(); it++)
	{
		if(ext==*it)
			est_absent=false;
	}
	if((tempsSouhaite && !noExtens && !statutRecherche)&&(heureSouhaitee<=heure && heure<heureSouhaitee+1))
		Ajouter(l);
	else if((!tempsSouhaite && noExtens && !statutRecherche)&&(est_absent))
		Ajouter(l);
	else if((tempsSouhaite && noExtens && !statutRecherche)&&(heureSouhaitee<=heure && heure<heureSouhaitee+1) && (est_absent))
			Ajouter(l);
	else if ((tempsSouhaite && !noExtens && statutRecherche)&&(heureSouhaitee<=heure && heure<heureSouhaitee+1) && (statut==statutRecherche))
			Ajouter(l);
	else if ((tempsSouhaite && noExtens && statutRecherche)&&(heureSouhaitee<=heure && heure<heureSouhaitee+1) && (statut==statutRecherche) && (est_absent))
			Ajouter(l);
	else if ((!tempsSouhaite && noExtens && statutRecherche) && (statut==statutRecherche) && (est_absent))
			Ajouter(l);
	else if ((!tempsSouhaite && !noExtens && statutRecherche) && (statut==statutRecherche))
			Ajouter(l);
}//----- Ajouter

void Graphe::Afficher()
{
	Digraph::iterator debut = arborescence.begin();
	Digraph::iterator fin = arborescence.end();
	while(debut!= fin)
	{
		cout << debut->first.first << " vers " << debut->first.second << " nbRequetes: " <<debut->second << endl;;
		debut++;
	}
}//----- Afficher


void Graphe::EcrireDot(string nomFichier){
	ofstream file;
	file.open(nomFichier);
	if(!file){
		cerr << "Problème avec le fichier " << nomFichier << endl;
	}else{
		file << "digraph {" << endl;
		
		//Affichage de tous les noeuds contenus dans le SET
		EnsembleAdresses::iterator debut = adresses.begin();
		while(debut != adresses.end()){
				int index = std::distance(adresses.begin(),debut);
				file << "node" << index << " " <<"[label=\"" << *debut << "\"];" << endl;
			debut++;
		}

		//Affichage de chaques connexions entre les noeuds
		Digraph::iterator itDebut = arborescence.begin();
		while(itDebut != arborescence.end()){
			int indexRef = distance(adresses.begin(),adresses.find(itDebut->first.first));
			int indexCible = distance(adresses.begin(),adresses.find(itDebut->first.second));
			file << "node" << indexRef << " -> node" << indexCible << " [label=\"" << itDebut->second <<"\"];" << endl;
			itDebut++;
		}
		file << "}" << endl;

	}

}//------EcrireDot


//-------------------------------------------- Constructeurs - destructeur

Graphe::Graphe()
{
#ifdef MAP
    cout << "Appel au constructeur de <Graphe>" << endl;
#endif
	extension.push_back("css");
	extension.push_back("jpg");
	extension.push_back("jpeg");
	extension.push_back("png");
	extension.push_back("js");
	extension.push_back("gif");
} //----- Fin de Graphe


Graphe::~Graphe()
{
#ifdef MAP
    cout << "Appel au destructeur de <Graphe>" << endl;
#endif
} //----- Fin de ~Graphe
