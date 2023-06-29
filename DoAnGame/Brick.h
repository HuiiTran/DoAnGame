#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_WOOD_BRICK 10001
#define ID_ANI_SHINING_BRICK 10002

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_IDLE_SHINING 10000
#define BRICK_STATE_GOLD 11000

class CBrick : public CGameObject {
protected:
	int type = 0; //0 normal, 1 wood, 2 shining brick 
public:

	CBrick(float x, float y, int type = 0) : CGameObject(x, y) {
		this->type = type;
		if(type == 2)
			SetState(BRICK_STATE_IDLE_SHINING);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int GetType() { return this->type; }

	void SetState(int state);
};