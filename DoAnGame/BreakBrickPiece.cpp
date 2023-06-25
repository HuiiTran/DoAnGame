#include "BreakBrickPiece.h"

void CBreakBrickPiece::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CBreakBrickPiece::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{ 
	vy += ay * dt;
	vx += ax * dt;

	if (GetTickCount64() - start_break > PIECE_TIMEOUT)
	{
		isDeleted = true;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBreakBrickPiece::Render()
{
	int aniId = ID_ANI_BREAK_BRICK_PIECES;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CBreakBrickPiece::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIECE_STATE_LEFT:
		vx = -PIECES_SPEED_X;
		vy = -PIECES_SPEED_Y;
		start_break = GetTickCount64();
		break;
	case PIECE_STATE_RIGHT:
		vx = PIECES_SPEED_X;
		vy = -PIECES_SPEED_Y;
		start_break = GetTickCount64();
		break;
	default:
		break;
	}
}
