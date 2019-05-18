#pragma once
#include <string>
class Unit;
#include "Unit.h"

class Player
{
public:
	//Members
	std::string m_Name;
	std::list<Unit*> m_Units;
};