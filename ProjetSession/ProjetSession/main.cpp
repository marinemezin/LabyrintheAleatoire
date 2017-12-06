#include<iostream>
#include <Windows.h>
#include "CPlateau.h"
#include "CEcran.h"

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
// Notions/technologie non vu ne cours

//Activit�s bonus
//Ne r�afficher que le tour du joueur pour que �a lague moins
//Entr�e et sortie peuvent �tre n'importe o� autour du laby mais pas sur la m�me face

//Fait
//Timer et arret du jeu
//Plusieurs parties � la suite
//Score = dur�e restante sur le timer
//Labyrinthe se g�n�re al�atoirement, entr�e et sortie al�atoire
//Joueur peut se d�placer
//Joueur ne saute pas de mur, ne sort pas du plateau
//Identification de fin et d�but de jeu
//On poss�de 1 thread pour le timer qui se lance dans la m�thode DeplacerJoueur
