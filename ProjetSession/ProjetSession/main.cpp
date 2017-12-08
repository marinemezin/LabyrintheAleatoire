#include<iostream>
#include <string>
#include <Windows.h>
#include "CPlateau.h"
#include "CEcran.h"
#include "sqlite3.h"

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
			cout << endl << "Veuillez entrer un caractère.";
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

/*bool ConnectDB(sqlite3* database)
{
	if (sqlite3_open(DB, &database) == SQLITE_OK)
	{
		isOpenDB = true;
		return true;
	}

	return false;
}*/

/*void DisconnectDB(sqlite3* database)
{
	if (isOpenDB == true)
	{
		sqlite3_close(database);
	}
}*/

void BaseDeDonnees() {
	try {
		sqlite3* database;
		string name = GetUsername();
		
		//Connexion à la DB
		if (sqlite3_open(DB, &database) == SQLITE_OK) {
			isOpenDB = true;
		}
		cout << "Connection a la base de donnees reussi" << endl;
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
	/*bool onContinue = false;
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
	cout << "Score final : " << monPlateau->GetResultat() << endl;*/
	bool decision = ChoixEnregistrement();
	if (decision) {
		//cout << GetUsername() << endl;
		BaseDeDonnees();
	}
	system("PAUSE");
	return 0;
}


//A faire
// Notions/technologie non vu ne cours -> base de donnée qui enregistre les meilleurs score (avoir un username) ?
//Ajouter des choses à la liste...

//Activités bonus
//Ne réafficher que le tour du joueur pour que ça lague moins
//Entrée et sortie peuvent être n'importe où autour du laby mais pas sur la même face
//Ajouter des choses à la liste...

//Fait
//Timer et arret du jeu
//Plusieurs parties à la suite
//Score = durée restante sur le timer
//Labyrinthe se génère aléatoirement, entrée et sortie aléatoire
//Joueur peut se déplacer
//Joueur ne saute pas de mur, ne sort pas du plateau
//Identification de fin et début de jeu
//On possède 1 thread pour le timer qui se lance dans la méthode DeplacerJoueur
//Ajouter des choses à la liste...
