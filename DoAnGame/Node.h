#pragma once
#include "GameObject.h"
class CNode : public CGameObject
{
protected: 
	int type;
	bool allowLeft;
	bool allowRight;
	bool allowUp;
	bool allowDown;
public:
	CNode(float x, float y, int type, bool allowLeft, bool allowRight, bool allowUp, bool allowDown) : CGameObject(x, y)
	{
		this->type = type; //1 normal, 2 stage
		this->allowLeft = allowLeft;
		this->allowRight = allowRight;
		this->allowUp = allowUp;
		this->allowDown = allowDown;
	}
	void Render();
	void Update(DWORD dt) {}
	virtual int IsBlocking() { return 0;}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	bool GetAllowLeft() { return allowLeft; }
	bool GetAllowRight() { return allowRight; }
	bool GetAllowUp() { return allowUp; }
	bool GetAllowDown() { return allowDown; }

	int GetType() { return type; }

};

