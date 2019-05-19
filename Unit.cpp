#include "Unit.h"

void Unit::Update()
{
	MoveToPoint();
}

//Functions
void Unit::SetDestination(int x, int y)
{
	m_destination = POINT{ x,y };
}

void Unit::MoveToPoint()
{
	if (m_destination.x != -1 && m_destination.y != -1)
	{
		POINT velocityDir = {
			long(m_destination.x - (GetPosition().left + GetWidth() / 2)),
			long(m_destination.y - (GetPosition().top + GetHeight() / 2))
		};
		long hypot = long(sqrt(pow(velocityDir.x, 2) + pow(velocityDir.y, 2)) / 5);
		POINT normalizedVelocityDir = { m_movementSpeed*velocityDir.x / hypot,m_movementSpeed*velocityDir.y / hypot };
		SetVelocity(normalizedVelocityDir);

		// Stop overshoot
		POINT ptNewPosition, ptSpriteSize, ptBoundsSize;
		ptNewPosition.x = m_rcPosition.left + m_ptVelocity.x;
		ptNewPosition.y = m_rcPosition.top + m_ptVelocity.y;
		
		//Stop X overshoot
		if (
			(ptNewPosition.x < m_destination.x && m_ptVelocity.x < 0) ||
			(ptNewPosition.x > m_destination.x && m_ptVelocity.x>0)
			) {m_ptVelocity = POINT{0,m_ptVelocity.y};}
		//Stop Y overshoot
		if (
			(ptNewPosition.y < m_destination.y && m_ptVelocity.y < 0) ||
			(ptNewPosition.y > m_destination.y && m_ptVelocity.y>0)
			){m_ptVelocity = POINT{ m_ptVelocity.x,0 };}


	}
}
