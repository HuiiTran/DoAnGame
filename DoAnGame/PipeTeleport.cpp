#include "PipeTeleport.h"

void CPipeTeleport::Render()
{
	RenderBoundingBox();
}

void CPipeTeleport::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CPipeTeleport::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 10 / 2;
	t = y - 16 / 2;
	r = l + 10;
	b = t + 16;
}
