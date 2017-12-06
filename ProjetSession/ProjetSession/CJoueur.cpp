#include "CJoueur.h"

CJoueur::CJoueur(int ligdep, int coldep) {
	ligne = ligdep;
	colonne = coldep;
	score = 0;
}

CJoueur::~CJoueur() {
}

int CJoueur::GetLigne() {
	return ligne;
}

int CJoueur::GetColonne() {
	return colonne;
}

void CJoueur::Deplacement(int lig, int col)
{
	ligne = lig;
	colonne = col;
}