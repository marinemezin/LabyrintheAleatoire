#pragma once
#include <vector>
#include "CCellule.h"

static const int LIGNE = 8;
static const int COLONNE = 25;


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

	void initialisationDepArr();

public : 
	CPlateau();
	~CPlateau();
	void detruiremurbas(int ligne, int colonne);
	void detruiremurhaut(int ligne, int colonne);
	void detruiremurdroit(int ligne, int colonne);
	void detruiremurgauche(int ligne, int colonne);
	void afficheplateau();
};
