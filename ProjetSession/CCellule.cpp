#include "CCellule.h"

CCellule::CCellule(int lig, int col, CPlateau p){
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

}
void CCellule::modifmurbas() {

}
void CCellule::modifmurdroit() {

}
void CCellule::modifmurgauche() {

}