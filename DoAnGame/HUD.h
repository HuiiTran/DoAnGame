#pragma once

#define ID_ANI_HUD 200000
#define ID_ANI_BLACK_BG 200001
#define ID_ANI_M_SYMBOL 200002
#define ID_ANI_ARROW_LEVEL_RUN 200003
#define ID_ANI_LEVEL_RUN_MAX 200004


//number 
#define ID_ANI_NUMBER_0 200010
#define ID_ANI_NUMBER_1 200011
#define ID_ANI_NUMBER_2 200012
#define ID_ANI_NUMBER_3 200013
#define ID_ANI_NUMBER_4 200014
#define ID_ANI_NUMBER_5 200015
#define ID_ANI_NUMBER_6 200016
#define ID_ANI_NUMBER_7 200017
#define ID_ANI_NUMBER_8 200018
#define ID_ANI_NUMBER_9 200019



//card

#define ID_ANI_MUSHROOM_CARD	200020
#define ID_ANI_STAR_CARD		200021
#define ID_ANI_FLOWER_CARD		200022
//offset
#define HUD_OFFSET_Y 9

#define M_SYMBOL_OFFSET_X 104
#define M_SYMBOL_OFFSET_Y 14

#define LEVELRUN_BASE_OFFSET_X 60
#define LEVELRUN_SPACE_OFFSET_X	8
#define LEVELRUN_OFFSET_Y 5

#define	CARD_OFFSET_X_1	55
#define	CARD_OFFSET_X_2	80
#define	CARD_OFFSET_X_3	105
#define	CARD_OFFSET_Y	9

#define COIN_OFFSET_Y	6
#define COIN_TENS_OFFSET_X	20
#define COIN_UNIT_OFFSET_X	28

#define SCORE_OFFSET_Y	14
#define SCORE_OFFSET_X	12
#define SCORE_SPACE_OFFSET_X 8

#define LIFE_OFFSET_X	75
#define LIFE_OFFSET_Y	14
#define LIFE_SPACE_OFFSET_X 8

class CHUD
{
private:
	float x, y;
public:
	CHUD(float x, float y);

	void PrintNumber(int n, float x, float y);

	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

