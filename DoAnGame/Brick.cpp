#include "Brick.h"
#include "PlayScene.h"
#include "P_Power.h"
#include "Coin.h"
void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (type == 0)
		animations->Get(ID_ANI_BRICK)->Render(x, y);
	else if (type == 2)
		animations->Get(ID_ANI_SHINING_BRICK)->Render(x, y);
	else
		animations->Get(ID_ANI_WOOD_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	switch (state)
	{
	case BRICK_STATE_GOLD:
	{
		this->Delete();
		CCoin* coin = new CCoin(this->x, this->y);
		thisscene->AddObjectToScene(coin);
		break;
	}
	default:
		break;
	}
}
