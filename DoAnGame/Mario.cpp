#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "QuestionBrick.h"
#include "Collision.h"
#include "MushRoom.h"
#include "Leaf.h"
#include "Koopa.h"
#include "FireBall.h"
#include "VenusFireTrap.h"
#include "FlyGoomba.h"
#include "P_Power.h"
#include "Effect.h"
#include "PiranhaPlant.h"
#include "GreenKoopa.h"
#include "InvisibleBlock.h"
#include "Node.h"
#include "PipeTeleport.h"
#include "Brick.h"
#include "BreakBrickPiece.h"
#include "PlayScene.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	DebugOutTitle(L"%d", isUsingPipe);
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
	if (currentscene == SCENE_WORLD_MAP)
	{
		if (isGoingNodeX == true)
		{
			if (vx * (x - startX) >= 0)
			{
				x = startX;
				vx = 0;
				vy = 0;
				isGoingNodeX = false;
			}
		}
		if (isGoingNodeY == true)
		{
			if (vy * (y - startY) >= 0)
			{
				y = startY;
				vx = 0;
				vy = 0;
				isGoingNodeY = false;
			}
		}
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
		return;
	}
	if (isChanging) // change form so make mario not moving
	{
		vx = 0;
		vy = 0;
	}
	else {
		vy += ay * dt;
		vx += ax * dt;
	}

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (holdingObject != NULL)
	{
		if (dynamic_cast<CKoopa*>(holdingObject))
		{
			CKoopa* koopa = dynamic_cast<CKoopa*>(holdingObject);

			if (koopa->GetState() == KOOPA_STATE_WALKING)
			{
				SetHoldingObject(NULL);
			}
			else
			{
				float holdingObjX, holdingObjY;
				int width = MARIO_SMALL_BBOX_WIDTH;
				if (level == MARIO_LEVEL_BIG)
				{
					width = MARIO_BIG_BBOX_WIDTH;
					if (nx > 0)
					{
						holdingObjX = x + width;
						holdingObjY = y + 3;
					}
					else
					{
						holdingObjX = x - width;
						holdingObjY = y + 3;
					}
					koopa->SetPosition(holdingObjX, holdingObjY);
				}
				else if (level == MARIO_LEVEL_TANOOKI)
				{
					width = MARIO_TANOOKI_BBOX_WIDTH;
					if (nx > 0)
					{
						holdingObjX = x + width;
						holdingObjY = y + 2;
					}
					else
					{
						holdingObjX = x - width;
						holdingObjY = y + 2;
					}
					koopa->SetPosition(holdingObjX, holdingObjY);
				}
				else
				{
					if (nx > 0)
					{
						holdingObjX = x + width;
						holdingObjY = y - 2;
					}
					else
					{
						holdingObjX = x - width;
						holdingObjY = y - 2;
					}
					koopa->SetPosition(holdingObjX, holdingObjY);
				}
			}
		}
		else if (dynamic_cast<CGreenKoopa*>(holdingObject))
		{
			CGreenKoopa* greenkoopa = dynamic_cast<CGreenKoopa*>(holdingObject);

			if (greenkoopa->GetState() == GREEN_KOOPA_STATE_WALKING)
			{
				SetHoldingObject(NULL);
			}
			else
			{
				float holdingObjX, holdingObjY;
				int width = MARIO_SMALL_BBOX_WIDTH;
				if (level == MARIO_LEVEL_BIG)
				{
					width = MARIO_BIG_BBOX_WIDTH;
					if (nx > 0)
					{
						holdingObjX = x + width;
						holdingObjY = y + 3;
					}
					else
					{
						holdingObjX = x - width;
						holdingObjY = y + 3;
					}
					greenkoopa->SetPosition(holdingObjX, holdingObjY);
				}
				else if (level == MARIO_LEVEL_TANOOKI)
				{
					width = MARIO_TANOOKI_BBOX_WIDTH;
					if (nx > 0)
					{
						holdingObjX = x + width;
						holdingObjY = y + 2;
					}
					else
					{
						holdingObjX = x - width;
						holdingObjY = y + 2;
					}
					greenkoopa->SetPosition(holdingObjX, holdingObjY);
				}
				else
				{
					if (nx > 0)
					{
						holdingObjX = x + width;
						holdingObjY = y - 2;
					}
					else
					{
						holdingObjX = x - width;
						holdingObjY = y - 2;
					}
					greenkoopa->SetPosition(holdingObjX, holdingObjY);
				}
			}
		}
	}
	//kick koopa
	if (isKicking)
	{
		if (GetTickCount64() - start_kick > TIME_KICK)
		{
			isKicking = false;
			start_kick = 0;
		}
	}
	if (GetTickCount64() - start_change > TIME_CHANGING)
	{
		isChanging = false;
		isDecreaseLevel = false;
		start_change = 0;
	}
	//running 
	if ( (!isRunning) || (!vx) || (IsBrace() && !isFlying) || ((!isOnPlatform) && (isFlying) && (vy > 0) ))
	{
		if (GetTickCount64() - stop_level_run > TIME_TO_LEVEL_RUN)
		{
			if (level_run > 0)
			{
				level_run--;
			}
			stop_level_run = GetTickCount64();
		}
			start_prepare_run = GetTickCount64();
	}
	else
	{
		if (GetTickCount64() - start_prepare_run > TIME_PREPARE_LEVEL_RUN)
		{
			if (GetTickCount64() - start_level_run > TIME_TO_LEVEL_RUN)
			{
				if (level_run < LEVEL_RUN_MAX)
				{
					level_run++;
				}
				start_level_run = GetTickCount64();
			}
		}
	}
	//DebugOutTitle(L"Coins: %d", isFlying);
	//fly
	if (isFlying)
	{
		if (isOnPlatform)
		{
			isFlying = false;
			ay = MARIO_GRAVITY;
			start_fly = 0;
		}
		else
		{
			if (start_fly == 0)
				start_fly = GetTickCount64();
			
			if (GetTickCount64() - start_fly > TIME_FLY && level_run == LEVEL_RUN_MAX)
			{
				isFlying = false;
				level_run = 0;
				start_fly = 0;
			}
		}
	}

	if (state == MARIO_STATE_DIE && GetTickCount64() - start_die > 2000)
	{
		CGame::GetInstance()->InitiateSwitchScene(1);
	}

	if (isTailAttacking)
	{
		if (GetTickCount64() - start_tailattack > 300)
		{
			isTailAttacking = false;
			start_tailattack = 0;
		}
	}
	//Using pipe
	if (isUsingPipe == true)
	{
		if (GetTickCount64() - start_usingPipe > 300)
		{
			if (directUsingpipe == 2)
			{
				if(level != MARIO_LEVEL_SMALL)
					SetPosition(UsingPipeDes_X, UsingPipeDes_Y - 10);
				else
					SetPosition(UsingPipeDes_X, UsingPipeDes_Y);
			}
			else
				SetPosition(UsingPipeDes_X, UsingPipeDes_Y);

			if (GetTickCount64() - start_usingPipe > 600)
			{
				isUsingPipe = false;
				start_usingPipe = 0;
				UsingPipeDes_X = 0;
				UsingPipeDes_Y = 0;
				directUsingpipe = 0;
				ay = MARIO_GRAVITY;
			}

		}
	}
	isOnPlatform = false;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
	if(currentscene == SCENE_MAP_1_1)
	{
		if (e->ny != 0 && e->obj->IsBlocking())
		{
			vy = 0;
			if (e->ny < 0) isOnPlatform = true;
		}
		else
			if (e->nx != 0 && e->obj->IsBlocking())
			{
				vx = 0;
			}

		if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		else if (dynamic_cast<CCoin*>(e->obj))
			OnCollisionWithCoin(e);
		else if (dynamic_cast<CPortal*>(e->obj))
			OnCollisionWithPortal(e);
		else if (dynamic_cast<CQuestionBrick*>(e->obj))
			OnCollisionWithQuestionBrick(e);
		else if (dynamic_cast<CMushRoom*>(e->obj))
			OnCollisionWithMushRoom(e);
		else if (dynamic_cast<CLeaf*>(e->obj))
			OnCollisionWithLeaf(e);
		else if (dynamic_cast<CKoopa*>(e->obj))
			OnCollisionWithKoopa(e);
		else if (dynamic_cast<CFireBall*>(e->obj))
			OnCollisionWithFireBall(e);
		else if (dynamic_cast<CVenusFireTrap*>(e->obj))
			OnCollisionWithVenusFireTrap(e);
		else if (dynamic_cast<CFlyGoomba*>(e->obj))
			OnCollisionWithFlyGoomba(e);
		else if (dynamic_cast<CP_Power*>(e->obj))
			OnCollisionWithPPOWER(e);
		else if (dynamic_cast<CPiranhaPlant*>(e->obj))
			OnCollisionWithPiranhaPlant(e);
		else if (dynamic_cast<CGreenKoopa*>(e->obj))
			OnCollisionWithGreenKoopa(e);
		else if (dynamic_cast<CInvisibleBlock*>(e->obj))
			OnCollisionWithInvisibleBlock(e);
		else if (dynamic_cast<CPipeTeleport*>(e->obj))
			OnCollisionWithPipeTeleport(e);
		else if (dynamic_cast<CBrick*>(e->obj))
			OnCollisionWithBrick(e);
	}
	else if (currentscene == SCENE_WORLD_MAP)
	{
		if (e->obj->IsBlocking()) {
			vx = 0;
			vy = 0;
		}
		if (dynamic_cast<CNode*>(e->obj))
			OnCollisionWithNode(e);
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() == GOOMBA_STATE_DIE_JUMP || goomba->GetState() == GOOMBA_STATE_DIE)
		return;

	if (isTailAttacking && (e->nx > 0 || e->nx < 0))
	{
		goomba->SetState(GOOMBA_STATE_DIE_JUMP);
		
	}
	else
	{
		// jump on top >> kill Goomba and deflect a bit 
		if (e->ny < 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				goomba->SetState(GOOMBA_STATE_DIE);
				if (isFlying)
					vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
				else
					vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else // hit by Goomba
		{
			if (untouchable == 0)
			{
				if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_JUMP)
				{
					if (level > MARIO_LEVEL_SMALL)
					{
						DecreaseLevel();
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);
					}
				}
			}
		}
	}
}
void CMario::OnCollisionWithFlyGoomba(LPCOLLISIONEVENT e)
{
	CFlyGoomba* flygoomba = dynamic_cast<CFlyGoomba*>(e->obj);
	if (flygoomba->GetState() == FLYGOOMBA_STATE_DIE_JUMP || flygoomba->GetState() == FLYGOOMBA_STATE_DIE)
		return;
	if (isTailAttacking && (e->nx > 0 || e->nx < 0))
	{
		flygoomba->SetState(FLYGOOMBA_STATE_DIE_JUMP);
	}
	else
	{
		if (e->ny < 0)
		{
			if (flygoomba->GetState() != FLYGOOMBA_STATE_DIE)
			{
				if (isFlying)
					vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
				else
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				if (flygoomba->GetState() == FLYGOOMBA_STATE_WING_FLY || flygoomba->GetState() == FLYGOOMBA_STATE_WING_JUMPFLY || flygoomba->GetState() == FLYGOOMBA_STATE_WING_WALKING)
				{
					flygoomba->SetState(FLYGOOMBA_STATE_WALKING);
					MScore += FLYGOOMBA_SCORE;
				}
				else if (flygoomba->GetState() == FLYGOOMBA_STATE_WALKING)
				{
					flygoomba->SetState(FLYGOOMBA_STATE_DIE);
				}
			}
		}
		else
		{
			if (untouchable == 0)
			{
				if (flygoomba->GetState() != FLYGOOMBA_STATE_DIE)
				{
					if (level > MARIO_LEVEL_SMALL)
					{
						DecreaseLevel();
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);
					}
				}
			}
		}
	}
}
void CMario::DecreaseLevel()
{
	isDecreaseLevel = true;
	switch (level)
	{
	case MARIO_LEVEL_TANOOKI:
		SetLevel( MARIO_LEVEL_BIG);
		break;
	case MARIO_LEVEL_BIG:
		SetLevel(MARIO_LEVEL_SMALL);
		break;
	case MARIO_LEVEL_SMALL:
		SetState(MARIO_STATE_DIE);
		break;
	default:
		break;
	}
}
void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	float koopaX, koopaY;
	if (koopa->GetIsHolded()) return;

	if (isTailAttacking && (e->nx > 0 || e->nx < 0))
	{
		koopa->SetMLevel(this->level);
		koopa->SetisFlip(true);
		koopa->SetState(KOOPA_STATE_SHELL_FLIP);
	}
	else
	{
		if (e->ny < 0 && !this->isOnPlatform)
		{
			koopa->SetMLevel(this->level);
			if (koopa->GetState() != KOOPA_STATE_SHELL)
			{
				koopa->GetPosition(koopaX, koopaY);
				koopa->SetPosition(koopaX, koopaY - 10);
				koopa->SetState(KOOPA_STATE_SHELL);
				if (isFlying)
					vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
				else
					vy = -MARIO_JUMP_DEFLECT_SPEED;

				LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
				CEffect* effect = new CEffect(x + 10, y, KOOPA_SCORE);
				thisscene->AddObjectToScene(effect);
				MScore += FLYGOOMBA_SCORE;
			}
			else
			{
				if (nx > 0)
				{
					koopa->GetPosition(koopaX, koopaY);
					koopa->SetPosition(koopaX + 5, koopaY - 10);
					koopa->SetSpeed(KOOPA_SHELL_SCROLL_SPEED, 0);
					if (isFlying)
						vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
					else
						vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				else
				{
					koopa->GetPosition(koopaX, koopaY);
					koopa->SetPosition(koopaX - 5, koopaY - 10);
					koopa->SetSpeed(-KOOPA_SHELL_SCROLL_SPEED, 0);
					if (isFlying)
						vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
					else
						vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				koopa->SetState(KOOPA_STATE_SHELL_SCROLL);

				LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
				CEffect* effect = new CEffect(x + 10, y, KOOPA_SCORE);
				thisscene->AddObjectToScene(effect);
				MScore += FLYGOOMBA_SCORE;
			}
		}
		else if (nx > 0 && koopa->GetState() == KOOPA_STATE_SHELL && isHolding == false)
		{
			isKicking = true;
			start_kick = GetTickCount64();
			koopa->SetMLevel(this->level);
			koopa->SetSpeed(KOOPA_SHELL_SCROLL_SPEED, 0);
			koopa->SetState(KOOPA_STATE_SHELL_SCROLL);
		}
		else if (nx < 0 && koopa->GetState() == KOOPA_STATE_SHELL && isHolding == false)
		{
			isKicking = true;
			start_kick = GetTickCount64();
			koopa->SetMLevel(this->level);
			koopa->SetSpeed(-KOOPA_SHELL_SCROLL_SPEED, 0);
			koopa->SetState(KOOPA_STATE_SHELL_SCROLL);
		}
		else //being hit
		{
			if (!untouchable)
			{
				if (koopa->GetState() == KOOPA_STATE_SHELL)
				{
					if (isHolding) {
						koopa->SetPosition(x + nx * 15, y);
						koopa->SetIsHolded(true);
						SetHoldingObject(koopa);
					}
					else
					{
						if (nx > 0) {
							koopa->SetSpeed(KOOPA_SHELL_SCROLL_SPEED, 0);
						}
						else {

							koopa->SetSpeed(-KOOPA_SHELL_SCROLL_SPEED, 0);
						}
						koopa->SetState(KOOPA_STATE_SHELL_SCROLL);
					}
				}
				else if (koopa->GetState() != KOOPA_STATE_DIE || koopa->GetState() == KOOPA_STATE_RESPAWN)
				{
					if (level > MARIO_LEVEL_SMALL)
					{
						DecreaseLevel();
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);
					}
				}
			}
		}
	}
}
void CMario::OnCollisionWithGreenKoopa(LPCOLLISIONEVENT e)
{
	CGreenKoopa* greenkoopa = dynamic_cast<CGreenKoopa*>(e->obj);

	float greenkoopaX, greenkoopaY;

	if (greenkoopa->GetIsHolded()) return;

	if (isTailAttacking && (e->nx > 0 || e->nx < 0))
	{
		greenkoopa->SetMLevel(this->level);
		greenkoopa->SetisFlip(true);
		greenkoopa->SetState(KOOPA_STATE_SHELL_FLIP);
	}
	else
	{
		if (e->ny < 0 && !this->isOnPlatform)
		{
			greenkoopa->SetMLevel(this->level);
			if (greenkoopa->GetState() != GREEN_KOOPA_STATE_SHELL)
			{
				greenkoopa->GetPosition(greenkoopaX, greenkoopaY);
				greenkoopa->SetPosition(greenkoopaX, greenkoopaY - 10);
				greenkoopa->SetState(GREEN_KOOPA_STATE_SHELL);
				if (isFlying)
					vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
				else
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
				CEffect* effect = new CEffect(x + 10, y, GREEN_KOOPA_SCORE);
				thisscene->AddObjectToScene(effect);
			}
			else
			{
				if (nx > 0)
				{
					greenkoopa->GetPosition(greenkoopaX, greenkoopaY);
					greenkoopa->SetPosition(greenkoopaX + 5, greenkoopaY - 10);
					greenkoopa->SetSpeed(GREEN_KOOPA_SHELL_SCROLL_SPEED, 0);
					if (isFlying)
						vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
					else
						vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				else
				{
					greenkoopa->GetPosition(greenkoopaX, greenkoopaY);
					greenkoopa->SetPosition(greenkoopaX - 5, greenkoopaY - 10);
					greenkoopa->SetSpeed(-GREEN_KOOPA_SHELL_SCROLL_SPEED, 0);
					if (isFlying)
						vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
					else
						vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				greenkoopa->SetState(GREEN_KOOPA_STATE_SHELL_SCROLL);

				LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
				CEffect* effect = new CEffect(x + 10, y, GREEN_KOOPA_SCORE);
				thisscene->AddObjectToScene(effect);
			}
		}
		else if (nx > 0 && greenkoopa->GetState() == GREEN_KOOPA_STATE_SHELL && isHolding == false)
		{
			isKicking = true;
			start_kick = GetTickCount64();
			greenkoopa->SetMLevel(this->level);
			greenkoopa->SetSpeed(GREEN_KOOPA_SHELL_SCROLL_SPEED, 0);
			greenkoopa->SetState(GREEN_KOOPA_STATE_SHELL_SCROLL);
		}
		else if (nx < 0 && greenkoopa->GetState() == GREEN_KOOPA_STATE_SHELL && isHolding == false)
		{
			isKicking = true;
			start_kick = GetTickCount64();
			greenkoopa->SetMLevel(this->level);
			greenkoopa->SetSpeed(-GREEN_KOOPA_SHELL_SCROLL_SPEED, 0);
			greenkoopa->SetState(GREEN_KOOPA_STATE_SHELL_SCROLL);
		}
		else //being hit
		{
			if (!untouchable)
			{
				if (greenkoopa->GetState() == GREEN_KOOPA_STATE_SHELL)
				{
					if (isHolding) {
						greenkoopa->SetPosition(x + nx * 15, y);
						greenkoopa->SetIsHolded(true);
						SetHoldingObject(greenkoopa);
					}
					else
					{
						if (nx > 0) {
							greenkoopa->SetSpeed(GREEN_KOOPA_SHELL_SCROLL_SPEED, 0);
						}
						else {

							greenkoopa->SetSpeed(-GREEN_KOOPA_SHELL_SCROLL_SPEED, 0);
						}
						greenkoopa->SetState(GREEN_KOOPA_STATE_SHELL_SCROLL);
					}
				}
				else if (greenkoopa->GetState() != GREEN_KOOPA_STATE_DIE || greenkoopa->GetState() == GREEN_KOOPA_STATE_RESPAWN)
				{
					if (level > MARIO_LEVEL_SMALL)
					{
						DecreaseLevel();
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);
					}
				}
			}
		}
	}
}
void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionbrick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->ny > 0 && questionbrick->IsEmpty() == false)
	{
		if(questionbrick->GetBrickType() == 0) //coin
		{
			questionbrick->SetEmpty(true);
			float questionbrick_x, questionbrick_y;
			questionbrick->GetPosition(questionbrick_x, questionbrick_y);


			CCoin* newCoin = new CCoin(questionbrick_x, questionbrick_y -2* COIN_WIDTH, 1);
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

			thisscene->AddObjectToScene(newCoin);
			newCoin->SetFly(true);

			questionbrick->SetPosition(questionbrick_x, questionbrick_y - QUESTIONBRICK_UP);
			coin++;
			//score
			CEffect* effect = new CEffect(questionbrick_x + COIN_WIDTH / 2, questionbrick_y - 2 * QUESTIONBRICK_UP, COIN_SCORE);
			thisscene->AddObjectToScene(effect);
			MScore += COIN_SCORE;
		}
		if ((questionbrick->GetBrickType() == 1 && this->level == MARIO_LEVEL_SMALL) || (questionbrick->GetBrickType() == 2 && this->level == MARIO_LEVEL_SMALL)) //mushroom
		{
			questionbrick->SetEmpty(true);
			float questionbrick_x, questionbrick_y;
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

			questionbrick->GetPosition(questionbrick_x, questionbrick_y);
			questionbrick->Delete();

			CMushRoom* newMush = new CMushRoom(questionbrick_x, questionbrick_y - 5 , 0 );
			if (nx < 0)
				newMush->SetState(MUSHROOM_APPEAR_STATE_LEFT);
			else
				newMush->SetState(MUSHROOM_APPEAR_STATE_RIGHT);
			thisscene->AddObjectToScene(newMush);
			
			CQuestionBrick* newbrick = new CQuestionBrick(questionbrick_x, questionbrick_y);
			newbrick->SetEmpty(true);
			thisscene->AddObjectToScene(newbrick);
			newbrick->SetPosition(questionbrick_x, questionbrick_y - QUESTIONBRICK_UP);
			
		}
		if ((questionbrick->GetBrickType() == 2 && (this->level == MARIO_LEVEL_BIG || this->level == MARIO_LEVEL_TANOOKI)) || (questionbrick->GetBrickType() == 1 && (this->level == MARIO_LEVEL_BIG || this->level == MARIO_LEVEL_TANOOKI))) //leaf
		{
			questionbrick->SetEmpty(true);
			float questionbrick_x, questionbrick_y;
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

			questionbrick->GetPosition(questionbrick_x, questionbrick_y);
			questionbrick->SetPosition(questionbrick_x, questionbrick_y - QUESTIONBRICK_UP);

			CLeaf* newLeaf = new CLeaf(questionbrick_x, questionbrick_y -QUESTIONBRICK_UP);
			thisscene->AddObjectToScene(newLeaf);
		}
		if (questionbrick->GetBrickType() == 3) //life up
		{
			questionbrick->SetEmpty(true);
			float questionbrick_x, questionbrick_y;
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
			
			questionbrick->GetPosition(questionbrick_x, questionbrick_y);
			questionbrick->SetPosition(questionbrick_x, questionbrick_y - QUESTIONBRICK_UP);
			questionbrick->Delete();

			CMushRoom* newMush = new CMushRoom(questionbrick_x, questionbrick_y - 5, 1);
			if (nx < 0)
				newMush->SetState(MUSHROOM_APPEAR_STATE_LEFT);
			else
				newMush->SetState(MUSHROOM_APPEAR_STATE_RIGHT);
			thisscene->AddObjectToScene(newMush);

			CQuestionBrick* newbrick = new CQuestionBrick(questionbrick_x, questionbrick_y);
			newbrick->SetEmpty(true);
			thisscene->AddObjectToScene(newbrick);
			newbrick->SetPosition(questionbrick_x, questionbrick_y - QUESTIONBRICK_UP);
		}
		if (questionbrick->GetBrickType() == 4) //p_power change shining brick to coin
		{
			questionbrick->SetEmpty(true);
			float questionbrick_x, questionbrick_y;
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

			questionbrick->GetPosition(questionbrick_x, questionbrick_y);
			questionbrick->SetPosition(questionbrick_x, questionbrick_y - QUESTIONBRICK_UP);
			questionbrick->Delete();

			CP_Power* ppower = new CP_Power(questionbrick_x, questionbrick_y - 16);
			thisscene->AddObjectToScene(ppower);
			CEffect* effect = new CEffect(questionbrick_x, questionbrick_y - 16);
			thisscene->AddObjectToScene(effect);

			CQuestionBrick* newbrick = new CQuestionBrick(questionbrick_x, questionbrick_y);
			newbrick->SetEmpty(true);
			thisscene->AddObjectToScene(newbrick);
			newbrick->SetPosition(questionbrick_x, questionbrick_y - QUESTIONBRICK_UP);
		}

	}
}
void CMario::OnCollisionWithMushRoom(LPCOLLISIONEVENT e)
{
	CMushRoom* mushroom = dynamic_cast<CMushRoom*>(e->obj);
	
	if (mushroom->Gettype() == 0)
	{
		float mX, mY;
		mushroom->GetPosition(mX, mY);
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

		CEffect* effect = new CEffect(mX + 10, mY, MUSHROOM_SCORE);
		thisscene->AddObjectToScene(effect);
		if (this->level == MARIO_LEVEL_SMALL)
		{
			y -= 10;
			SetLevel(MARIO_LEVEL_BIG);
		}
		MScore += MUSHROOM_SCORE;
	}
	else
	{
		float mX, mY;
		mushroom->GetPosition(mX, mY);
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

		CEffect* effect = new CEffect(mX, mY, 2);
		thisscene->AddObjectToScene(effect);
		this->MLife += 1;
	}
	mushroom->Delete();
}
void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	if (this->level != MARIO_LEVEL_TANOOKI)
	{
		y -= 10;
		SetLevel(MARIO_LEVEL_TANOOKI);
	}
	float lX, lY;
	leaf->GetPosition(lX, lY);
	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

	CEffect* effect = new CEffect(lX, lY, LEAF_SCORE);
	thisscene->AddObjectToScene(effect);
	MScore += LEAF_SCORE;

	leaf->Delete();
}
void CMario::OnCollisionWithPPOWER(LPCOLLISIONEVENT e)
{
	CP_Power* ppower = dynamic_cast<CP_Power*>(e->obj);
	if (ppower->GetisHit() == false)
	{
		ppower->SetisHit(true);
		ppower->SetState(P_POWER_STATE_HIT);
	}
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
	MScore += COIN_SCORE / 2;
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	float bX, bY;

	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	brick->GetPosition(bX, bY);
	if ( e->nx != 0 && (brick->GetType() == 2) && (abs(bY - this->y) < MARIO_SMALL_BBOX_HEIGHT / 2) )
	{
		if(isTailAttacking)
		{
			brick->Delete();
			CBreakBrickPiece* piece_1 = new CBreakBrickPiece(bX, bY - PIECE_OFFSET);
			piece_1->SetState(PIECE_STATE_LEFT);
			CBreakBrickPiece* piece_2 = new CBreakBrickPiece(bX, bY + PIECE_OFFSET);
			piece_2->SetState(PIECE_STATE_LEFT);
			CBreakBrickPiece* piece_3 = new CBreakBrickPiece(bX, bY - PIECE_OFFSET);
			piece_3->SetState(PIECE_STATE_RIGHT);
			CBreakBrickPiece* piece_4 = new CBreakBrickPiece(bX, bY + PIECE_OFFSET);
			piece_4->SetState(PIECE_STATE_RIGHT);

			thisscene->AddObjectToScene(piece_1);
			thisscene->AddObjectToScene(piece_2);
			thisscene->AddObjectToScene(piece_3);
			thisscene->AddObjectToScene(piece_4);
		}
	}
}
void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}
void CMario::OnCollisionWithPipeTeleport(LPCOLLISIONEVENT e)
{
	CPipeTeleport* pipe = (CPipeTeleport*)e->obj;
	directUsingpipe = pipe->GetDirect();
	UsingPipeDes_X = pipe->GetdesX();
	UsingPipeDes_Y = pipe->GetdesY();
}

