#include "GreenKoopa.h"
#include "Goomba.h"
#include "InvisibleBlock.h"
#include "QuestionBrick.h"
#include "Coin.h"
#include "Mario.h"
#include "MushRoom.h"
#include "Leaf.h"
#include "FlyGoomba.h"
#include "Effect.h"
#include "Brick.h"
#include "BreakBrickPiece.h"
#include "PiranhaPlant.h"
#include "P_Power.h"
#include "Koopa.h"
#include "PlayScene.h"
CGreenKoopa::CGreenKoopa(float x, float y, bool isHaveWing ) : CGameObject(x,y)
{
	this->ax = 0;
	this->ay = GREEN_KOOPA_GRAVITY;
	this->isHaveWing = isHaveWing;
	nx = -1;
	die_start = -1;
	respawn_start = -1;
	flip_start = -1;
	isHolded = false;
	mario_level = 1;
	isFlip = false;
	beginX = x;
	beginY = y;
	beginIsHaveWing = isHaveWing;
	if(!isHaveWing)
		SetState(GREEN_KOOPA_STATE_WALKING);
	else
		SetState(GREEN_KOOPA_STATE_FLY_UP);
}
void CGreenKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GREEN_KOOPA_STATE_WALKING || isHaveWing)
	{
		left = x - GREEN_KOOPA_BBOX_WIDTH / 2;
		top = y - GREEN_KOOPA_BBOX_HEIGHT / 2;
		right = left + GREEN_KOOPA_BBOX_WIDTH;
		bottom = top + GREEN_KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - GREEN_KOOPA_BBOX_WIDTH / 2;
		top = y - GREEN_KOOPA_BBOX_SHELL_HEIGHT / 2;
		right = left + GREEN_KOOPA_BBOX_WIDTH;
		bottom = top + GREEN_KOOPA_BBOX_SHELL_HEIGHT;
	}
}

void CGreenKoopa::Render()
{
	int aniId = -1;
	switch (state)
	{
	case GREEN_KOOPA_STATE_RESPAWN:
	{
		if (isFlip == false)
			aniId = ID_ANI_GREEN_KOOPA_RESPAWN;
		else
			aniId = ID_ANI_GREEN_KOOPA_RESPAWN_FLIP;
		break;
	}
	case GREEN_KOOPA_STATE_SHELL_FLIP:
	case GREEN_KOOPA_STATE_SHELL:
	case GREEN_KOOPA_STATE_SHELL_HOLD:
		{
		if (isFlip == false)
			aniId = ID_ANI_GREEN_KOOPA_SHELL;
		else
			aniId = ID_ANI_GREEN_KOOPA_SHELL_FLIP;
		break;
	}
	case GREEN_KOOPA_STATE_SHELL_SCROLL:
	{
		if (isFlip == false)
			aniId = ID_ANI_GREEN_KOOPA_SHELL_ROLL;
		else
			aniId = ID_ANI_GREEN_KOOPA_SHELL_ROLL_FLIP;
		break;
	}
	case GREEN_KOOPA_STATE_JUMP_DIE:
		aniId = ID_ANI_GREEN_KOOPA_SHELL_FLIP;
		break;
	case GREEN_KOOPA_STATE_FLY_DOWN:
	case GREEN_KOOPA_STATE_FLY_UP:
	{
		if (nx > 0)
			aniId = ID_ANI_GREEN_KOOPA_FLY_RIGHT;
		else
			aniId = ID_ANI_GREEN_KOOPA_FLY_LEFT;
		break;
	}
	default:
		if (vx > 0)
			aniId = ID_ANI_GREEN_KOOPA_WALKING_RIGHT;
		else
			aniId = ID_ANI_GREEN_KOOPA_WALKING_LEFT;
		break;
	}
	
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CGreenKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CGreenKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	if (state == GREEN_KOOPA_STATE_SHELL_SCROLL || state == GREEN_KOOPA_STATE_SHELL_HOLD) {
		if (dynamic_cast<CGoomba*>(e->obj)) {
			OnCollisionWithGoomba(e);
		}
		else if (dynamic_cast<CQuestionBrick*>(e->obj)) {
			OnCollisionWithQuestionBrick(e);
		}
		else if (dynamic_cast<CVenusFireTrap*>(e->obj)) {
			OnCollisionWithVenusFireTrap(e);
		}
		else if (dynamic_cast<CFlyGoomba*>(e->obj)) {
			OnCollisionWithFlyGoomba(e);
		}
		else if (dynamic_cast<CBrick*>(e->obj)) {
			OnCollisionWithBrick(e);
		}
		else if (dynamic_cast<CPiranhaPlant*>(e->obj)) {
			OnCollisionWithPiranhaPlant(e);
		}
		else if (dynamic_cast<CKoopa*>(e->obj)) {
			OnCollisionWithKoopa(e);
		}
		else if (dynamic_cast<CGreenKoopa*>(e->obj)) {
			OnCollisionWithGreenKoopa(e);
		}
	}
	if (dynamic_cast<CInvisibleBlock*>(e->obj)) {
		OnCollisionWithInvisibleBlock(e);
	}
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		nx = -nx;
	}
}

void CGreenKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() == GOOMBA_STATE_DIE_JUMP)
	{
		return;
	}
	if (state == GREEN_KOOPA_STATE_SHELL_SCROLL || state == GREEN_KOOPA_STATE_SHELL_HOLD)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_JUMP)
		{
			goomba->SetState(GOOMBA_STATE_DIE_JUMP);
		}
	}
}

void CGreenKoopa::OnCollisionWithFlyGoomba(LPCOLLISIONEVENT e)
{
	CFlyGoomba* Flygoomba = dynamic_cast<CFlyGoomba*>(e->obj);
	if (Flygoomba->GetState() == FLYGOOMBA_STATE_DIE_JUMP)
	{
		return;
	}
	if (state == GREEN_KOOPA_STATE_SHELL_SCROLL || state == GREEN_KOOPA_STATE_SHELL_HOLD)
	{
		if (Flygoomba->GetState() != FLYGOOMBA_STATE_DIE && Flygoomba->GetState() != FLYGOOMBA_STATE_DIE_JUMP)
		{
			Flygoomba->SetState(FLYGOOMBA_STATE_DIE_JUMP);
		}
	}
}

void CGreenKoopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionbrick = dynamic_cast<CQuestionBrick*>(e->obj);

	if ((e->nx > 0 || e->nx < 0) && questionbrick->IsEmpty() == false)
	{
		if (questionbrick->GetBrickType() == 0)
		{
			questionbrick->SetEmpty(true);
			float questionbrick_x, questionbrick_y;
			questionbrick->GetPosition(questionbrick_x, questionbrick_y);

			CCoin* newCoin = new CCoin(questionbrick_x, questionbrick_y - 2 * COIN_WIDTH, 1);
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

			thisscene->AddObjectToScene(newCoin);
			newCoin->SetFly(true);
		}
		if ((questionbrick->GetBrickType() == 1 && this->mario_level == MARIO_LEVEL_SMALL) || (questionbrick->GetBrickType() == 2 && this->mario_level == MARIO_LEVEL_SMALL)) //mushroom
		{
			questionbrick->SetEmpty(true);
			float questionbrick_x, questionbrick_y;
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

			questionbrick->GetPosition(questionbrick_x, questionbrick_y);
			questionbrick->Delete();

			CMushRoom* newMush = new CMushRoom(questionbrick_x, questionbrick_y - 5, 0);
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
		if ((questionbrick->GetBrickType() == 2 && (this->mario_level == MARIO_LEVEL_BIG || this->mario_level == MARIO_LEVEL_TANOOKI)) || (questionbrick->GetBrickType() == 1 && (this->mario_level == MARIO_LEVEL_BIG || this->mario_level == MARIO_LEVEL_TANOOKI))) //leaf
		{
			questionbrick->SetEmpty(true);
			float questionbrick_x, questionbrick_y;
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

			questionbrick->GetPosition(questionbrick_x, questionbrick_y);
			questionbrick->SetPosition(questionbrick_x, questionbrick_y - QUESTIONBRICK_UP);

			CLeaf* newLeaf = new CLeaf(questionbrick_x, questionbrick_y - QUESTIONBRICK_UP);
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
		if (questionbrick->GetBrickType() == 4) //life up
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

void CGreenKoopa::OnCollisionWithInvisibleBlock(LPCOLLISIONEVENT e)
{
	this->SetPosition(beginX, beginY);
	if (beginIsHaveWing == true)
		SetState(GREEN_KOOPA_STATE_FLY_DOWN);
	else
		SetState(GREEN_KOOPA_STATE_WALKING);
}

void CGreenKoopa::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
	float Tx, Ty;
	e->obj->GetPosition(Tx, Ty);
	e->obj->Delete();
	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CEffect* effect = new CEffect(Tx, Ty);
	CEffect* score = new CEffect(Tx, Ty,VENUSFIRETRAP_SCORE);
	mario->SetMScore(VENUSFIRETRAP_SCORE);
	thisscene->AddObjectToScene(effect);
	thisscene->AddObjectToScene(score);
}

void CGreenKoopa::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	float Tx, Ty;
	e->obj->GetPosition(Tx, Ty);
	e->obj->Delete();
	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CEffect* effect = new CEffect(Tx, Ty);
	CEffect* score = new CEffect(Tx, Ty, PIRANHA_PLANT_SCORE);
	mario->SetMScore(PIRANHA_PLANT_SCORE);
	thisscene->AddObjectToScene(effect);
	thisscene->AddObjectToScene(score);

}

void CGreenKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	float bX, bY;

	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	brick->GetPosition(bX, bY);
	if ((e->nx > 0 || e->nx < 0) && brick->GetType() == 2)
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

void CGreenKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (koopa->GetState() == KOOPA_STATE_JUMP_DIE)
		return;
	koopa->SetState(KOOPA_STATE_JUMP_DIE);
}

