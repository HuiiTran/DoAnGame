#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"
class CBlockingObject : public CGameObject
{
public:
	CBlockingObject(float x, float y) : CGameObject(x, y) { }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() 
	{ 
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mario->GetState() == MARIO_END_MAP_STATE)
			return 0;
		else
			return 1; 
	}
};

