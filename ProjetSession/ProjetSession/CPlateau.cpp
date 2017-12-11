#include <iostream>
#include <string>
#include <Windows.h>
#include <stdlib.h> /*srand, rand*/
#include <stdio.h> /*NULL*/
#include <time.h> /*time*/
#include "CEcran.h"
#include "CPlateau.h"

using namespace std;

mutex CPlateau::Verrou;
int CPlateau::firstInit = 0;
const int rayonAffichage = 2;
const int DUREE_PARTIE = 30;

//27
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
	ligArr = rand() % LIGNE;;
	colArr = COLONNE - 1;
	ligActuelle = ligDep;
	colActuelle = colDep;
	timeOver = false;
	seconds = 0;

	//Initialiser le départ
	plateau[ligDep][colDep]->SetMurDroit(false);

	//Initialisation
	visites[LIGNE*COLONNE];
	for (int i = 0; i < LIGNE*COLONNE; i++) {
		visites[i] = 0;
	}
	nbVisites = 1;
	GenerateRandomLaby();
	monJoueur = new CJoueur(ligDep, colDep);
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
	delete monJoueur;
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
	catch (char* const e) { return false; }
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
	catch (char* const e) { return false; }
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
	catch (char* const e) { return false; }
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
	catch (char* const e) { return false; }
}

/*void CPlateau::AffichePlateau2() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			//Affichage du mur du haut
			if (plateau[i][j]->GetMurHaut()) { cout << "* * * "; }
			else { cout << "*   * "; }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			//Mur droit et case centre (correspond à l'espace)
			if (plateau[i][j]->GetMurDroit()) { cout << "* "; }
			else { cout << "  "; }
			//Le joueur
			if (monJoueur->GetLigne() == i && monJoueur->GetColonne() == j) {
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
}*/ //a garder

//37
void CPlateau::AffichePlateau() {
	Verrou.lock();
	CEcran::ClrScr();
	CEcran::Gotoxy(0, 0);
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			//Affichage du mur du haut
			if ((i > monJoueur->GetLigne() - rayonAffichage) && (i < monJoueur->GetLigne() + rayonAffichage) && (j > monJoueur->GetColonne() - rayonAffichage) && (j < monJoueur->GetColonne() + rayonAffichage)) {
				if (plateau[i][j]->GetMurHaut()) { cout << "* * * "; }
				else { cout << "*   * "; }
			}
			else { cout << "------"; }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			if ((i > monJoueur->GetLigne() - rayonAffichage) && (i < monJoueur->GetLigne() + rayonAffichage) && (j > monJoueur->GetColonne() - rayonAffichage) && (j < monJoueur->GetColonne() + rayonAffichage)) {
				//Mur droit et case centre (correspond à l'espace)
				if (plateau[i][j]->GetMurDroit()) { cout << "* "; }
				else { cout << "  "; }
				//Le joueur
				if (monJoueur->GetLigne() == i 
					&& monJoueur->GetColonne() == j) { cout << "O "; }
				else { cout << "  "; }
				//Mur gauche
				if (plateau[i][j]->GetMurGauche()) { cout << "* "; }
				else { cout << "  "; }
			}
			else { cout << "------"; }
		}
		cout << endl;
		for (int j = 0; j < COLONNE; j++) {
			if ((i > monJoueur->GetLigne() - rayonAffichage) && (i < monJoueur->GetLigne() + rayonAffichage) && (j > monJoueur->GetColonne() - rayonAffichage) && (j < monJoueur->GetColonne() + rayonAffichage)) {
				//Affichage du mur du bas
				if (plateau[i][j]->GetMurBas()) { cout << "* * * "; }
				else { cout << "*   * "; }
			}
			else { cout << "------"; }
		}
		cout << endl;
	}
	Verrou.unlock();
}

bool CPlateau::IsVisited(int ligNew, int colNew) {
	return plateau[ligNew][colNew]->GetVisite();
}

void CPlateau::ResetValues(int & haut, int & bas, int & droit, int & gauche, int & javance) {
	haut = 0;
	bas = 0;
	droit = 0;
	gauche = 0;
	javance = 0;
}

CCellule * CPlateau::RecupererCelluleDavant(CCellule* oldCell) {
	for (int i = 0; i < LIGNE * COLONNE; i++) {
		if ((visites[i]->GetLigne() == oldCell->GetLigne())
			&& (visites[i]->GetColonne() == oldCell->GetColonne())) {
			if (i == 0) { return visites[i]; }
			return visites[i - 1];
		}
	}
	return nullptr;
}

