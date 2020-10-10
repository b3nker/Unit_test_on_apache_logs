/*************************************************************************
                           Log  -  description
                             -------------------
    début                : 15/01/2020
    copyright            : (C) 2020 par VERSMEE Erwan et KERMANI Benjamin
    e-mail               : erwan.versmee@insa-lyon.fr benjamin.kermani@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Log> (fichier Log.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>

//------------------------------------------------------ Include personnel
#include "Log.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

bool Log::LireFichier()
// Algorithme :
//Retourne vrai vrai tant que la fin du fichier n'est pas atteinte.
{
	string heure_buffer;
	string statut_buffer;

	file.ignore(256,SEP_HEURE);
	getline(file,heure_buffer,SEP_HEURE);
	
	if(!file.eof()){
		renseignements.heure=stoi(heure_buffer);
    		file.ignore(256 ,SEP_SLASH);
		int pos = file.tellg();
    		getline(file,renseignements.adresseCible,SEP_ESP);
		if(renseignements.adresseCible.find(".")!=string::npos)
		{
			file.seekg(pos,ios_base::beg);
			file.ignore(256 ,'.');
			getline(file,renseignements.extension,SEP_ESP);
		}

		file.ignore(256,SEP_ADR);
		file.ignore(1);
       		getline(file,statut_buffer,SEP_ESP);
		renseignements.statut=stoi(statut_buffer);
		file.ignore(256,SEP_ADR);
        	string referant ="";
		pos=file.tellg();
		getline(file,referant,SEP_ADR);

		if(referant!="-")
		{
			referant="";
			file.seekg(pos,ios_base::beg);
       			getline(file,renseignements.adresseReferant,SEP_SLASH);
       			referant += renseignements.adresseReferant + "/";
       			getline(file,renseignements.adresseReferant,SEP_SLASH);
       			referant += renseignements.adresseReferant + "/";
       			getline(file,renseignements.adresseReferant,SEP_SLASH);
       			referant += renseignements.adresseReferant;
       			string adresse_locale = "if.insa-lyon.fr";
       			if(referant.find(adresse_locale)!=string::npos)
			{
				if(referant == "http://if.insa-lyon.fr")
				{
					renseignements.adresseReferant = "adresse locale";
				}
				else
				{
					getline(file,renseignements.adresseReferant,SEP_ADR);
				}
        		}
			else
			{	
				referant += "/";
       				getline(file,renseignements.adresseReferant,SEP_ADR);
       				referant += renseignements.adresseReferant;
				if(referant.find("?") != string::npos)
				{
					file.seekg(pos,ios_base::beg);
					getline(file,renseignements.adresseReferant,'?');
				}
				else
				{
    					renseignements.adresseReferant = referant;
				}
							
			}
		}
		else
		{
			renseignements.adresseReferant = referant;
		}
		file.ignore(256 ,'\n');
		return true;
	}
	else
	{
		return false;
	}
} //----- LireFichier


InfosLog Log::getRenseignements()
{
	return renseignements;
} //----- getRenseignements


//-------------------------------------------- Constructeurs - destructeur



Log::Log ( const string nomFichier)
{
#ifdef MAP
    cout << "Appel au constructeur de <Log>" << endl;
#endif
    file.open(nomFichier);
    if(!file)
    {
	cerr << "Problème avec le fichier " << nomFichier << endl;
    }
} //----- Fin de Log


Log::~Log()
{
#ifdef MAP
    cout << "Appel au destructeur de <Log>" << endl;
#endif
    file.close();
} //----- Fin de ~Log

