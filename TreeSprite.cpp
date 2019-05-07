#pragma once
#include "TreeSprite.h"

TreeSprite::TreeSprite(Bitmap * pBitmap) :Sprite(pBitmap)
{
}

TreeSprite::TreeSprite(Bitmap * pBitmap, RECT & rcBounds, BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds, baBoundsAction)
{
}

TreeSprite::TreeSprite(Bitmap * pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder, RECT & rcBounds, BOUNDSACTION baBoundsAction) :
	Sprite(pBitmap, ptPosition, ptVelocity, iZOrder, rcBounds, baBoundsAction)
{
}

void TreeSprite::OnCollisionEnter(Sprite * otherSprite)
{
	//Checking the sprite type
	TreeSprite* pRect = dynamic_cast<TreeSprite*>(otherSprite);
	if (pRect !=NULL)//Type of tree
	{
		std::cout << "Tree collision enter!" << std::endl;
		this->SetVelocity(-1,0);
		pRect->SetVelocity(-1, 0);
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
	//Checking the sprite type
	TreeSprite* pRect = dynamic_cast<TreeSprite*>(otherSprite);
	if (pRect != NULL)//Type of tree
	{
		this->SetVelocity(3,0);
		//pRect->SetVelocity(3,0);
	}
}
