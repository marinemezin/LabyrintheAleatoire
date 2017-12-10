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

	//Liste ordonnée des cases visitées
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
	catch (char* const e) {
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
		return false;
	}
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

void CPlateau::ResetValues(int & haut, int & bas, int & droit, int & gauche, int & javance)
{
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

void CPlateau::ResetPlateau() {
	//Remet à jour les tableaux
	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			delete plateau[i][j];
			plateau[i][j] = new CCellule(i, j);
		}
	}
	for (int i = 0; i < LIGNE * COLONNE; i++) {
		visites[i] = 0;
	}
	//Remet à jour les variables
	ligDep = rand() % LIGNE;
	colDep = 0;
	ligArr = rand() % LIGNE;;
	colArr = COLONNE - 1;
	ligActuelle = ligDep;
	colActuelle = colDep;
	timeOver = false;
	seconds = 0;

	//Reset Joueur
	monJoueur->SetLigne(ligDep);
	monJoueur->SetColonne(colDep);

	//Initialiser le départ
	plateau[ligDep][colDep]->SetMurDroit(false);

	nbVisites = 1;

	GenerateRandomLaby();

	temps->join();
}

void CPlateau::GenerateRandomLaby() {
	/* Choisissez un point de départ dans le champ.
	* Choisissez aléatoirement un mur à ce point et découpez un passage dans la cellule adjacente, mais seulement si la cellule adjacente n'a pas encore été visitée. Cela devient la nouvelle cellule actuelle.
	* Si toutes les cellules adjacentes ont été visitées, sauvegardez jusqu'à la dernière cellule qui a des murs non courbes et répétez.
	* L'algorithme se termine lorsque le processus a été sauvegardé jusqu'au point de départ.
	*/

	//Point de départ
	CCellule* celluleActuelle = plateau[ligActuelle][colActuelle];

	//Mettre un compteur pour compter si les 4 cases adjacentes a ma case actuelle sont déjà visitées
	int javance = 0; //si on réussi à avancer dans une cellule non visitée, peut être pourra être enlevee

					 //Ne pas incrémenter 2 fois si on test 2 fois un mur du haut
	int testHaut = 0, testBas = 0, testDroit = 0, testGauche = 0;
	//4 variables pour s'assurer qu'on ajoute pas 2 fois la même face à 'bloquee'

	bool auMoinsBougeUneFois = false;
	//Choix du mur
	bool bonChoix = false;
	int choixMur = 0; //entre 0 et 3
					  //0 Mur Haut
					  //1 Mur Gauche
					  //2 Mur Bas
					  //3 Mur Droit



	//do while : tant que on est pas revenu au point de départ
	do {
		//On choisi un mur a suppr
		do {
			choixMur = rand() % 4;
			if ((testHaut == 0) && (choixMur == 0)) { bonChoix = true; }
			else if ((testGauche == 0) && (choixMur == 1)) { bonChoix = true; }
			else if ((testBas == 0) && (choixMur == 2)) { bonChoix = true; }
			else if ((testDroit == 0) && (choixMur == 3)) { bonChoix = true; }
		} while (!bonChoix);

		if ((testHaut == 0) || (testBas == 0) || (testDroit == 0) || (testGauche == 0)) { //s'il reste des cases non visitées autour
			switch (choixMur)
			{
			case 0:
				if ((ligActuelle - 1 >= 0) && (ligActuelle - 1 < LIGNE)) { //si une case au dessus existe
					if (!IsVisited(ligActuelle - 1, colActuelle)) { //si la case adjacente n'a pas été visitée
						if (DetruireMurHaut(ligActuelle, colActuelle)) { //si le mur du haut a pu être détruit
							ligActuelle -= 1; //on se déplace sur la case adjacente
							celluleActuelle = plateau[ligActuelle][colActuelle];
							javance = 1;
						}
					}
					else { testHaut = 1; }
				}
				else { testHaut = 1; }
				break;
			case 1:
				if ((colActuelle + 1 >= 0) && (colActuelle + 1 < COLONNE)) { //si une case à gauche existe
					if (!IsVisited(ligActuelle, colActuelle + 1)) { //si la case adjacente n'a pas été visitée
						if (DetruireMurGauche(ligActuelle, colActuelle)) { //si le mur de gauche a pu être détruit
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
					if (!IsVisited(ligActuelle + 1, colActuelle)) { //si la case adjacente n'a pas été visitée
						if (DetruireMurBas(ligActuelle, colActuelle)) { //si le mur du bas a pu être détruit
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
				if ((colActuelle - 1 >= 0) && (colActuelle - 1 < COLONNE)) { //si une case à droite existe
					if (!IsVisited(ligActuelle, colActuelle - 1)) { //si la case adjacente n'a pas été visitée
						if (DetruireMurDroit(ligActuelle, colActuelle)) { //si le mur de droite a pu être détruit
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
		else { //On ne peux plus avancer dans une case non visitée, on reviens en arrière
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

	//Création de la sortie
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
			}
			break;
		case 113: //q
			if (!(plateau[ligne][colonne]->GetMurDroit()) && (colonne > 0)) {
				monJoueur->Deplacement(ligne, colonne - 1);
			}
			break;
		case 115: //s
			if (!(plateau[ligne][colonne]->GetMurBas())) {
				monJoueur->Deplacement(ligne + 1, colonne);
			}
			break;
		case 100: //d
			if (!(plateau[ligne][colonne]->GetMurGauche())) {
				monJoueur->Deplacement(ligne, colonne + 1);
			}
			break;
		default:
			break;
		}
		AffichePlateau();
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