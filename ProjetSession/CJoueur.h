#pragma once


class CJoueur
{
private:
	int ligne;
	int colonne;
	int score;

public:
	CJoueur(int ligDep, int colDep);
	~CJoueur();
};