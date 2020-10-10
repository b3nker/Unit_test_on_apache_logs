/*************************************************************************
                         	    main
                             -------------------
    début                : 22/01/2020
    copyright            : (C) 2020 par VERSMEE Erwan et KERMANI Benjamin
    e-mail               : erwan.versmee@insa-lyon.fr benjamin.kermani@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <main> (fichier main.cpp) ------------
//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <iostream>
#include <locale>
//------------------------------------------------------ Include personnel
#include "Log.h"
#include "DixSites.h"
#include "Graphe.h"

bool testNombre(char* arg);

int main(int argc, char** argv)
{
	//Création des instances nécessaires
	Graphe g;
	DixSites D;
	Log* l1;

	//Pour les options
	bool option =false; //-t ou -e ou -s
	bool Graph = false; // -g
	bool exclure = false; // -e
	bool temps = false; //-t
	int heure=25;
	int statut =0;
	string nomFic; //Nom du fichier dot

	const char* optionGraph = "-g";
	const char* optionExclure = "-e";
	const char* optionHeure = "-t";
	const char* optionStatut = "-s";
	string nomDot;

	if(argc>1)
	{
		//Le nom du fichier log doit être le dernier paramètre de la ligne de commande
		nomFic=argv[argc-1];
		l1 = new Log(nomFic);
	}	
	if(argc==1)
	{
		//Aucun nom de fichier n'a été passé en paramètre
		cerr << "Donnez un nom de fichier log"<< endl;
		cerr << "Erreur de syntaxe : ./analog nomfichier.log"<<endl;
		return 1;
	}
	else if(nomFic.find(".log")==string::npos)
	{
		//L'extension du fichier log n'es pas correct
		cerr << "Entrez un nom de fichier log"<< endl;
		cerr << "Erreur de syntaxe : ./analog nomfichier.log"<<endl;
		return 1;
	}
	else
	{
		if(argc==2)
		{
			//Cas où aucune option n'est demandée par l'utilisateur : on affiche les 10 documents les plus recherchés
			while(l1->LireFichier())
			{
				D.Ajouter(*l1);
			}
			D.Retourner();
			D.Afficher();
			if(D.testVide())
			{
				//Aucune ligne n'a été ajouté alors qu'aucune option n'a été rentré par l'utilisateur : le fichier est vide
				cerr<< "Le fichier est vide"<<endl;
				delete l1;
				return 1;
			}
			else
			{
				delete l1;
				return 0;
			}
		}
		else
		{
			//Des options ont été demandées par l'utilisateur
			for(int i=1;i<argc-1;i++)
			{
				if(strcmp(argv[i],optionExclure)==0)
				{
					//Option -e
					option=true;
					exclure=true;
				}
				else if(strcmp(argv[i],optionHeure)==0)
				{
					//Option -t
					option=true;
					temps=true;
					i++;
					//L'heure de la requête doit être entré juste après l'option -t
					//Test si l'heure entrée est bien entière
					if(testNombre(argv[i]))
					{
						heure = stoi(argv[i]);
					}
					else
					{
						cerr << "Erreur : il faut entrer un nombre pour l'heure "<< endl;
						delete l1;
						return 1;
					}
					if(heure<0 || heure >24)
					{
						//L'heure n'existe pas
						cerr << "Entrez une heure comprise entre 00 et 24" << endl;
						cerr << "Erreur de syntaxe : ./analog -t 00 nomfichier.log"<<endl;
						delete l1;
						return 1;
					}
				}
				else if(strcmp(argv[i],optionStatut)==0)
				{
					//Option -s
					option=true;
					i++;
					//Le statut recherché doit suivre le -s
					//Test si le statut entré est bien entier
					if(testNombre(argv[i]))
					{
						statut = stoi(argv[i]);
					}
					else
					{
						cerr << "Erreur : il faut entrer un nombre pour le statut "<< endl;
						delete l1;
						return 1;
					}
						
				}
				else if(strcmp(argv[i],optionGraph)==0)
				{
					//Option -g
					Graph=true;
					i++;
					//Le nom du fichier dot doit suivre l'option -g
					nomDot = argv[i];
				}
				else
				{
					//Si on a rentré une option inconnue du programme
					cout <<"Option : "<< argv[i] <<" non connue"<< endl;
				}
			}
			if(option)
			{
				//Si on a entré des options, on utilise la méthode Ajouter spécifique
				while(l1->LireFichier())
				{
					g.Ajouter(*l1,temps,heure%24,exclure,statut);
					D.Ajouter(*l1,temps,heure%24,exclure,statut);
				}
			}
			else
			{
				while(l1->LireFichier())
				{
					g.Ajouter(*l1);
					D.Ajouter(*l1);
				}
			}
			if(D.testVide() && !option)
			{
				//Si seul l'option -g a été rentré mais que le fichier est vide
				cerr<< "Le fichier est vide"<<endl;
				delete l1;
				return 1;
			}
			else if(D.testVide())
			{
				//Si aucune requêtes ne satisfait les options demandées
				cerr<< "Aucune requête ne satisfait les options demandées"<<endl;
				delete l1;
				return 1;
			}
			if(Graph)
			{
				g.EcrireDot(nomDot);
			}
			D.Retourner();
			//On affiche le tableau des 10 documents les plus consultés
			D.Afficher();
			delete l1;
			return 0;
		}
	}
}// ----- fin de main

//Permet de tester si un char* n'est composé que de nombre
bool testNombre(char* arg)
//On utilise la fonction isdigit pour vérifier que chaque caractère est un nombre
{
	bool estNombre=true;
	for(uint i=0;i<strlen(arg);i++)
	{
		if(!isdigit(arg[i]))
		{
			estNombre=false;
			return estNombre;
		}
	}
	return estNombre;
}
