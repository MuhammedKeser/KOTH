#pragma once
#include "Sprite.h"
class Player;
#include "Player.h"

class Unit : public Sprite
{
public:
	// Constructor(s)/Destructor
	Unit(HDC hDC, HINSTANCE hInstance) :Sprite(hDC, hInstance) {};
	Unit(Bitmap* pBitmap) :Sprite(pBitmap) {};
	Unit(Bitmap* pBitmap, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) : Sprite(pBitmap, rcBounds, baBoundsAction) {};
	Unit(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) :
		Sprite(pBitmap, ptPosition, ptVelocity, iZOrder, rcBounds, baBoundsAction) {};
	virtual ~Unit() {};
	BOOL isSelected = false;

	//Functions
	void SetDestination(int x, int y);
	void MoveToPoint();

//Members
private:
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