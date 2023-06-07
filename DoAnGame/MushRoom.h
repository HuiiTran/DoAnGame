#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Animation.h"
#include "Platform.h"
#define ID_ANI_MUSHROOM 13000
#define ID_ANI_MUSHROOM_LIFEUP 13001

#define MUSHROOM_MOVING_STATE 100
#define MUSHROOM_APPEAR_STATE 200

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define MUSHROOM_SPEED 0.05f
#define MUSHROOM_GRAVITY 0.002f

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
		this->ax = 0;
		this->ay = MUSHROOM_GRAVITY;
		this->vx = MUSHROOM_SPEED;
		this->type = type;
		appear_start = -1;
		SetState(MUSHROOM_APPEAR_STATE);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	int Gettype() { return this->type; }
	void SetState(int state);
};
