#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.09f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_LEVEL_RUN_SPEED 0.01f
#define LEVEL_RUN_MAX 7


#define MARIO_ACCEL_WALK_X	0.0003f
#define MARIO_ACCEL_RUN_X	0.0002f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define TIME_TO_LEVEL_RUN 140
#define TIME_PREPARE_LEVEL_RUN 650

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0

#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_HOLDING			700
//#define MARIO_STATE_HOLDING

#pragma region ANIMATION_ID
#define ID_ANI_MARIO_KICKING_RIGHT 220
#define ID_ANI_MARIO_KICKING_LEFT 221

#define ID_ANI_MARIO_HOLD_RIGHT 330
#define ID_ANI_MARIO_HOLD_LEFT 331

#define ID_ANI_MARIO_HOLD_RIGHT_IDLE 340
#define ID_ANI_MARIO_HOLD_LEFT_IDLE 341

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_RUNNING_RIGHT_FAST 610
#define ID_ANI_MARIO_RUNNING_LEFT_FAST 611

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001



#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT_FAST 1310
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT_FAST 1311

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_HOLD_RIGHT 1700
#define ID_ANI_MARIO_SMALL_HOLD_LEFT 1701

#define ID_ANI_MARIO_SMALL_HOLD_RIGHT_IDLE 1710
#define ID_ANI_MARIO_SMALL_HOLD_LEFT_IDLE 1711

#define ID_ANI_MARIO_SMALL_KICKING_RIGHT 1800
#define ID_ANI_MARIO_SMALL_KICKING_LEFT 1801

#define ID_ANI_MARIO_SMALL_TO_BIG_RIGHT 1810
#define ID_ANI_MARIO_SMALL_TO_BIG_LEFT 1811

//Tanooki MARIO

#define ID_ANI_MARIO_CHANGE_TO_TANOOKI_RIGHT 2120
#define	ID_ANI_MARIO_CHANGE_TO_TANOOKI_LEFT 2121

#define ID_ANI_MARIO_TANOOKI_IDLE_RIGHT 2100
#define ID_ANI_MARIO_TANOOKI_IDLE_LEFT 2101

#define ID_ANI_MARIO_TANOOKI_WALKING_RIGHT 2200
#define ID_ANI_MARIO_TANOOKI_WALKING_LEFT 2201

#define ID_ANI_MARIO_TANOOKI_RUNNING_RIGHT 2300
#define ID_ANI_MARIO_TANOOKI_RUNNING_LEFT 2301

#define ID_ANI_MARIO_TANOOKI_RUNNING_RIGHT_FAST 2310
#define ID_ANI_MARIO_TANOOKI_RUNNING_LEFT_FAST 2311

#define ID_ANI_MARIO_TANOOKI_BRACE_RIGHT 2400
#define ID_ANI_MARIO_TANOOKI_BRACE_LEFT 2401

#define ID_ANI_MARIO_TANOOKI_JUMP_WALK_RIGHT 2500
#define ID_ANI_MARIO_TANOOKI_JUMP_WALK_LEFT 2501

#define ID_ANI_MARIO_TANOOKI_JUMP_RUN_RIGHT 2600
#define ID_ANI_MARIO_TANOOKI_JUMP_RUN_LEFT 2601

#define ID_ANI_MARIO_TANOOKI_SIT_RIGHT 2700
#define ID_ANI_MARIO_TANOOKI_SIT_LEFT 2701

#define ID_ANI_MARIO_TANOOKI_HOLD_RIGHT 2800
#define ID_ANI_MARIO_TANOOKI_HOLD_LEFT 2801

#define ID_ANI_MARIO_TANOOKI_HOLD_RIGHT_IDLE 2880
#define ID_ANI_MARIO_TANOOKI_HOLD_LEFT_IDLE 2881

#define ID_ANI_MARIO_TANOOKI_KICKING_RIGHT	2900
#define ID_ANI_MARIO_TANOOKI_KICKING_LEFT 2901
#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TANOOKI	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_TANOOKI_BBOX_WIDTH  16
#define MARIO_TANOOKI_BBOX_HEIGHT 24

#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
	BOOLEAN isOnPlatform;
	BOOLEAN isSitting;
	BOOLEAN isHolding;
	BOOLEAN isKicking;
	BOOLEAN isChanging;
	BOOLEAN isDecreaseLevel;
	BOOLEAN isRunning;
	
	CGameObject* holdingObject;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 


	int level; 
	int untouchable; 
	int level_run = 0;

	ULONGLONG untouchable_start;
	ULONGLONG wait;
	ULONGLONG start_kick;
	ULONGLONG start_change;
	ULONGLONG start_prepare_run;
	ULONGLONG stop_level_run;
	ULONGLONG start_level_run;
	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithFlyGoomba(LPCOLLISIONEVENT e);
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdTanooki();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		isHolding = false;
		holdingObject = NULL;

		level = MARIO_LEVEL_SMALL;//MARIO_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		wait = -1;
		isOnPlatform = false;
		coin = 0;

		isKicking = false;
		start_kick = -1;

		isChanging = false;
		isDecreaseLevel = false;
		start_change = -1;

		level_run = 0;
		isRunning = false;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }
	bool IsBrace() { return (ax * vx < 0); } // return if there is a brace or not

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return this->level; }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartWait() { wait = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	bool GetisHolding() { return this->isHolding; }
	void SetisHolding(BOOLEAN isHolding) { this->isHolding = isHolding;}
	CGameObject* GetHoldingObject() {
		return this->holdingObject;
	}
	void SetHoldingObject(CGameObject* holdingObject);
	void DecreaseLevel();
};