#include "Warrior.h"

void Warrior::OnCollisionEnter(Sprite * otherSprite)
{
	Unit::OnCollisionEnter(otherSprite);
}

void Warrior::OnCollisionExit(Sprite * otherSprite)
{
}

void Warrior::OnCollisionStay(Sprite * otherSprite)
{
	Fight(otherSprite);
}

void Warrior::Update()
{
	Unit::Update();
}

//TODO
//1.We're going to be using a grid-based map. Turn this from collision-based attacking to neighboring cell attacking
//ALSO perform a player check to make sure you're not attacking your own units
//2.If it's a gatherer, win it over instead of fighting it
void Warrior::Fight(Sprite* otherSprite)
{

	if (Unit* otherUnit = dynamic_cast<Unit*>(otherSprite))
	{
		if (otherUnit->GetStatus() != UNIT_STATUS::DEAD
			&& m_timeOfLastAttack+m_attackInterval*1000<GetTickCount())
		{
			
			std::cout << "ATTACK!" << std::endl;
			//Lower the other unit's health
			otherUnit->SetHealth(otherUnit->GetHealth() - m_damage);

			//Set the time of attack
			m_timeOfLastAttack = GetTickCount();
		}
	}
}

void Warrior::HandleDeath()
{
	//If your health is below a certain threshold...
	//1.Set your status to dead.
	//2.Perhaps play a death animation.
	//3. Upon the end of the death animation, Remove yourself from the player's list of units, and the gameEngine's sprite list
}
