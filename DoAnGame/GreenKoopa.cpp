#include "GreenKoopa.h"


CGreenKoopa::CGreenKoopa(float x, float y, bool isHaveWing) : CGameObject(x,y)
{
	this->ax = 0;
	this->ay = GREEN_KOOPA_GRAVITY;
	nx = -1;
	die_start = -1;
	respawn_start = -1;
	isHolded = false;
	mario_level = 1;
	SetState(GREEN_KOOPA_STATE_WALKING);
}
void CGreenKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GREEN_KOOPA_STATE_WALKING)
	{
		left = x - GREEN_KOOPA_BBOX_WIDTH / 2;
		top = y - GREEN_KOOPA_BBOX_HEIGHT / 2;
		right = left + GREEN_KOOPA_BBOX_WIDTH;
		bottom = top + GREEN_KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - GREEN_KOOPA_BBOX_WIDTH / 2;
		top = y - GREEN_KOOPA_BBOX_SHELL_HEIGHT / 2;
		right = left + GREEN_KOOPA_BBOX_WIDTH;
		bottom = top + GREEN_KOOPA_BBOX_SHELL_HEIGHT;
	}
}

void CGreenKoopa::Render()
{
	int aniId = -1;

	switch (state)
	{
	case GREEN_KOOPA_STATE_RESPAWN:
	{
		aniId = ID_ANI_GREEN_KOOPA_RESPAWN;
		break;
	}
	case GREEN_KOOPA_STATE_SHELL:
	case GREEN_KOOPA_STATE_SHELL_HOLD:
	{
		aniId = ID_ANI_GREEN_KOOPA_SHELL;
		break;
	}
	case GREEN_KOOPA_STATE_SHELL_SCROLL:
	{
		aniId = ID_ANI_GREEN_KOOPA_SHELL_ROLL;
		break;
	}
	default:
		if (vx > 0)
			aniId = ID_ANI_GREEN_KOOPA_WALKING_RIGHT;
		else
			aniId = ID_ANI_GREEN_KOOPA_WALKING_LEFT;
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CGreenKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CGreenKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		nx = -nx;
	}
}

void CGreenKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
}

void CGreenKoopa::OnCollisionWithFlyGoomba(LPCOLLISIONEVENT e)
{
}

void CGreenKoopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
}

void CGreenKoopa::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
}

void CGreenKoopa::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
}

void CGreenKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
}

void CGreenKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GREEN_KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GREEN_KOOPA_BBOX_HEIGHT - GREEN_KOOPA_BBOX_SHELL_HEIGHT) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GREEN_KOOPA_STATE_SHELL:
		vx = 0;
		vy = 0;
		respawn_start = GetTickCount64();
		break;
	case GREEN_KOOPA_STATE_RESPAWN:
		respawn_end = GetTickCount64();
		isRespawning = true;
		break;
	case GREEN_KOOPA_STATE_WALKING:
		if (isRespawning) {
			y += (GREEN_KOOPA_BBOX_SHELL_HEIGHT - GREEN_KOOPA_BBOX_HEIGHT) / 2;
			isRespawning = false;
		}
		vx = nx * GREEN_KOOPA_WALKING_SPEED;
		ay = GREEN_KOOPA_GRAVITY;
		break;
	case GREEN_KOOPA_STATE_CHANGE_DIRECT:
		vx = -vx;
		nx = -nx;
		break;
	default:
		break;
	}
}

void CGreenKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isInCam(this)) return;

	vy += ay * dt;
	vx += ax * dt;

	if (isHolded) {
		vy = 0;
		vx = 0;
	}
	if (state == GREEN_KOOPA_STATE_JUMP_DIE) {
		if (GetTickCount64() - die_start > GREEN_KOOPA_JUMP_DIE_TIMEOUT) {
			isDeleted = true;
			return;
		}
	}
	if ((state == GREEN_KOOPA_STATE_DIE))
	{
		isDeleted = true;
		return;
	}
	if ((state == GREEN_KOOPA_STATE_SHELL) && (GetTickCount64() - respawn_start > GREEN_KOOPA_RESPAWN_START_TIME))
	{
		SetState(GREEN_KOOPA_STATE_RESPAWN);
		return;
	}
	if ((state == GREEN_KOOPA_STATE_RESPAWN) && (GetTickCount64() - respawn_end > GREEN_KOOPA_RESPAWN_TIME))
	{
		isHolded = false;
		SetState(GREEN_KOOPA_STATE_WALKING);
		return;
	}
	if (state == GREEN_KOOPA_STATE_WALKING)
	{

	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
