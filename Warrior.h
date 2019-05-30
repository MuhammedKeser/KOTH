#pragma once
#include "Unit.h"
#include <iostream>
#include "Resource.h"

class Warrior: public Unit
{
public:
	// Constructor(s)/Destructor
	Warrior(HDC hDC, HINSTANCE hInstance) :Unit(hDC, hInstance, IDB_WARRIORR) {};
	Warrior(Bitmap* pBitmap) :Unit(pBitmap, IDB_WARRIORR) { };
	Warrior(Bitmap* pBitmap, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) : Unit(pBitmap, rcBounds, IDB_WARRIORR, baBoundsAction) {};
	Warrior(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder, RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP) :
		Unit(pBitmap, ptPosition, ptVelocity, iZOrder, rcBounds, IDB_WARRIORR, baBoundsAction) {
	};
	virtual ~Warrior() {};

	virtual void OnCollisionEnter(Sprite* otherSprite) override;
	virtual void OnCollisionExit(Sprite* otherSprite) override;
	virtual void OnCollisionStay(Sprite* otherSprite) override;
	void Update() override;
	void Fight(Sprite* otherSprite);
	void HandleDeath();

	//Getters/Setters
	int GetDamage() { return m_damage; };
	float GetAttackInterval() { return m_attackInterval; };
	float GetTimeOfLastAttack() { return m_timeOfLastAttack; };
	bool GetIsMounted() { return m_isMounted; };

	void SetDamage(int damage) { m_damage=damage; };
	void SetAttackInterval(float attackInterval) { m_attackInterval=attackInterval; };
	void SetTimeOfLastAttack(int timeOfLastAttack) { m_timeOfLastAttack=timeOfLastAttack; };
	void SetIsMounted(bool isMounted) { m_isMounted = isMounted; };

protected:
	//members
	int m_damage = 4;
	float m_attackInterval = 1.0f;//The time (in seconds) between attacks
	int m_timeOfLastAttack = -1;
	bool m_isMounted = false;

};