void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	if (untouchable) return;
	e->obj->Delete();
	if (level > MARIO_LEVEL_SMALL)
	{
		DecreaseLevel();
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
	
}
void CMario::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
	if (untouchable) return;
	if (isTailAttacking)
	{
		float Tx, Ty;
		e->obj->GetPosition(Tx, Ty);
		e->obj->Delete();
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
		CEffect* effect = new CEffect(Tx, Ty);
		CEffect* score = new CEffect(Tx, Ty, VENUSFIRETRAP_SCORE);
		thisscene->AddObjectToScene(effect);
		thisscene->AddObjectToScene(score);
		MScore += VENUSFIRETRAP_SCORE;
	}
	else
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			DecreaseLevel();
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	if (untouchable) return;
	if (isTailAttacking )
	{
		float Tx, Ty;
		e->obj->GetPosition(Tx, Ty);
		e->obj->Delete();
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
		CEffect* effect = new CEffect(Tx, Ty);
		CEffect* score = new CEffect(Tx, Ty, PIRANHA_PLANT_SCORE);
		thisscene->AddObjectToScene(effect);
		thisscene->AddObjectToScene(score);
		MScore += PIRANHA_PLANT_SCORE;
	}
	else
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			DecreaseLevel();
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}
void CMario::OnCollisionWithInvisibleBlock(LPCOLLISIONEVENT e)
{
	DebugOut(L">>> Mario DIE >>> \n");
	SetState(MARIO_STATE_DIE);
}
void CMario::OnCollisionWithNode(LPCOLLISIONEVENT e)
{
	CNode* node = dynamic_cast<CNode*>(e->obj);
	isAllowLeft = node->GetAllowLeft();
	isAllowRight = node->GetAllowRight();
	isAllowUp = node->GetAllowUp();
	isAllowDown = node->GetAllowDown();
	if (e->nx != 0) {
		Go1NodeX(node);
	}
	if (e->ny != 0) {
		Go1NodeY(node);
	}
	if (node->GetType() == 2)
	{
		SetState(MARIO_SELECTSTAGE_STATE);
	}
}
void CMario::Go1NodeX(LPGAMEOBJECT gameobject) {
	float tempY;
	gameobject->GetPosition(startX, tempY);	
	isGoingNodeX = true;
}
void CMario::Go1NodeY(LPGAMEOBJECT gameobject) {
	float tempX;
	gameobject->GetPosition(tempX, startY);
	isGoingNodeY = true;
}

