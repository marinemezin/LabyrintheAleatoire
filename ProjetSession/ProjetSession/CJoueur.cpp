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

int CJoueur::GetScore() {
	return score;
}

void CJoueur::SetScore(int value) {
	if (value > 0) {
		score += value;
	}
}

void CJoueur::SetLigne(int value) {
	ligne = value;
}

void CJoueur::SetColonne(int value) {
	colonne = value;
}

void CJoueur::Deplacement(int lig, int col)
{
	ligne = lig;
	colonne = col;
}