#include "Node.h"

void CNode::Render()
{
	//RenderBoundingBox();
}

void CNode::GetBoundingBox(float& l, float& t, float& r, float& b)
{
		l = x - 16 / 2;
		t = y - 16 / 2;
		r = l + 16;
		b = t + 16;
}
