/*************************************************************************
                           Log  -  description
                             -------------------
    début                : 15/01/2020
    copyright            : (C) 2020 par VERSMEE Erwan et KERMANI Benjamin
    e-mail               : erwan.versmee@insa-lyon.fr benjamin.kermani@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Log> (fichier Log.h) ----------------
#if ! defined ( LOG_H )
#define LOG_H

//--------------------------------------------------- Interfaces utilisées
#include<string>
#include <fstream>
using namespace std;
//------------------------------------------------------------- Constantes
const char SEP_ESP=' ';
const char SEP_HEURE=':';
const char SEP_ADR='"';
const char SEP_SLASH = '/';
//------------------------------------------------------------------ Types
typedef struct InfosLog{
    string adresseReferant ;
    int heure;
    int statut;
    string adresseCible;
    string extension;
    InfosLog(string adR="", int h=25, int s=0, string adC="", string ext=""):adresseReferant(adR),heure(h),statut(s),adresseCible(adC), extension(ext){}
}InfosLog;

//------------------------------------------------------------------------
// Rôle de la classe <Log>
//La classe permet de lire une ligne d'un fichier log et d'en stocker les informations qui nous intéressent (l'heure, le statut, l'adresse référente, l'adresse cible et son extension de la requête)
//Elle permet également d'ouvrir le fichier .log (constructeur) et de le fermer à la fin de la requête (destructeur)
//------------------------------------------------------------------------

class Log
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	
	bool LireFichier();
	// Mode d'emploi :
	//Lit une ligne par "morceaux", séparés par des éléments séparateurs bien définis entre chaque information (voir les constantes définies ci-dessus) et stocke les informations dans notre structure InfosLog.

	InfosLog getRenseignements();
	// Mode d'emploi :
	//Permet de renvoyer les informations d'un log

//-------------------------------------------- Constructeurs - destructeur


	Log(const string nomFic);
	// Mode d'emploi :
	//Ouvre un fichier log

	virtual ~Log ( );
	// Mode d'emploi :
	//Ferme un fichier log

//------------------------------------------------------------------ PRIVE

private:
	InfosLog renseignements;
public: 
	ifstream file;
};

#endif // LOG_H

