#include "CJoueur.h"

CJoueur::CJoueur(int ligdep, int coldep) {
	ligne = ligdep;
	colonne = coldep;
	score = 0;
}

CJoueur::~CJoueur() {
}

int CJoueur::getligne() {
	return ligne;
}

int CJoueur::getcolonne() {
	return colonne;
}

void CJoueur::deplacement(int lig, int col)
{
	ligne = lig;
	colonne = col;
}