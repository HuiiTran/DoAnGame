#include "Data.h"
#include "Mario.h" 
CData::CData()
{
	ResetGame();
}

void CData::ResetGame()
{
	this->Life = 4;
	this->Score = 0;
	this->Coin = 0;
	this->Level = MARIO_LEVEL_SMALL;
}

