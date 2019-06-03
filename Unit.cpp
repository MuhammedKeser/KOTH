#include "Unit.h"

void Unit::Update()
{
	MoveToPoint();
}

void Unit::PreventOverlap(Sprite* otherSprite)
{

	Unit* unit = dynamic_cast<Unit*>(otherSprite);

	//TODO->Inline this badboy so you don't have to fill the stack up with it
	auto Collision = [this, &unit]()
	{
		std::cout << "Collision Overlap" << std::endl;
		CalcCollisionRect();
		unit->CalcCollisionRect();
		ResetCollisionList();
		unit->ResetCollisionList();
	};

	auto XCollision = [this, &unit, &Collision]()
	{
		Collision();
		m_ptVelocity.x = 0;
	};

	auto YCollision = [this, &unit, &Collision]()
	{
		Collision();
		m_ptVelocity.y = 0;
	};
	/*
	if (unit
		&&
		(
		(m_ptVelocity.x < 0
			&& unit->GetVelocity().x > 0)
			||
			(
				m_ptVelocity.x > 0
				&& unit->GetVelocity().x < 0
				)
			)
		&&
		(
			otherSprite->GetPosition().right > m_rcPosition.left
			|| otherSprite->GetPosition().right < m_rcPosition.left
			)
		)
	{
		std::cout << "SET POS" << std::endl;
		m_rcPosition = { GetPosition().left - m_ptVelocity.x, m_rcPosition.top, GetPosition().right - m_ptVelocity.x, m_rcPosition.bottom };
		XCollision();
	}

	if (unit
		&&
		(
		(m_ptVelocity.y < 0
			&& unit->GetVelocity().y > 0)
			||
			(
				m_ptVelocity.y > 0
				&& unit->GetVelocity().y < 0
				)
			)
		&&
		(
			otherSprite->GetPosition().bottom > m_rcPosition.top
			|| otherSprite->GetPosition().bottom < m_rcPosition.top
			)
		)
	{
		m_rcPosition = { m_rcPosition.left, GetPosition().top - m_ptVelocity.y,  m_rcPosition.right,GetPosition().bottom - m_ptVelocity.y };
		YCollision();
	}
	*/
	//VELOCITY COLLISIONS
	/*
	if (unit
		&& m_ptVelocity.x > 0
		&& unit->GetVelocity().x == 0
		&& otherSprite->GetPosition().left < m_rcPosition.right)
	{
		std::cout << "SET POS" << std::endl;
		m_rcPosition = { otherSprite->GetPosition().left - GetWidth() , m_rcPosition.top, otherSprite->GetPosition().left, m_rcPosition.bottom };
		XCollision();
	}
	if (unit
		&& m_ptVelocity.x < 0
		&& unit->GetVelocity().x == 0
		&& otherSprite->GetPosition().right > m_rcPosition.left)
	{
		std::cout << "SET POS" << std::endl;
		m_rcPosition = { otherSprite->GetPosition().right, m_rcPosition.top, otherSprite->GetPosition().right + GetWidth(), m_rcPosition.bottom };
		XCollision();
	}

	if (unit
		&& m_ptVelocity.y > 0
		&& unit->GetVelocity().y == 0
		&& otherSprite->GetPosition().top < m_rcPosition.bottom)
	{

		m_rcPosition = { m_rcPosition.left ,otherSprite->GetPosition().top - GetHeight(), m_rcPosition.right,otherSprite->GetPosition().top };
		YCollision();
	}
	if (unit
		&& m_ptVelocity.y < 0
		&& unit->GetVelocity().y == 0
		&& otherSprite->GetPosition().bottom > m_rcPosition.top)
	{
		std::cout << "SET POS" << std::endl;
		m_rcPosition = { m_rcPosition.left,otherSprite->GetPosition().bottom , m_rcPosition.right,otherSprite->GetPosition().bottom + GetHeight()};
		YCollision();
	}*/

	//No velocity collisions
	if (unit
		&& otherSprite->GetPosition().left < m_rcPosition.right)
	{
		m_rcPosition = { otherSprite->GetPosition().left - GetWidth() , m_rcPosition.top, otherSprite->GetPosition().left, m_rcPosition.bottom };
		XCollision();
	}
	else if (unit
		&& otherSprite->GetPosition().right > m_rcPosition.left)
	{
		m_rcPosition = { otherSprite->GetPosition().right, m_rcPosition.top, otherSprite->GetPosition().right + GetWidth(), m_rcPosition.bottom };
		XCollision();
	}

	if (unit
		&& otherSprite->GetPosition().top < m_rcPosition.bottom)
	{

		m_rcPosition = { m_rcPosition.left ,otherSprite->GetPosition().top - GetHeight(), m_rcPosition.right,otherSprite->GetPosition().top };
		YCollision();
	}
	else if (unit
		&& otherSprite->GetPosition().bottom > m_rcPosition.top)
	{
		std::cout << "SET POS" << std::endl;
		m_rcPosition = { m_rcPosition.left,otherSprite->GetPosition().bottom , m_rcPosition.right,otherSprite->GetPosition().bottom + GetHeight() };
		YCollision();
	}

}

