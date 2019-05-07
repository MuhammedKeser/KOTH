//-----------------------------------------------------------------
// Fore 2 Application
// C++ Header - Fore.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Resource.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "TreeSprite.h"

//#include <stack>
//#include <queue>

class coord {
public:
	int x;
	int y;
	int dist;
	coord* prev;

public:
	coord::coord(int x, int y) {
		this->x = x; this->y = y;
		dist = 0;    prev = NULL;
	}
	coord::coord(int x, int y, int dist, coord* prev) {
		this->x = x; this->y = y;
		this->dist = dist; this->prev = prev;
	}
};

//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE   _hInstance;
GameEngine* _pGame;
HDC         _hOffscreenDC;
HBITMAP     _hOffscreenBitmap;
Bitmap*     _pForestBitmap;
Bitmap*     _pGolfBallBitmap;
Sprite*     _pDragSprite;

int **map;
int maxrow = 15, maxcol = 21;  // 6*9
int wall, maxwall = ((maxrow - 3) / 2)*((maxcol - 3) / 2);