#include "CPlateau.h"
#include <iostream>
#include <string>
#include <stdlib.h> /*srand, rand*/
#include <stdio.h> /*NULL*/
#include <time.h> /*time*/

using namespace std;

int CPlateau::firstInit = 0;

CPlateau::CPlateau() {
	if(firstInit == 0) { 
		firstInit = 1;
		srand(time(NULL));
	}

	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			plateau[i][j] = new CCellule(i, j);
		}
	}
	ligDep = rand() % LIGNE;
	colDep = 0;
	ligArr = 0;
	colArr = COLONNE - 1;
	ligActuelle = ligDep;
	colActuelle = colDep;

	//Initialiser le d�part
	plateau[ligDep][colDep]->SetMurDroit(false);

	//Liste ordonn�e des cases visit�es
	//Initialisation
	visites[LIGNE*COLONNE];
	for (int i = 0; i < LIGNE*COLONNE; i++) {
		visites[i] = 0;
	}

	//?? why ? ne faut-il pas modifier la valeur de la premi�re case dans ce cas et mettre une valeur dans le tableau ?
	nbVisites = 1;

	//GenerateRandomLaby();

	//Test
	/**DetruireMurGauche(ligDep, colDep);
	DetruireMurBas(ligDep, colDep + 1);
	DetruireMurGauche(ligDep + 1, colDep + 1);
	DetruireMurGauche(ligDep + 1, colDep + 2);
	DetruireMurGauche(ligDep + 1, colDep + 3);
	DetruireMurHaut(ligDep + 1, colDep + 4);
	DetruireMurHaut(ligDep, colDep + 4);
	DetruireMurDroit(ligDep - 1, colDep + 4);
	DetruireMurDroit(ligDep - 1, colDep + 3);/**/
}


CPlateau::~CPlateau() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			delete plateau[i][j];
		}
	}
}

bool CPlateau::DetruireMurBas(int ligne, int colonne) {
	try {
		if ((ligne < 0) || (ligne >= LIGNE) || (colonne < 0) || (colonne >= COLONNE)) {
			throw "ERROR : index outside of the range";
		}
		if (ligne + 1 < LIGNE) {
			plateau[ligne][colonne]->SetMurBas(false);
			plateau[ligne + 1][colonne]->SetMurHaut(false);
			return true;
		}
		return false;
	}
	catch (char* const e) {
		cerr << e << endl;
		return false;
	}
}

bool CPlateau::DetruireMurHaut(int ligne, int colonne) {
	try {
		if ((ligne < 0) || (ligne >= LIGNE) || (colonne < 0) || (colonne >= COLONNE)) {
			throw "ERROR : index outside of the range";
		}
		if (ligne - 1 >= 0) {
			plateau[ligne][colonne]->SetMurHaut(false);
			plateau[ligne - 1][colonne]->SetMurBas(false);
			return true;
		}
		return false;
	}
	catch (char* const e) {
		cerr << e << endl;
		return false;
	}
}

bool CPlateau::DetruireMurDroit(int ligne, int colonne) {
	try {
		if ((ligne < 0) || (ligne >= LIGNE) || (colonne < 0) || (colonne >= COLONNE)) {
			throw "ERROR : index outside of the range";
		}
		if (colonne - 1 >= 0) {
			plateau[ligne][colonne]->SetMurDroit(false);
			plateau[ligne][colonne - 1]->SetMurGauche(false);
			return true;
		}
		return false;
	}
	catch (char* const e) {
		cerr << e << endl;
		return false;
	}
}

bool CPlateau::DetruireMurGauche(int ligne, int colonne) {
	try {
		if ((ligne < 0) || (ligne >= LIGNE) || (colonne < 0) || (colonne >= COLONNE)) {
			throw "ERROR : index outside of the range";
		}
		if (colonne + 1 < COLONNE) {
			plateau[ligne][colonne]->SetMurGauche(false);
			plateau[ligne][colonne + 1]->SetMurDroit(false);
			return true;
		}
		return false;
	}
	catch (char* const e) {
		cerr << e << endl;
		return false;
	}
}

