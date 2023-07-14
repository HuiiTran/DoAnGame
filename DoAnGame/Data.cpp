#include "Data.h"
#include "Mario.h" 
CData::CData()
{
	ResetGame();
}

void CData::ResetGame()
{
	Life = 4;
	Score = 0;
	Coin = 0;
	Level = MARIO_LEVEL_SMALL;
}

