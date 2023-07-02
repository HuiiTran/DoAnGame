#pragma once

#define ID_ANI_HUD 200000
#define ID_ANI_BLACK_BG 200001

#define HUD_OFFSET_Y 9
class CHUD
{
private:
	float x, y;
public:
	CHUD(float x, float y);

	virtual void Render();

};

