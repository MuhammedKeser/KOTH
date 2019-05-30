#pragma once
#include "Sprite.h"
class Player;
#include "Player.h"

enum UNIT_STATUS 
{
	DEAD,
	ALIVE
};

class Unit : public Sprite
{
public:
	// Constructor(s)/Destructor
	Unit(HDC hDC, HINSTANCE hInstance,UINT BITMAP_ID) :Sprite(hDC, hInstance, BITMAP_ID) {};
	Unit(Bitmap* pBitmap, UINT BITMAP_ID) :Sprite(pBitmap, BITMAP_ID) {};
	Unit(Bitmap* pBitmap, RECT& rcBounds, UINT BITMAP_ID, BOUNDSACTION baBoundsAction = BA_STOP) : Sprite(pBitmap, rcBounds, BITMAP_ID, baBoundsAction) {};
	Unit(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder, RECT& rcBounds, UINT BITMAP_ID, BOUNDSACTION baBoundsAction = BA_STOP) :
		Sprite(pBitmap, ptPosition, ptVelocity, iZOrder, rcBounds, BITMAP_ID, baBoundsAction) {};
	virtual ~Unit() {};
	BOOL isSelected = false;

	//Functions
	void Unit::SetDestination(int x, int y, int cellWidth, int cellHeight);
	void Pathfind(int **map);
	void MoveToPoint();

//Members
protected:
	Player *m_player;
	float m_movementSpeed = 1.0f;
	POINT m_destinationIndex = POINT{-1,-1};
	POINT m_destination = POINT{-1,-1};
	int status = UNIT_STATUS::ALIVE;
	int m_health=100;

//Methods
public:
	//GETTERS/SETTERS
	const Player& GetPlayer() { return *m_player; }
	void SetPlayer(Player* player) { m_player = player; }
	const float& GetMovementSpeed() { return m_movementSpeed; }
	void SetMovementSpeed(float movementSpeed) { m_movementSpeed = movementSpeed; }
	void Update() override;
	void OnCollisionEnter(Sprite* otherSprite) override;
	void OnCollisionStay(Sprite* otherSprite) override;
	void PreventOverlap(Sprite* otherSprite);
	int GetXIndex(int mapCellWidth) { return floor(((m_rcPosition.left + m_rcPosition.right) / 2) / mapCellWidth); };
	int GetYIndex(int mapCellHeight) { return floor(((m_rcPosition.top + m_rcPosition.bottom) / 2) / mapCellHeight); };
	int GetStatus() { return status; };
	void SetStatus(UNIT_STATUS statusToSet) { status = statusToSet; };
	int GetHealth() { return m_health; };
	void SetHealth(int newHealth) { m_health = newHealth; };
};