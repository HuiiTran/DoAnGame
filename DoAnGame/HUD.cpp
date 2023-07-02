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

	CAnimations::GetInstance()->Get(ID_ANI_BLACK_BG)->Render(x, y + HUD_OFFSET_Y);

	CAnimations::GetInstance()->Get(ID_ANI_HUD)->Render(x, y + HUD_OFFSET_Y);

	
}
