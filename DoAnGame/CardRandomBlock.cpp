#include "CardRandomBlock.h"

void CCardRandomBlock::Render()
{
	int sprite = -1;
	switch (state)
	{
	case CARD_FLOWER_STATE:
		sprite = ID_SPRITE_FLOWER_CARD;
		break;
	case CARD_STAR_STATE:
		sprite = ID_SPRITE_STAR_CARD;
		break;
	case CARD_MUSHROOM_STATE:
		sprite = ID_SPRITE_MUSHROOM_CARD;
		break;
	default:
		break;
	}
	if(isHit == false)
	{
		CSprites* sprites = CSprites::GetInstance();
		sprites->Get(sprite)->Draw(x, y);
	}
	
}

void CCardRandomBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == CARD_FLOWER_STATE && GetTickCount64() - showing_start > SHOWING_TIME)
	{
		showing_start = 0;
		SetState(CARD_MUSHROOM_STATE);
		
	}
	if (state == CARD_STAR_STATE && GetTickCount64() - showing_start > SHOWING_TIME)
	{
		showing_start = 0;
		SetState(CARD_FLOWER_STATE);
		
	}
	if (state == CARD_MUSHROOM_STATE && GetTickCount64() - showing_start > SHOWING_TIME)
	{
		showing_start = 0;
		SetState(CARD_STAR_STATE);
		
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCardRandomBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CARD_BLOCK_WIDTH / 2;
	t = y - CARD_BLOCK_HEIGHT / 2;
	r = l + CARD_BLOCK_WIDTH;
	b = t + CARD_BLOCK_HEIGHT;
}

void CCardRandomBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CARD_FLOWER_STATE:
		showing_start = GetTickCount64();
		break;
	case CARD_STAR_STATE:
		showing_start = GetTickCount64();
		break;
	case CARD_MUSHROOM_STATE:
		showing_start = GetTickCount64();
		break;
	default:
		break;
	}
}
