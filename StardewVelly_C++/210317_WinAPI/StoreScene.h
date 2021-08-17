#pragma once
#include "GameNode.h"

class PlayerShip;
class Image;
class TilemapTool;
class StoreScene : public GameNode
{
private:
	Image* storeImg;
	PlayerShip* player;

	FPOINT pos;
	FPOINT cameraPos;
	POINT camTilePos;
	RECT CameraShape;

	TilemapTool* tilemapTool;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	
	virtual ~StoreScene() {};
};

