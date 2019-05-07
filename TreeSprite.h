#pragma once
#include "Sprite.h"
#include <iostream>

class TreeSprite : public Sprite
{
public:
	// Constructor(s)/Destructor
	TreeSprite(Bitmap* pBitmap);
	TreeSprite(Bitmap* pBitmap, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP);
	TreeSprite(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP);
	virtual ~TreeSprite() {};

	virtual void OnCollisionEnter(Sprite* otherSprite) override;
	virtual void OnCollisionExit(Sprite* otherSprite) override;
	virtual void OnCollisionStay(Sprite* otherSprite) override;
};