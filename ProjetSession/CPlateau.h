#pragma once
#include <vector>
class CPlateau
{
private : 
	CCellule plateau[10][15];
	int ligdep;
	int coldep;
	int ligarr;
	int colarr;


public : 
	void detruiremurbas(int ligne, int colonne);
	void detruiremurhaut(int ligne, int colonne);
	void detruiremurdroit(int ligne, int colonne);
	void detruiremurgauche(int ligne, int colonne);
	
};
