#include "CCellule.h"
#include "CPlateau.h"

CCellule::CCellule(int lig, int col){
	visite = false;
	ligne = lig;
	colonne = col;
	murHaut = true;
	murBas = true;
	murDroit = true;
	murGauche = true;
}

CCellule::~CCellule(){
}

bool CCellule::GetMurHaut() {
	return murHaut;
}

bool CCellule::GetMurBas() {
	return murBas;
}

bool CCellule::GetMurDroit() {
	return murDroit;
}

bool CCellule::GetMurGauche() {
	return murGauche;
}

void CCellule::SetMurDroit(bool valeur) {
	murDroit = valeur;
}

void CCellule::SetMurGauche(bool valeur) {
	murGauche = valeur;
}

void CCellule::SetMurHaut(bool valeur) {
	murHaut = valeur;
}

void CCellule::SetMurBas(bool valeur) {
	murBas = valeur;
}
