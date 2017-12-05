#include "CPlateau.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include "CEcran.h"
#include <stdlib.h> /*srand, rand*/
#include <stdio.h> /*NULL*/
#include <time.h> /*time*/

using namespace std;

mutex CPlateau::Verrou;

int CPlateau::firstInit = 0;
const int aff = 3;

CPlateau::CPlateau() {
	if (firstInit == 0) {
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

	nbVisites = 1;

	GenerateRandomLaby();
	monJoueur = new CJoueur(ligDep, colDep);
	temps = new thread(&CPlateau::timer, this);
}


CPlateau::~CPlateau() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			delete plateau[i][j];
		}
	}
	for (int i = 0; i < LIGNE * COLONNE; i++) {
		delete visites[i];
	}
	temps->detach();
	delete temps;
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
			else { cout << "*   * "; }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			//Mur droit et case centre (correspond � l'espace)
			if (plateau[i][j]->GetMurDroit()) { cout << "* "; }
			else { cout << "  "; }
			//Le joueur
			if (monJoueur->getligne() == i && monJoueur->getcolonne() == j) {
				cout << "O ";
			}
			else {
				cout << "  ";
			}
			//Mur gauche
			if (plateau[i][j]->GetMurGauche()) { cout << "* "; }
			else { cout << "  "; }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			//Affichage du mur du bas
			if (plateau[i][j]->GetMurBas()) { cout << "* * * "; }
			else { cout << "*   * "; }
		}
		cout << endl;
	}
}

void CPlateau::AffichePlateau2() {
	Verrou.lock();
	CEcran::ClrScr();
	CEcran::Gotoxy(0, 0);
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			//Affichage du mur du haut
			if ((i > monJoueur->getligne() - aff) && (i < monJoueur->getligne() + aff) && (j > monJoueur->getcolonne() - aff) && (j < monJoueur->getcolonne() + aff)) {
				if (plateau[i][j]->GetMurHaut()) { cout << "* * * "; }
				else { cout << "*   * "; }
			}
			else { cout << "      "; }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			if ((i > monJoueur->getligne() - aff) && (i < monJoueur->getligne() + aff) && (j > monJoueur->getcolonne() - aff) && (j < monJoueur->getcolonne() + aff)) {
				//Mur droit et case centre (correspond � l'espace)
				if (plateau[i][j]->GetMurDroit()) { cout << "* "; }
				else { cout << "  "; }
				//Le joueur
				if (monJoueur->getligne() == i && monJoueur->getcolonne() == j) {
					cout << "O ";
				}
				else {
					cout << "  ";
				}
				//Mur gauche
				if (plateau[i][j]->GetMurGauche()) { cout << "* "; }
				else { cout << "  "; }
			}
			else { cout << "      "; }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			if ((i > monJoueur->getligne() - aff) && (i < monJoueur->getligne() + aff) && (j > monJoueur->getcolonne() - aff) && (j < monJoueur->getcolonne() + aff)) {
				//Affichage du mur du bas
				if (plateau[i][j]->GetMurBas()) { cout << "* * * "; }
				else { cout << "*   * "; }
			}
			else { cout << "      "; }
		}
		cout << endl;
	}
	Verrou.unlock();
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
	//return la cellule qui se trouve une case avant celle que l'on cherche
	for (int i = 0; i < LIGNE * COLONNE; i++) {
		if ((visites[i]->GetLigne() == oldCellule->GetLigne())
			&& (visites[i]->GetColonne() == oldCellule->GetColonne())) {
			if (i == 0) { return visites[i]; }
			return visites[i - 1];
		}
	}
	return nullptr; //security
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
			celluleActuelle = RecupererCelluleDavant(celluleActuelle);
			ligActuelle = celluleActuelle->GetLigne();
			colActuelle = celluleActuelle->GetColonne();
			ResetValues(testHaut, testBas, testDroit, testGauche, javance);
		}
		if (javance == 1) {
			ResetValues(testHaut, testBas, testDroit, testGauche, javance);
			nbVisites++;
			AjoutDansTableau(celluleActuelle);
		}
	} while ((celluleActuelle != plateau[ligDep][colDep]) || (nbVisites < LIGNE * COLONNE));

	//Cr�ation de la sortie
	ligArr = rand() % LIGNE;
	plateau[ligArr][colArr]->SetMurGauche(false);
}

bool CPlateau::aGagne() {
	bool ok = false;
	if ((monJoueur->getcolonne() == colArr) && (monJoueur->getligne() == ligArr)) {
		ok = true;
	}
	return ok;
}

void CPlateau::deplacementJoueur() {
	AffichePlateau2();
	char moncarac = _getch();
	while (!aGagne()) {
		int ligne = monJoueur->getligne();
		int colonne = monJoueur->getcolonne();
		switch (moncarac) {
		case 122: //z
			if (!(plateau[ligne][colonne]->GetMurHaut())) {
				monJoueur->deplacement(ligne - 1, colonne);
				AffichePlateau2();
			}
			break;
		case 113: //q
			if (!(plateau[ligne][colonne]->GetMurDroit()) && (colonne > 0)) {
				monJoueur->deplacement(ligne, colonne - 1);
				AffichePlateau2();
			}
			break;
		case 115: //s
			if (!(plateau[ligne][colonne]->GetMurBas())) {
				monJoueur->deplacement(ligne + 1, colonne);
				AffichePlateau2();
			}
			break;
		case 100: //d
			if (!(plateau[ligne][colonne]->GetMurGauche())) {
				monJoueur->deplacement(ligne, colonne + 1);
				AffichePlateau2();
			}
			break;
		default:
			break;
		}
		moncarac = _getch();
	}
}

void CPlateau::timer() {
	int milliseconds = 0;
	int seconds = 0;
	int prevSeconds = -1;
	int minutes = 0;
	while (minutes != 1) {
		if (milliseconds == 10) {
			++seconds;
			milliseconds = 0;
		}
		if (seconds == 60) {
			++minutes;
			seconds = 0;
		}
		if (prevSeconds != seconds) {
			Verrou.lock();
			CEcran::Gotoxy(0, 25);
			cout << "Timer : " << minutes << ":" << seconds;
			Verrou.unlock();
		}
		++milliseconds;
		Sleep(100);
	}
}