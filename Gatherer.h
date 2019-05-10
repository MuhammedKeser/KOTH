#pragma once
#include "Unit.h"
#include <iostream>
#include "Resource.h"

class Gatherer : public Unit
{
public:
	// Constructor(s)/Destructor
	Gatherer(HDC hDC, HINSTANCE hInstance) :Unit(hDC,hInstance) {};
	Gatherer(Bitmap* pBitmap) :Unit(pBitmap) {};
	Gatherer(Bitmap* pBitmap, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) : Unit(pBitmap, rcBounds, baBoundsAction) {};
	Gatherer(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) :
		Unit(pBitmap, ptPosition, ptVelocity, iZOrder, rcBounds, baBoundsAction) {};
	virtual ~Gatherer() {};

	virtual void OnCollisionEnter(Sprite* otherSprite) override;
	virtual void OnCollisionExit(Sprite* otherSprite) override;
	virtual void OnCollisionStay(Sprite* otherSprite) override;
protected:
	UINT BITMAP_ID = IDB_GOLFBALL;
}; 
