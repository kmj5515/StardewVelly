#pragma once
#include "GameNode.h"

class PlayerShip;
class Image;
class TilemapTool;
class FarmScene : public GameNode
{
public:
	enum SCENE_ID{ START, MYHOUSE, CAVE, FARM, STORE, BUS, INVEN, TILETOOL};
private:
	Image* gameFarmBg;
	Image* farmBg;
	Image* plowImg;
	Image* endingMsgImg;
	Image* notTicketMsgImg;
	Image* farmSheet;
	Image* pond;

	PlayerShip* player;

	FPOINT pos;
	FPOINT cameraPos;
	POINT camTilePos;
	RECT CameraShape;
	RECT tmp;

	TilemapTool* tilemapTool;

	int loadStageNum;

	float ZoomSize;
	int size;

	float FocusPx;
	float FocusPy;

	float camSpeed;
	bool IsCamera;

	char szText[128] = "";

	bool SetLeftDown;
	bool SetRightDown;
	bool SetTopDown;
	bool SetBottomDown;

	FPOINT plow;
	POINT plowTile;

	int plowFrame;

	bool haveTicket;
	bool IsEnding;
	bool IsNotEnding;

	int pondSizeX;
	int pondSizeY;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void CheckBlockCollision();

	void CameraMove(float moveSpeed);
	void AdjustTileUpScale(int size);
	void AdjustTileDownScale(int size);

	void UseEnergy();
	void DayPlowCollision();

	virtual ~FarmScene() {};
};
