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
std::list<Sprite*> selectedSprites;
int originMouseX = -1;
int originMouseY = -1;
bool selectMode = false;
RECT selectBounds = { 0, 0, 600, 400 };
RECT bounds = { -1000,-1000,10000,10000 };
Sprite* selectSprite;
Bitmap* _pSelectBitmap;
HDC hDC;

int grassCount = 5;
Bitmap** _pGrassBitmaps=new Bitmap*[grassCount];
Player player("Momo");
Player player2("ASP");
int rowCount = 64;
int colCount = 64;
//int ** gameMap = new int *[rowCount];
int cellWidth, cellHeight;
//DEBUG
StateHandler_Gatherer* debugStateHandler;

void MoveSelectedSprites() 
{
	if (Input::KeyPressed(InputKeys::KEY::MOUSERIGHT) &&
		selectedSprites.size() > 0)
	{
		list<Sprite*>::iterator curSprite;
		for (curSprite = selectedSprites.begin(); curSprite != selectedSprites.end(); curSprite++)
		{
			Unit* curUnit = dynamic_cast<Unit*>(*curSprite);
			if (!curUnit)
				continue;
			curUnit->SetDestination(Input::GetWorldMouseX(), Input::GetWorldMouseY(),cellWidth,cellHeight);
		}
		std::cout << selectedSprites.size();

		//selectedSprites.clear();
	}
}

