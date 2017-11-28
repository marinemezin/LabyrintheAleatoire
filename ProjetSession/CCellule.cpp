#include "CCellule.h"

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

bool CCellule::GetVisite()
{
	return visite;
}

int CCellule::GetLigne()
{
	return ligne;
}

int CCellule::GetColonne()
{
	return colonne;
}

void CCellule::SetVisite(bool valeur)
{
	visite = valeur;
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
