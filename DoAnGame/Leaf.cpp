#include "Leaf.h"

void CLeaf::Render()
{
	CSprites* sprites = CSprites::GetInstance();

	int Id = ID_ANI_LEAF_LEFT;
	
	if (nx > 0)
		Id = ID_ANI_LEAF_RIGHT;
	sprites->Get(Id)->Draw(x, y);

	
}
void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	if (state == LEAF_FLY_STATE)
	{
		if (GetTickCount64() - fly_up > 500)
			SetState(LEAF_FALL_STATE);
	}
	if (state == LEAF_FALL_STATE || state == LEAF_CHANGE_DIREC_STATE)
	{
		if (GetTickCount64() - change_direction > 400)
		{
			vx = nx * LEAF_SPEED;
			vy = -LEAF_BACK_Y;
		}

		if (GetTickCount64() - change_direction > 1200)
		{
			SetState(LEAF_CHANGE_DIREC_STATE);
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void  CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}
void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case LEAF_FLY_STATE: {
		vx = 0.0f;
		vy = -LEAF_UP;
		BeginFly();
		break;
	}
	case LEAF_FALL_STATE: {
		vy = 0.0f;
		ChangeDirection();
		break;
	}
	case LEAF_CHANGE_DIREC_STATE: {
		nx = -nx;
		vx = nx * LEAF_SPEED;
		ChangeDirection();
		break;
	}
	default:
		break;
	}
}