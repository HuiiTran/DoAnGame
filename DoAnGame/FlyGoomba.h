#pragma once
#include "GameObject.h"

#define FLYGOOMBA_GRAVITY 0.001f
#define FLYGOOMBA_WALKING_SPEED 0.05f
#define FLYGOOMBA_DEFLECT_SPEED_JUMP 0.1f
#define FLYGOOMBA_DEFLECT_SPEED_FLY 0.3f
#define FLYGOOMBA_JUMP_DIE_SPEED 0.1f

#define FLYGOOMBA_WING_BBOX_WIDTH 20
#define FLYGOOMBA_WING_BBOX_HEIGHT 19
#define FLYGOOMBA_FLY_BBOX_HEIGHT 19
#define FLYGOOMBA_BBOX_WIDTH 16
#define FLYGOOMBA_BBOX_HEIGHT 14
#define FLYGOOMBA_BBOX_HEIGHT_DIE 7

#define FLYGOOMBA_DIE_TIMEOUT 500

#define FLYGOOMBA_STATE_WING_WALKING 1
#define FLYGOOMBA_STATE_WING_JUMPFLY 2
#define FLYGOOMBA_STATE_WING_FLY 3
#define FLYGOOMBA_STATE_WALKING 4
#define FLYGOOMBA_STATE_DIE 5
#define FLYGOOMBA_STATE_DIE_JUMP 6

#define ID_ANI_FLYGOOMBA_WALKING_WING 180000
#define ID_ANI_FLYGOOMBA_JUMP_WING 180001
#define ID_ANI_FLYGOOMBA_WALKING 180002
#define ID_ANI_FLYGOOMBA_DIE 180003
#define ID_ANI_FLYGOOMBA_DIE_JUMP 180004


#define WALKING_TIME 1000
#define JUMP_TIME 500
#define FLY_TIME 500
class CFlyGoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG JumpTime;
	ULONGLONG FLyTime;
	ULONGLONG WalkingTime;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CFlyGoomba(float x, float y);

	virtual void SetState(int state);
};

