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
	bool timeOver;
	int seconds;

	static int firstInit;
	static mutex Verrou;

	void GenerateRandomLaby();
	bool IsVisited(int ligNew, int colNew);
	void ResetValues(int& haut, int& bas, int& droit, int& gauche, int& javance);
	CCellule* RecupererCelluleDavant(CCellule* oldCellule);
	bool AjoutDansTableau(CCellule* cellule);
	void ModifJoueur(int lig, int col);

public:
	CPlateau();
	~CPlateau();
	bool DetruireMurBas(int ligne, int colonne);
	bool DetruireMurHaut(int ligne, int colonne);
	bool DetruireMurDroit(int ligne, int colonne);
	bool DetruireMurGauche(int ligne, int colonne);
	//void AffichePlateau2(); //a garder !!!
	void AffichePlateau();
	void DeplacerJoueur();
	bool aGagne();
	int GetResultat();
	void Chronometre();
	void ResetPlateau();
	void ModifCellule(int lig, int col, bool visible);
	void ModifZ();
	void ModifQ();
	void ModifS();
	void ModifD();
};
