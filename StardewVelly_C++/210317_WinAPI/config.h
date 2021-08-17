// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <map>
#include <vector>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"
#include "GameData.h"

#define WINSIZE_X	1080
#define WINSIZE_Y	820
#define TILEMAPTOOLSIZE_X	896 * 2
#define TILEMAPTOOLSIZE_Y	896 * 2
#define ASTARSIZE_X	1620
#define ASTARSIZE_Y	900

#define PI			3.141592f
#define DegToRad(x)	((x) * PI / 180.0f)
#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); delete p; p = nullptr; } }

// 샘플 타일 정보
// 640 * 288
#define SAMPLE_TILE_X	32	//16  32
#define SAMPLE_TILE_Y	32	//16  32
#define TILESIZE		28	//32  16

// 메인 그리기 공간 정보
#define	TILE_X			32	//16  32
#define	TILE_Y			32	//16  32

// 타일씬-> 맵 범위 설정
#define PLAY_SCENE_X 50
#define PLAY_SCENE_Y 50

#define INVEN_X 12
#define INVEN_Y	3
#define INVEN_SIZE 64

enum MOTION { DOWN, RIGHT, UP, LEFT, STAY };
enum TILETYPE { WALL, ROAD, GOTOFARM, GOTOHOME, GOTOSTORE, GOTOBUS, INVENTORYSTORE, BED, };
enum PLOWTYPE { DRYPLOW = 10, WETPLOW, WATER };
enum SEEDTYPE { PEACHSEED_0 = 20, PEACHSEED_1, PEACHSEED_2, PEACHSEED_3, PEACHSEED_4, PEACHSEED_5,
				EGGPLANTSEED_0 = 30, EGGPLANTSEED_1, EGGPLANTSEED_2, EGGPLANTSEED_3, EGGPLANTSEED_4, EGGPLANTSEED_5,
				PEPPERSEED_0 = 40, PEPPERSEED_1, PEPPERSEED_2, PEPPERSEED_3, PEPPERSEED_4, PEPPERSEED_5, NOTSEED = 50 };
enum INVENTYPE { BLANK, AXE, HOE, WATERING, EGGPLANT, PEPPER, PEACH, TICKET };

typedef struct tagTile
{
	RECT rcTile;
	int frameX;
	int frameY;
	int glowTime;
	TILETYPE tileType;
	PLOWTYPE plowType;
	SEEDTYPE seedType;
} TILE_INFO;

typedef struct tagInven
{
	RECT rcInven;
	int price;
	int glowDay;
	INVENTYPE invenType;
} INVEN_INFO;

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;


#define WELL_TILE_SIZE 30

#define WELL_X	20
#define WELL_Y	20

enum wellDirection { WELL_DOWN, WELL_UP, WELL_LEFT, WELL_RIGHT };