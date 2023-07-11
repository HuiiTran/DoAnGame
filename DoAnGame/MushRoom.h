#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Animation.h"
#include "Platform.h"
#define ID_ANI_MUSHROOM 13000
#define ID_ANI_MUSHROOM_LIFEUP 13001

#define MUSHROOM_APPEAR_STATE_LEFT 1
#define MUSHROOM_APPEAR_STATE_RIGHT 2
#define MUSHROOM_MOVING_STATE_LEFT 3
#define MUSHROOM_MOVING_STATE_RIGHT 4

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define MUSHROOM_SPEED 0.05f
#define MUSHROOM_GRAVITY 0.002f

#define MUSHROOM_SCORE	1000
class CMushRoom : public CGameObject
{
protected:
	float ax;
	float ay;
	int type; //0 normal, 1 life_up

	ULONGLONG appear_start;
public:
	CMushRoom(float x, float y, int type = 0) : CGameObject(x, y)
	{
		this->vx = 0;
		this->vy = 0;
		this->type = type;
		appear_start = -1;
		SetState(MUSHROOM_APPEAR_STATE_RIGHT);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	int Gettype() { return this->type; }

	virtual void SetState(int state);
	void StartAppear() { appear_start = GetTickCount64(); }
};

