#include "CCellule.h"

CCellule::CCellule(int lig, int col){
	visite = false;
	int ligne = lig;
	int colonne = col;
	bool murhaut = true;
	bool murbas = true;
	bool murdroit = true;
	bool murgauche = true;
}

CCellule::~CCellule(){

}


void CCellule::modifmurhaut() {
	murhaut = false;
}
void CCellule::modifmurbas() {

}
void modifmurdroit() {

}
void modifmurgauche() {

}