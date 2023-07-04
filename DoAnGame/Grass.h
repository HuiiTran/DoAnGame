#pragma once
#include "GameObject.h"

#define ID_ANI_GRASS 221000
class CGrass : public CGameObject
{
public: 
	CGrass(float x, float y) : CGameObject(x,y){}
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

