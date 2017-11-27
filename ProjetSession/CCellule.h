#pragma once

class CPlateau;

class CCellule
{
private:
	bool visite;
	int ligne;
	int colonne;
	bool murhaut;
	bool murbas;
	bool murdroit;
	bool murgauche;
	CPlateau *plateau; 

public:
	CCellule(int lig, int col, CPlateau *p);
	~CCellule();
	void modifmurhaut();
	void modifmurbas();
	void modifmurdroit();
	void modifmurgauche();
	void suppmurhaut();
	void suppmurbas();
	void suppmurdroit();
	void suppmurgauche();
	void afficheCellule();
	bool getMurHaut();
	bool getMurBas();
	bool getMurDroit();
	bool getMurGauche();
	void setMurDroit(bool valeur);
	void setMurGauche(bool valeur);
	void setMurHaut(bool valeur);
	void setMurBas(bool valeur);
};