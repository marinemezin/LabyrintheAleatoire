#include "CPlateau.h"

CPlateau::CPlateau() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			plateau[i][j] = &CCellule(i, j, this);
		}
	}
	ligdep = LIGNE/2 -LIGNE%2;
	coldep = 0;
	ligarr = ligdep;
	colarr = COLONNE;
	ligactuelle = ligdep;
	colactuelle = coldep;
	visites[150][2];
	visites[0][0] = ligdep;
	visites[0][1] = coldep;
	for (int i = 1; i < LIGNE*COLONNE; i++) {
		visites[i][0] = 0;
		visites[i][1] = 0;
	}
	nbvisites = 1;
}


CPlateau::~CPlateau() {

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

void CPlateau::parcoursplateau() {
	
}