void CGreenKoopa::OnCollisionWithGreenKoopa(LPCOLLISIONEVENT e)
{
	CGreenKoopa* greenkoopa = dynamic_cast<CGreenKoopa*>(e->obj);
	if (greenkoopa->GetState() == GREEN_KOOPA_STATE_JUMP_DIE)
		return;
	if (state == KOOPA_STATE_SHELL_SCROLL || state == KOOPA_STATE_SHELL_HOLD)
	{
		if (greenkoopa->GetState() != GREEN_KOOPA_STATE_DIE)
		{
			greenkoopa->SetState(GREEN_KOOPA_STATE_JUMP_DIE);
		}
	}
}

void CGreenKoopa::SetState(int state)
{
	CGameObject::SetState(state);

	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	LPGAMEOBJECT player = thisscene->GetPlayer();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	float px, py;
	player->GetPosition(px, py);
	switch (state)
	{
	case GREEN_KOOPA_STATE_DIE:
	{
		die_start = GetTickCount64();
		y += (GREEN_KOOPA_BBOX_HEIGHT - GREEN_KOOPA_BBOX_SHELL_HEIGHT) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		CEffect* effect = new CEffect(x + 10, y, GREEN_KOOPA_SCORE);
		thisscene->AddObjectToScene(effect);
		mario->SetMScore(GREEN_KOOPA_SCORE);
		break;
	}
	case GREEN_KOOPA_STATE_JUMP_DIE:
	{
		if (px > x)
		{
			vx = -GREEN_KOOPA_WALKING_SPEED;
			vy = -GREEN_KOOPA_JUMP_DIE_SPEED;
			ay = GREEN_KOOPA_GRAVITY;
		}
		else if (px < x)
		{
			vx = GREEN_KOOPA_WALKING_SPEED;
			vy = -GREEN_KOOPA_JUMP_DIE_SPEED;
			ay = GREEN_KOOPA_GRAVITY;
		}
		die_start = GetTickCount64();
		CEffect* effect = new CEffect(x + 10, y, GREEN_KOOPA_SCORE);
		thisscene->AddObjectToScene(effect);
		mario->SetMScore(GREEN_KOOPA_SCORE);
		break;
	}
	case GREEN_KOOPA_STATE_SHELL:
		vx = 0;
		vy = 0;
		ay = GREEN_KOOPA_GRAVITY;
		respawn_start = GetTickCount64();
		break;
	case GREEN_KOOPA_STATE_SHELL_FLIP:
	{
		if (px > x)
		{
			vx = -GREEN_KOOPA_WALKING_SPEED;
			vy = -GREEN_KOOPA_JUMP_DIE_SPEED;
		}
		else if (px < x)
		{
			vx = GREEN_KOOPA_WALKING_SPEED;
			vy = -GREEN_KOOPA_JUMP_DIE_SPEED;
		}
		flip_start = GetTickCount64();
		break;
		break;
	}
	case GREEN_KOOPA_STATE_RESPAWN:
		respawn_end = GetTickCount64();
		isRespawning = true;
		break;
	case GREEN_KOOPA_STATE_WALKING:
		if (isRespawning) {
			y += (GREEN_KOOPA_BBOX_SHELL_HEIGHT - GREEN_KOOPA_BBOX_HEIGHT) / 2;
			isRespawning = false;
		}
		vx = nx * GREEN_KOOPA_WALKING_SPEED;
		ay = GREEN_KOOPA_GRAVITY;
		break;
	case GREEN_KOOPA_STATE_CHANGE_DIRECT:
		vx = -vx;
		nx = -nx;
		break;
	case GREEN_KOOPA_STATE_FLY_UP:
	{
		ay = -GREEN_KOOPA_FLY_UP;
		vx = nx * GREEN_KOOPA_WALKING_SPEED / 2;
		fly_start = GetTickCount64();
		break;
	}
	case GREEN_KOOPA_STATE_FLY_DOWN:
		ay = GREEN_KOOPA_GRAVITY * 1.5;
		vx = nx * GREEN_KOOPA_WALKING_SPEED / 2;
		fly_start = GetTickCount64();
		break;
	default:
		break;
	}
}

void CGreenKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isInCam(this)) return;

	vy += ay * dt;
	vx += ax * dt;

	if (isHaveWing)
	{
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
		LPGAMEOBJECT player = thisscene->GetPlayer();

		float px, py;
		player->GetPosition(px, py);

		if (x > px)
			nx = -1;
		else
			nx = 1;
	}

	if (isHolded) {
		vy = 0;
		vx = 0;
	}
	if (state == GREEN_KOOPA_STATE_JUMP_DIE) {
		if (GetTickCount64() - die_start > GREEN_KOOPA_JUMP_DIE_TIMEOUT) {
			isDeleted = true;
			return;
		}
	}
	if ((state == GREEN_KOOPA_STATE_DIE))
	{
		isDeleted = true;
		return;
	}
	if ((state == GREEN_KOOPA_STATE_SHELL_FLIP) && GetTickCount64() - flip_start > 500)
		{
			SetState(GREEN_KOOPA_STATE_SHELL);
			return;
	}
	if ((state == GREEN_KOOPA_STATE_SHELL) && (GetTickCount64() - respawn_start > GREEN_KOOPA_RESPAWN_START_TIME))
	{
		SetState(GREEN_KOOPA_STATE_RESPAWN);
		return;
	}
	if ((state == GREEN_KOOPA_STATE_RESPAWN) && (GetTickCount64() - respawn_end > GREEN_KOOPA_RESPAWN_TIME))
	{
		isHolded = false;
		isFlip = false;
		SetState(GREEN_KOOPA_STATE_WALKING);
		return;
	}
	if (state == GREEN_KOOPA_STATE_WALKING)
	{

	}

	if (state == GREEN_KOOPA_STATE_FLY_UP && GetTickCount64() - fly_start > GREEN_KOOPA_FLY_TIME)
	{
		//fly_start = 0;
		SetState(GREEN_KOOPA_STATE_FLY_DOWN);
		
	}
	if (state == GREEN_KOOPA_STATE_FLY_DOWN && GetTickCount64() - fly_start > GREEN_KOOPA_FLY_TIME)
	{
		//fly_start = 0;
		SetState(GREEN_KOOPA_STATE_FLY_UP);
		
	}
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
