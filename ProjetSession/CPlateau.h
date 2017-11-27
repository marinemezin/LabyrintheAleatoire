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
	void GenerateRandomLaby();
	bool IsVisited(int ligNew, int colNew);

	static int firstInit;

public : 
	CPlateau();
	~CPlateau();
	bool DetruireMurBas(int ligne, int colonne);
	bool DetruireMurHaut(int ligne, int colonne);
	bool DetruireMurDroit(int ligne, int colonne);
	bool DetruireMurGauche(int ligne, int colonne);
	void AffichePlateau();
	void AfficheElse(int i, int j);
};
