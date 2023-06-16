#include "VenusFireTrap.h"
#include "FireBall.h"
#include "Pipe.h"
#include "debug.h"
void CVenusFireTrap::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - VENUSFIRETRAP_BBOX_WIDTH / 2;
	t = y - VENUSFIRETRAP_BBOX_HEIGHT / 2;
	r = l + VENUSFIRETRAP_BBOX_WIDTH;
	b = t + VENUSFIRETRAP_BBOX_HEIGHT;
}

void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"%d", state);
	if (state == VENUSFIRETRAP_STATE_WAITING)
	{
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
		LPGAMEOBJECT player = thisscene->GetPlayer();

		float px, py;
		player->GetPosition(px, py);

		int new_nx, new_ny;
		if (py > y + VENUSFIRETRAP_BBOX_HEIGHT / 2)
			new_ny = 1;
		else
			new_ny = -1;

		if (px > x + VENUSFIRETRAP_BBOX_WIDTH)
			new_nx = 1;
		else
			new_nx = -1;

		this->nx = new_nx;
		this->ny = new_ny;
	}

	//hide
	if (state == VENUSFIRETRAP_STATE_HIDDEN)
	{
		if (y > initial_y + VENUSFIRETRAP_BBOX_HEIGHT)
		{
			y = initial_y + VENUSFIRETRAP_BBOX_HEIGHT;
			SetState(VENUSFIRETRAP_STATE_SHOW);
		}
	}
	else
	{
		if (hide != 0 && GetTickCount64() - hide > 3000)
		{
			SetState(VENUSFIRETRAP_STATE_HIDDEN);
		}
	}

	//showing
	if (state == VENUSFIRETRAP_STATE_SHOWING)
	{
		if (y < initial_y - VENUSFIRETRAP_BBOX_HEIGHT)
		{
			y = initial_y - VENUSFIRETRAP_BBOX_HEIGHT;
			SetState(VENUSFIRETRAP_STATE_WAITING);
		}
	}
	else
	{
		if (show != 0 && GetTickCount64() - show > 2000)
		{
			SetState(VENUSFIRETRAP_STATE_SHOWING);
		}
	}

	if (fire != 0 && GetTickCount64() - fire > 1000)
	{
		SetState(VENUSFIRETRAP_STATE_SHOOT);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CVenusFireTrap::Render()
{
	switch (state)
	{
	case VENUSFIRETRAP_STATE_WAITING:
	{
		if (nx > 0) {
			//right
			if (ny > 0) {
				current_ani = ID_ANI_VENUSFIRETRAP_MOVING_RIGHT_DOWN;
			}
			else {
				current_ani = ID_ANI_VENUSFIRETRAP_MOVING_RIGHT_UP;
			}
		}
		else {
			//left
			if (ny > 0) {
				current_ani = ID_ANI_VENUSFIRETRAP_MOVING_LEFT_DOWN;
			}
			else {
				current_ani = ID_ANI_VENUSFIRETRAP_MOVING_LEFT_UP;
			}
		}
		break;
	}
	case VENUSFIRETRAP_STATE_SHOOT:
	{
		if (nx > 0) {
			//right
			if (ny > 0) {
				current_ani = ID_ANI_VENUSFIRETRAP_SHOOTING_RIGHT_DOWN;
			}
			else {
				current_ani = ID_ANI_VENUSFIRETRAP_SHOOTING_RIGHT_UP;
			}
		}
		else {
			//left
			if (ny > 0) {
				current_ani = ID_ANI_VENUSFIRETRAP_SHOOTING_LEFT_DOWN;
			}
			else {
				current_ani = ID_ANI_VENUSFIRETRAP_SHOOTING_LEFT_UP;
			}
		}
		break;
	}
	default:
		break;
	}
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(current_ani)->Draw(x, y);
	//RenderBoundingBox();
}

void CVenusFireTrap::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VENUSFIRETRAP_STATE_HIDDEN: {
		vy = VENUSFIRETRAP_SPEED;
		break;
	}
	case VENUSFIRETRAP_STATE_SHOWING: {
		vy = -VENUSFIRETRAP_SPEED;
		break;
	}
	case VENUSFIRETRAP_STATE_SHOW: {
		vy = 0;
		StartShow();
		break;
	}
	case VENUSFIRETRAP_STATE_WAITING: {
		vy = 0;
		StartWaiting();
		StartFire();
		break;
	}
	case VENUSFIRETRAP_STATE_SHOOT: {
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
		int zone;
		if (nx > 0)
		{
			if (ny < 0)
				zone = 3;
			else
				zone = 1;
		}
		else
		{
			if (ny < 0)
				zone = 4;
			else
				zone = 2;
		}
		CFireBall* fireball = new CFireBall(x, y - 5, zone, this->nx);
		thisscene->AddObjectToScene(fireball);

		StopFire();
		StopShow();
		break;
	}
	default:
		break;
	}
}