void Unit::OnCollisionEnter(Sprite * otherSprite)
{
	Unit* unit = dynamic_cast<Unit*>(otherSprite);

	//TODO->Inline this badboy so you don't have to fill the stack up with it
	auto Collision = [this, &unit]()
	{
		CalcCollisionRect();
		unit->CalcCollisionRect();
		ResetCollisionList();
		unit->ResetCollisionList();
	};

	auto XCollision = [this, &unit, &Collision]()
	{
		Collision();
		m_ptVelocity.x = 0;
	};

	auto YCollision = [this, &unit, Collision]()
	{
		Collision();
		m_ptVelocity.y = 0;
	};

	if (unit
		&&
		(
		(m_ptVelocity.x < 0
			&& unit->GetVelocity().x > 0)
			||
			(
				m_ptVelocity.x > 0
				&& unit->GetVelocity().x < 0
				)
			)
		&&
		(
			otherSprite->GetPosition().right > m_rcPosition.left
			|| otherSprite->GetPosition().right < m_rcPosition.left
			)
		)
	{
		m_rcPosition = { GetPosition().left - m_ptVelocity.x, m_rcPosition.top, GetPosition().right - m_ptVelocity.x, m_rcPosition.bottom };
		XCollision();
	}

	if (unit
		&&
		(
		(m_ptVelocity.y < 0
			&& unit->GetVelocity().y > 0)
			||
			(
				m_ptVelocity.y > 0
				&& unit->GetVelocity().y < 0
				)
			)
		&&
		(
			otherSprite->GetPosition().bottom > m_rcPosition.top
			|| otherSprite->GetPosition().bottom < m_rcPosition.top
			)
		)
	{
		m_rcPosition = { m_rcPosition.left, GetPosition().top - m_ptVelocity.y,  m_rcPosition.right,GetPosition().bottom - m_ptVelocity.y };
		YCollision();
	}

	if (unit
		&& m_ptVelocity.x > 0
		&& unit->GetVelocity().x >= 0
		&& otherSprite->GetPosition().left < m_rcPosition.right)
	{
		m_rcPosition = { otherSprite->GetPosition().left - GetWidth() - 1, m_rcPosition.top, otherSprite->GetPosition().left - 1, m_rcPosition.bottom };
		XCollision();
	}
	if (unit
		&& m_ptVelocity.x < 0
		&& unit->GetVelocity().x <= 0
		&& otherSprite->GetPosition().right > m_rcPosition.left)
	{
		m_rcPosition = { otherSprite->GetPosition().right + 1, m_rcPosition.top, otherSprite->GetPosition().right + GetWidth() + 1, m_rcPosition.bottom };
		XCollision();
	}

	if (unit
		&& m_ptVelocity.y > 0
		&& unit->GetVelocity().y >= 0
		&& otherSprite->GetPosition().top < m_rcPosition.bottom)
	{

		m_rcPosition = { m_rcPosition.left ,otherSprite->GetPosition().top - GetHeight() - 1, m_rcPosition.right,otherSprite->GetPosition().top - 1 };
		YCollision();
	}
	if (unit
		&& m_ptVelocity.y < 0
		&& unit->GetVelocity().y <= 0
		&& otherSprite->GetPosition().bottom > m_rcPosition.top)
	{
		m_rcPosition = { m_rcPosition.left,otherSprite->GetPosition().bottom + 1, m_rcPosition.right,otherSprite->GetPosition().bottom + GetHeight() + 1 };
		YCollision();
	}
}

