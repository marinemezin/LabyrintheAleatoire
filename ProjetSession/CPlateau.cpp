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
	ligDep = LIGNE/2 -LIGNE%2; //a modif pour que ça soit random entre 0 et LIGNE non inclu
	colDep = 0;
	ligArr = ligDep; //a modif pour que ça soit random entre 0 et LIGNE non inclu
	colArr = COLONNE - 1;
	ligActuelle = ligDep;
	colActuelle = colDep;

	//Liste ordonnée des cases visitées
	visites[LIGNE*COLONNE][2];
	visites[0][0] = ligDep;
	visites[0][1] = colDep;
	for (int i = 1; i < LIGNE*COLONNE; i++) {
		visites[i][0] = 0;
		visites[i][1] = 0;
	}

	//?? why ? ne faut-il pas modifier la valeur de la première case dans ce cas et mettre une valeur dans le tableau ?
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
			//Mur droit et case centre (correspond à l'espace)
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
	/* Choisissez un point de départ dans le champ.
	 * Choisissez aléatoirement un mur à ce point et découpez un passage dans la cellule adjacente, mais seulement si la cellule adjacente n'a pas encore été visitée. Cela devient la nouvelle cellule actuelle.
	 * Si toutes les cellules adjacentes ont été visitées, sauvegardez jusqu'à la dernière cellule qui a des murs non courbes et répétez.
	 * L'algorithme se termine lorsque le processus a été sauvegardé jusqu'au point de départ.
	 */
	
	//Point de départ
	CCellule* celluleActuelle = plateau[ligActuelle][colActuelle];


	//Commencer un while ici ? tant que on est pas revenu au point de départ




	//Mettre un compteur pour compter si les 4 cases adjacentes a ma case actuelle sont déjà visitées
	int javance; //si on réussi à avancer dans une cellule non visitée
	int bloquee; //a incrementer si on rencontre une case adjacente déjà visitée
	//Si bloquee = 4 on utilise le tableau pour retourner à la case d'avant (caseActuelle = cadeDavant)

	//Ne pas incrémenter 2 fois si on test 2 fois un mur du haut
	int testHaut;
	int testBas;
	int testDroit;
	int testGauche; //4 variables pour s'assurer qu'on ajoute pas 2 fois la même face à 'bloquee'




	//Choix du mur
	int choixMur = rand() % 4; //entre 0 et 3
	//0 Mur Haut
	//1 Mur Gauche
	//2 Mur Bas
	//3 Mur Droit

	//Faire une vérif préalable avant le switch
	//Exemple si testBas = 1
	//Cela veux dire que le bas a déjà été testé et c'est une case adjacente
	//Donc on ne veux pas retirer le 2
	//On refait un random sur choixMur jusqu'à ce qu'il soit différent de 2

	switch (choixMur)
	{
	case 0:
		if ((ligActuelle - 1 >= 0) && (ligActuelle - 1 < LIGNE)) { //si une case au dessus existe
			if (!IsVisited(ligActuelle - 1, colActuelle)) { //si la case adjacente n'a pas été visitée
				if (DetruireMurHaut(ligActuelle, colActuelle)) { //si le mur du haut a pu être détruit
					ligActuelle -= 1; //on se déplace sur la case adjacente
					celluleActuelle = plateau[ligActuelle][colActuelle];
					//Ajouter la case dans les cases visitees : créer méthode pour
				}
			}
		}
		break;
	case 1:
		if ((colActuelle + 1 >= 0) && (colActuelle + 1 < COLONNE)) { //si une case à gauche existe
			if (!IsVisited(ligActuelle, colActuelle + 1)) { //si la case adjacente n'a pas été visitée
				if (DetruireMurGauche(ligActuelle, colActuelle)) { //si le mur de gauche a pu être détruit
					colActuelle += 1;
					celluleActuelle = plateau[ligActuelle][colActuelle];
					//Ajouter la case dans les cases visitees : créer méthode pour
				}
			}
		}
		break;
	case 2:
		if ((ligActuelle + 1 >= 0) && (ligActuelle + 1 < LIGNE)) { //si une case en dessous existe
			if (!IsVisited(ligActuelle + 1, colActuelle)) { //si la case adjacente n'a pas été visitée
				if (DetruireMurBas(ligActuelle, colActuelle)) { //si le mur du bas a pu être détruit
					ligActuelle += 1;
					celluleActuelle = plateau[ligActuelle][colActuelle];
					//Ajouter la case dans les cases visitees : créer méthode pour
				}
			}
		}
		break;
	case 3:
		if ((colActuelle - 1 >= 0) && (colActuelle - 1 < COLONNE)) { //si une case à droite existe
			if (!IsVisited(ligActuelle, colActuelle - 1)) { //si la case adjacente n'a pas été visitée
				if (DetruireMurDroit(ligActuelle, colActuelle)) { //si le mur de droite a pu être détruit
					colActuelle -= 1;
					celluleActuelle = plateau[ligActuelle][colActuelle];
					//Ajouter la case dans les cases visitees : créer méthode pour
				}
			}
		}
		break;
	default:
		break;
	}


	//En dehors du while
	//Créer la sortie qui a pour colonne = COLONNE - 1; et ligne aléatoire entre 0 et LIGNE -1
}