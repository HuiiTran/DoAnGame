#include "QuestionBrick.h"

void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (this->brick_type == 4 || brick_type == 3)
		animations->Get(ID_ANI_SHINING_BRICK)->Render(x, y);
	else
	{
		if (this->isEmpty == false)
			animations->Get(ID_ANI_QUESTIONBRICK)->Render(x, y);
		else
			animations->Get(ID_ANI_EMPTY)->Render(x, y);
	}
	
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTIONBRICK_BBOX_WIDTH / 2;
	t = y - QUESTIONBRICK_BBOX_HEIGTH / 2;
	r = l + QUESTIONBRICK_BBOX_WIDTH;
	b = t + QUESTIONBRICK_BBOX_HEIGTH;
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (y < beforeHit_y && this->isEmpty == true)
	{
		vy = QUESTIONBRICK_DOWN * dt;
	}
	else
	{
		vy = 0;
		y = beforeHit_y;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}