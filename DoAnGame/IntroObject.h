#pragma once
#include "GameObject.h"
class CIntroObject : public CGameObject
{
protected:
	int type;
	float ay;
public:
	CIntroObject(float x, float y, int type) : CGameObject(x, y)
	{
		this->type = type;
		this->ay = 0;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoudingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);

	virtual void OnNoCollsition(DWORD dt);
};

