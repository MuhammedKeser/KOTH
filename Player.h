#pragma once
#include <string>
class Unit;
#include "Unit.h"
#include "Windows.h"
class GameEngine;

class Player
{
public:
	//CTOR
	Player(std::string name):m_Name(name) {};

	//Members
	std::string m_Name;
	std::list<Unit*> m_Units;
	int m_food=0;

//Functions
	template <typename T>
	void SpawnUnit(HDC hDC,GameEngine* pGame, int x, int y)
	{
		T* newUnit = pGame->CreateSprite<T>(hDC);
		m_Units.push_back(newUnit);
		RECT newPosition = { x,y,x+ newUnit->GetWidth(),y+ newUnit->GetHeight() };
		newUnit->SetPosition(newPosition);
		newUnit->SetPlayer(this);
	}

};