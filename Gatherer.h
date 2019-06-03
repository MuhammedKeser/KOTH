#pragma once
#include "Unit.h"
#include <iostream>
#include "Resource.h"
#include "TreeSprite.h"
#include "Warrior.h"
class Gatherer : public Unit
{
public:
	// Constructor(s)/Destructor
	Gatherer(HDC hDC, HINSTANCE hInstance) :Unit(hDC, hInstance,IDB_GATHERERL) {};
	Gatherer(Bitmap* pBitmap) :Unit(pBitmap, IDB_GATHERERL) { };
	Gatherer(Bitmap* pBitmap, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) : Unit(pBitmap, rcBounds, IDB_GATHERERL,baBoundsAction) {};
	Gatherer(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) :
		Unit(pBitmap, ptPosition, ptVelocity, iZOrder, rcBounds, IDB_GATHERERL,baBoundsAction) {
	};
	virtual ~Gatherer() {};

	virtual void OnCollisionEnter(Sprite* otherSprite) override;
	virtual void OnCollisionExit(Sprite* otherSprite) override;
	virtual void OnCollisionStay(Sprite* otherSprite) override;
	void Update() override;
	void RequestWinOver(Warrior* warrior);
private:
	void SapTree(TreeSprite* tree);
	
	//Members
private:
	int sapSpeed = 1;
}; 