void CPlateau::AffichePlateau() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			//Affichage du mur du haut
			if (plateau[i][j]->GetMurHaut()) { cout << "* * * "; }
			else { AfficheElse(i, j); }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			//Mur droit et case centre (correspond � l'espace)
			if (plateau[i][j]->GetMurDroit()) { cout << "*   "; }
			else { cout << "    "; }
			//Mur gauche
			if (plateau[i][j]->GetMurGauche()) { cout << "* "; }
			else { cout << "  "; }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			//Affichage du mur du bas
			if (plateau[i][j]->GetMurBas()) { cout << "* * * "; }
			else { AfficheElse(i, j); }
		}
		cout << endl;
	}
}

void CPlateau::AfficheElse(int i, int j) {
	if (plateau[i][j]->GetMurDroit()) { cout << "*   "; }
	else if ((!plateau[i][j]->GetMurDroit()) && (i + 1 >= LIGNE)) { //si je suis sur la derni�re ligne
		cout << "*   ";
	}
	else if ((!plateau[i][j]->GetMurDroit()) && (plateau[i + 1][j]->GetMurDroit())) {
		cout << "*   ";
	}
	else { cout << "    "; }
	if (plateau[i][j]->GetMurGauche()) { cout << "* "; }
	else if ((!plateau[i][j]->GetMurGauche()) && (i + 1 >= LIGNE)) {
		cout << "* ";
	}
	else if ((!plateau[i][j]->GetMurGauche()) && (plateau[i + 1][j]->GetMurGauche())) {
		cout << "* ";
	}
	else { cout << "  "; }
}

bool CPlateau::IsVisited(int ligNew, int colNew) {
	return plateau[ligNew][colNew]->GetVisite();
}

void CPlateau::ResetValues(int & haut, int & bas, int & droit, int & gauche, int & javance)
{
	haut = 0;
	bas = 0;
	droit = 0;
	gauche = 0;
	javance = 0;
}

CCellule * CPlateau::RecupererCelluleDavant(CCellule* oldCellule)
{
	return nullptr;
	//return la cellule qui se trouve une case avant celle que l'on cherche
}

void CPlateau::AjoutDansTableau(CCellule * cellule)
{
	cellule->SetVisite(true);
	bool ajoute = false;
	for (int i = 0; i < LIGNE*COLONNE; i++) {
		if ((visites[i] == 0) && (!ajoute)) {
			visites[i] = cellule;
			ajoute = true;
		}
	}
}

