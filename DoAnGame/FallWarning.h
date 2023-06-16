#pragma once
#include "GameObject.h"

#define GRAVITY 0.001f

#define FALL_CELL_WIDTH	14
#define FALL_CELL_HEIGHT 26
class CFallWarning : public CGameObject
{
protected:
	float ay;

public:
	CFallWarning(float x, float y);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

