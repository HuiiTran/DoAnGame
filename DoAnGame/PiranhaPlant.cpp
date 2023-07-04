#include "PiranhaPlant.h"

void CPiranhaPlant::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}

void CPiranhaPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIRANHA_PLANT_BBOX_WIDTH / 2;
	t = y - PIRANHA_PLANT_BBOX_HEIGHT / 2;
	r = l + PIRANHA_PLANT_BBOX_WIDTH;
	b = t + PIRANHA_PLANT_BBOX_HEIGHT;
}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isInCam(this)) return;

	//DebugOut(L"%d", state);
	if (state == PIRANHA_PLANT_STATE_WAITING)
	{
		
	}
	//hide
	if (state == PIRANHA_PLANT_STATE_HIDDEN)
	{
		if (y > initial_y + PIRANHA_PLANT_BBOX_HEIGHT)
		{
			y = initial_y + PIRANHA_PLANT_BBOX_HEIGHT;
			SetState(PIRANHA_PLANT_STATE_SHOW);
		}
	}
	else
	{
		if (hide != 0 && GetTickCount64() - hide > PIRANHA_PLANT_HIDE_TIME)
		{
			SetState(PIRANHA_PLANT_STATE_HIDDEN);
		}
	}

	//showing
	if (state == PIRANHA_PLANT_STATE_SHOWING)
	{
		if (y < initial_y - PIRANHA_PLANT_BBOX_HEIGHT)
		{
			y = initial_y - PIRANHA_PLANT_BBOX_HEIGHT;
			SetState(PIRANHA_PLANT_STATE_WAITING);
		}
	}
	else
	{
		if (show != 0 && GetTickCount64() - show > PIRANHA_PLANT_SHOW_TIME)
		{
			SetState(PIRANHA_PLANT_STATE_SHOWING);
		}
	}
	if (bite != 0 && GetTickCount64() - bite > PIRANHA_PLANT_BITE_TIME)
	{
		SetState(PIRANHA_PLANT_STATE_BITE);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_PIRANHA_PLANT)->Render(x, y);
}

void CPiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHA_PLANT_STATE_HIDDEN: {
		vy = PIRANHA_PLANT_SPEED;
		break;
	}
	case PIRANHA_PLANT_STATE_SHOWING: {
		vy = -PIRANHA_PLANT_SPEED;
		break;
	}
	case PIRANHA_PLANT_STATE_SHOW: {
		vy = 0;
		StartShow();
		break;
	}
	case PIRANHA_PLANT_STATE_WAITING: {
		vy = 0;
		StartWaiting();
		StartBite();
		break;
	}
	case PIRANHA_PLANT_STATE_BITE: {
		StopBite();
		StopShow();
	}
	default:
		break;
	}
}
