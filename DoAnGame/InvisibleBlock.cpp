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
	l = x - 8 / 2;
	t = y - 8 / 2;
	r = l + 8;
	b = t + 8;
}