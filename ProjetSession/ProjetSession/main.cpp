#include<iostream>
#include "CPlateau.h"
using namespace std;


int main()
{
	try {
		CPlateau* monPlateau = new CPlateau();
		monPlateau->DeplacerJoueur();
	}
	catch (char* e) {
		cout << e;
	}
	system("PAUSE");
	return 0;
}
