#include "FlyGoomba.h"
#include "Effect.h"
CFlyGoomba::CFlyGoomba(float x, float y)
{
	this->ax = 0;
	this->ay = FLYGOOMBA_GRAVITY;
	this->nx = -1;
	die_start = -1;
	JumpTime = 0;
	WalkingTime = 0;
	FLyTime = 0;
	SetState(FLYGOOMBA_STATE_WING_WALKING);
}
void CFlyGoomba::SetState(int state)
{
	CGameObject::SetState(state);

	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	LPGAMEOBJECT player = thisscene->GetPlayer();

	float px, py;
	player->GetPosition(px, py);
	switch (state)
	{
	case FLYGOOMBA_STATE_DIE:
	{
		die_start = GetTickCount64();
		y += (FLYGOOMBA_BBOX_HEIGHT - FLYGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		CEffect* effect = new CEffect(x + 10, y, FLYGOOMBA_SCORE);
		thisscene->AddObjectToScene(effect);
		break;
	}
	case FLYGOOMBA_STATE_DIE_JUMP:
	{
		die_start = GetTickCount64();
		//y += (FLYGOOMBA_BBOX_HEIGHT - FLYGOOMBA_BBOX_HEIGHT_DIE) / 2;
		if (px > x)
		{
			vx = -FLYGOOMBA_WALKING_SPEED;
			vy = -FLYGOOMBA_JUMP_DIE_SPEED;
		}
		else if (px < x)
		{
			vx = FLYGOOMBA_WALKING_SPEED;
			vy = -FLYGOOMBA_JUMP_DIE_SPEED;
		}
		CEffect* effect = new CEffect(x + 10, y, FLYGOOMBA_SCORE);
		thisscene->AddObjectToScene(effect);
		break;
	}
	case FLYGOOMBA_STATE_WALKING:
		vx = FLYGOOMBA_WALKING_SPEED * nx;
		break;
	case FLYGOOMBA_STATE_WING_JUMPFLY:
		JumpTime = GetTickCount64();
		break;
	case FLYGOOMBA_STATE_WING_FLY:
		FLyTime = GetTickCount64();
		break;
	case FLYGOOMBA_STATE_WING_WALKING:
		WalkingTime = GetTickCount64();
		vx = FLYGOOMBA_WALKING_SPEED * nx;
		break;
	default:
		break;
	}
}
void CFlyGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FLYGOOMBA_STATE_DIE)
	{
		left = x - FLYGOOMBA_BBOX_WIDTH / 2;
		top = y - FLYGOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + FLYGOOMBA_BBOX_WIDTH;
		bottom = top + FLYGOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (state == FLYGOOMBA_STATE_WING_WALKING)
	{
		left = x - FLYGOOMBA_WING_BBOX_WIDTH / 2;
		top = y - FLYGOOMBA_WING_BBOX_HEIGHT / 2;
		right = left + FLYGOOMBA_WING_BBOX_WIDTH;
		bottom = top + FLYGOOMBA_WING_BBOX_HEIGHT;
	}
	else if (state == FLYGOOMBA_STATE_WING_JUMPFLY)
	{
		left = x - FLYGOOMBA_WING_BBOX_WIDTH / 2;
		top = y - FLYGOOMBA_FLY_BBOX_HEIGHT / 2;
		right = left + FLYGOOMBA_WING_BBOX_WIDTH;
		bottom = top + FLYGOOMBA_FLY_BBOX_HEIGHT;
	}
	else if (state == FLYGOOMBA_STATE_WING_FLY)
	{
		left = x - FLYGOOMBA_WING_BBOX_WIDTH / 2;
		top = y - FLYGOOMBA_FLY_BBOX_HEIGHT / 2;
		right = left + FLYGOOMBA_WING_BBOX_WIDTH;
		bottom = top + FLYGOOMBA_FLY_BBOX_HEIGHT;
	}
	else
	{
		left = x - FLYGOOMBA_BBOX_WIDTH / 2;
		top = y - FLYGOOMBA_BBOX_HEIGHT / 2;
		right = left + FLYGOOMBA_BBOX_WIDTH;
		bottom = top + FLYGOOMBA_BBOX_HEIGHT;
	}
}

void CFlyGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isInCam(this)) return;

	vx += ax * dt;
	vy += ay * dt;

	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	LPGAMEOBJECT player = thisscene->GetPlayer();

	float px, py;
	player->GetPosition(px, py);

	if (x > px)
		nx = -1;
	else
		nx = 1;

	if (state != FLYGOOMBA_STATE_WALKING)
	{
		if (state == FLYGOOMBA_STATE_WING_WALKING && (GetTickCount64() - WalkingTime > WALKING_TIME))
		{
			SetState(FLYGOOMBA_STATE_WING_JUMPFLY);
		}
		else if (state == FLYGOOMBA_STATE_WING_JUMPFLY && (GetTickCount64() - JumpTime > JUMP_TIME))
		{
			SetState(FLYGOOMBA_STATE_WING_FLY);
		}
		else if (state == FLYGOOMBA_STATE_WING_FLY && (GetTickCount64() - FLyTime > FLY_TIME))
		{
			SetState(FLYGOOMBA_STATE_WING_WALKING);
		}
	}

	if (state == FLYGOOMBA_STATE_DIE && (GetTickCount64() - die_start > FLYGOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if (state == FLYGOOMBA_STATE_DIE_JUMP && (GetTickCount64() - die_start > FLYGOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFlyGoomba::Render()
{
	int aniId = ID_ANI_FLYGOOMBA_WALKING_WING;
	if (state == FLYGOOMBA_STATE_WING_WALKING)
		aniId = ID_ANI_FLYGOOMBA_WALKING_WING;
	else if (state == FLYGOOMBA_STATE_WING_FLY || state == FLYGOOMBA_STATE_WING_JUMPFLY)
		aniId = ID_ANI_FLYGOOMBA_JUMP_WING;
	else if (state == FLYGOOMBA_STATE_WALKING)
		aniId = ID_ANI_FLYGOOMBA_WALKING;
	else if (state == FLYGOOMBA_STATE_DIE)
		aniId = ID_ANI_FLYGOOMBA_DIE;
	else if (state == FLYGOOMBA_STATE_DIE_JUMP)
		aniId = ID_ANI_FLYGOOMBA_DIE_JUMP;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CFlyGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CFlyGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
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

	if (state == FLYGOOMBA_STATE_WING_JUMPFLY)
	{
		if (e->ny < 0)
		{
			vy -= FLYGOOMBA_DEFLECT_SPEED_JUMP;
		}
	}
	else if (state == FLYGOOMBA_STATE_WING_FLY)
	{
		if (e->ny < 0)
		{
			vy -= FLYGOOMBA_DEFLECT_SPEED_FLY;
		}
	}
}


