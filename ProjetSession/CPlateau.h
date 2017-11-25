#pragma once
#include <vector>
#include "CCellule.h"

const int LIGNE = 10;
const int COLONNE = 15;
class CPlateau
{
private : 
	CCellule* plateau[LIGNE][COLONNE];
	int ligdep;
	int coldep;
	int ligarr;
	int colarr;
	int ligactuelle;
	int colactuelle; 
	int visites[LIGNE*COLONNE][2];
	int nbvisites;

public : 
	CPlateau();
	~CPlateau();
	void detruiremurbas(int ligne, int colonne);
	void detruiremurhaut(int ligne, int colonne);
	void detruiremurdroit(int ligne, int colonne);
	void detruiremurgauche(int ligne, int colonne);
	void parcoursplateau();

};