void CMario::SetHoldingObject(CGameObject* holdingObject)
{
	if (holdingObject == NULL)
	{
		if (dynamic_cast<CKoopa*>(this->holdingObject))
		{
			CKoopa* koopa = dynamic_cast<CKoopa*>(this->holdingObject);
			if (koopa->GetState() == KOOPA_STATE_SHELL)
			{
				if (nx > 0)
				{
					koopa->SetSpeed(KOOPA_SHELL_SCROLL_SPEED, 0);
				}
				else
				{
					koopa->SetSpeed(-KOOPA_SHELL_SCROLL_SPEED, 0);
				}
				koopa->SetIsHolded(false);
				koopa->SetState(KOOPA_STATE_SHELL_SCROLL);
			}
			else if (koopa->GetState() == KOOPA_STATE_RESPAWN) 
			{
				if (nx > 0) 
				{
					koopa->SetSpeed(KOOPA_SHELL_SCROLL_SPEED, 0);
				}
				else 
				{
					koopa->SetSpeed(-KOOPA_SHELL_SCROLL_SPEED, 0);
				}
				koopa->SetIsHolded(false);
				koopa->SetState(KOOPA_STATE_SHELL_SCROLL);
			}
		}

		else if (dynamic_cast<CGreenKoopa*>(this->holdingObject))
		{
			CGreenKoopa* greenkoopa = dynamic_cast<CGreenKoopa*>(this->holdingObject);
			if (greenkoopa->GetState() == GREEN_KOOPA_STATE_SHELL)
			{
				if (nx > 0)
				{
					greenkoopa->SetSpeed(GREEN_KOOPA_SHELL_SCROLL_SPEED, 0);
				}
				else
				{
					greenkoopa->SetSpeed(-GREEN_KOOPA_SHELL_SCROLL_SPEED, 0);
				}
				greenkoopa->SetIsHolded(false);
				greenkoopa->SetState(GREEN_KOOPA_STATE_SHELL_SCROLL);
			}
			else if (greenkoopa->GetState() == GREEN_KOOPA_STATE_RESPAWN)
			{
				if (nx > 0)
				{
					greenkoopa->SetSpeed(GREEN_KOOPA_SHELL_SCROLL_SPEED, 0);
				}
				else
				{
					greenkoopa->SetSpeed(-GREEN_KOOPA_SHELL_SCROLL_SPEED, 0);
				}
				greenkoopa->SetIsHolded(false);
				greenkoopa->SetState(GREEN_KOOPA_STATE_SHELL_SCROLL);
			}
		}
	}
	this->holdingObject = holdingObject;
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isChanging)
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
			}
		}
		else if (holdingObject)
		{
			if (vx == 0)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SMALL_HOLD_RIGHT_IDLE;
				else
					aniId = ID_ANI_MARIO_SMALL_HOLD_LEFT_IDLE;
			}
			else
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SMALL_HOLD_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_HOLD_LEFT;
			}
		}
		else if (isKicking)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_KICKING_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_KICKING_LEFT;
		}
		else if (isUsingPipe)
		{
			aniId = ID_ANI_MARIO_SMALL_USINGPIPE;
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else
			{
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
					{
						if(level_run == LEVEL_RUN_MAX)
							aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT_FAST;
						else
							aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					}
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
					{
						if(level_run == LEVEL_RUN_MAX)
							aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT_FAST;
						else
							aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					}

					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
			}
	}
	else
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_SMALL_TO_BIG_RIGHT;
		else
			aniId = ID_ANI_MARIO_SMALL_TO_BIG_LEFT;
	}
	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isChanging)
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
		else if (holdingObject)
		{
			if (vx == 0)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_HOLD_RIGHT_IDLE;
				else
					aniId = ID_ANI_MARIO_HOLD_LEFT_IDLE;
			}
			else
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_HOLD_RIGHT;
				else
					aniId = ID_ANI_MARIO_HOLD_LEFT;
			}
		}
		else if (isKicking)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_KICKING_RIGHT;
			else
				aniId = ID_ANI_MARIO_KICKING_LEFT;
		}
		else if (isUsingPipe)
		{
			aniId = ID_ANI_MARIO_USINGPIPE;
		}
		else
		{
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
					{
						if(level_run == LEVEL_RUN_MAX)
							aniId = ID_ANI_MARIO_RUNNING_RIGHT_FAST;
						else
							aniId = ID_ANI_MARIO_RUNNING_RIGHT;
					}
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
					{
						if (level_run == LEVEL_RUN_MAX)
							aniId = ID_ANI_MARIO_RUNNING_LEFT_FAST;
						else
							aniId = ID_ANI_MARIO_RUNNING_LEFT;
					}	
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
				}
		}
	}
	else
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_SMALL_TO_BIG_RIGHT;
		else
			aniId = ID_ANI_MARIO_SMALL_TO_BIG_LEFT;
	}
	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}
