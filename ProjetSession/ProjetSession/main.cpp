#include<iostream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include "CPlateau.h"
#include "CEcran.h"

/* Apres avoir cr�� le .lib depuis le .dll dans un dossier dans le projet
 * Integrer au Projet le chemin pour acc�der � la librairie et au .h 
 * Dans C/C++/G�n�ral 1er truc en haut et dans Editeur de liens/G�n�ral/Ajouter librairies additionnel et Entree/Ajouter le /lib
 * Ajouter dans C:\Windows\System32 le fichier .dll
 * La base de donn�es a �t� cr�� au pr�alable dans un logiciel
 * Ajouter la base de donn�es dans le m�me sous dossier que le main ou alors pr�ciser son chemin
*/
#include "bin\sqlite3.h"

#define DB "scores.db"

using namespace std;

const int NB_PARTIE = 2;
bool isOpenDB = false;

void AnnonceNewPartie() {
	CEcran::ClrScr();
	cout << "Une nouvelle partie va demarrer. Soyez pret !";
	Sleep(3000);
	CEcran::ClrScr();
}

bool ChoixEnregistrement() {
	cout << "Souhaitez vous enregistrer votre score ? ";
	char choix = 'a';
	do {
		try { cin >> choix; }
		catch (exception& e) {
			cout << endl << "Veuillez entrer un caract�re.";
		}
		if ((choix != 'O') && (choix != 'N')) {
			cout << endl << "Veuillez choisir entre O et N : ";
		}

	} while ((choix != 'O') && (choix != 'N'));
	cout << endl;
	if (choix == 'O') { return true; }
	else { return false; }
}

string GetUsername() {
	cout << "Entrez votre nom d'utilisateur : ";
	string name = "";
	cin.ignore();
	getline(cin, name);
	return name;
}

// Insert a data row into the table 
bool addDataRow(sqlite3* database, string name, int score)
{
	char *messageError = NULL;
	sqlite3_exec(database, "INSERT INTO MeilleurScores(Nom, Score) VALUES ('name', 1)", NULL, 0, &messageError);
	if (messageError != NULL) {
		sqlite3_free(messageError);
		messageError = NULL;
		return false;
	}
	return true;
}

void BaseDeDonnees(int score) {
	try {
		sqlite3* database;
		string name = GetUsername();
		cout << "Connection a la base de donnees..." << endl;
		//Connexion � la DB
		if (sqlite3_open(DB, &database) == SQLITE_OK) {
			isOpenDB = true;
		}
		cout << "Connecte !" << endl;
		if (addDataRow(database, name, score)) {
			cout << "Data added" << endl;
		}
		else {
			cout << "Ajout failed" << endl;
		}
		if (isOpenDB == true) {
			sqlite3_close(database);
		}
	}
	catch (exception& e) {
		cout << "Connexion a la base de donnees impossible" << endl;
	}
}

int main()
{
	bool onContinue = false;
	int compteurPartie = 0;
	CPlateau* monPlateau = new CPlateau();
	do {
		monPlateau->DeplacerJoueur();
		compteurPartie++;
		if (compteurPartie == NB_PARTIE) { onContinue = true; }
		if (compteurPartie < NB_PARTIE) { 
			AnnonceNewPartie(); 
			monPlateau->ResetPlateau();
		}
	} while (!onContinue);
	CEcran::ClrScr();
	cout << "Score final : " << monPlateau->GetResultat() << endl;
	/*bool decision = ChoixEnregistrement();
	if (decision) {
		//cout << GetUsername() << endl;
		BaseDeDonnees(monPlateau->GetResultat());
	}*/
	system("PAUSE");
	return 0;
}


//A faire
// Notions/technologie non vu ne cours -> base de donn�e qui enregistre les meilleurs score (avoir un username) ?
//Ajouter des choses � la liste...

//Activit�s bonus
//Ne r�afficher que le tour du joueur pour que �a lague moins
//Entr�e et sortie peuvent �tre n'importe o� autour du laby mais pas sur la m�me face
//Ajouter des choses � la liste...

//Fait
//Timer et arret du jeu
//Plusieurs parties � la suite
//Score = dur�e restante sur le timer
//Labyrinthe se g�n�re al�atoirement, entr�e et sortie al�atoire
//Joueur peut se d�placer
//Joueur ne saute pas de mur, ne sort pas du plateau
//Identification de fin et d�but de jeu
//On poss�de 1 thread pour le timer qui se lance dans la m�thode DeplacerJoueur
//Ajouter des choses � la liste...
