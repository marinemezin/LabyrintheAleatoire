#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <conio.h>
#include "CCellule.h"
#include "CJoueur.h"

static const int LIGNE = 8;
static const int COLONNE = 15;
using namespace std;
class CPlateau
{
private:
	CCellule* plateau[LIGNE][COLONNE];
	int ligDep;
	int colDep;
	int ligArr;
	int colArr;
	int ligActuelle;
	int colActuelle;
	CCellule* visites[LIGNE*COLONNE];
	int nbVisites;
	CJoueur* monJoueur;
	thread* temps;

	void GenerateRandomLaby();
	bool IsVisited(int ligNew, int colNew);
	void ResetValues(int& haut, int& bas, int& droit, int& gauche, int& javance);
	CCellule* RecupererCelluleDavant(CCellule* oldCellule);
	void AjoutDansTableau(CCellule* cellule);
	void timer();

	static int firstInit;
	static mutex Verrou;

public:
	CPlateau();
	~CPlateau();
	bool DetruireMurBas(int ligne, int colonne);
	bool DetruireMurHaut(int ligne, int colonne);
	bool DetruireMurDroit(int ligne, int colonne);
	bool DetruireMurGauche(int ligne, int colonne);
	void AffichePlateau();
	void AffichePlateau2();
	void deplacementJoueur();
	bool aGagne();
};
