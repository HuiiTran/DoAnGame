#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "MushRoom.h"
#include "ColorBlock.h"
#include "BackGround.h"
#include "Koopa.h"
#include "InvisibleBlock.h"
#include "VenusFireTrap.h"
#include "Pipe.h"
#include "BlockingObject.h"
#include "FlyGoomba.h"
#include "HUD.h"
#include "PiranhaPlant.h"
#include "GreenKoopa.h"
#include "Grass.h"
#include "Node.h"
#include "PipeTeleport.h"
#include "SampleKeyEventHandler.h"
#include "CardRandomBlock.h"
#include "HammerEnemy.h"
#include "Mario.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

#define MAX_Y_CAM -300
#define MIN_Y_CAM	10
#define MID_Y_CAM	-45

#define UNDERGROUND_Y_CAM_MIN 61
#define UNDERGROUND_Y_CAM_MAX 205
#define UNDERGROUND_X_CAM_MIN 1900
#define UNDERGROUND_X_CAM_MAX 2200

#define UNDERGROUND_X_CAM_MIN_LIMIT 1960
#define UNDERGROUND_X_CAM_MAX_LIMIT 2160

#define GOAL_X_CAM	2524

#define CAM_WORLDMAP_X	0
#define CAM_WORLDMAP_Y	-50




void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_INVISIBLEBLOCK: obj = new CInvisibleBlock(x, y); break;
	case OBJECT_TYPE_BLOCKINGOBJECT: obj = new CBlockingObject(x, y); break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x,y); break;
	case OBJECT_TYPE_KOOPA:	obj = new CKoopa(x, y); break;
	case OBJECT_TYPE_HAMMER_ENEMIES:	obj = new CHammerEnemy(x, y); break;
	case OBJECT_TYPE_CARD_BLOCK:	obj = new CCardRandomBlock(x, y); break;
	case OBJECT_TYPE_GREEN_KOOPA: 
	{
		bool isHaveWing = (bool)atoi(tokens[3].c_str());
		obj = new CGreenKoopa(x, y, isHaveWing); 
		break;
	}
	case OBJECT_TYPE_FLYGOOMBA: obj = new CFlyGoomba(x, y); break;
	case OBJECT_TYPE_VENUSFIRETRAP: obj = new CVenusFireTrap(x, y); break;
	case OBJECT_TYPE_PIRANHAPLANT: obj = new CPiranhaPlant(x, y); break;
	case OBJECT_TYPE_GRASS: obj = new CGrass(x, y); break;
	case OBJECT_TYPE_PIPE_TELE:
	{
		int direct = (int)atoi(tokens[3].c_str());
		float desX = (float)atoi(tokens[4].c_str());
		float desY = (float)atoi(tokens[5].c_str());
		obj = new CPipeTeleport(x, y, direct, desX, desY);
		break;
	}
	case OBJECT_TYPE_BRICK: 
	{
		int brick_type = (int)atoi(tokens[3].c_str());
		obj = new CBrick(x, y, brick_type); 
		break;
	}
	case OBJECT_TYPE_COIN: 
	{
		int coin_type = (int)atoi(tokens[3].c_str());
		obj = new CCoin(x, y,coin_type); 
		break;
	}
	case OBJECT_TYPE_QUESTIONBRICK: 
	{
		int block_type = (int)atoi(tokens[3].c_str());
		obj = new CQuestionBrick(x, y, block_type); 
		break;
	}
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_PIPE:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPipe(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_COLORBLOCK:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CColorBlock(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_BACKGROUND:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CBackGround(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	case OBJECT_TYPE_NODE:
	{
		int type = atoi(tokens[3].c_str());
		bool allowLeft = atoi(tokens[4].c_str());
		bool allowRight = atoi(tokens[5].c_str());
		bool allowUp = atoi(tokens[6].c_str());
		bool allowDown = atoi(tokens[7].c_str());
		obj = new CNode(x, y, type, allowLeft, allowRight, allowUp, allowDown);
		break;
	}


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;
	//DebugOutTitle(L"%f", cx);
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (currentscene == SCENE_MAP_1_1)
	{
		if (cx < 0) cx = 0;
		if (cx > -160 && cy < UNDERGROUND_Y_CAM_MIN)
		{
			if (cy > MIN_Y_CAM)
				cy = MIN_Y_CAM;
			else if (MID_Y_CAM < cy && cy < MIN_Y_CAM)
				cy = MIN_Y_CAM;
			else
				cy = cy - MID_Y_CAM + MIN_Y_CAM;

			if (cy < MAX_Y_CAM)
				cy = MAX_Y_CAM;
			if (cx > GOAL_X_CAM) cx = GOAL_X_CAM;
		}
		else if (cy > UNDERGROUND_Y_CAM_MIN && (cx > UNDERGROUND_X_CAM_MIN && cx < UNDERGROUND_X_CAM_MAX))
		{
			if (mario->GetState() == MARIO_STATE_DIE)
			{
				cy = MID_Y_CAM;
				return;
			}
			else
			{
				cy = UNDERGROUND_Y_CAM_MAX;
				if (cx > UNDERGROUND_X_CAM_MAX_LIMIT)
					cx = UNDERGROUND_X_CAM_MAX_LIMIT;
				else if (cx < UNDERGROUND_X_CAM_MIN_LIMIT)
					cx = UNDERGROUND_X_CAM_MIN_LIMIT;
			}
		}
		else if (cy > UNDERGROUND_Y_CAM_MIN)
		{
			if (mario->GetState() == MARIO_STATE_DIE)
			{
				cy = MID_Y_CAM;
				return;
			}
			else
				cy = 10;
		}
	}
	else if (currentscene == SCENE_WORLD_MAP || currentscene == SCENE_INTRO)
	{
		cy = CAM_WORLDMAP_Y;
		cx = CAM_WORLDMAP_X;
	}

	CGame::GetInstance()->SetCamPos(cx, cy);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	float camX, camY;
	CGame* game = CGame::GetInstance();
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();

	game->GetCamPos(camX, camY);
	if(currentscene != SCENE_INTRO)
	{
		CHUD* hud = new CHUD(camX + 150, camY + 210);
		hud->Render();
	}
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}