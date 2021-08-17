#pragma once
#include "Singleton.h"
#include "config.h"
#include <queue>
#include <vector>

class FloodFillAlgorithm  : public Singleton<FloodFillAlgorithm>
{
private:
	int wellInfo[WELL_X][WELL_Y];
	bool check[WELL_X][WELL_Y];

	int dir;

	int checkX[4] = { 0, 0, -1, 1 };
	int checkY[4] = { -1, 1, 0, 0 };

	int randMinNumX;
	int randMinNumY;
	int randMaxNumX;
	int randMaxNumY;

	bool IsCheck;
	int checkCount;

	POINT minGap;
	POINT maxGap;
	POINT gap;


	char szText[128] = "";
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	inline void SetGap(POINT gap) { this->gap = gap; }
	inline POINT GetGap() { return this->gap; }

	void bfs(int start, int wellInfo[WELL_X][WELL_Y], bool check[WELL_X][WELL_Y]);
	void RoofWell(int startI, int endI, int startJ, int endJ);

	virtual ~FloodFillAlgorithm() {};
};