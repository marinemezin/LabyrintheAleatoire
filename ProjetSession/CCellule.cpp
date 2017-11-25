#include "CCellule.h"

CCellule::CCellule(int lig, int col, CPlateau *p){
	visite = false;
	ligne = lig;
	colonne = col;
	murhaut = true;
	murbas = true;
	murdroit = true;
	murgauche = true;
	plateau = p;
}

CCellule::~CCellule(){

}


void CCellule::modifmurhaut() {
	murhaut = false;
	plateau->detruiremurbas(ligne + 1, colonne);
}

void CCellule::modifmurbas() {
	murbas = false;
	plateau->detruiremurhaut(ligne - 1, colonne);
}

void CCellule::modifmurdroit() {
	murdroit = false;
	plateau->detruiremurgauche(ligne, colonne + 1);
}

void CCellule::modifmurgauche() {
	murgauche = false;
	plateau->detruiremurdroit(ligne, colonne - 1);
}

void CCellule::suppmurhaut() {
	murhaut = false;
}

void CCellule::suppmurbas() {
	murbas = false;
}

void CCellule::suppmurdroit() {
	murdroit = false;
}

void CCellule::suppmurgauche() {
	murgauche = false;
}