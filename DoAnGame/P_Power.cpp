#include "P_Power.h"
#include "PlayScene.h"
void CP_Power::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(isHit)
		animations->Get(ID_ANI_P_POWER_EMPTY)->Render(x, y);
	else
		animations->Get(ID_ANI_P_POWER)->Render(x, y);
	//RenderBoundingBox();
}

void CP_Power::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - P_POWER_BBOX_WIDTH / 2;
	t = y - P_POWER_BBOX_HEIGHT / 2;
	r = l + P_POWER_BBOX_WIDTH;
	b = t + P_POWER_BBOX_HEIGHT;
}

void CP_Power::SetState(int state)
{
	CGameObject::SetState(state);
	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	switch (state)
	{
	case P_POWER_STATE_HIT:
	{
		vector<LPGAMEOBJECT> objects = thisscene->GetListObjects();
		for (int i = 0; i < objects.size();i++)
		{
			if (dynamic_cast<CBrick*>(objects[i]))
			{
				if (objects[i]->GetState() == BRICK_STATE_IDLE)
				{
					objects[i]->SetState(BRICK_STATE_GOLD);
				}
			}
		}
		break;
	}
	default:
		break;
	}
}

