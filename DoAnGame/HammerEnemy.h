#pragma once
#include "GameObject.h"

#define SPEED_HAMMER 0.007f

#define HAMMER_BBOX_WIDTH 16
#define HAMMER_BBOX_HEIGHT 16


#define ID_ANI_HAMMER_LEFT 250002
#define ID_ANI_HAMMER_RIGHT 250001
class CHammerEnemy : public CGameObject
{
public:
	CHammerEnemy(float x, float y) : CGameObject(x, y)
	{
		vx = SPEED_HAMMER;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnNoCollision(DWORD dt) {
		x += vx * dt;
		y += vy * dt;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