void SelectSprites()
{
	if (Input::KeyPressed(InputKeys::KEY::MOUSELEFT))
	{
		selectedSprites.clear();
		selectMode = true;
		originMouseX=Input::GetWorldMouseX();
		originMouseY=Input::GetWorldMouseY();
		bounds = { -1000,-1000,10000,10000 };
		selectSprite = new Sprite(_pSelectBitmap, bounds, BA_WRAP);
		selectSprite->SetPosition(Input::GetWorldMouseX(), Input::GetWorldMouseY());
		selectSprite->Scale(1.0f, 1.0f);
		_pGame->AddSprite((Sprite*)selectSprite);
	}

	if (selectMode)
	{
		if (Input::KeyHeld(InputKeys::KEY::MOUSELEFT))
		{
			selectSprite->Scale((float)(Input::GetWorldMouseX() - originMouseX) / (float)selectSprite->GetWidth(), (float)(Input::GetWorldMouseY() - originMouseY) / (float)selectSprite->GetHeight());
			selectedSprites = selectSprite->GetCollisionList();
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

std::list<Tile*>backgroundTiles;
void GenerateMap()
{
	cellWidth = _pWallBitmap->GetWidth();
	cellHeight = _pWallBitmap->GetHeight();
	Map::CreateMap(64, 64,cellWidth,cellHeight);

	//DEBUG
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{

			if (Map::GetGridCell(i,j) == 1)
			{
				Sprite* newSprite = (Sprite*)_pGame->CreateSprite<Sprite>(hDC);
				newSprite->SetBitmap(_pWallBitmap);
				RECT rect = { newSprite->GetWidth()*j,newSprite->GetHeight()*i,newSprite->GetWidth()*(j + 1),newSprite->GetHeight()*(i + 1) };
				newSprite->SetPosition(rect);
				newSprite->RecalculateColliderRect();
				newSprite->isStatic = true;
				newSprite->name = "WALL";
				Map::SetSpriteGridCell(i,j,newSprite);
			}

			if (Map::GetGridCell(i, j) == 2)
			{
				TreeSprite* newSprite = (TreeSprite*)_pGame->CreateSprite<TreeSprite>(hDC);
				RECT rect = { newSprite->GetWidth()*j,newSprite->GetHeight()*i,newSprite->GetWidth()*(j + 1),newSprite->GetHeight()*(i + 1) };
				newSprite->SetPosition(rect);
				newSprite->RecalculateColliderRect();
				newSprite->isStatic = true;
				Map::SetSpriteGridCell(i, j, newSprite);
			}

			if (Map::GetGridCell(i, j) == 0 || Map::GetGridCell(i, j) == 2)
			{
				Bitmap* tileBitmap = _pGrassBitmaps[rand() % grassCount];
				RECT tilePosition = { tileBitmap->GetWidth()*j,tileBitmap->GetHeight()*i,tileBitmap->GetWidth()*(j + 1),tileBitmap->GetHeight()*(i + 1) };
				Tile* newTile = new Tile(tilePosition, tileBitmap);
				backgroundTiles.push_back(newTile);
			}
			std::cout << Map::GetGridCell(i, j);
		}
		std::cout << std::endl;
	}


	
}

BOOL GameInitialize(HINSTANCE hInstance)
{
  // Create the game engine
  _pGame = new GameEngine(hInstance, TEXT("King of the Hill"), TEXT("King of the Hill"), IDI_FORE, IDI_FORE_SM, 21*50, 15*50);
  if (_pGame == NULL)
    return FALSE;

  // Set the frame rate
  _pGame->SetFrameRate(60);

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
	hDC = GetDC(hWindow);
	_pForestBitmap = new Bitmap(hDC, IDB_FOREST, _hInstance);
	_pGolfBallBitmap = new Bitmap(hDC, IDB_GOLFBALL, _hInstance);
	_pTargetBitmap = new Bitmap(hDC, IDB_TARGET, _hInstance);
	_pSelectBitmap = new Bitmap(hDC, IDB_SELECT, _hInstance);
	_pWallBitmap = new Bitmap(hDC, IDB_WALL1, _hInstance);
	_pGrassBitmaps[0] =  new Bitmap(hDC, IDB_GRASS1, _hInstance) ;
	_pGrassBitmaps[1] =  new Bitmap(hDC, IDB_GRASS2, _hInstance) ;
	_pGrassBitmaps[2] = new Bitmap(hDC, IDB_GRASS3, _hInstance);
	_pGrassBitmaps[3] = new Bitmap(hDC, IDB_GRASS4, _hInstance);
	_pGrassBitmaps[4] = new Bitmap(hDC, IDB_GRASS5, _hInstance);


	GenerateMap();

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

  // Create the target, pow, and guy sprites
  _pTargetSprite = new Sprite(_pTargetBitmap, bounds, BA_STOP);
  _pTargetSprite->SetZOrder(4);
  _pGame->AddSprite(_pTargetSprite);
  _pTargetSprite->SetHidden(TRUE);


  
  //DEBUG
  //Gatherer* gatherer = new Gatherer(gathererBitmap);
  //gatherer->SetBitmap(_pGolfBallBitmap);
  //Gatherer* gatherer = new Gatherer(hDC, _hInstance);
  //_pGame->AddSprite((Sprite*)gatherer);


  /*
  Gatherer* gatherer = (_pGame->CreateSprite<Gatherer>(hDC));
  RECT newPosition = {100,100,100+gatherer->GetWidth(),100+gatherer->GetHeight()};
  gatherer->SetPosition(newPosition);

  gatherer = (_pGame->CreateSprite<Gatherer>(hDC));
  newPosition = { 200,200,200 + gatherer->GetWidth(),200 + gatherer->GetHeight() };
  gatherer->SetPosition(newPosition);

  Warrior* warrior = (_pGame->CreateSprite<Warrior>(hDC));
  newPosition = { 100,200,100 + warrior->GetWidth(),200 + warrior->GetHeight() };
  warrior->SetPosition(newPosition);
  */

  player.SpawnUnit<Gatherer>(hDC,_pGame,100,100);
  player.SpawnUnit<Warrior>(hDC, _pGame, 200, 200);
  player2.SpawnUnit<Warrior>(hDC, _pGame, 400, 200);
  Horse* horse = _pGame->CreateSprite<Horse>(hDC);
  horse->SetPosition(250,250);


  player.SpawnUnit<Gatherer>(hDC, _pGame, 150, 100);
  player.SpawnUnit<Warrior>(hDC, _pGame, 250, 200);

  //Debug->The static sprite optimization really helped!
  /*for (int i = 0; i < 100; i++)
  {
	  (_pGame->CreateSprite<Gatherer>(hDC));
  }*/

  //DEBUG
  debugStateHandler =new StateHandler_Gatherer();

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
  //RECT bgRect = { 0, 0, _pGame->GetWidth(), _pGame->GetHeight() };
  //_pGame->DrawBackground(hDC, _pForestBitmap, bgRect);

	//Draw the tiles
  /*
  std::list<Tile*>::iterator it;
  int tileCount = 0;
  for (it = backgroundTiles.begin(); it != backgroundTiles.end(); it++)
  {

	  if (
		  (*it)->m_position.left <= camera.GetPosition().x + _pGame->GetWidth() &&
		  camera.GetPosition().x <= (*it)->m_position.right &&
		  (*it)->m_position.top <= camera.GetPosition().y + _pGame->GetHeight() &&
		  camera.GetPosition().y <= (*it)->m_position.bottom
		  )
	  {
		  (*it)->Draw(hDC, &camera);
		  tileCount++;
	  }

  }
  */
  //std::cout << "TileCount: " << tileCount << std::endl;

  // Draw the sprites
  _pGame->DrawSprites(hDC,&camera);
}

void GameCycle()
{
	//Update the inputs
	Input::UpdateKeys();

	//DEBUG
	debugStateHandler->HandleTransitions();
	debugStateHandler->currentState->Act();
	//Handle the input keys
	_pGame->HandleCameraMovement(&camera);


  //Update the sprite collisions
  _pGame->UpdateCollisions();

  // Update the sprites
  _pGame->UpdateSprites();


  SelectSprites();
  MoveSelectedSprites();

  if (selectedSprites.size() > 0)
  {
	  list<Sprite*>::iterator curSprite;
	  for (curSprite = selectedSprites.begin(); curSprite != selectedSprites.end(); curSprite++)
	  {
		  //std::cout << "Selected!" << std::endl;
	  }
	  //std::cout << "Selected: " << selectedSprites.size() << std::endl;
  }


  _pGame->DeleteSprites();

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

	if (bLeft)
	{
		// Temporarily hide the target and pow sprites
		_pTargetSprite->SetHidden(FALSE);
	}


}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
	if (bLeft)
	{
		// Temporarily hide the target and pow sprites
		_pTargetSprite->SetHidden(TRUE);
	}

}

void MouseMove(int x, int y)
{
	Input::UpdateMousePosition(x, y,&camera);

	// Track the mouse with the target sprite
	_pTargetSprite->SetPosition(x - (_pTargetSprite->GetWidth() / 2), y - (_pTargetSprite->GetHeight() / 2));

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
