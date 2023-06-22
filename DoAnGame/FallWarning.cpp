#include "FallWarning.h"
#include "Textures.h"

CFallWarning::CFallWarning(float x, float y) : CGameObject(x, y)
{
	this->ay = GRAVITY;
}

void CFallWarning::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CFallWarning::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->IsBlocking()) return;

	if (e->ny < 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
}

void CFallWarning::Render()
{
	RenderBoundingBox();
}

void CFallWarning::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFallWarning::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FALL_CELL_WIDTH / 4;
	t = y - FALL_CELL_HEIGHT / 6;
	r = l + FALL_CELL_WIDTH / 2;
	b = t + FALL_CELL_HEIGHT / 3;
}


