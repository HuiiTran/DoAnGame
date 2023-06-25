#pragma once

#include "GameObject.h"

#define ID_ANI_BREAK_BRICK_PIECES 170001

#define PIECES_GRAVITY 0.0007f

#define PIECES_SPEED_Y 0.25f
#define PIECES_SPEED_X 0.08f

#define PIECE_STATE_LEFT 1
#define PIECE_STATE_RIGHT 2

#define PIECE_TIMEOUT 900

class CBreakBrickPiece : public CGameObject
{
protected:
	float ay;
	float ax;

	ULONGLONG start_break;
public:
	CBreakBrickPiece(float x, float y) : CGameObject(x, y)
	{
		start_break = -1;

		this->x = x;
		this->y = y;

		this->ay = PIECES_GRAVITY;
		this->ax = 0;
	}
	void OnNoCollision(DWORD dt);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; };
	
	void SetState(int state);

};