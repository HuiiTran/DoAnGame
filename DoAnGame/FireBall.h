#pragma once
#include "GameObject.h"

#define FIREBALL_BBOX_WIDTH 10
#define FIREBALL_BBOX_HEIGHT 10

#define FIREBALL_SPEED 0.05f

#define ID_ANI_FIREBALL	140000


class CFireBall : public CGameObject
{
public:
	CFireBall(float x, float y, int zone, int dir);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnNoCollision(DWORD dt);
};

