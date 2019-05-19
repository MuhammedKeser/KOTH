#include "Gatherer.h"


void Gatherer::OnCollisionEnter(Sprite * otherSprite)
{
}

void Gatherer::OnCollisionExit(Sprite * otherSprite)
{
}

void Gatherer::OnCollisionStay(Sprite * otherSprite)
{
}

void Gatherer::Update()
{
	Unit::Update();
	/*
	std::cout	<< "Left: " + m_rcCollision.left	<<std::endl
				<< "Top: " + m_rcCollision.top		<<std::endl
				<< "Right: " + m_rcCollision.right	<<std::endl	
				<< "Bottom: " + m_rcCollision.bottom << std::endl;
				*/
}