//Get ani for tanooki
int CMario::GetAniIdTanooki()
{
	int aniId = -1;
	if (!isChanging)
	{
		if (!isOnPlatform)
		{
			if (isTailAttacking)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_TANOOKI_TAILATTACKING_RIGHT;
				else
					aniId = ID_ANI_MARIO_TANOOKI_TAILATTACKING_LEFT;
			}
			else
			{
				if (abs(ax) == MARIO_ACCEL_RUN_X)
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_TANOOKI_JUMP_RUN_RIGHT;
					else
						aniId = ID_ANI_MARIO_TANOOKI_JUMP_RUN_LEFT;
				}
				else
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_TANOOKI_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_TANOOKI_JUMP_WALK_LEFT;
				}
				if (isFlying)
				{
					if (level_run == LEVEL_RUN_MAX)
					{
						if (nx > 0)
							aniId = ID_ANI_MARIO_TANOOKI_FLY_RIGHT;
						else
							aniId = ID_ANI_MARIO_TANOOKI_FLY_LEFT;
					}
					else
					{
						if (nx > 0)
							aniId = ID_ANI_MARIO_TANOOKI_FALL_RIGHT;
						else
							aniId = ID_ANI_MARIO_TANOOKI_FALL_LEFT;
					}
				}
				if (isTailAttacking)
				{
					if (nx > 0)
						aniId = ID_ANI_MARIO_TANOOKI_TAILATTACKING_RIGHT;
					else
						aniId = ID_ANI_MARIO_TANOOKI_TAILATTACKING_LEFT;
				}
			}
		}
		else if (holdingObject)
		{
			if (vx == 0)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_TANOOKI_HOLD_RIGHT_IDLE;
				else
					aniId = ID_ANI_MARIO_TANOOKI_HOLD_LEFT_IDLE;
			}
			else
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_TANOOKI_HOLD_RIGHT;
				else
					aniId = ID_ANI_MARIO_TANOOKI_HOLD_LEFT;
			}
		}
		else if (isKicking)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_TANOOKI_KICKING_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANOOKI_KICKING_LEFT;
		}
		else if (isUsingPipe)
		{
			aniId = ID_ANI_MARIO_TANOOKI_USINGPIPE;
		}
		else if (isTailAttacking)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_TANOOKI_TAILATTACKING_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANOOKI_TAILATTACKING_LEFT;
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_TANOOKI_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_TANOOKI_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_TANOOKI_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_TANOOKI_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_TANOOKI_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
					{
						if (level_run == LEVEL_RUN_MAX)
							aniId = ID_ANI_MARIO_TANOOKI_RUNNING_RIGHT_FAST;
						else
							aniId = ID_ANI_MARIO_TANOOKI_RUNNING_RIGHT;
					}
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_TANOOKI_WALKING_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_TANOOKI_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
					{
						if (level_run == LEVEL_RUN_MAX)
							aniId = ID_ANI_MARIO_TANOOKI_RUNNING_LEFT_FAST;
						else
							aniId = ID_ANI_MARIO_TANOOKI_RUNNING_LEFT;
					}
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_TANOOKI_WALKING_LEFT;
				}
	}
	else
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_CHANGE_TO_TANOOKI_RIGHT;
		else
			aniId = ID_ANI_MARIO_CHANGE_TO_TANOOKI_LEFT;
	}
	if (aniId == -1) aniId = ID_ANI_MARIO_TANOOKI_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
	if(currentscene == SCENE_MAP_1_1)
	{
		if (state == MARIO_STATE_DIE)
			aniId = ID_ANI_MARIO_DIE;
		else if (level == MARIO_LEVEL_BIG)
			aniId = GetAniIdBig();
		else if (level == MARIO_LEVEL_SMALL)
			aniId = GetAniIdSmall();
		else if (level == MARIO_LEVEL_TANOOKI)
			aniId = GetAniIdTanooki();

		if ((level > MARIO_LEVEL_BIG) && (isDecreaseLevel))
		{

		}
		else
		{
			if (!untouchable)
			{
				animations->Get(aniId)->Render(x, y);
			}
			else if (untouchable)
			{
				int check = rand() % 2;
				if (check == 0)
				{
					animations->Get(aniId)->Render(x, y);

				}
			}
		}
	}
	else if (currentscene == SCENE_WORLD_MAP)
	{
		if (level == MARIO_LEVEL_SMALL)
			aniId = ID_ANI_MARIO_SMALL_MINI;
		else if (level == MARIO_LEVEL_BIG)
			aniId = ID_ANI_MARIO_BIG_MINI;
		else if (level == MARIO_LEVEL_TANOOKI)
			aniId = ID_ANI_MARIO_TANOOKI_MINI;

		animations->Get(aniId)->Render(x, y);
	}

	RenderBoundingBox();
	

}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
	if(currentscene == SCENE_MAP_1_1)
	{
		if (this->state == MARIO_STATE_DIE) return;

		switch (state)
		{
		case MARIO_STATE_RUNNING_RIGHT:
			if (isSitting) break;
			maxVx = MARIO_RUNNING_SPEED + level_run * MARIO_LEVEL_RUN_SPEED;
			ax = MARIO_ACCEL_RUN_X;
			nx = 1;
			isRunning = true;
			break;
		case MARIO_STATE_RUNNING_LEFT:
			if (isSitting) break;
			maxVx = -MARIO_RUNNING_SPEED - level_run * MARIO_LEVEL_RUN_SPEED;
			ax = -MARIO_ACCEL_RUN_X;
			nx = -1;
			isRunning = true;
			break;
		case MARIO_STATE_WALKING_RIGHT:
			if (isSitting) break;
			maxVx = MARIO_WALKING_SPEED;
			ax = MARIO_ACCEL_WALK_X;
			nx = 1;
			isRunning = false;
			break;
		case MARIO_STATE_WALKING_LEFT:
			if (isSitting) break;
			maxVx = -MARIO_WALKING_SPEED;
			ax = -MARIO_ACCEL_WALK_X;
			nx = -1;
			isRunning = false;
			break;
		case MARIO_STATE_JUMP:
			if (isSitting) break;
			if (isOnPlatform)
			{
				if (abs(this->vx) == MARIO_RUNNING_SPEED)
					vy = -MARIO_JUMP_RUN_SPEED_Y;
				else
					vy = -MARIO_JUMP_SPEED_Y;
			}
			break;

		case MARIO_STATE_RELEASE_JUMP:
			if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
			break;

		case MARIO_STATE_SIT:
			if (isOnPlatform && level != MARIO_LEVEL_SMALL)
			{
				state = MARIO_STATE_IDLE;
				isSitting = true;
				isRunning = false;
				vx = 0; vy = 0.0f;
				y += MARIO_SIT_HEIGHT_ADJUST;
			}
			break;

		case MARIO_STATE_SIT_RELEASE:
			if (isSitting)
			{
				isSitting = false;
				state = MARIO_STATE_IDLE;
				y -= MARIO_SIT_HEIGHT_ADJUST;
			}
			break;

		case MARIO_STATE_IDLE:
			ax = 0.0f;
			vx = 0.0f;
			if (isSitting) {
				state = MARIO_STATE_SIT_RELEASE;
			}
			break;

		case MARIO_STATE_FLY:
			isFlying = true;
			isOnPlatform = false;
			if (level_run == LEVEL_RUN_MAX)
			{
				vy = -MARIO_FLY_Y;
				ay = MARIO_GRAVITY / 6;
			}
			else
			{
				vy = -MARIO_FALL_WITH_TAIL_Y;
				ay = MARIO_GRAVITY / 4;
			}
			break;
		case MARIO_TAIL_ATTACKING_STATE:
			isTailAttacking = true;
			start_tailattack = GetTickCount64();
			break;
		case MARIO_GOING_DOWN_PIPE_STATE:
			ay = MARIO_GRAVITY / 6;
			isUsingPipe = true;
			start_usingPipe = GetTickCount64();
			break;
		case MARIO_GOING_UP_PIPE_STATE:
			ay = MARIO_GRAVITY ;
			vy = -MARIO_JUMP_SPEED_Y;
			isUsingPipe = true;
			start_usingPipe = GetTickCount64();
			break;
		case MARIO_STATE_DIE:
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			vx = 0;
			ax = 0;
			start_die = GetTickCount64();
			break;
		}
	}
	else if (currentscene == SCENE_WORLD_MAP)
	{
		switch (state)
		{
		case MARIO_GO_LEFT:
		{
			vy = 0.0f;
			vx = -MARIO_WORLDMAP_SPEED;
			break;
		}
		case MARIO_GO_RIGHT:
		{
			vy = 0.0f;
			vx = MARIO_WORLDMAP_SPEED;
			break;
		}
		case MARIO_GO_UP:
		{
			vx = 0.0f;
			vy = -MARIO_WORLDMAP_SPEED;
			break;
		}case MARIO_GO_DOWN:
		{
			vx = 0.0f;
			vy = MARIO_WORLDMAP_SPEED;
			break;
		}
		default:
			break;
		}
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
	else
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_TANOOKI_BBOX_WIDTH / 2 ;
			top = y - MARIO_TANOOKI_BBOX_HEIGHT / 2;
			right = left + MARIO_TANOOKI_BBOX_WIDTH;
			bottom = top + MARIO_TANOOKI_BBOX_HEIGHT;
		}
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	isChanging = true;
	start_change = GetTickCount64();
	level = l;
}

