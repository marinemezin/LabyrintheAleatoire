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
	void deplacement(int lig, int col);
	int getligne();
	int getcolonne();
};