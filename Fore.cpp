//-----------------------------------------------------------------
// Fore 2 Application
// C++ Source - Fore.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Fore.h"

//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------

Camera camera;

//DEBUG
std::list<Sprite> selectedSprites;
int originMouseX = -1;
int originMouseY = -1;
bool selectMode = false;
RECT    selectBounds = { 0, 0, 600, 400 };
TreeSprite* selectSprite;
Bitmap* _pSelectBitmap;

void SelectSprites()
{
	if (Input::KeyPressed(InputKeys::KEY::MOUSELEFT))
	{
		selectMode = true;
		originMouseX=Input::GetWorldMouseX();
		originMouseY=Input::GetWorldMouseY();

		selectSprite = new TreeSprite(_pSelectBitmap, selectBounds, BA_WRAP);
		selectSprite->SetPosition(Input::GetWorldMouseX(), Input::GetWorldMouseY());
		selectSprite->Scale(0.0f, 0.0f);
		_pGame->AddSprite((Sprite*)selectSprite);
	}

	if (selectMode)
	{
		if (Input::KeyHeld(InputKeys::KEY::MOUSELEFT))
		{
			selectSprite->Scale((float)(Input::GetWorldMouseX() - originMouseX) / (float)selectSprite->GetWidth(), (float)(Input::GetWorldMouseY() - originMouseY) / (float)selectSprite->GetHeight());
			//_pSelectBitmap->SetWidth(Input::MouseX - originMouseX);
			//_pSelectBitmap->SetHeight(Input::MouseY - originMouseY);
			//selectSprite->SetBounds(RECT{ originMouseX,originMouseY,Input::MouseX,Input::MouseY });
		}

		if (Input::KeyReleased(InputKeys::KEY::MOUSELEFT))
		{
			selectMode = false;
			originMouseX = -1;
			originMouseY = -1;
			_pGame->DeleteSprite(selectSprite);
		}
	}
}

void GenerateMap()
{

}

BOOL GameInitialize(HINSTANCE hInstance)
{
  // Create the game engine
  _pGame = new GameEngine(hInstance, TEXT("Fore 2"), TEXT("Fore 2"), IDI_FORE, IDI_FORE_SM, 21*50, 15*50);
  if (_pGame == NULL)
    return FALSE;

  // Set the frame rate
  _pGame->SetFrameRate(30);

  // Store the instance handle
  _hInstance = hInstance;

  return TRUE;
}

int rowCount = 32;
int colCount = 64;
int ** gameMap = new int * [rowCount];

