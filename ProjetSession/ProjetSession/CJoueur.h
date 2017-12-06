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
	int GetScore();
	void SetScore(int value);
	void SetLigne(int value);
	void SetColonne(int value);
};