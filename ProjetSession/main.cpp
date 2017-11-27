#include<iostream>
#include "CPlateau.h"
using namespace std;


int main()
{
	CPlateau* monPlateau = new CPlateau();
	monPlateau->AffichePlateau();
	system("PAUSE");
	return 0;
}


/* une cellule a 9 cases sont centre est vide et ces murs sont des etoiles et il y a des doubles murs
pour passer de l'un a l'autre on fait passer le bonhomme dans sont centre
*/

/* 
Réfléchir à la manière d'enregistrer les cases visitées
Commencer à réfléchir aux méthodes de CJoueur (déplacer, ...)
Réfléchir pour interface, couvrir une partie du labyrinthe, etc...
*/
