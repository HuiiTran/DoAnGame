#include "Koopa.h"
#include "Goomba.h"
#include "InvisibleBlock.h"
#include "QuestionBrick.h"
#include "Coin.h"
#include "Mario.h"
#include "MushRoom.h"
#include "Leaf.h"
#include "Effect.h"

CKoopa::CKoopa(float x, float y, bool isHaveWing) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	nx = -1;
	die_start = -1;
	respawn_start = -1;
	isHolded = false;
	mario_level = 1;
	SetState(KOOPA_STATE_WALKING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_WALKING)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_SHELL_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_SHELL_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_SCROLL || state == KOOPA_STATE_SHELL_HOLD) {
		if (dynamic_cast<CGoomba*>(e->obj)) {
			OnCollisionWithGoomba(e);
		}
		else if (dynamic_cast<CQuestionBrick*>(e->obj)) {
			OnCollisionWithQuestionBrick(e);
		}
		else if (dynamic_cast<CVenusFireTrap*>(e->obj)) {
			OnCollisionWithVenusFireTrap(e);
		}
	}
	if (dynamic_cast<CInvisibleBlock*>(e->obj) && state == KOOPA_STATE_WALKING) {
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

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (state == KOOPA_STATE_SHELL_SCROLL || state == KOOPA_STATE_SHELL_HOLD)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE_JUMP);
		}
	}
}

void CKoopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionbrick = dynamic_cast<CQuestionBrick*>(e->obj);
	
	if ( (e->nx > 0 || e->nx < 0) && questionbrick->IsEmpty() == false) 
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
	}
}

void CKoopa::OnCollisionWithInvisibleBlock(LPCOLLISIONEVENT e)
{
	CInvisibleBlock* invisible = dynamic_cast<CInvisibleBlock*>(e->obj);
	if (this->state != KOOPA_STATE_SHELL || this->state != KOOPA_STATE_SHELL_SCROLL || this->state != KOOPA_STATE_SHELL_HOLD)
	{
		this->SetState(KOOPA_STATE_CHANGE_DIRECT);
	}

}
void CKoopa::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
	float Tx, Ty;
	e->obj->GetPosition(Tx, Ty);
	e->obj->Delete();
	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	CEffect* effect = new CEffect(Tx, Ty);
	thisscene->AddObjectToScene(effect);
}
void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (isHolded) {
		vy = 0;
		vx = 0;
	}

	if (state == KOOPA_STATE_JUMP_DIE) {
		if (GetTickCount64() - die_start > KOOPA_JUMP_DIE_TIMEOUT) {
			isDeleted = true;
			return;
		}
	}

	if ((state == KOOPA_STATE_DIE))
	{
		isDeleted = true;
		return;
	}

	if ((state == KOOPA_STATE_SHELL) && (GetTickCount64() - respawn_start > KOOPA_RESPAWN_START_TIME))
	{
		SetState(KOOPA_STATE_RESPAWN);
		return;
	}

	if ((state == KOOPA_STATE_RESPAWN) && (GetTickCount64() - respawn_end > KOOPA_RESPAWN_TIME))
	{
		isHolded = false;
		SetState(KOOPA_STATE_WALKING);
		return;
	}

	if (state == KOOPA_STATE_WALKING) 
	{
		isHolded = false;
	}

	if (state == KOOPA_STATE_CHANGE_DIRECT)
	{
		SetState(KOOPA_STATE_WALKING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{
	int aniId = -1;

	switch (state)
	{
	case KOOPA_STATE_RESPAWN:
	{
		aniId = ID_ANI_KOOPA_RESPAWN;
		break;
	}
	case KOOPA_STATE_SHELL:
	case KOOPA_STATE_SHELL_HOLD:
	{
		aniId = ID_ANI_KOOPA_SHELL;
		break;
	}
	case KOOPA_STATE_SHELL_SCROLL:
	{
		aniId = ID_ANI_KOOPA_SHELL_ROLL;
		break;
	}
	default:
		if (vx > 0)
			aniId = ID_ANI_KOOPA_WALKING_RIGHT;
		else
			aniId = ID_ANI_KOOPA_WALKING_LEFT;
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_SHELL_HEIGHT) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_SHELL:
		vx = 0;
		vy = 0;
		respawn_start = GetTickCount64();
		break;
	case KOOPA_STATE_RESPAWN:
		respawn_end = GetTickCount64();
		isRespawning = true;
		break;
	case KOOPA_STATE_WALKING:
		if (isRespawning) {
			y += (KOOPA_BBOX_SHELL_HEIGHT - KOOPA_BBOX_HEIGHT) / 2;
			isRespawning = false;
		}
		vx = nx * KOOPA_WALKING_SPEED;
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_CHANGE_DIRECT:
		vx = -vx;
		nx = -nx;
		break;
	default:
		break;
	}
}