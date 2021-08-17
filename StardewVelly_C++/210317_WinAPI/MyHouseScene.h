#pragma once
#include "GameNode.h"

class PlayerShip;
class Image;
class TilemapTool;
class SmallInven;
class MyHouseScene : public GameNode
{
private:
	Image* myHomeBgImg;
	Image* myHomeBg;
	Image* talkIconImg;
	Image* sleepMsgImg;

	PlayerShip* player;

	POINT pos;
	TilemapTool* tilemapTool;

	RECT rcTalkIcon;

	char szText[128] = "";

	int dayCount;
	bool IsSleep;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~MyHouseScene() {};
};
