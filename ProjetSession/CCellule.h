#pragma once

class CCellule
{
private:
	bool visite;
	int ligne;
	int colonne;
	bool murHaut;
	bool murBas;
	bool murDroit;
	bool murGauche;

public:
	CCellule(int lig, int col);
	~CCellule();
	bool GetMurHaut();
	bool GetMurBas();
	bool GetMurDroit();
	bool GetMurGauche();
	bool GetVisite();
	void SetVisite(bool valeur);
	void SetMurDroit(bool valeur);
	void SetMurGauche(bool valeur);
	void SetMurHaut(bool valeur);
	void SetMurBas(bool valeur);
};