#include "InvisibleBlock.h"
void CInvisibleBlock::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	int Id = 120000;
	sprites->Get(Id)->Draw(x, y);
	RenderBoundingBox();
}
void  CInvisibleBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 16 / 2;
	t = y - 16 / 2;
	r = l +	16;
	b = t + 16;
}