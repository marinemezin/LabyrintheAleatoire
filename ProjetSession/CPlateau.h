#pragma once
#include <vector>
#include "CCellule.h"

static const int LIGNE = 8;
static const int COLONNE = 15;


class CPlateau
{
private : 
	CCellule* plateau[LIGNE][COLONNE];
	int ligDep;
	int colDep;
	int ligArr;
	int colArr;
	int ligActuelle;
	int colActuelle; 
	int visites[LIGNE*COLONNE][2];
	int nbVisites;

	void InitialisationDepArr();

public : 
	CPlateau();
	~CPlateau();
	void DetruireMurBas(int ligne, int colonne);
	void DetruireMurHaut(int ligne, int colonne);
	void DetruireMurDroit(int ligne, int colonne);
	void DetruireMurGauche(int ligne, int colonne);
	void AffichePlateau();
	void AfficheElse(int i, int j);
};
