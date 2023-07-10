#pragma once
#include "GameObject.h"

#define ID_ANI_DISAPPEAR 170000

#define ID_ANI_SCORE_100 170100
#define ID_ANI_SCORE_200 170200
#define ID_ANI_SCORE_400 170400
#define ID_ANI_SCORE_800 170800
#define ID_ANI_SCORE_1000 171000
#define ID_ANI_SCORE_2000 172000
#define ID_ANI_SCORE_4000 174000
#define ID_ANI_SCORE_8000 178000

#define ID_ANI_LIFE_UP	171001
#define EFFECT_STATE_START 1
#define EFFECT_STATE_END 2
class CEffect : public CGameObject
{
protected:
	int type;// 0 disappear, score(100,200,400,800,1000,2000,4000,8000)
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