bool CPlateau::AjoutDansTableau(CCellule * cellule) {
	cellule->SetVisite(true);
	for (int i = 0; i < LIGNE*COLONNE; i++) {
		if (visites[i] == 0) {
			visites[i] = cellule;
			return true;
		}
	}
	return false;
}

//25
void CPlateau::ResetPlateau() {
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			delete plateau[i][j];
			plateau[i][j] = new CCellule(i, j);
		}
	}
	for (int i = 0; i < LIGNE * COLONNE; i++) {
		visites[i] = 0;
	}
	ligDep = rand() % LIGNE;
	colDep = 0;
	ligArr = rand() % LIGNE;;
	colArr = COLONNE - 1;
	ligActuelle = ligDep;
	colActuelle = colDep;
	timeOver = false;
	seconds = 0;
	monJoueur->SetLigne(ligDep);
	monJoueur->SetColonne(colDep);
	plateau[ligDep][colDep]->SetMurDroit(false);
	nbVisites = 1;
	GenerateRandomLaby();
	temps->join();
}

//87
/* Choisissez un point de départ dans le champ.
* Choisissez aléatoirement un mur à ce point et découpez un passage dans la cellule adjacente, mais seulement si la cellule adjacente n'a pas encore été visitée. Cela devient la nouvelle cellule actuelle.
* Si toutes les cellules adjacentes ont été visitées, sauvegardez jusqu'à la dernière cellule qui a des murs non courbes et répétez.
* L'algorithme se termine lorsque le processus a été sauvegardé jusqu'au point de départ.
*/
void CPlateau::GenerateRandomLaby() {
	CCellule* celluleActuelle = plateau[ligActuelle][colActuelle];
	int javance = 0;
	int testHaut = 0, testBas = 0, testDroit = 0, testGauche = 0;
	bool auMoinsBougeUneFois = false;
	bool bonChoix = false;
	int choixMur = 0;
	do {
		do {
			choixMur = rand() % 4;
			if ((testHaut == 0) && (choixMur == 0)) { bonChoix = true; }
			else if ((testGauche == 0) && (choixMur == 1)) { bonChoix = true; }
			else if ((testBas == 0) && (choixMur == 2)) { bonChoix = true; }
			else if ((testDroit == 0) && (choixMur == 3)) { bonChoix = true; }
		} while (!bonChoix);
		if ((testHaut == 0) || (testBas == 0) || (testDroit == 0) || (testGauche == 0)) { //s'il reste des cases non visitées autour
			switch (choixMur) {
			case 0: //Mur Haut
				if ((ligActuelle - 1 >= 0) && (ligActuelle - 1 < LIGNE)) { 
					if (!IsVisited(ligActuelle - 1, colActuelle)) { 
						if (DetruireMurHaut(ligActuelle, colActuelle)) {
							ligActuelle -= 1;
							celluleActuelle = plateau[ligActuelle][colActuelle];
							javance = 1;
						}
					}
					else { testHaut = 1; }
				}
				else { testHaut = 1; }
				break;
			case 1: //Mur Gauche
				if ((colActuelle + 1 >= 0) && (colActuelle + 1 < COLONNE)) { 
					if (!IsVisited(ligActuelle, colActuelle + 1)) { 
						if (DetruireMurGauche(ligActuelle, colActuelle)) { 
							colActuelle += 1;
							celluleActuelle = plateau[ligActuelle][colActuelle];
							javance = 1;
						}
					}
					else { testGauche = 1; }
				}
				else { testGauche = 1; }
				break;
			case 2: //Mur Bas
				if ((ligActuelle + 1 >= 0) && (ligActuelle + 1 < LIGNE)) { 
					if (!IsVisited(ligActuelle + 1, colActuelle)) { 
						if (DetruireMurBas(ligActuelle, colActuelle)) { 
							ligActuelle += 1;
							celluleActuelle = plateau[ligActuelle][colActuelle];
							javance = 1;
						}
					}
					else { testBas = 1; }
				}
				else { testBas = 1; }
				break;
			case 3: //Mur Droit
				if ((colActuelle - 1 >= 0) && (colActuelle - 1 < COLONNE)) { 
					if (!IsVisited(ligActuelle, colActuelle - 1)) { 
						if (DetruireMurDroit(ligActuelle, colActuelle)) { 
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
		else {
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
	plateau[ligArr][colArr]->SetMurGauche(false);
}

bool CPlateau::aGagne() {
	if ((monJoueur->GetColonne() == colArr) && (monJoueur->GetLigne() == ligArr)) {
		monJoueur->SetScore(DUREE_PARTIE - seconds);
		seconds = DUREE_PARTIE;
		return true;
	}
	return false;
}

int CPlateau::GetResultat() {
	return monJoueur->GetScore();
}

//38
void CPlateau::DeplacerJoueur() {
	temps = new thread(&CPlateau::Chronometre, this);
	AffichePlateau();
	char moncarac = _getch();
	while ((!aGagne()) && (!timeOver)) {
		int ligne = monJoueur->GetLigne();
		int colonne = monJoueur->GetColonne();
		switch (moncarac) {
		case 122: //z
			if (!(plateau[ligne][colonne]->GetMurHaut())) {
				monJoueur->Deplacement(ligne - 1, colonne);
				ModifZ();
			}
			break;
		case 113: //q
			if (!(plateau[ligne][colonne]->GetMurDroit()) && (colonne > 0)) {
				monJoueur->Deplacement(ligne, colonne - 1);
				ModifQ();
			}
			break;
		case 115: //s
			if (!(plateau[ligne][colonne]->GetMurBas())) {
				monJoueur->Deplacement(ligne + 1, colonne);
				ModifS();
			}
			break;
		case 100: //d
			if (!(plateau[ligne][colonne]->GetMurGauche())) {
				monJoueur->Deplacement(ligne, colonne + 1);
				ModifD();
			}
			break;
		default:
			break;
		}
		moncarac = _getch();
	}
}

void CPlateau::Chronometre() {
	int milliseconds = 0, minutes = 0;
	seconds = 0;
	while (seconds < DUREE_PARTIE) {
		if (milliseconds == 10) {
			seconds++;
			milliseconds = 0;
		}
		Verrou.lock();
		CEcran::Gotoxy(0, 25);
		cout << "Timer : " << seconds;
		Verrou.unlock();
		++milliseconds;
		Sleep(100);
	}
	timeOver = true;
}

//27
void CPlateau::ModifCellule(int lig, int col, bool visible) {
	if (visible) {
		Verrou.lock();
		CEcran::Gotoxy(6 * col, 3 * lig);
		if (plateau[lig][col]->GetMurHaut()) { cout << "* * * "; }
		else { cout << "*   * "; }
		CEcran::Gotoxy(6 * col, 3 * lig + 1);
		if (plateau[lig][col]->GetMurDroit() && plateau[lig][col]->GetMurGauche()) { cout << "*   * "; }
		if (!plateau[lig][col]->GetMurDroit() && plateau[lig][col]->GetMurGauche()) { cout << "    * "; }
		if (plateau[lig][col]->GetMurDroit() && !plateau[lig][col]->GetMurGauche()) { cout << "*     "; }
		if (!plateau[lig][col]->GetMurDroit() && !plateau[lig][col]->GetMurGauche()) { cout << "      "; }
		CEcran::Gotoxy(6 * col, 3 * lig + 2);
		if (plateau[lig][col]->GetMurBas()) { cout << "* * * "; }
		else { cout << "*   * "; }
		Verrou.unlock();
	}
	else {
		Verrou.lock();
		CEcran::Gotoxy(6 * col, 3 * lig);
		cout << "------";
		CEcran::Gotoxy(6 * col, 3 * lig + 1);
		cout << "------";
		CEcran::Gotoxy(6 * col, 3 * lig + 2);
		cout << "------";
		Verrou.unlock();
	}
}

void CPlateau::ModifZ() {
	for (int i = -rayonAffichage + 1; i < rayonAffichage; i++) {
		if (monJoueur->GetLigne() + rayonAffichage >= 0 && monJoueur->GetLigne() + rayonAffichage < LIGNE && monJoueur->GetColonne() + i >= 0 && monJoueur->GetColonne() + i < COLONNE) {
			ModifCellule(monJoueur->GetLigne() + rayonAffichage, monJoueur->GetColonne() + i, false);
		}
		if (monJoueur->GetLigne() + 1 - rayonAffichage >= 0 && monJoueur->GetLigne() + 1 - rayonAffichage < LIGNE && monJoueur->GetColonne() + i >= 0 && monJoueur->GetColonne() + i < COLONNE) {
			ModifCellule(monJoueur->GetLigne() + 1 - rayonAffichage, monJoueur->GetColonne() + i, true);
		}
	}
	Verrou.lock();
	CEcran::Gotoxy(6 * monJoueur->GetColonne() + 1, 3 * monJoueur->GetLigne() + 4);
	cout << "  ";
	CEcran::Gotoxy(6 * monJoueur->GetColonne() + 1, 3 * monJoueur->GetLigne() + 1);
	cout << " O";
	Verrou.unlock();
}

void CPlateau::ModifQ() {
	for (int i = -rayonAffichage + 1; i < rayonAffichage; i++) {
		if (monJoueur->GetLigne() + i >= 0 && monJoueur->GetLigne() + i < LIGNE && monJoueur->GetColonne() + rayonAffichage >= 0 && monJoueur->GetColonne() + rayonAffichage < COLONNE) {
			ModifCellule(monJoueur->GetLigne() + i, monJoueur->GetColonne() + rayonAffichage, false);
		}
		if (monJoueur->GetLigne() + i >= 0 && monJoueur->GetLigne() + i < LIGNE && monJoueur->GetColonne() + 1 - rayonAffichage >= 0 && monJoueur->GetColonne() + 1 - rayonAffichage < COLONNE) {
			ModifCellule(monJoueur->GetLigne() + i, monJoueur->GetColonne() + 1 - rayonAffichage, true);
		}
	}
	Verrou.lock();
	CEcran::Gotoxy(6 * monJoueur->GetColonne() + 7, 3 * monJoueur->GetLigne() + 1);
	cout << "  ";
	CEcran::Gotoxy(6 * monJoueur->GetColonne() + 1, 3 * monJoueur->GetLigne() + 1);
	cout << " O";
	Verrou.unlock();
}

void CPlateau::ModifS() {
	for (int i = -rayonAffichage + 1; i < rayonAffichage; i++) {
		if (monJoueur->GetLigne() - rayonAffichage >= 0 && monJoueur->GetLigne() - rayonAffichage < LIGNE && monJoueur->GetColonne() + i >= 0 && monJoueur->GetColonne() + i < COLONNE) {
			ModifCellule(monJoueur->GetLigne() - rayonAffichage, monJoueur->GetColonne() + i, false);
		}
		if (monJoueur->GetLigne() - 1 + rayonAffichage >= 0 && monJoueur->GetLigne() - 1 + rayonAffichage < LIGNE && monJoueur->GetColonne() + i >= 0 && monJoueur->GetColonne() + i < COLONNE) {
			ModifCellule(monJoueur->GetLigne() -1 + rayonAffichage, monJoueur->GetColonne() + i, true);
		}
	}
	Verrou.lock();
	CEcran::Gotoxy(6 * monJoueur->GetColonne() + 1, 3 * monJoueur->GetLigne() - 2);
	cout << "  ";
	CEcran::Gotoxy(6 * monJoueur->GetColonne() + 1, 3 * monJoueur->GetLigne() + 1);
	cout << " O";
	Verrou.unlock();
}

void CPlateau::ModifD() {
	for (int i = -rayonAffichage + 1; i < rayonAffichage; i++) {
		if (monJoueur->GetLigne() + i >= 0 && monJoueur->GetLigne() + i < LIGNE && monJoueur->GetColonne() - rayonAffichage >= 0 && monJoueur->GetColonne() - rayonAffichage < COLONNE) {
			ModifCellule(monJoueur->GetLigne() + i, monJoueur->GetColonne() - rayonAffichage, false);
		}
		if (monJoueur->GetLigne() + i >= 0 && monJoueur->GetLigne() + i < LIGNE && monJoueur->GetColonne() - 1 + rayonAffichage >= 0 && monJoueur->GetColonne() - 1 + rayonAffichage < COLONNE) {
			ModifCellule(monJoueur->GetLigne() + i, monJoueur->GetColonne() - 1 + rayonAffichage, true);
		}
	}
	Verrou.lock();
	CEcran::Gotoxy(6 * monJoueur->GetColonne() - 5, 3 * monJoueur->GetLigne() + 1);
	cout << "  ";
	CEcran::Gotoxy(6 * monJoueur->GetColonne() + 1, 3 * monJoueur->GetLigne() + 1);
	cout << " O";
	Verrou.unlock();
}
