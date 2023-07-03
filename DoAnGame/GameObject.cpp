#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	state = -1;
	isDeleted = false;
}

bool CGameObject::isInCam(CGameObject* obj)
{
	float screen_width = 32.0f;
	float screen_height = 32.0f;
	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);

	if (obj->x + screen_width  <= camX ||  camX + SCREEN_WIDTH <= obj->x)
		return false;

	if (obj->y + screen_height <= camY || camY + SCREEN_HEIGHT + screen_height <= obj->y)
		return false;

	return true;
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy; 
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, &rect, BBOX_ALPHA);
}

CGameObject::~CGameObject()
{

}