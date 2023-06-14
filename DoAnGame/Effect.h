#pragma once
#include "GameObject.h"

#define ID_ANI_DISAPPEAR 170000

#define EFFECT_STATE_START 1
#define EFFECT_STATE_END 2
class CEffect : public CGameObject
{
protected:
	int type = 0;// 0 disappear
	ULONGLONG apppear_start;
public:
	CEffect(float x, float y, int type = 0) : CGameObject(x, y) {
		this->type = type;
		apppear_start = -1;
		SetState(EFFECT_STATE_START);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};