void CPlateau::GenerateRandomLaby() {
	/* Choisissez un point de d�part dans le champ.
	 * Choisissez al�atoirement un mur � ce point et d�coupez un passage dans la cellule adjacente, mais seulement si la cellule adjacente n'a pas encore �t� visit�e. Cela devient la nouvelle cellule actuelle.
	 * Si toutes les cellules adjacentes ont �t� visit�es, sauvegardez jusqu'� la derni�re cellule qui a des murs non courbes et r�p�tez.
	 * L'algorithme se termine lorsque le processus a �t� sauvegard� jusqu'au point de d�part.
	 */

	 //Point de d�part
	CCellule* celluleActuelle = plateau[ligActuelle][colActuelle];

	//Mettre un compteur pour compter si les 4 cases adjacentes a ma case actuelle sont d�j� visit�es
	int javance = 0; //si on r�ussi � avancer dans une cellule non visit�e, peut �tre pourra �tre enlevee

	//Ne pas incr�menter 2 fois si on test 2 fois un mur du haut
	int testHaut = 0, testBas = 0, testDroit = 0, testGauche = 0;
	//4 variables pour s'assurer qu'on ajoute pas 2 fois la m�me face � 'bloquee'

	bool auMoinsBougeUneFois = false;
	//Choix du mur
	bool bonChoix = false;
	int choixMur = 0; //entre 0 et 3
	//0 Mur Haut
	//1 Mur Gauche
	//2 Mur Bas
	//3 Mur Droit



	//do while : tant que on est pas revenu au point de d�part
	do {
		//On choisi un mur a suppr
		do {
			choixMur = rand() % 4;
			if ((testHaut == 0) && (choixMur == 0)) { bonChoix = true; }
			else if ((testGauche == 0) && (choixMur == 1)) { bonChoix = true; }
			else if ((testBas == 0) && (choixMur == 2)) { bonChoix = true; }
			else if ((testDroit == 0) && (choixMur == 3)) { bonChoix = true; }
		} while (!bonChoix);

		if ((testHaut == 0) || (testBas == 0) || (testDroit == 0) || (testGauche == 0)) { //s'il reste des cases non visit�es autour
			switch (choixMur)
			{
			case 0:
				if ((ligActuelle - 1 >= 0) && (ligActuelle - 1 < LIGNE)) { //si une case au dessus existe
					if (!IsVisited(ligActuelle - 1, colActuelle)) { //si la case adjacente n'a pas �t� visit�e
						if (DetruireMurHaut(ligActuelle, colActuelle)) { //si le mur du haut a pu �tre d�truit
							ligActuelle -= 1; //on se d�place sur la case adjacente
							celluleActuelle = plateau[ligActuelle][colActuelle];
							javance = 1;
						}
					}
					else { testHaut = 1; }
				}
				else { testHaut = 1; }
				break;
			case 1:
				if ((colActuelle + 1 >= 0) && (colActuelle + 1 < COLONNE)) { //si une case � gauche existe
					if (!IsVisited(ligActuelle, colActuelle + 1)) { //si la case adjacente n'a pas �t� visit�e
						if (DetruireMurGauche(ligActuelle, colActuelle)) { //si le mur de gauche a pu �tre d�truit
							colActuelle += 1;
							celluleActuelle = plateau[ligActuelle][colActuelle];
							javance = 1;
						}
					}
					else { testGauche = 1; }
				}
				else { testGauche = 1; }
				break;
			case 2:
				if ((ligActuelle + 1 >= 0) && (ligActuelle + 1 < LIGNE)) { //si une case en dessous existe
					if (!IsVisited(ligActuelle + 1, colActuelle)) { //si la case adjacente n'a pas �t� visit�e
						if (DetruireMurBas(ligActuelle, colActuelle)) { //si le mur du bas a pu �tre d�truit
							ligActuelle += 1;
							celluleActuelle = plateau[ligActuelle][colActuelle];
							javance = 1;
						}
					}
					else { testBas = 1; }
				}
				else { testBas = 1; }
				break;
			case 3:
				if ((colActuelle - 1 >= 0) && (colActuelle - 1 < COLONNE)) { //si une case � droite existe
					if (!IsVisited(ligActuelle, colActuelle - 1)) { //si la case adjacente n'a pas �t� visit�e
						if (DetruireMurDroit(ligActuelle, colActuelle)) { //si le mur de droite a pu �tre d�truit
							colActuelle -= 1;
							celluleActuelle = plateau[ligActuelle][colActuelle];
							javance = 1;
						}
					}
					else { testDroit = 1; }
				}
				else { testDroit = 1; }
				break;
			default:
				break;
			}
		}
		else { //On ne peux plus avancer dans une case non visit�e, on reviens en arri�re
			//TODO : revoir le else
			celluleActuelle = RecupererCelluleDavant(celluleActuelle);
			ligActuelle = celluleActuelle->GetLigne();
			colActuelle = celluleActuelle->GetColonne();
			ResetValues(testHaut, testBas, testDroit, testGauche, javance);
		}
		if(javance = 1){ 
			ResetValues(testHaut, testBas, testDroit, testGauche, javance);
			auMoinsBougeUneFois = true;
			AjoutDansTableau(celluleActuelle);
		}
	} while ((celluleActuelle != plateau[ligDep][colDep]) && (!auMoinsBougeUneFois));

	//Cr�ation de la sortie
	int ligArr = rand() % LIGNE;
	plateau[ligArr][colArr]->SetMurGauche(false);
}