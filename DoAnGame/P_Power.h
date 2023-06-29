#pragma once

#include "GameObject.h"

#define ID_ANI_P_POWER 190000
#define ID_ANI_P_POWER_EMPTY 190001


#define P_POWER_BBOX_WIDTH 16
#define P_POWER_BBOX_HEIGHT 10

#define P_POWER_BBOX_HEIGHT_HIT 8

#define P_POWER_STATE_IDLE 1
#define P_POWER_STATE_HIT 2

#define P_POWER_HIT_TIMEOUT 700

class CP_Power : public CGameObject
{
protected:
	bool isHit;
	ULONGLONG stop_change = -1;
public:
	CP_Power(float x, float y) : CGameObject(x,y)
	{
		isHit = false;
		SetState(P_POWER_STATE_IDLE);
	}

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return !isHit; };

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetisHit(bool isHit) { this->isHit = isHit; }
	bool GetisHit() { return this->isHit; }

	void SetState(int state);
};

