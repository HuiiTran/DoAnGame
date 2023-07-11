#pragma once
#include "GameObject.h"

#define VENUSFIRETRAP_SPEED 0.04f
#define	VENUSFIRETRAP_GRAVITY 0.04f

#define VENUSFIRETRAP_BBOX_WIDTH 16
#define VENUSFIRETRAP_BBOX_HEIGHT	32

#define ID_ANI_VENUSFIRETRAP_SHOOTING_LEFT_UP 160010
#define ID_ANI_VENUSFIRETRAP_SHOOTING_RIGHT_UP 160020
#define ID_ANI_VENUSFIRETRAP_SHOOTING_LEFT_DOWN 160030
#define ID_ANI_VENUSFIRETRAP_SHOOTING_RIGHT_DOWN 160040

#define ID_ANI_VENUSFIRETRAP_MOVING_LEFT_UP 160011
#define ID_ANI_VENUSFIRETRAP_MOVING_RIGHT_UP 160021
#define ID_ANI_VENUSFIRETRAP_MOVING_LEFT_DOWN 160031
#define ID_ANI_VENUSFIRETRAP_MOVING_RIGHT_DOWN 160041

#define VENUSFIRETRAP_STATE_HIDDEN 1
#define VENUSFIRETRAP_STATE_SHOWING 2
#define VENUSFIRETRAP_STATE_SHOOT 3
#define VENUSFIRETRAP_STATE_WAITING 4
#define VENUSFIRETRAP_STATE_SHOW 5

#define VENUSFIRETRAP_HIDE_TIME	3000
#define VENUSFIRETRAP_SHOW_TIME	2000
#define VENUSFIRETRAP_FIRE_TIME	1000

#define VENUSFIRETRAP_SCORE	100
class CVenusFireTrap : public CGameObject
{
public:
	int dir;
	float ay;
	int current_ani;
	float initial_y;
	ULONGLONG show;
	ULONGLONG hide;
	ULONGLONG fire;
	int ny = 0;

	CVenusFireTrap(float x, float y) : CGameObject(x, y)
	{
		ay = 0;
		this->nx = -1;
		dir = -1;
		SetState(VENUSFIRETRAP_STATE_WAITING);
		current_ani = ID_ANI_VENUSFIRETRAP_SHOOTING_LEFT_DOWN;
	}
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	
	virtual void SetState(int state);

	void StartShow() {
		hide = 0;
		show = GetTickCount64();
		initial_y = y;
	}
	void StopShow() {
		show = 0;
		hide = GetTickCount64();
		initial_y = y;
	}
	void StartWaiting() {
		show = 0;
		hide = 0;
	}
	void StartFire() { fire = GetTickCount64(); }
	void StopFire() { fire = 0; }
};

