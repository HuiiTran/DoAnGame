#include "HammerEnemy.h"

void CHammerEnemy::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (vx > 0) animations->Get(ID_ANI_HAMMER_RIGHT)->Render(x, y);
	else animations->Get(ID_ANI_HAMMER_LEFT)->Render(x, y);
}

void CHammerEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x > 193) {
		x = 193;
		vx = -vx;
	}
	if (x < 160) {
		x = 160;
		vx = -vx;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
