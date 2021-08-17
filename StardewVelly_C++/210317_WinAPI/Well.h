#pragma once
#include "GameNode.h"

#define WELL_X 10
#define WELL_Y 10

#define WELL_SIZE 10

typedef struct tagWell
{
	RECT rcTile;
	int wellNumber;
} WELL_INFO;

class Well : public GameNode
{
private:
	int dr[4] = { 0, 0, 1, -1 };
	int dc[4] = { 1, -1, 0, 0 };

	int divisionX;
	int divisionY;

	COLORREF color;
	HBRUSH hBrush;
	HBRUSH hOldBrush;

public:
	static WELL_INFO wellInfo[WELL_X][WELL_Y];

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~Well() {};
};

