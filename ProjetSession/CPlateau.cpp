#include "CPlateau.h"
#include <iostream>
#include <string>

using namespace std;

static int fistInit = 0;

CPlateau::CPlateau() {
	if(firstInit == 0) { 
		firstInit = 1;
		srand(NULL);
	}

	for (int i = 0; i < LIGNE; i++) {
		for (int j = 0; j < COLONNE; j++) {
			plateau[i][j] = new CCellule(i, j);
		}
	}
	ligDep = LIGNE/2 -LIGNE%2; //a modif pour que �a soit random entre 0 et LIGNE non inclu
	colDep = 0;
	ligArr = ligDep; //a modif pour que �a soit random entre 0 et LIGNE non inclu
	colArr = COLONNE - 1;
	ligActuelle = ligDep;
	colActuelle = colDep;

	//Liste ordonn�e des cases visit�es
	visites[LIGNE*COLONNE][2];
	visites[0][0] = ligDep;
	visites[0][1] = colDep;
	for (int i = 1; i < LIGNE*COLONNE; i++) {
		visites[i][0] = 0;
		visites[i][1] = 0;
	}

	//?? why ? ne faut-il pas modifier la valeur de la premi�re case dans ce cas et mettre une valeur dans le tableau ?
	nbVisites = 1;

	InitialisationDepArr();
	GenerateRandomLaby();
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
		if ((ligne >= 0) && (ligne < LIGNE) && (colonne >= 0) && (colonne < COLONNE)) {
			throw "ERROR : index outside of the range";
		}
		plateau[ligne][colonne]->SetMurBas(false);
		if (ligne + 1 < LIGNE) {
			plateau[ligne + 1][colonne]->SetMurHaut(false);
		}
		return true;
	}
	catch (string const& error) {
		cerr << error << endl;
		return false;
	}
}

bool CPlateau::DetruireMurHaut(int ligne, int colonne) {
	try {
		if ((ligne >= 0) && (ligne < LIGNE) && (colonne >= 0) && (colonne < COLONNE)) {
			throw "ERROR : index outside of the range";
		}
		plateau[ligne][colonne]->SetMurHaut(false);
		if (ligne - 1 >= 0) {
			plateau[ligne - 1][colonne]->SetMurBas(false);
		}
		return true;
	}
	catch (string const& error) {
		cerr << error << endl;
		return false;
	}
}

bool CPlateau::DetruireMurDroit(int ligne, int colonne) {
	try {
		if ((ligne >= 0) && (ligne < LIGNE) && (colonne >= 0) && (colonne < COLONNE)) {
			throw "ERROR : index outside of the range";
		}
		plateau[ligne][colonne]->SetMurDroit(false);
		if (colonne - 1 >= 0) {
			plateau[ligne][colonne - 1]->SetMurGauche(false);
		}
		return true;
	}
	catch (string const& error) {
		cerr << error << endl;
		return false;
	}
}

