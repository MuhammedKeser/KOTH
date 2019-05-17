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
	if (Input::KeyPressed(Input::KEY::MOUSELEFT))
	{
		selectMode = true;
		originMouseX=Input::WorldMouseX;
		originMouseY=Input::WorldMouseY;

		selectSprite = new TreeSprite(_pSelectBitmap, selectBounds, BA_WRAP);
		selectSprite->SetPosition(Input::WorldMouseX, Input::WorldMouseY);
		_pGame->AddSprite((Sprite*)selectSprite);
	}

	if (selectMode)
	{
		if (Input::KeyHeld(Input::KEY::MOUSELEFT))
		{
			selectSprite->Scale((float)(Input::WorldMouseX - originMouseX) / (float)selectSprite->GetWidth(), (float)(Input::WorldMouseY - originMouseY) / (float)selectSprite->GetHeight());
			//_pSelectBitmap->SetWidth(Input::MouseX - originMouseX);
			//_pSelectBitmap->SetHeight(Input::MouseY - originMouseY);
			//selectSprite->SetBounds(RECT{ originMouseX,originMouseY,Input::MouseX,Input::MouseY });
		}

		if (Input::KeyReleased(Input::KEY::MOUSELEFT))
		{
			selectMode = false;
			originMouseX = -1;
			originMouseY = -1;
			
		}
	}
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

void GameStart(HWND hWindow)
{
  // Seed the random number generator
  srand(GetTickCount());

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
  // See if a ball was clicked with the left mouse button
  if (bLeft && (_pDragSprite == NULL))
  {
    if ((_pDragSprite = _pGame->IsPointInSprite(x+camera.GetPosition().x, y + camera.GetPosition().y)) != NULL)
    {
      // Capture the mouse
      SetCapture(_pGame->GetWindow());

      // Simulate a mouse move to get started
      MouseMove(x, y);
    }
  }



}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
  // Release the mouse
  ReleaseCapture();

  // Stop dragging
  _pDragSprite = NULL;
}

void MouseMove(int x, int y)
{
	Input::UpdateMousePosition(x, y,&camera);

	//std::cout << Input::MouseX<<std::endl;
  if (_pDragSprite != NULL)
  {
    // Move the sprite to the mouse cursor position
    _pDragSprite->SetPosition(Input::WorldMouseX+camera.GetPosition().x - (_pDragSprite->GetWidth() / 2),
      Input::WorldMouseY+camera.GetPosition().y - (_pDragSprite->GetHeight() / 2));

  }
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
