#include "Effect.h"

void CEffect::Render()
{
	int aniId = -1;
	if (type == 0)
		aniId = ID_ANI_DISAPPEAR;
	else if (type == 100)
		aniId = ID_ANI_SCORE_100;
	else if (type == 200)
		aniId = ID_ANI_SCORE_200;
	else if (type == 400)
		aniId = ID_ANI_SCORE_400;
	else if (type == 800)
		aniId = ID_ANI_SCORE_800;
	else if (type == 1000)
		aniId = ID_ANI_SCORE_1000;
	else if (type == 2000)
		aniId = ID_ANI_SCORE_2000;
	else if (type == 4000)
		aniId = ID_ANI_SCORE_4000;
	else if (type == 8000)
		aniId = ID_ANI_SCORE_8000;
	else if (type == 2)
		aniId = ID_ANI_LIFE_UP;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type != 0)
	{
		vy += ay * dt;
	}
	if (state == EFFECT_STATE_END)
	{
		this->Delete();
		return;
	}

	if (state == EFFECT_STATE_START && GetTickCount64() - apppear_start > 300)
	{
		SetState(EFFECT_STATE_END);
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}

void CEffect::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case EFFECT_STATE_START:
		apppear_start = GetTickCount64();
		break;
	case EFFECT_STATE_END:
		break;
	default:
		break;
	}
}

void CEffect::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}
