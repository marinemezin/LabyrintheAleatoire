#include<iostream>
#include "CPlateau.h"
using namespace std;


int main()
{
	CPlateau* monPlateau = new CPlateau();
	monPlateau->afficheplateau();
	system("PAUSE");
	return 0;	
}


/* une cellule a 9 cases sont centre est vide et ces murs sont des etoiles et il y a des doubles murs
pour passer de l'un a l'autre on fait passer le bonhomme dans sont centre
*/

/* 
Choisissez un point de d�part dans le champ.
Choisissez al�atoirement un mur � ce point et d�coupez un passage dans la cellule adjacente, mais seulement si la cellule adjacente n'a pas encore �t� visit�e. Cela devient la nouvelle cellule actuelle.
Si toutes les cellules adjacentes ont �t� visit�es, sauvegardez jusqu'� la derni�re cellule qui a des murs non courbes et r�p�tez.
L'algorithme se termine lorsque le processus a �t� sauvegard� jusqu'au point de d�part.
*/

/*il n'est pas g�r� si on essaie de supprimer un mur qui n'est pas dans le tableau*/
