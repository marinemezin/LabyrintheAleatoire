#include "CEcran.h"
#include "CCoul.h"
#include <iostream>
#include <Windows.h>


void CEcran::ClrScr()
{
/*#ifdef LINUX
	setCouleur(CCoul::Noir, CCoul::Blanc);
	for (int y = 0; y < 40; y++)
		std::cout << std::endl;
#else*/
	system("cls");
//#endif
}

void CEcran::Gotoxy(int x, int y)
{
/*#ifdef LINUX
	printf("%c[%d;%df", 0x1B, y, x);
#else*/
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD point;
	point.X = x;
	point.Y = y;
	SetConsoleCursorPosition(H, point);
//#endif
}


void CEcran::setCouleur(int couleurDeFond, int couleurDuTexte)
{
/*#ifdef LINUX
	if (couleurDeFond >= 0 && couleurDeFond < 8 &&
		couleurDuTexte >= 0 && couleurDuTexte < 8)
	{
		couleurDeFond += 40;
		couleurDuTexte += 30;
		printf("\x1b[%dm", couleurDeFond);
		printf("\x1b[%dm", couleurDuTexte);
	}
#else*/
	if (couleurDeFond >= 0 && couleurDeFond < 8 &&
		couleurDuTexte >= 0 && couleurDuTexte < 8)
	{
		HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
	}
//#endif
}



