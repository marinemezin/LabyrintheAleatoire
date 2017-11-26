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
Choisissez un point de départ dans le champ.
Choisissez aléatoirement un mur à ce point et découpez un passage dans la cellule adjacente, mais seulement si la cellule adjacente n'a pas encore été visitée. Cela devient la nouvelle cellule actuelle.
Si toutes les cellules adjacentes ont été visitées, sauvegardez jusqu'à la dernière cellule qui a des murs non courbes et répétez.
L'algorithme se termine lorsque le processus a été sauvegardé jusqu'au point de départ.
*/

/*il n'est pas géré si on essaie de supprimer un mur qui n'est pas dans le tableau*/
