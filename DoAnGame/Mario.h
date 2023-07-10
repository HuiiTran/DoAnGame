#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.12f
#define MARIO_RUNNING_SPEED		0.16f

#define MARIO_LEVEL_RUN_SPEED 0.01f
#define LEVEL_RUN_MAX 7


#define MARIO_ACCEL_WALK_X	0.00015f
#define MARIO_ACCEL_RUN_X	0.00016f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.51f

#define TIME_TO_LEVEL_RUN 150
#define TIME_PREPARE_LEVEL_RUN 650
#define TIME_KICK 100
#define TIME_CHANGING 550
#define TIME_FLY 4000

#define MARIO_GRAVITY			0.0019f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_FLY_Y 0.33f
#define MARIO_FALL_WITH_TAIL_Y 0.0005f

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

#define MARIO_STATE_FLY				800

#define MARIO_STATE_IN_WORLDMAP		900

#define MARIO_GO_LEFT				1001
#define MARIO_GO_RIGHT				1002
#define MARIO_GO_UP					1003
#define MARIO_GO_DOWN				1004
#define MARIO_WORLDMAP_SPEED		0.1f

#define MARIO_SELECTSTAGE_STATE		1005

#define MARIO_GOING_DOWN_PIPE_STATE	1101
#define MARIO_GOING_UP_PIPE_STATE	1102

#define MARIO_TAIL_ATTACKING_STATE	1103
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

#define	ID_ANI_MARIO_USINGPIPE	1010

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_MINI	1160
#define ID_ANI_MARIO_BIG_MINI	1170
#define ID_ANI_MARIO_TANOOKI_MINI	1180

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

#define	ID_ANI_MARIO_SMALL_USINGPIPE	1410

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

#define ID_ANI_MARIO_TANOOKI_FALL_RIGHT 2610
#define ID_ANI_MARIO_TANOOKI_FALL_LEFT 2611

#define ID_ANI_MARIO_TANOOKI_FLY_RIGHT 2620
#define ID_ANI_MARIO_TANOOKI_FLY_LEFT 2621

#define ID_ANI_MARIO_TANOOKI_SIT_RIGHT 2700
#define ID_ANI_MARIO_TANOOKI_SIT_LEFT 2701

#define ID_ANI_MARIO_TANOOKI_HOLD_RIGHT 2800
#define ID_ANI_MARIO_TANOOKI_HOLD_LEFT 2801

#define ID_ANI_MARIO_TANOOKI_HOLD_RIGHT_IDLE 2880
#define ID_ANI_MARIO_TANOOKI_HOLD_LEFT_IDLE 2881

#define ID_ANI_MARIO_TANOOKI_KICKING_RIGHT	2900
#define ID_ANI_MARIO_TANOOKI_KICKING_LEFT 2901

#define	ID_ANI_MARIO_TANOOKI_USINGPIPE	2410

#define ID_ANI_MARIO_TANOOKI_TAILATTACKING_RIGHT	2910
#define ID_ANI_MARIO_TANOOKI_TAILATTACKING_LEFT	2911

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

#define MARIO_TANOOKI_BBOX_WIDTH  15
#define MARIO_TANOOKI_BBOX_HEIGHT 24
#define MARIO_TANOOKI_BBOX_WIDTH_TAILATTACK  23

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
	BOOLEAN isFlying;
	BOOLEAN isUsingPipe;
	BOOLEAN isTailAttacking;
	CGameObject* holdingObject;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 


	int level; 
	int untouchable; 
	int level_run = 0;

	int directUsingpipe = 0;

	ULONGLONG untouchable_start;
	ULONGLONG wait;
	ULONGLONG start_kick;
	ULONGLONG start_change;
	ULONGLONG start_prepare_run;
	ULONGLONG stop_level_run;
	ULONGLONG start_level_run;
	ULONGLONG start_fly;
	ULONGLONG start_die;
	ULONGLONG start_usingPipe;
	ULONGLONG start_tailattack;
	int coin; 

	//world map mario/////////
	bool isAllowLeft = 0;
	bool isAllowRight = 1;
	bool isAllowUp = 0;
	bool isAllowDown = 0;

	float startX, startY;
	bool isGoingNodeX = false;
	bool isGoingNodeY = false;
	////////////
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
	void OnCollisionWithPPOWER(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithGreenKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithInvisibleBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithNode(LPCOLLISIONEVENT e);
	void OnCollisionWithPipeTeleport(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdTanooki();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;

		int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
		if (currentscene == 5) ay = MARIO_GRAVITY;
		else ay = 0;

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

		isFlying = false;
		start_fly = 0;

		isUsingPipe = false;
		start_usingPipe = 0;

		isTailAttacking = false;
		start_tailattack = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return ((state != MARIO_STATE_DIE && untouchable==0)); }
	bool IsBrace() { return (ax * vx < 0); } // return if there is a brace or not
	int GetLevelRun() { return this->level_run; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return this->level; }
	void DecreaseLevel();

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartWait() { wait = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	bool GetisHolding() { return this->isHolding; }
	void SetisHolding(BOOLEAN isHolding) { this->isHolding = isHolding;}
	CGameObject* GetHoldingObject() {
		return this->holdingObject;
	}
	void SetHoldingObject(CGameObject* holdingObject);

	void SetisKicking(bool isKicking) { this->isKicking = isKicking; }
	void StartKick() { start_kick = GetTickCount64(); }

	bool GetisOnPlatform() { return this->isOnPlatform; }

	int GetCoin() { return this->coin; }

	void SetisUsingPipe(bool isUsingPipe) { this->isUsingPipe = isUsingPipe; }
	int GetisUsingPipe() { return this->isUsingPipe; }

	int GetdirectUsingPipe() { return this->directUsingpipe; }
	///world map mario
	bool GetisAllowLeft() { return isAllowLeft; }
	bool GetisAllowRight() { return isAllowRight; }
	bool GetisAllowUp() { return isAllowUp; }
	bool GetisAllowDown() { return isAllowDown; }

	void Go1NodeX(LPGAMEOBJECT gameobject);
	void Go1NodeY(LPGAMEOBJECT gameobject);

};