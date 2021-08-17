#pragma once
#include "GameNode.h"

//// 샘플 타일 정보
//// 640 * 288
//#define SAMPLE_TILE_X	32	//16  32
//#define SAMPLE_TILE_Y	28	//16  32
//#define TILESIZE		16	//32  16
//
//// 메인 그리기 공간 정보
//#define	TILE_X			32	//16  32
//#define	TILE_Y			28	//16  32

//enum TILETYPE {WALL, ROAD, DOOR};
//
//typedef struct tagTile
//{
//	RECT rcTile;
//	int frameX;
//	int frameY;
//	TILETYPE tileType;
//} TILE_INFO;

class Button;
class Image;
class TilemapTool : public GameNode
{
private:
	// 샘플 타일 이미지
	Image* sampleTile;
	TILE_INFO sampleTileInfo[SAMPLE_TILE_Y][SAMPLE_TILE_X];
	RECT rcSample;

	// 메인타일의 정보
	RECT rcMain;

	POINT ptStartSelectedFrame;
	POINT ptEndSelectedFrame;

	POINT ptSelected[2];
	HBRUSH hSelectedBrush;
	HBRUSH hOldSelectedBrush;

	// UI button
	Button* btnSave;
	Button* btnLoad;

	int tileTypeNum = 0;

public:
	static TILE_INFO tileInfo[TILE_Y][TILE_X];

	char szText[128] = "";

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static void Save(int stageNum);
	static void Load(int stageNum);

	static void ResetLoad(int stageNum);

	virtual ~TilemapTool() {};
};

