#pragma once
#include "GameObject.h"

#define ID_ANI_PIRANHA_PLANT 160050

#define PIRANHA_PLANT_WIDTH 16
#define PIRANHA_PLANT_HEIGHT 32

#define PIRANHA_PLANT_SPEED 0.04f
#define PIRANHA_PLANT_GRAVITY	0.002f

#define PIRANHA_PLANT_BBOX_WIDTH 16
#define PIRANHA_PLANT_BBOX_HEIGHT 32

#define PIRANHA_PLANT_STATE_HIDDEN 1
#define PIRANHA_PLANT_STATE_SHOWING 2
#define PIRANHA_PLANT_STATE_WAITING 3
#define PIRANHA_PLANT_STATE_SHOW 4

#define PIRANHA_PLANT_HIDE_TIME	3000
#define PIRANHA_PLANT_SHOW_TIME	2000

class CPiranhaPlant : public CGameObject
{
protected:
	float ay;
	float initial_y;
	ULONGLONG show;
	ULONGLONG hide;
	ULONGLONG fire;
	int ny = 0;
public:
	CPiranhaPlant(float x, float y) : CGameObject(x, y)
	{
		ay = 0;
		this->nx = -1;
		SetState(PIRANHA_PLANT_STATE_WAITING);
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
};

