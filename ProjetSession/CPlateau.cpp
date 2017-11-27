#include "CPlateau.h"
#include <iostream>

using namespace std;

CPlateau::CPlateau() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			plateau[i][j] = new CCellule(i, j);
		}
	}
	ligDep = LIGNE/2 -LIGNE%2; //a modif pour que ça soit random entre 0 et LIGNE non inclu
	colDep = 0;
	ligArr = ligDep; //a modif pour que ça soit random entre 0 et LIGNE non inclu
	colArr = COLONNE - 1;
	ligActuelle = ligDep;
	colActuelle = colDep;

	//Quesako ?
	visites[LIGNE*COLONNE][2];
	visites[0][0] = ligDep;
	visites[0][1] = colDep;
	for (int i = 1; i < LIGNE*COLONNE; i++) {
		visites[i][0] = 0;
		visites[i][1] = 0;
	}
	nbVisites = 1;
	//Fin du quesako

	InitialisationDepArr();

	//Test
	/**DetruireMurGauche(ligDep, colDep);
	DetruireMurBas(ligDep, colDep + 1);
	DetruireMurGauche(ligDep + 1, colDep + 1);
	DetruireMurGauche(ligDep + 1, colDep + 2);
	DetruireMurGauche(ligDep + 1, colDep + 3);
	DetruireMurHaut(ligDep + 1, colDep + 4);
	DetruireMurHaut(ligDep, colDep + 4);
	DetruireMurDroit(ligDep - 1, colDep + 4);
	DetruireMurDroit(ligDep - 1, colDep + 3);/**/
}


CPlateau::~CPlateau() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			delete plateau[i][j];
		}
	}
}

void CPlateau::DetruireMurBas(int ligne, int colonne) {
	plateau[ligne][colonne]->SetMurBas(false);
	if (ligne + 1 < LIGNE) { 
		plateau[ligne + 1][colonne]->SetMurHaut(false);
	}
}

void CPlateau::DetruireMurHaut(int ligne, int colonne) {
	plateau[ligne][colonne]->SetMurHaut(false);
	if (ligne - 1 >= 0) {
		plateau[ligne - 1][colonne]->SetMurBas(false);
	}
}

void CPlateau::DetruireMurDroit(int ligne, int colonne) {
	plateau[ligne][colonne]->SetMurDroit(false);
	if (colonne - 1 >= 0) {
		plateau[ligne][colonne - 1]->SetMurGauche(false);
	}
}

void CPlateau::DetruireMurGauche(int ligne, int colonne) {
	plateau[ligne][colonne]->SetMurGauche(false);
	if (colonne + 1 < COLONNE) {
		plateau[ligne][colonne + 1]->SetMurDroit(false);
	}
}

void CPlateau::AffichePlateau() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			//Affichage du mur du haut
			if (plateau[i][j]->GetMurHaut()) { cout << "* * * "; }
			else { AfficheElse(i, j); }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			//Mur droit et case centre (correspond à l'espace)
			if (plateau[i][j]->GetMurDroit()) { cout << "*   "; }
			else { cout << "    "; }
			//Mur gauche
			if (plateau[i][j]->GetMurGauche()) { cout << "* "; }
			else { cout << "  "; }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			//Affichage du mur du bas
			if (plateau[i][j]->GetMurBas()) { cout << "* * * "; }
			else { AfficheElse(i, j); }
		}
		cout << endl;
	}
}

void CPlateau::AfficheElse(int i, int j) {
	if (plateau[i][j]->GetMurDroit()) { cout << "*   "; }
	else if ((!plateau[i][j]->GetMurDroit()) && (plateau[i + 1][j]->GetMurDroit())) {
		cout << "*   ";
	}
	else { cout << "    "; }
	if (plateau[i][j]->GetMurGauche()) { cout << "* "; }
	else if ((!plateau[i][j]->GetMurGauche()) && (plateau[i + 1][j]->GetMurGauche())) {
		cout << "* ";
	}
	else { cout << "  "; }
}

void CPlateau::InitialisationDepArr() {
	plateau[ligDep][colDep]->SetMurDroit(false);
	plateau[ligArr][colArr]->SetMurGauche(false);
}
