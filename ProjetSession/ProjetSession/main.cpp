#include<iostream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include "CPlateau.h"
#include "CEcran.h"

/* Apres avoir créé le .lib depuis le .dll dans un dossier dans le projet
 * Integrer au Projet le chemin pour accéder à la librairie et au .h 
 * Dans C/C++/Général 1er truc en haut et dans Editeur de liens/Général/Ajouter librairies additionnel et Entree/Ajouter le /lib
 * Ajouter dans C:\Windows\System32 le fichier .dll
 * La base de données a été créé au préalable dans un logiciel
 * Ajouter la base de données dans le même sous dossier que le main ou alors préciser son chemin
*/
#include "bin\sqlite3.h"

#define DB "scores.db"

using namespace std;

const int NB_PARTIE = 3;
bool isOpenDB = false;

void AnnonceNewPartie() {
	CEcran::ClrScr();
	cout << "Une nouvelle partie va demarrer. Soyez pret !";
	Sleep(3000);
	CEcran::ClrScr();
}

//17
bool ChoixEnregistrement() {
	cout << "Souhaitez vous enregistrer votre score ? (O ou N) ";
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

bool addDataRow(sqlite3* database, string name, int score) {
	char *messageError = NULL;
	string sql = "INSERT INTO MeilleurScores(Nom, Score) VALUES ('" + name + "', " + to_string(score) + ")";
	char* sql2 = (char *)sql.c_str();
	sqlite3_exec(database, sql2, NULL, 0, &messageError);
	if (messageError != NULL) {
		cout << messageError << endl;
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
		if (sqlite3_open(DB, &database) == SQLITE_OK) { isOpenDB = true; }
		if (addDataRow(database, name, score)) {
			cout << "Score ajoute avec succes !" << endl;
		}
		else { cout << "Score non ajoute" << endl; }
		if (isOpenDB == true) { sqlite3_close(database); }
	}
	catch (exception& e) { cout << "ERROR : " << e.what() << endl;	}
}

//25
void getTableData(sqlite3* database) {
	sqlite3_stmt *statement;
	int prevRES[5];
	for (int i = 0; i < 5; i++) { prevRES[i] = 0; }
	char* query = "SELECT Nom, Score FROM MeilleurScores ORDER BY Score DESC";
	if (sqlite3_prepare(database, query, -1, &statement, 0) == SQLITE_OK) {
		int ctotal = sqlite3_column_count(statement);
		int res = 0, fin = 0;
		while (fin != 5) {
			res = sqlite3_step(statement);
			if (res == SQLITE_ROW) {
				for (int i = 0; i < ctotal; i++) {
					string s = (char*)sqlite3_column_text(statement, i); 
					cout << s;
					if (s.size() < 10) { cout << "\t\t"; }
					else { cout << "\t"; }
				}
				cout << endl;
			}
			if (res == SQLITE_DONE || res == SQLITE_ERROR) { break; }
			fin++;
		}
	}
}

void AffichageMeilleursScores() {
	try {
		sqlite3* database;
		if (sqlite3_open(DB, &database) == SQLITE_OK) { isOpenDB = true; }
		cout << endl;
		cout << "Nom du joueur\tScore" << endl;
		getTableData(database);
		if (isOpenDB == true) { sqlite3_close(database); }
	}
	catch (exception& e) { cout << "ERROR : " << e.what() << endl; }
}

//24
int main() {
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
	cout << "Score final : " << monPlateau->GetResultat() << endl << endl;
	bool decision = ChoixEnregistrement();
	if (decision) {
		BaseDeDonnees(monPlateau->GetResultat());
	}
	AffichageMeilleursScores();
	cout << endl;
	system("PAUSE");
	return 0;
}