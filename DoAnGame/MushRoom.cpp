#include "MushRoom.h"
#include "Mario.h"
void CMushRoom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == MUSHROOM_APPEAR_STATE || state == MUSHROOM_MOVING_STATE) {
		if (this->type == 0)
			animations->Get(ID_ANI_MUSHROOM)->Render(x, y);
		else
			animations->Get(ID_ANI_MUSHROOM_LIFEUP)->Render(x, y);
	}
}
void CMushRoom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == MUSHROOM_APPEAR_STATE)
	{
		if (GetTickCount64() - appear_start > 300)
		{
			SetState(MUSHROOM_MOVING_STATE);
			return;
		}
	}
	if (state == MUSHROOM_MOVING_STATE) 
	{
		vy += ay * dt;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	
}
void CMushRoom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}
void CMushRoom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CMushRoom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}
void CMushRoom::SetState(int state)
{
	
	switch (state)
	{
	case MUSHROOM_APPEAR_STATE:
		StartAppear();
		vy = -MUSHROOM_SPEED;
		break;
	case MUSHROOM_MOVING_STATE:
		ay = MUSHROOM_GRAVITY;
		vy = 0;
		vx = MUSHROOM_SPEED;
		break;
	}
	CGameObject::SetState(state);
}