void GameStart(HWND hWindow)
{


	// Seed the random number generator
	srand(GetTickCount());

	//Initialize the map
	for (int i = 0; i < rowCount; i++)
	{
		gameMap[i] = (int*)calloc(colCount,sizeof(int));
	}

	//Fill in the borders
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			if(i==0 || i==rowCount-1||j==0||j==colCount-1)
				gameMap[i][j] = 1;
		}
	}

	//Provide center obstacles
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			//The closer it is to the midpoint to the center, the higher the likelyhood
			if (rand() % (abs(abs((i - rowCount / 2))-rowCount/4) + 1) < 1
				&& rand() % (abs(abs((j - colCount / 2))-colCount/4) + 1) < 1)
				gameMap[i][j] = 1;
			
			//The closer it is to the center, the higher the likelyhood
			if (rand() % (abs(i - rowCount / 2)+ 1) < 1
				&& rand() % (abs(j - colCount / 2) + 1) < 1)
				gameMap[i][j] = 1;
		}
	}

	//todo->check 4 adjacent cells around each cell. If there's not even a single 1-valued cell, make this cell (and 3 random cells 1 cell adjacent to it) equal to 1

	//Fill in with some random obstacles
	int roundCount = 7;
	for (int curRound = 0; curRound < roundCount; curRound++)
	{
		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < colCount; j++)
			{
				int neighborCount = 0;

				for (int neighborRow = -2; neighborRow <= 2; neighborRow++)
				{
					for (int neighborCol = -2; neighborCol <= 2; neighborCol++)
					{
						if (i + neighborRow < 0 || i + neighborRow >= rowCount
							|| j + neighborCol < 0 || j + neighborCol >= colCount)
							continue;

						if (neighborRow == 0 && neighborCol == 0)
							continue;

						if (gameMap[i + neighborRow][j + neighborCol] == 1)
							neighborCount++;

					}
				}

				if (neighborCount>8 && rand()%100>75)
					gameMap[i][j] = 1;
			}
		}
	}

	roundCount = 2;
	for (int curRound = 0; curRound < roundCount; curRound++)
	{
		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < colCount; j++)
			{
				int neighborCount = 0;

				for (int neighborRow = -1; neighborRow <= 1; neighborRow++)
				{
					for (int neighborCol = -1; neighborCol <= 1; neighborCol++)
					{
						if (i + neighborRow < 0 || i + neighborRow >= rowCount
							|| j + neighborCol < 0 || j + neighborCol >= colCount)
							continue;

						if (neighborRow == 0 && neighborCol == 0)
							continue;

						if (gameMap[i + neighborRow][j + neighborCol] == 1)
							neighborCount++;

					}
				}

				if (neighborCount > 2 && rand() % 100 > 75)
					gameMap[i][j] = 1;
			}
		}
	}

	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			int neighborCount = 0;

			for (int neighborRow = -1; neighborRow <= 1; neighborRow++)
			{
				for (int neighborCol = -1; neighborCol <= 1; neighborCol++)
				{
					if (i + neighborRow < 0 || i + neighborRow >= rowCount
						|| j + neighborCol < 0 || j + neighborCol >= colCount)
						continue;

					if (neighborRow == 0 && neighborCol == 0)
						continue;

					if (gameMap[i + neighborRow][j + neighborCol] == 1)
						neighborCount++;

				}
			}

			if (neighborCount==0)
				gameMap[i][j] = 0;
		}
	}
	

	//Fill in with some random obstacles
	
	
	



	//DEBUG
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			std::cout << gameMap[i][j];
		}
		std::cout << std::endl;
	}


  // Create the offscreen device context and bitmap
  _hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
  _hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow),
    _pGame->GetWidth(), _pGame->GetHeight());
  SelectObject(_hOffscreenDC, _hOffscreenBitmap);

  // Create and load the bitmaps
  HDC hDC = GetDC(hWindow);
  _pForestBitmap = new Bitmap(hDC, IDB_FOREST, _hInstance);
  _pGolfBallBitmap = new Bitmap(hDC, IDB_GOLFBALL, _hInstance);
  _pSelectBitmap = new Bitmap(hDC, IDB_GOLFBALL, _hInstance);

  // Create the golf ball sprites
  /*
  RECT    rcBounds = { 0, 0, 600, 400 };
  TreeSprite* pSprite;
  pSprite = new TreeSprite(_pGolfBallBitmap, rcBounds, BA_WRAP);
  pSprite->SetVelocity(5, 3);
  _pGame->AddSprite((Sprite*)pSprite);
  pSprite = new TreeSprite(_pGolfBallBitmap, rcBounds, BA_WRAP);
  pSprite->SetVelocity(3, 2);
  _pGame->AddSprite((Sprite*)pSprite);
  rcBounds.left = 265; rcBounds.right = 500; rcBounds.bottom = 335;
  pSprite = new TreeSprite(_pGolfBallBitmap, rcBounds, BA_BOUNCE);
  pSprite->SetVelocity(-6, 5);
  _pGame->AddSprite((Sprite*)pSprite);
  rcBounds.right = 470;
  pSprite = new TreeSprite(_pGolfBallBitmap, rcBounds, BA_BOUNCE);
  pSprite->SetVelocity(7, -3);
  _pGame->AddSprite((Sprite*)pSprite);
  */
  camera = Camera();

  // Set the initial drag info
  _pDragSprite = NULL;
  
  //DEBUG
  Bitmap* gathererBitmap = new Bitmap(hDC, IDB_FOREST, _hInstance);
  //Gatherer* gatherer = new Gatherer(gathererBitmap);
  //gatherer->SetBitmap(_pGolfBallBitmap);
  //Gatherer* gatherer = new Gatherer(hDC, _hInstance);
  //_pGame->AddSprite((Sprite*)gatherer);

  Gatherer* gatherer = (_pGame->CreateSprite<Gatherer>(hDC));

}

void GameEnd()
{
  // Cleanup the offscreen device context and bitmap
  DeleteObject(_hOffscreenBitmap);
  DeleteDC(_hOffscreenDC);  

  // Cleanup the bitmaps
  delete _pForestBitmap;
  delete _pGolfBallBitmap;

  // Cleanup the sprites
  _pGame->CleanupSprites();

  // Cleanup the game engine
  delete _pGame;
}

void GameActivate(HWND hWindow)
{
}

void GameDeactivate(HWND hWindow)
{
}

void GamePaint(HDC hDC)
{
	

  // Draw the background forest
  //_pForestBitmap->Draw(hDC, 0, 0);
  RECT bgRect = { 0, 0, 0, 0 };
  _pGame->DrawBackground(hDC, _pForestBitmap, bgRect,&camera);

  // Draw the sprites
  _pGame->DrawSprites(hDC,&camera);
}

void GameCycle()
{
	//Update the inputs
	Input::UpdateKeys();

	SelectSprites();

	//Handle the input keys
	_pGame->HandleCameraMovement(&camera);

  // Update the sprites
  _pGame->UpdateSprites();

  // Obtain a device context for repainting the game
  HWND  hWindow = _pGame->GetWindow();
  HDC   hDC = GetDC(hWindow);

  // Paint the game to the offscreen device context
  GamePaint(_hOffscreenDC);

  // Blit the offscreen bitmap to the game screen
  BitBlt(hDC, 0, 0, _pGame->GetWidth(), _pGame->GetHeight(),
    _hOffscreenDC, 0, 0, SRCCOPY);

  //TODO -> This is a bit buggy
  //Reset the offscreen device context AKA clear the screen

  BitBlt(_hOffscreenDC, 0, 0, _pGame->GetWidth(), _pGame->GetHeight(),
	  _hOffscreenDC, 0, 0, BLACKNESS);

  // Cleanup
  ReleaseDC(hWindow, hDC);
}

void HandleKeys()
{
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{
}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
}

void MouseMove(int x, int y)
{
	Input::UpdateMousePosition(x, y,&camera);
}

void HandleJoystick(JOYSTATE jsJoystickState)
{
}

BOOL SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{
  // Swap the sprite velocities so that they appear to bounce
  POINT ptSwapVelocity = pSpriteHitter->GetVelocity();
  pSpriteHitter->SetVelocity(pSpriteHittee->GetVelocity());
  pSpriteHittee->SetVelocity(ptSwapVelocity);
  return TRUE;
}
