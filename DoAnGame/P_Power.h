#pragma once

#include "GameObject.h"

#define ID_ANI_P_POWER 190000
#define ID_ANI_P_POWER_EMPTY 190001


#define P_POWER_BBOX_WIDTH 16
#define P_POWER_BBOX_HEIGHT 16

#define P_POWER_BBOX_HEIGHT_HIT 8

class CP_Power : public CGameObject
{
protected:
	bool isHit;
public:
	CP_Power(float x, float y) : CGameObject(x,y)
	{
		isHit = false;
	}

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return !isHit; };

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetisHit(bool isHit) { this->isHit = isHit; }
};

