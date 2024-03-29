#include "HUD.h"
#include "Textures.h"
#include "Animations.h"
#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"
CHUD::CHUD(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CHUD::PrintNumber(int n, float x, float y)
{
	if(n == 0)
		CAnimations::GetInstance()->Get(ID_ANI_NUMBER_0)->Render(x, y);
	if (n == 1)
		CAnimations::GetInstance()->Get(ID_ANI_NUMBER_1)->Render(x, y);
	if (n == 2)
		CAnimations::GetInstance()->Get(ID_ANI_NUMBER_2)->Render(x, y);
	if (n == 3)
		CAnimations::GetInstance()->Get(ID_ANI_NUMBER_3)->Render(x, y);
	if (n == 4)
		CAnimations::GetInstance()->Get(ID_ANI_NUMBER_4)->Render(x, y);
	if (n == 5)
		CAnimations::GetInstance()->Get(ID_ANI_NUMBER_5)->Render(x, y);
	if (n == 6)
		CAnimations::GetInstance()->Get(ID_ANI_NUMBER_6)->Render(x, y);
	if (n == 7)
		CAnimations::GetInstance()->Get(ID_ANI_NUMBER_7)->Render(x, y);
	if (n == 8)
		CAnimations::GetInstance()->Get(ID_ANI_NUMBER_8)->Render(x, y);
	if (n == 9)
		CAnimations::GetInstance()->Get(ID_ANI_NUMBER_9)->Render(x, y);
}

void CHUD::PrintCard(int n, float x, float y)
{
	if(n == TYPE_CARD_MUSHROOM)
		CAnimations::GetInstance()->Get(ID_ANI_MUSHROOM_CARD)->Render(x, y);
	if(n == TYPE_CARD_STAR)
		CAnimations::GetInstance()->Get(ID_ANI_STAR_CARD)->Render(x, y );
	if(n == TYPE_CARD_FLOWER)
		CAnimations::GetInstance()->Get(ID_ANI_FLOWER_CARD)->Render(x , y );
}

void CHUD::Render()
{
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//back ground
	CAnimations::GetInstance()->Get(ID_ANI_BLACK_BG)->Render(x, y + HUD_OFFSET_Y);
	//HUD
	CAnimations::GetInstance()->Get(ID_ANI_HUD)->Render(x, y + HUD_OFFSET_Y);
	//M SYMBOL
	CAnimations::GetInstance()->Get(ID_ANI_M_SYMBOL)->Render(x - M_SYMBOL_OFFSET_X, y + M_SYMBOL_OFFSET_Y);



	//LEVEL RUN INCREASE 
	if(mario->GetLevelRun() > 1)
		CAnimations::GetInstance()->Get(ID_ANI_ARROW_LEVEL_RUN)->Render(x - LEVELRUN_BASE_OFFSET_X, y + LEVELRUN_OFFSET_Y);
	if (mario->GetLevelRun() > 2)
		CAnimations::GetInstance()->Get(ID_ANI_ARROW_LEVEL_RUN)->Render(x - LEVELRUN_BASE_OFFSET_X + 1 * LEVELRUN_SPACE_OFFSET_X, y + LEVELRUN_OFFSET_Y);
	if (mario->GetLevelRun() > 3)
		CAnimations::GetInstance()->Get(ID_ANI_ARROW_LEVEL_RUN)->Render(x - LEVELRUN_BASE_OFFSET_X + 2 * LEVELRUN_SPACE_OFFSET_X, y + LEVELRUN_OFFSET_Y);
	if (mario->GetLevelRun() > 4)
		CAnimations::GetInstance()->Get(ID_ANI_ARROW_LEVEL_RUN)->Render(x - LEVELRUN_BASE_OFFSET_X + 3 * LEVELRUN_SPACE_OFFSET_X, y + LEVELRUN_OFFSET_Y);
	if (mario->GetLevelRun() > 5)
		CAnimations::GetInstance()->Get(ID_ANI_ARROW_LEVEL_RUN)->Render(x - LEVELRUN_BASE_OFFSET_X + 4 * LEVELRUN_SPACE_OFFSET_X, y + LEVELRUN_OFFSET_Y);
	if (mario->GetLevelRun() > 6)
		CAnimations::GetInstance()->Get(ID_ANI_ARROW_LEVEL_RUN)->Render(x - LEVELRUN_BASE_OFFSET_X + 5 * LEVELRUN_SPACE_OFFSET_X, y + LEVELRUN_OFFSET_Y);
	if (mario->GetLevelRun() == LEVEL_RUN_MAX)
		CAnimations::GetInstance()->Get(ID_ANI_LEVEL_RUN_MAX)->Render(x - LEVELRUN_SPACE_OFFSET_X, y + LEVELRUN_OFFSET_Y);

	//NUMBER WORLD
	CAnimations::GetInstance()->Get(ID_ANI_NUMBER_1)->Render(x - 75, y + 6);

	//card 
	if (mario->GetCard_1() != 0)
	{
		PrintCard(mario->GetCard_1(), x + CARD_OFFSET_X_1, y + CARD_OFFSET_Y);
	}
	if (mario->GetCard_2() != 0)
	{
		PrintCard(mario->GetCard_2(), x + CARD_OFFSET_X_2, y + CARD_OFFSET_Y);
	}
	if (mario->GetCard_3() != 0)
	{
		PrintCard(mario->GetCard_3(), x + CARD_OFFSET_X_3, y + CARD_OFFSET_Y);
	}

	//Print coin
	int coin = mario->GetCoin();
	if (coin / 10 > 0)
	{
		PrintNumber(coin / 10, x + COIN_TENS_OFFSET_X, y + COIN_OFFSET_Y);
	}
	PrintNumber(coin % 10, x + COIN_UNIT_OFFSET_X, y + COIN_OFFSET_Y);

	//Print score
	int score = mario->GetMScore();
	PrintNumber(score		% 10, x - SCORE_OFFSET_X - SCORE_SPACE_OFFSET_X * 0, y + SCORE_OFFSET_Y); // unit
	PrintNumber(score / 10 % 10, x - SCORE_OFFSET_X - SCORE_SPACE_OFFSET_X * 1, y + SCORE_OFFSET_Y);
	PrintNumber(score / 100 % 10, x - SCORE_OFFSET_X - SCORE_SPACE_OFFSET_X * 2, y + SCORE_OFFSET_Y);
	PrintNumber(score / 1000 % 10, x - SCORE_OFFSET_X - SCORE_SPACE_OFFSET_X * 3, y + SCORE_OFFSET_Y);
	PrintNumber(score / 10000 % 10, x - SCORE_OFFSET_X - SCORE_SPACE_OFFSET_X * 4, y + SCORE_OFFSET_Y);
	PrintNumber(score / 100000 % 10, x - SCORE_OFFSET_X - SCORE_SPACE_OFFSET_X * 5, y + SCORE_OFFSET_Y);
	PrintNumber(score / 1000000 % 10, x - SCORE_OFFSET_X - SCORE_SPACE_OFFSET_X * 6, y + SCORE_OFFSET_Y);

	//Print life
	int life = mario->GetMLife();
	if (life / 10 > 0)
	{
		PrintNumber(life / 10, x - LIFE_OFFSET_X - LIFE_SPACE_OFFSET_X, y + LIFE_OFFSET_Y);
	}
	PrintNumber(life % 10, x - LIFE_OFFSET_X, y + LIFE_OFFSET_Y);

	//Print timer
	int Timer = mario->GetTimer();
	if (currentscene == SCENE_MAP_1_1)
	{
		PrintNumber(Timer % 10		, x + TIMER_OFFSET_X, y + TIMER_OFFSET_Y);
		PrintNumber(Timer / 10 % 10	, x + TIMER_OFFSET_X - TIMER_SPACE_OFFSET_X, y + TIMER_OFFSET_Y);
		PrintNumber(Timer / 100		, x + TIMER_OFFSET_X - 2 * TIMER_SPACE_OFFSET_X, y + TIMER_OFFSET_Y);
	}

	if (mario->GetMLife() == 0)
	{
		if(currentscene == SCENE_WORLD_MAP)
			CAnimations::GetInstance()->Get(ID_ANI_GAMEOVER)->Render(x, y - 110);
	}

	if (mario->GetState() == MARIO_END_MAP_STATE)
	{
		CAnimations::GetInstance()->Get(ID_ANI_END_GAME)->Render(x, y - 170);
		PrintCard(mario->GetDisplayCard(), x + 60, y - 150);
	}
}
