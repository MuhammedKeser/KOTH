#pragma once
#include "Sprite.h"
#include "Player.h"

class Unit : public Sprite
{
public:
	// Constructor(s)/Destructor
	Unit(HDC hDC, HINSTANCE hInstance) :Sprite(hDC,hInstance){};
	Unit(Bitmap* pBitmap) :Sprite(pBitmap) {};
	Unit(Bitmap* pBitmap, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) : Sprite(pBitmap, rcBounds, baBoundsAction) {};
	Unit(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) :
		Sprite(pBitmap, ptPosition, ptVelocity, iZOrder, rcBounds, baBoundsAction) {};
	virtual ~Unit() {};

//Members
private:
	Player m_player;

//Methods
public:
	const Player& GetPlayer() { return m_player; }
	void SetPlayer(Player* player) { m_player = *player; }

};