#pragma once
#include "GameObject.h"

#define CARD_BLOCK_WIDTH	16
#define CARD_BLOCK_HEIGHT	16

#define CARD_FLOWER_STATE	1
#define CARD_MUSHROOM_STATE	2
#define CARD_STAR_STATE	3

#define ID_SPRITE_FLOWER_CARD	120030
#define ID_SPRITE_STAR_CARD		120031
#define ID_SPRITE_MUSHROOM_CARD	120032

#define SHOWING_TIME	200

class CCardRandomBlock : public CGameObject
{
protected:
	bool isHit;

	ULONGLONG showing_start;
public:
	CCardRandomBlock(float x, float y) : CGameObject(x, y)
	{
		isHit = false;
		showing_start = 0;
		SetState(CARD_FLOWER_STATE);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);

	void SetisHit(bool isHit) { this->isHit = isHit; }
};

