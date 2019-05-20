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
	
}

void TreeSprite::OnCollisionExit(Sprite * otherSprite)
{
}

void TreeSprite::OnCollisionStay(Sprite * otherSprite)
{
}
