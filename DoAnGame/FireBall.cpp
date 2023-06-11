#include "FireBall.h"
CFireBall::CFireBall(float x, float y, int zone, int dir) :CGameObject(x, y)
{
	int angle = 1;

	if (zone > 2) angle = -1;

	if (zone == 1 || zone == 3)
	{
		vx = FIREBALL_SPEED * dir;
		vy = FIREBALL_SPEED * angle;
	}
	else
	{
		vx = FIREBALL_SPEED * dir * 2;
		vy = FIREBALL_SPEED * angle;
	}
}

void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBALL_BBOX_WIDTH / 2;
	top = y - FIREBALL_BBOX_HEIGHT / 2;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}

void CFireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
}

void CFireBall::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*x += vx * dt;
	y += vy * dt;*/
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireBall::Render()
{

	int aniId = ID_ANI_FIREBALL;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	// RenderBoundingBox();
}

