#pragma once
#include "GameObject.h"
class CInvisibleBlock : public CGameObject
{
public:
	CInvisibleBlock(float x, float y) : CGameObject(x, y) { }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
};

