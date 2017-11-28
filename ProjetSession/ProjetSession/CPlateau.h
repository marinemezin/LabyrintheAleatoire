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
	CCellule* visites[LIGNE*COLONNE];
	int nbVisites;

	void GenerateRandomLaby();
	bool IsVisited(int ligNew, int colNew);
	void ResetValues(int& haut, int& bas, int& droit, int& gauche, int& javance);
	CCellule* RecupererCelluleDavant(CCellule* oldCellule);
	void AjoutDansTableau(CCellule* cellule);

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
	void AffichePlateau2();
};
