#pragma once
#include "GameObject.h"

#define PIPE_WIDTH 16
#define PIPE_HEIGHT 16

class CPipe : public CGameObject
{
protected:
	int length;				
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public:
	CPipe(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 1; }
};

typedef CPipe* LPPIPE;