void Unit::OnCollisionStay(Sprite * otherSprite)
{
	Unit* unit = dynamic_cast<Unit*>(otherSprite);

	//TODO->Inline this badboy so you don't have to fill the stack up with it
	auto Collision = [this, &unit]()
	{
		CalcCollisionRect();
		unit->CalcCollisionRect();
		ResetCollisionList();
		unit->ResetCollisionList();
	};

	auto XCollision = [this, &unit, &Collision]()
	{
		Collision();
		m_ptVelocity.x = 0;
	};

	auto YCollision = [this, &unit, Collision]()
	{
		Collision();
		m_ptVelocity.y = 0;
	};

	if (unit
		&&
		(
		(m_ptVelocity.x < 0
			&& unit->GetVelocity().x > 0)
			||
			(
				m_ptVelocity.x > 0
				&& unit->GetVelocity().x < 0
				)
			)
		&&
		(
			otherSprite->GetPosition().right > m_rcPosition.left
			|| otherSprite->GetPosition().right < m_rcPosition.left
			)
		)
	{
		std::cout << "SET POS" << std::endl;
		m_rcPosition = { GetPosition().left - m_ptVelocity.x, m_rcPosition.top, GetPosition().right - m_ptVelocity.x, m_rcPosition.bottom };
		XCollision();
	}

	if (unit
		&&
		(
		(m_ptVelocity.y < 0
			&& unit->GetVelocity().y > 0)
			||
			(
				m_ptVelocity.y > 0
				&& unit->GetVelocity().y < 0
				)
			)
		&&
		(
			otherSprite->GetPosition().bottom > m_rcPosition.top
			|| otherSprite->GetPosition().bottom < m_rcPosition.top
			)
		)
	{
		m_rcPosition = { m_rcPosition.left, GetPosition().top - m_ptVelocity.y,  m_rcPosition.right,GetPosition().bottom - m_ptVelocity.y };
		YCollision();
	}

	if (unit
		&& m_ptVelocity.x > 0
		&& unit->GetVelocity().x == 0
		&& otherSprite->GetPosition().left < m_rcPosition.right)
	{
		std::cout << "SET POS" << std::endl;
		m_rcPosition = { otherSprite->GetPosition().left - GetWidth() - 1, m_rcPosition.top, otherSprite->GetPosition().left - 1, m_rcPosition.bottom };
		XCollision();
	}
	if (unit
		&& m_ptVelocity.x < 0
		&& unit->GetVelocity().x == 0
		&& otherSprite->GetPosition().right > m_rcPosition.left)
	{
		std::cout << "SET POS" << std::endl;
		m_rcPosition = { otherSprite->GetPosition().right + 1, m_rcPosition.top, otherSprite->GetPosition().right + GetWidth() + 1, m_rcPosition.bottom };
		XCollision();
	}

	if (unit
		&& m_ptVelocity.y > 0
		&& unit->GetVelocity().y == 0
		&& otherSprite->GetPosition().top < m_rcPosition.bottom)
	{

		m_rcPosition = { m_rcPosition.left ,otherSprite->GetPosition().top - GetHeight() - 1, m_rcPosition.right,otherSprite->GetPosition().top - 1 };
		YCollision();
	}
	if (unit
		&& m_ptVelocity.y < 0
		&& unit->GetVelocity().y == 0
		&& otherSprite->GetPosition().bottom > m_rcPosition.top)
	{
		std::cout << "SET POS" << std::endl;
		m_rcPosition = { m_rcPosition.left,otherSprite->GetPosition().bottom + 1, m_rcPosition.right,otherSprite->GetPosition().bottom + GetHeight() + 1 };
		YCollision();
	}
}

//Functions
void Unit::SetDestination(int x, int y, int cellWidth, int cellHeight)
{
	int destinationX = floor(x/cellWidth);
	int destinationY = floor(y/cellHeight);

	std::cout << "X: " << destinationX << " Y: " << destinationY << std::endl;
	m_destinationIndex = POINT{ destinationX,destinationY};
	m_destination = POINT{ long(destinationX*cellWidth)+long(floor(cellWidth/2))-long(GetWidth()/2),long(destinationY*cellHeight) + long(floor(cellHeight / 2))-long(GetHeight()/2)};
}

void Unit::Pathfind(int ** map)
{
	//Make sure that our destination is set
	if (m_destination.x != -1 && m_destination.y != -1)
	{
		//PERFORM PATHFINDING
		//UPDATE THE MAP WITH YOUR CURRENT POSITION
	}
}


void Unit::MoveToPoint()
{
	if (m_destination.x != -1 && m_destination.y != -1)
	{
		//DEBUG
		SetPosition(m_destination.x,m_destination.y);

		//Pull the next destination from your pathfinding Queue
		//Find the velocity required to reach it, and apply it here.

		//Replace this with pathfinding movement (one square at a time or something)
		/*
		POINT velocityDir = {
			long(m_destination.x - (GetPosition().left + GetWidth() / 2)),
			long(m_destination.y - (GetPosition().top + GetHeight() / 2))
		};
		long hypot = long(sqrt(pow(velocityDir.x, 2) + pow(velocityDir.y, 2)) / 5);
		POINT normalizedVelocityDir = { m_movementSpeed*velocityDir.x / hypot,m_movementSpeed*velocityDir.y / hypot };
		SetVelocity(normalizedVelocityDir);
		*/

		/*
		// Stop overshoot
		POINT ptNewPosition, ptSpriteSize, ptBoundsSize;
		ptNewPosition.x = m_rcPosition.left + m_ptVelocity.x;
		ptNewPosition.y = m_rcPosition.top + m_ptVelocity.y;
		
		//Stop X overshoot
		if (
			(ptNewPosition.x < m_destination.x && m_ptVelocity.x < 0) ||
			(ptNewPosition.x > m_destination.x && m_ptVelocity.x > 0)
			) 
		{
			m_ptVelocity = POINT{ 0,m_ptVelocity.y };
			ptNewPosition = POINT{m_destination.x, ptNewPosition.y};
			SetPosition(ptNewPosition.x, ptNewPosition.y);
		}
		//Stop Y overshoot
		if (
			(ptNewPosition.y < m_destination.y && m_ptVelocity.y < 0) ||
			(ptNewPosition.y > m_destination.y && m_ptVelocity.y>0)
			)
		{
			m_ptVelocity = POINT{ m_ptVelocity.x,0 };
			ptNewPosition = POINT{ptNewPosition.x, m_destination.y };
			SetPosition(ptNewPosition.x, ptNewPosition.y);
		}
		*/

	}
}
