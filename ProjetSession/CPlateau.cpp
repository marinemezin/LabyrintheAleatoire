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

void CPlateau::GenerateRandomLaby() {
	/* Choisissez un point de départ dans le champ.
	 * Choisissez aléatoirement un mur à ce point et découpez un passage dans la cellule adjacente, mais seulement si la cellule adjacente n'a pas encore été visitée. Cela devient la nouvelle cellule actuelle.
	 * Si toutes les cellules adjacentes ont été visitées, sauvegardez jusqu'à la dernière cellule qui a des murs non courbes et répétez.
	 * L'algorithme se termine lorsque le processus a été sauvegardé jusqu'au point de départ.
	 */
	
	//Point de départ
	CCellule* celluleActuelle = plateau[ligActuelle][colActuelle];

	//Choix du mur
	int choixMur = rand() % 4; //entre 0 et 3
	//0 Mur Haut
	//1 Mur Gauche
	//2 Mur Bas
	//3 Mur Droit
	switch (choixMur)
	{
	case 0:
		if (/*celluleAdjacente pas visitee*/true) {
			celluleActuelle->SetMurHaut(false);
			ligActuelle -= 1;
			celluleActuelle = plateau[ligActuelle][colActuelle];
		}
		break;
	case 1:
		if (/*celluleAdjacente pas visitee*/true) {
			celluleActuelle->SetMurGauche(false);
			colActuelle += 1;
			celluleActuelle = plateau[ligActuelle][colActuelle];
		}
		break;
	case 2:
		if (/*celluleAdjacente pas visitee*/true) {
			celluleActuelle->SetMurBas(false);
			ligActuelle += 1;
			celluleActuelle = plateau[ligActuelle][colActuelle];
		}
		break;
	case 3:
		if (/*celluleAdjacente pas visitee*/true) {
			celluleActuelle->SetMurDroit(false);
			colActuelle -= 1;
			celluleActuelle = plateau[ligActuelle][colActuelle];
		}
		break;
	default:
		break;
	}

}