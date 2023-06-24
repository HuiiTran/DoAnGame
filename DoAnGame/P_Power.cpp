#include "P_Power.h"

void CP_Power::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(isHit)
		animations->Get(ID_ANI_P_POWER_EMPTY)->Render(x, y);
	else
		animations->Get(ID_ANI_P_POWER)->Render(x, y);
}

void CP_Power::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - P_POWER_BBOX_WIDTH / 2;
	t = y - P_POWER_BBOX_HEIGHT / 2;
	r = l + P_POWER_BBOX_WIDTH;
	b = t + P_POWER_BBOX_HEIGHT;
}

