#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LEAF_RIGHT 80000
#define ID_ANI_LEAF_LEFT 80001

#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16

#define LEAF_GRAVITY 0.0004f
#define LEAF_SPEED 0.03f
#define LEAF_UP 0.2f
#define LEAF_BACK_Y	0.01f

#define LEAF_FLY_STATE 1
#define LEAF_FALL_STATE 2
#define LEAF_CHANGE_DIREC_STATE 3

class CLeaf : public CGameObject
{
protected:
	float ay;
	float ax;

	ULONGLONG change_direction;
	ULONGLONG fly_up;

public:
	CLeaf(float x, float y) : CGameObject(x, y)
	{
		this->ax = 0;
		this->ay = LEAF_GRAVITY;
		this->vx = LEAF_SPEED;
		fly_up = -1;
		change_direction = -1;
		state = LEAF_FLY_STATE;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void SetState(int state);

	void BeginFly() { fly_up = GetTickCount64(); }
	void ChangeDirection() { change_direction = GetTickCount64(); }
};

