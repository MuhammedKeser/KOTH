#pragma once
#include "LivelySprite.h"


//DEBUG
void LivelySprite::Update()
{
	if (Input::KeyReleased(InputKeys::KEY::D))
	{
	}
}

void LivelySprite::startCountdown(const Player& myPlayer) {

	RECT rect;
	//DrawText(hDC, TEXT("Countdown Started!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void LivelySprite::OnCollisionEnter(Sprite* otherSprite)
{

	Unit* otherUnit = dynamic_cast<Unit*> (otherSprite);

	if (otherUnit != NULL) {

		startCountdown(otherUnit->GetPlayer());
	}

}

void LivelySprite::OnCollisionExit(Sprite* otherSprite)
{
}

void LivelySprite::OnCollisionStay(Sprite* otherSprite)
{
}