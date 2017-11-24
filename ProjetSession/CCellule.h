#pragma once
class CCellule
{
private:
	bool visite;
	int positionX;
	int positionY;
	bool murhaut;
	bool murbas;
	bool murdroit;
	bool murgauche;

public:
	CCellule(int positionX, int positionY);
	~CCellule();
	void modifmurhaut();
	void modifmurbas();
	void modifmurdroit();
	void modifmurgauche();

};