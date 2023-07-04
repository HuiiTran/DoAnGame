#include "PiranhaPlant.h"

void CPiranhaPlant::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CPiranhaPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIRANHA_PLANT_BBOX_WIDTH / 2;
	t = y - PIRANHA_PLANT_BBOX_HEIGHT / 2;
	r = l + PIRANHA_PLANT_BBOX_WIDTH;
	b = t + PIRANHA_PLANT_BBOX_HEIGHT;
}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CPiranhaPlant::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_PIRANHA_PLANT)->Render(x, y);
}

void CPiranhaPlant::SetState(int state)
{
}
