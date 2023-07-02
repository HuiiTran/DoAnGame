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

void CHUD::Render()
{
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

	//NUMBER test
	CAnimations::GetInstance()->Get(ID_ANI_NUMBER_9)->Render(x - 75, y + 5);

}
