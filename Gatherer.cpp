#include "Gatherer.h"


void Gatherer::OnCollisionEnter(Sprite * otherSprite)
{
}

void Gatherer::OnCollisionExit(Sprite * otherSprite)
{
}

void Gatherer::OnCollisionStay(Sprite * otherSprite)
{
	//Checking the sprite type
	TreeSprite* tree = dynamic_cast<TreeSprite*>(otherSprite);
	SapTree(tree);
}

void Gatherer::SapTree(TreeSprite* tree)
{
	if (tree != NULL && tree->m_Food>0)//Type of tree
	{
		if (m_player == NULL)
		{
			std::cout << "No player attached to gatherer!" << std::endl;
			return;
		}

		m_player->m_food += sapSpeed;
		tree->m_Food -= sapSpeed;
		tree->ScaleTree();
		std::cout << "Sapping!" << std::endl;
	}
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
