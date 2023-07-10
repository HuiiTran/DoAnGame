#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#include "VenusFireTrap.h"
#include "FallWarning.h"

#define GREEN_KOOPA_GRAVITY 0.002f
#define GREEN_KOOPA_WALKING_SPEED 0.05f
#define GREEN_KOOPA_SHELL_SCROLL_SPEED 0.1f
#define GREEN_KOOPA_JUMP_DIE_SPEED	0.5f
#define GREEN_KOOPA_WING_JUMP_SPEED	0.3f
#define GREEN_KOOPA_WING_GRAVITY 0.001f

#define GREEN_KOOPA_BBOX_WIDTH 16
#define GREEN_KOOPA_BBOX_HEIGHT 26
#define GREEN_KOOPA_BBOX_SHELL_HEIGHT 16

#define GREEN_KOOPA_STATE_WALKING 1
#define GREEN_KOOPA_STATE_RESPAWN 2
#define GREEN_KOOPA_STATE_SHELL 3
#define GREEN_KOOPA_STATE_SHELL_SCROLL 4
#define GREEN_KOOPA_STATE_SHELL_HOLD 5
#define GREEN_KOOPA_STATE_DIE 6
#define GREEN_KOOPA_STATE_JUMP_DIE 7
#define GREEN_KOOPA_STATE_CHANGE_DIRECT 8
#define GREEN_KOOPA_STATE_SHELL_FLIP	9

#define GREEN_KOOPA_RESPAWN_START_TIME 5000
#define GREEN_KOOPA_RESPAWN_TIME 3000
#define GREEN_KOOPA_JUMP_DIE_TIMEOUT 1000

#define ID_ANI_GREEN_KOOPA_RESPAWN 210001
#define ID_ANI_GREEN_KOOPA_RESPAWN_FLIP 210011

#define ID_ANI_GREEN_KOOPA_SHELL 210002
#define ID_ANI_GREEN_KOOPA_SHELL_FLIP 210012

#define ID_ANI_GREEN_KOOPA_SHELL_ROLL 210003
#define ID_ANI_GREEN_KOOPA_SHELL_ROLL_FLIP 210013

#define ID_ANI_GREEN_KOOPA_WALKING_RIGHT 210010
#define ID_ANI_GREEN_KOOPA_WALKING_LEFT 210020

#define GREEN_KOOPA_Y_OFFSET	15
#define GREEN_KOOPA_X_OFFSET	13
class CGreenKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	bool isFlip;

	int mario_level;
	bool isRespawning;
	bool isHolded;


	ULONGLONG die_start;
	ULONGLONG respawn_start;
	ULONGLONG respawn_end;
	ULONGLONG flip_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	virtual int IsCollidable() { return ((state != GREEN_KOOPA_STATE_DIE) && (state != GREEN_KOOPA_STATE_JUMP_DIE)); };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithFlyGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	//void OnCollisionWithInvisibleBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
public:
	CGreenKoopa(float x, float y, bool isHaveWing = false);
	virtual void SetState(int state);

	void SetMLevel(int l) { this->mario_level = l; };

	bool GetIsHolded() {
		return this->isHolded;
	}
	void SetIsHolded(bool isHolded) {
		this->isHolded = isHolded;
	};

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void SetisFlip(bool isFlip) { this->isFlip = isFlip; }
};

