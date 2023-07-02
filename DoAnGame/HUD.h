#pragma once

#define ID_ANI_HUD 200000
#define ID_ANI_BLACK_BG 200001
#define ID_ANI_M_SYMBOL 200002
#define ID_ANI_ARROW_LEVEL_RUN 200003
#define ID_ANI_TRIANGLE_LEVEL_RUN 200004

#define HUD_OFFSET_Y 9

#define M_SYMBOL_OFFSET_X 104
#define M_SYMBOL_OFFSET_Y 14

class CHUD
{
private:
	float x, y;
public:
	CHUD(float x, float y);

	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

