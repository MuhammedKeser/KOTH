#pragma once
#include "Sprite.h"
#include <iostream>
#include <windows.h>
#include "Resource.h"

class TreeSprite : public Sprite
{
public:
	// Constructor(s)/Destructor
	
	TreeSprite(HDC hDC, HINSTANCE hInstance) :Sprite(hDC, hInstance, IDB_TREE) {};
	TreeSprite(Bitmap* pBitmap) :Sprite(pBitmap, IDB_TREE) {};
	TreeSprite(Bitmap* pBitmap, RECT& rcBounds, UINT BITMAP_ID, BOUNDSACTION baBoundsAction = BA_STOP) : Sprite(pBitmap, rcBounds, IDB_TREE, baBoundsAction) {};
	TreeSprite(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) :
		Sprite(pBitmap, ptPosition, ptVelocity, iZOrder, rcBounds, IDB_TREE, baBoundsAction) {};
	virtual void Update() override;
	virtual ~TreeSprite() {};

	virtual void OnCollisionEnter(Sprite* otherSprite) override;
	virtual void OnCollisionExit(Sprite* otherSprite) override;
	virtual void OnCollisionStay(Sprite* otherSprite) override;
};