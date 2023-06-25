#include "Effect.h"

void CEffect::Render()
{
	int aniId = -1;
	if (type == 0)
		aniId = ID_ANI_DISAPPEAR;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
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
