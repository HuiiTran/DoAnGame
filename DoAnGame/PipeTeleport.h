#pragma once
#include "GameObject.h"
class CPipeTeleport : public CGameObject
{
protected:
	float desX, desY;
	int direct; //1 down, 2 up
public:
	CPipeTeleport(float x, float y,int direct, float desX, float desY) : CGameObject(x, y)
	{
		this->direct = direct;
		this->desX = desX;
		this->desY = desY;
	}
	int IsBlocking() { return 0; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int GetDirect() { return this->direct; }
	float GetdesX() { return this->desX; }
	float GetdesY() { return this->desY; }
};

