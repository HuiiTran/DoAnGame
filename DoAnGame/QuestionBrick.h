#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTIONBRICK 12000
#define ID_ANI_EMPTY 12001

#define QUESTIONBRICK_BBOX_WIDTH 16
#define QUESTIONBRICK_BBOX_HEIGTH 16

#define QUESTIONBRICK_STATE_HAVEITEM 100
#define	QUESTIONBRICK_STATE_EMPTY 200


#define QUESTIONBRICK_UP 19
#define QUESTIONBRICK_DOWN 0.007f

class CQuestionBrick : public CGameObject
{
	int brick_type; //0: coin , 1 mushroom, 2 leaf, 3 life up 
	bool isEmpty = false;
	float beforeHit_y;
public:
	CQuestionBrick(float x, float y, int type = 0) : CGameObject(x, y) { this->brick_type = type; this->beforeHit_y = y; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetEmpty(bool state) { this->isEmpty = state; }
	bool IsEmpty() { return this->isEmpty; }
	int GetBrickType() { return this->brick_type; }

};

