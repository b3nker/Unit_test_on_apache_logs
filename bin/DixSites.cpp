/*************************************************************************
                           DixSites  -  description
                             -------------------
    début                : 15/01/2020
    copyright            : (C) 2020 par VERSMEE Erwan et KERMANI Benjamin
    e-mail               : erwan.versmee@insa-lyon.fr benjamin.kermani@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <DixSites> (fichier DixSites.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;
//------------------------------------------------------ Include personnel
#include "DixSites.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void DixSites::Ajouter(Log &l)
{
	if(tableau.find(l.getRenseignements().adresseCible)==tableau.end())
	{
		tableau.insert(make_pair(l.getRenseignements().adresseCible,1));
	}
	else
	{
		Classement::iterator it = tableau.find(l.getRenseignements().adresseCible);
		it->second=it->second +1;
	}
}//----- Ajouter

void DixSites::Ajouter(Log &l,bool tempsSouhaite, int heureSouhaitee, bool noExtens, int statutRecherche)
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

void DixSites::Retourner()
{
	Classement::iterator debut = tableau.begin();
	Classement::iterator fin = tableau.end();
	while(debut!=fin)
	{
		tableauTrie.insert(make_pair(debut->second,debut->first));
		debut++;
	}
}//----- Retourner

void DixSites::Afficher()
//Les résultats se trouvant à la fin de la multimap, on la parcout avec un reverse_iterator partant directement de la fin
{
	ClassementInverse::reverse_iterator fin = tableauTrie.rbegin();

	int nbResultat = 0;
	while(fin != tableauTrie.rend() && nbResultat < 10)
	{
		if(fin->second!="")
		{
			cout<<"Adresse cible : " << fin->second<< " ; nombre de requête(s) : "<< fin->first<<endl;
			fin++;
			nbResultat ++;
		}
		else
		{
			cout<<"Adresse cible : de l'extérieur ; nombre de requête(s) : "<< fin->first<<endl;
			fin++;
			nbResultat ++;
		}
	}
}//----- Afficher

bool DixSites::testVide()
{
	if(tableau.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}//----- testVide

//-------------------------------------------- Constructeurs - destructeur

DixSites::DixSites ()
{
#ifdef MAP
    cout << "Appel au constructeur de <DixSites>" << endl;
#endif
	extension.push_back("jpg");
	extension.push_back("css");
	extension.push_back("jpeg");
	extension.push_back("png");
	extension.push_back("js");
	extension.push_back("gif");
} //----- Fin de DixSites


DixSites::~DixSites()
{
#ifdef MAP
    cout << "Appel au destructeur de <DixSites>" << endl;
#endif
} //----- Fin de ~DixSites
