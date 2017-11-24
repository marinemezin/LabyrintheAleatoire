#include "CPlateau.h"
#pragma once
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
	CPlateau plateau; 

public:
	CCellule(int positionX, int positionY);
	~CCellule();
	void modifmurhaut();
	void modifmurbas();
	void modifmurdroit();
	void modifmurgauche();

};