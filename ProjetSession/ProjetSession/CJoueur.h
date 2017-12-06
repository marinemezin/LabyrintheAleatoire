#pragma once


using namespace std;

class CJoueur
{
private:
	int ligne;
	int colonne;
	int score;

public:
	CJoueur(int ligdep, int coldep);
	~CJoueur();
	void Deplacement(int lig, int col);
	int GetLigne();
	int GetColonne();
};