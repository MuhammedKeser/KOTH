#pragma once
#include "Sprite.h"
class Player;
#include "Player.h"

class Unit : public Sprite
{
public:
	// Constructor(s)/Destructor
	Unit(HDC hDC, HINSTANCE hInstance,UINT BITMAP_ID, UINT BITMAP_IDR) :Sprite(hDC, hInstance, BITMAP_ID) {
		p_LeftBitmap = new Bitmap(hDC, BITMAP_ID, hInstance);
		p_RightBitmap = new Bitmap(hDC, BITMAP_IDR, hInstance);
	};
	Unit(Bitmap* pBitmap, UINT BITMAP_ID) :Sprite(pBitmap, BITMAP_ID) {};
	Unit(Bitmap* pBitmap, RECT& rcBounds, UINT BITMAP_ID, BOUNDSACTION baBoundsAction = BA_STOP) : Sprite(pBitmap, rcBounds, BITMAP_ID, baBoundsAction) {};
	Unit(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder, RECT& rcBounds, UINT BITMAP_ID, BOUNDSACTION baBoundsAction = BA_STOP) :
		Sprite(pBitmap, ptPosition, ptVelocity, iZOrder, rcBounds, BITMAP_ID, baBoundsAction) {};
	virtual ~Unit() {};
	BOOL isSelected = false;

	//Functions
	void SetDestination(int x, int y);
	void MoveToPoint();

//Members
protected:
	Bitmap* p_LeftBitmap;
	Bitmap* p_RightBitmap;
	Player *m_player;
	float m_movementSpeed = 1.0f;
	POINT m_destination = POINT{-1,-1};
//Methods
public:
	//GETTERS/SETTERS
	const Player& GetPlayer() { return *m_player; }
	void SetPlayer(Player* player) { m_player = player; }
	const float& GetMovementSpeed() { return m_movementSpeed; }
	void SetMovementSpeed(float movementSpeed) { m_movementSpeed = movementSpeed; }
	void Update() override;
};