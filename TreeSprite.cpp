#pragma once
#include "TreeSprite.h"


//DEBUG
void TreeSprite::Update() 
{
	if (Input::KeyReleased(InputKeys::KEY::D))
	{
		Scale(xScale+0.2f,yScale+0.3f);
	}
}

void TreeSprite::OnCollisionEnter(Sprite * otherSprite)
{
	//Checking the sprite type
	TreeSprite* pRect = dynamic_cast<TreeSprite*>(otherSprite);
	if (pRect !=NULL)//Type of tree
	{
		std::cout << "Tree collision enter!" << std::endl;
		//this->SetVelocity(-1,0);
		//pRect->SetVelocity(-1, 0);
	}
}

void TreeSprite::OnCollisionExit(Sprite * otherSprite)
{
	//Checking the sprite type
	TreeSprite* pRect = dynamic_cast<TreeSprite*>(otherSprite);
	if (pRect != NULL)//Type of tree
	{
		std::cout << "Tree collision exit!" << std::endl;
		this->SetVelocity(0,0);
	}
}

void TreeSprite::OnCollisionStay(Sprite * otherSprite)
{
	/*
	//Checking the sprite type
	TreeSprite* pRect = dynamic_cast<TreeSprite*>(otherSprite);
	if (pRect != NULL)//Type of tree
	{
	
	}
	*/
}
