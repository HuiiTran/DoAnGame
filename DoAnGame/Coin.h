#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_UP 2.0f
#define COIN_DOWN 0.007f
#define COIN_SPEED 0.16855f
class CCoin : public CGameObject {
	int isInQuestionB = 0; //0: normal, 1: in questionbrick
	bool isFly = false;
	float distanceUp = 0;
public:
	CCoin(float x, float y, int isIn = 0) : CGameObject(x, y)
	{
		this->isInQuestionB = isIn;
		if (isInQuestionB == 1)
			this->vy = COIN_SPEED;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnNoCollision(DWORD dt) { y -= vy * dt; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetCoinInQuestionB(){	return this->isInQuestionB;	}
	virtual void SetFly(bool state) { this->isFly = state; }
	int IsBlocking() { return 0; }
};