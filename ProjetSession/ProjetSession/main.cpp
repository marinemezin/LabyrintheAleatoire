#include<iostream>
#include <Windows.h>
#include "CPlateau.h"
#include "CEcran.h"
#include <winsqlite\winsqlite3.h>

using namespace std;

const int NB_PARTIE = 2;

void AnnonceNewPartie() {
	CEcran::ClrScr();
	cout << "Une nouvelle partie va demarrer. Soyez pret !";
	Sleep(3000);
	CEcran::ClrScr();
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
