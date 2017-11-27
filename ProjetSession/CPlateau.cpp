#include "CPlateau.h"
#include <iostream>

using namespace std;

CPlateau::CPlateau() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			//plateau[i][j] = &CCellule(i, j, this);
			plateau[i][j] = new CCellule(i, j, this);
		}
	}
	ligdep = LIGNE/2 -LIGNE%2; //a modif pour que ça soit random entre 0 et LIGNE non inclu
	coldep = 0;
	ligarr = ligdep; //a modif pour que ça soit random entre 0 et LIGNE non inclu
	colarr = COLONNE - 1;
	ligactuelle = ligdep;
	colactuelle = coldep;

	//Quesako ?
	visites[LIGNE*COLONNE][2];
	visites[0][0] = ligdep;
	visites[0][1] = coldep;
	for (int i = 1; i < LIGNE*COLONNE; i++) {
		visites[i][0] = 0;
		visites[i][1] = 0;
	}

	nbvisites = 1;

	initialisationDepArr();
}


CPlateau::~CPlateau() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			delete plateau[i][j];
		}
	}
}

void CPlateau::detruiremurbas(int ligne, int colonne) {
	plateau[ligne][colonne]->suppmurbas();
}

void CPlateau::detruiremurhaut(int ligne, int colonne) {
	plateau[ligne][colonne]->suppmurhaut();
}

void CPlateau::detruiremurdroit(int ligne, int colonne) {
	plateau[ligne][colonne]->suppmurdroit();
}

void CPlateau::detruiremurgauche(int ligne, int colonne) {
	plateau[ligne][colonne]->suppmurgauche();
}

void CPlateau::afficheplateau() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			//Affichage du mur du haut
			if (plateau[i][j]->getMurHaut()) { cout << "***"; }
			else { 
				if (plateau[i][j]->getMurDroit()) { cout << "* "; }
				else { cout << "  "; }
				if (plateau[i][j]->getMurGauche()) { cout << "*"; }
				else { cout << " "; }
			}
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			//Mur droit et case centre (correspond à l'espace)
			if (plateau[i][j]->getMurDroit()) { cout << "* "; }
			else { cout << "  "; }
			//Mur gauche
			if (plateau[i][j]->getMurGauche()) { cout << "*"; }
			else { cout << " "; }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			//Affichage du mur du bas
			if (plateau[i][j]->getMurBas()) { cout << "***"; }
			else {
				if (plateau[i][j]->getMurDroit()) { cout << "* "; }
				else { cout << "  "; }
				if (plateau[i][j]->getMurGauche()) { cout << "*"; }
				else { cout << " "; }
			}
		}
		cout << endl;
	}
}

void CPlateau::initialisationDepArr() {
	plateau[ligdep][coldep]->setMurDroit(false);
	plateau[ligarr][colarr]->setMurGauche(false);
}
