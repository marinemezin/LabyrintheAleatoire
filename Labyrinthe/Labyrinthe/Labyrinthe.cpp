#include <windows.h>
#include <stdio.h>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

#define TIMER_1 10001

const char NomDeClasse[] = "MaClasse";
const int NbrImages = 10;


// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		PAINTSTRUCT     ps;
		HDC             hdc;
		BITMAP          bitmap;
		HDC             hdcMem;
		HGDIOBJ         oldBitmap;

		hdc = BeginPaint(hwnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);

		/*for (int y = 0; y < NbrImages; y++)
		{
			oldBitmap = SelectObject(hdcMem, Images[y]->getImage());

			GetObject(Images[y]->getImage(), sizeof(bitmap), &bitmap);
			/**
			// il faut ajouter Msimg32.lib
			TransparentBlt(hdc, Images[y]->getX(), Images[y]->getY(),
				bitmap.bmWidth, bitmap.bmHeight,
				hdcMem,
				0, 0,
				bitmap.bmWidth, bitmap.bmHeight,
				RGB(255, 255, 255));
			/*
			SelectObject(hdcMem, oldBitmap);
		}
		DeleteDC(hdcMem);

		EndPaint(hwnd, &ps);*/
		break;
	case WM_CREATE:
		// Initialize the window. 
		break;
	case WM_KEYDOWN:
		//Liste complete  : https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
		switch (wParam)
		{
		case VK_LEFT:
			//Moi->gauche();
			break;
		case VK_RIGHT:
			//Moi->droite();
			break;
		case VK_UP:
			//Moi->haut();
			break;
		case VK_DOWN:
			//Moi->bas();
			break;
		case VK_SPACE:
			//Moi->stop();
			break;
		default:
			if (wParam >= 0x41 && wParam <= 0x5A)
			{
				TCHAR ch = (TCHAR)wParam;
				char Text[2];
				Text[0] = ch;
				Text[1] = '\0';

				MessageBox(hwnd, Text, "Touche enfoncée",
					MB_ICONEXCLAMATION | MB_OK);
			}
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


void update(HWND hwnd)
{
	while (true)
	{
		// ajuster le refresh rate
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		RECT zone;
		GetClientRect(hwnd, &zone);				// la zone Écran à mettre à jour

												//InvalidateRect(hwnd, &zone, true);		// tout redessinner
		UpdateWindow(hwnd);						// go -> redessine
	}
}

void DrawCenteredText(HWND hWnd, char *text)
{
	HDC hDC;
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);
	hDC = GetDC(hWnd);
	SetTextColor(hDC, 0x000000FF);
	SetBkMode(hDC, TRANSPARENT);
	SetTextAlign(hDC, TA_CENTER | TA_TOP);
	TextOut(hDC, (int)((float)rcClient.right / 2), 5, text, strlen(text));
	ReleaseDC(hWnd, hDC);
}

void DrawRectangle(HWND hWnd, int xInit, int yInit)
{
	RECT clientRect;
	HBRUSH hBrush;
	HPEN hPen;
	// Fill the client area with a brush
	GetClientRect(hWnd, &clientRect);
	//Pour modifier la couleur de fond
	/*HRGN bgRgn = CreateRectRgnIndirect(&clientRect);
	hBrush = CreateSolidBrush(RGB(200, 200, 200));
	FillRgn(GetDC(hWnd), bgRgn, hBrush);
	*/

	hPen = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	SelectObject(GetDC(hWnd), hPen);
	SetBkColor(GetDC(hWnd), RGB(0, 0, 0));
	Rectangle(GetDC(hWnd), 10, 10, 200, 200);
}


// C'est le main de windows
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX	wc;
	HWND		hwnd;
	MSG			Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;						// la prodédure de callback
	wc.cbClsExtra = 0;								// mémoire de plus par classe
	wc.cbWndExtra = 0;								// mémoire de plus par objet
	wc.hInstance = hInstance;						// handle de l'application
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);			// icon (32x32) de la barre de tâche 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);		// curseur sir la fenêtre
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	// couleur du fond
	wc.lpszMenuName = NULL;							// nom de la barre de menu
	wc.lpszClassName = NomDeClasse;					// notre classe
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);	// icon (16x16) du coin

	if (!RegisterClassEx(&wc))						// on enregistre notre classe
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,						// type de fenêtre
		NomDeClasse,							// la classe qu'on a enregitré
		"Jeu de Labyrinthe",					// le titre
		WS_OVERLAPPEDWINDOW | WS_HSCROLL,		// style de la fenêtre 
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 500,	// x,y et taille de la fenêtre
		NULL,									// Fenêtre parente
		NULL,									// Menu
		hInstance,								// l'application
		NULL);									// paramètres de création (pointeur)

	if (hwnd == NULL)							// toujours vérifier que c'est OK
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	/*for (int y = 0; y < NbrImages - 1; y++)
	{
		Images[y] = new CImage("IconShield.bmp", y * 40 + 1, (y % 10), hwnd, hInstance);
	}
	Moi = new CMoi("IconHydra.bmp", 300, 3, hwnd, hInstance);
	Images[NbrImages - 1] = Moi;
	*/

	ShowWindow(hwnd, nCmdShow);					// on affiche la fenêtre
	UpdateWindow(hwnd);							// mise à jour

	//new std::thread(update, hwnd);
	DrawCenteredText(hwnd, "Bienvenue sur le jeu de labyrinthe !!");
	DrawRectangle(hwnd, 10000, 10000);

	SetTimer(hwnd, TIMER_1, 10000, (TIMERPROC)NULL);
	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)	// on loop ici
	{
		TranslateMessage(&Msg);					// on fetch le message
		DispatchMessage(&Msg);					// On agit
		/*if ((Msg.message == WM_TIMER) && (Msg.wParam == TIMER_1) )
			MessageBox(NULL, "Déjà une minute de passé!", "Info", MB_OK);*/
	}
	return 1;
}