bool CPlateau::DetruireMurGauche(int ligne, int colonne) {
	try {
		if ((ligne >= 0) && (ligne < LIGNE) && (colonne >= 0) && (colonne < COLONNE)) {
			throw "ERROR : index outside of the range";
		}
		plateau[ligne][colonne]->SetMurGauche(false);
		if (colonne + 1 < COLONNE) {
			plateau[ligne][colonne + 1]->SetMurDroit(false);
		}
		return true;
	}
	catch (string const& error) {
		cerr << error << endl;
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
	else if ((!plateau[i][j]->GetMurDroit()) && (plateau[i + 1][j]->GetMurDroit())) {
		cout << "*   ";
	}
	else { cout << "    "; }
	if (plateau[i][j]->GetMurGauche()) { cout << "* "; }
	else if ((!plateau[i][j]->GetMurGauche()) && (plateau[i + 1][j]->GetMurGauche())) {
		cout << "* ";
	}
	else { cout << "  "; }
}

void CPlateau::InitialisationDepArr() {
	plateau[ligDep][colDep]->SetMurDroit(false);
	plateau[ligArr][colArr]->SetMurGauche(false);
}

bool CPlateau::IsVisited(int ligNew, int colNew) {
	return plateau[ligNew][colNew]->GetVisite();
}

void CPlateau::GenerateRandomLaby() {
	/* Choisissez un point de d�part dans le champ.
	 * Choisissez al�atoirement un mur � ce point et d�coupez un passage dans la cellule adjacente, mais seulement si la cellule adjacente n'a pas encore �t� visit�e. Cela devient la nouvelle cellule actuelle.
	 * Si toutes les cellules adjacentes ont �t� visit�es, sauvegardez jusqu'� la derni�re cellule qui a des murs non courbes et r�p�tez.
	 * L'algorithme se termine lorsque le processus a �t� sauvegard� jusqu'au point de d�part.
	 */
	
	//Point de d�part
	CCellule* celluleActuelle = plateau[ligActuelle][colActuelle];


	//Commencer un while ici ? tant que on est pas revenu au point de d�part




	//Mettre un compteur pour compter si les 4 cases adjacentes a ma case actuelle sont d�j� visit�es
	int javance; //si on r�ussi � avancer dans une cellule non visit�e
	int bloquee; //a incrementer si on rencontre une case adjacente d�j� visit�e
	//Si bloquee = 4 on utilise le tableau pour retourner � la case d'avant (caseActuelle = cadeDavant)

	//Ne pas incr�menter 2 fois si on test 2 fois un mur du haut
	int testHaut;
	int testBas;
	int testDroit;
	int testGauche; //4 variables pour s'assurer qu'on ajoute pas 2 fois la m�me face � 'bloquee'




	//Choix du mur
	int choixMur = rand() % 4; //entre 0 et 3
	//0 Mur Haut
	//1 Mur Gauche
	//2 Mur Bas
	//3 Mur Droit

	//Faire une v�rif pr�alable avant le switch
	//Exemple si testBas = 1
	//Cela veux dire que le bas a d�j� �t� test� et c'est une case adjacente
	//Donc on ne veux pas retirer le 2
	//On refait un random sur choixMur jusqu'� ce qu'il soit diff�rent de 2

	switch (choixMur)
	{
	case 0:
		if ((ligActuelle - 1 >= 0) && (ligActuelle - 1 < LIGNE)) { //si une case au dessus existe
			if (!IsVisited(ligActuelle - 1, colActuelle)) { //si la case adjacente n'a pas �t� visit�e
				if (DetruireMurHaut(ligActuelle, colActuelle)) { //si le mur du haut a pu �tre d�truit
					ligActuelle -= 1; //on se d�place sur la case adjacente
					celluleActuelle = plateau[ligActuelle][colActuelle];
					//Ajouter la case dans les cases visitees : cr�er m�thode pour
				}
			}
		}
		break;
	case 1:
		if ((colActuelle + 1 >= 0) && (colActuelle + 1 < COLONNE)) { //si une case � gauche existe
			if (!IsVisited(ligActuelle, colActuelle + 1)) { //si la case adjacente n'a pas �t� visit�e
				if (DetruireMurGauche(ligActuelle, colActuelle)) { //si le mur de gauche a pu �tre d�truit
					colActuelle += 1;
					celluleActuelle = plateau[ligActuelle][colActuelle];
					//Ajouter la case dans les cases visitees : cr�er m�thode pour
				}
			}
		}
		break;
	case 2:
		if ((ligActuelle + 1 >= 0) && (ligActuelle + 1 < LIGNE)) { //si une case en dessous existe
			if (!IsVisited(ligActuelle + 1, colActuelle)) { //si la case adjacente n'a pas �t� visit�e
				if (DetruireMurBas(ligActuelle, colActuelle)) { //si le mur du bas a pu �tre d�truit
					ligActuelle += 1;
					celluleActuelle = plateau[ligActuelle][colActuelle];
					//Ajouter la case dans les cases visitees : cr�er m�thode pour
				}
			}
		}
		break;
	case 3:
		if ((colActuelle - 1 >= 0) && (colActuelle - 1 < COLONNE)) { //si une case � droite existe
			if (!IsVisited(ligActuelle, colActuelle - 1)) { //si la case adjacente n'a pas �t� visit�e
				if (DetruireMurDroit(ligActuelle, colActuelle)) { //si le mur de droite a pu �tre d�truit
					colActuelle -= 1;
					celluleActuelle = plateau[ligActuelle][colActuelle];
					//Ajouter la case dans les cases visitees : cr�er m�thode pour
				}
			}
		}
		break;
	default:
		break;
	}


	//En dehors du while
	//Cr�er la sortie qui a pour colonne = COLONNE - 1; et ligne al�atoire entre 0 et LIGNE -1
}