#include "FloodFillAlgorithm.h"

HRESULT FloodFillAlgorithm::Init()
{
	for (int i = 0; i < WELL_Y; i++)
	{
		for (int j = 0; j < WELL_X; j++)
		{
			wellInfo[i][j] = 0;
			check[i][j] = 0;
		}
	}

	dir = 0;
	IsCheck = false;
	checkCount = 0;
	
	minGap.x = 0;
	minGap.y = 0;
	maxGap.x = 0;
	maxGap.y = 0;
	gap.x = 0;
	gap.y = 0;

	return S_OK;
}

void FloodFillAlgorithm::Release()
{
}

void FloodFillAlgorithm::Update()
{
	dir = rand() % 4;
	randMinNumX = rand() % 16 + 1;   
	randMinNumY = rand() % 16 + 1;
	randMaxNumX = rand() % 16 + 5;
	randMaxNumY = rand() % 16 + 5;

	if (checkCount < 9)
	{
		if (dir == WELL_DOWN)
		{
			RoofWell(0, randMaxNumY, 0, WELL_X);
		}
		else if (dir == WELL_UP)
		{
			RoofWell(randMinNumY, WELL_Y, 0, WELL_X);
		}
		else if (dir == WELL_LEFT)
		{
			RoofWell(0, WELL_Y, 0, randMaxNumX);
		}
		else if (dir == WELL_RIGHT)
		{
			RoofWell(0, WELL_Y, randMinNumX, WELL_X);
		}
		checkCount++;
	}
	else
	{
		bfs(10 + 10 * WELL_Y, wellInfo, check);
		IsCheck = true;

		for (int i = 1; i < WELL_Y; i++)	//gap 계산
		{
			for (int j = 1; j < WELL_X; j++)
			{
				if (check[i][j] == 1 && check[i][j - 1] == 0)
				{
					minGap.x = j;
				}
				if (check[i][j] == 1 && check[i][j + 1] == 0)
				{
					maxGap.x = j;
				}
				if (check[i][j] == 1 && check[i - 1][j] == 0)
				{
					minGap.y = i;
				}
				if (check[i][j] == 1 && check[i + 1][j] == 0)
				{
					maxGap.y = i;
				}
			}
		}
		gap.x = maxGap.x - minGap.x;
		gap.y = maxGap.y - minGap.y;
	}
}

void FloodFillAlgorithm::Render(HDC hdc)
{
	if (IsCheck)
	{
		for (int i = 0; i < WELL_Y; i++)
		{
			for (int j = 0; j < WELL_X; j++)
			{
				wsprintf(szText, "%d", check[i][j]);
				TextOut(hdc, 30 * i, 30 * j, szText, strlen(szText));
			}
		}
	}
	else
	{
		for (int i = 0; i < WELL_Y; i++)
		{
			for (int j = 0; j < WELL_X; j++)
			{
				wsprintf(szText, "%d", wellInfo[i][j]);
				TextOut(hdc, 30 * i, 30 * j, szText, strlen(szText));
			}
		}
	}
}

void FloodFillAlgorithm::RoofWell(int startI, int endI, int startJ, int endJ)
{
	for (int i = startI; i < endI; i++)
	{
		for (int j = startJ; j < endJ; j++)
		{
			wellInfo[i][j]++;
		}
	}
}

void FloodFillAlgorithm::bfs(int start, int wellInfo[WELL_X][WELL_Y], bool check[WELL_X][WELL_Y])
{
	queue<int> q;
	q.push(start);

	while (!q.empty())
	{
		int tmp = q.front();
		q.pop();

		int idX = tmp % WELL_X;
		int idY = tmp / WELL_X;
		check[idX][idY] = true;

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				// 4방향 조건 
				if (abs(i + j) % 2 == 0) continue;

				// 인덱스 값 범위 컨티뉴
				if (idX + i < 0 && idX + i > WELL_X && idY + j < 0 && idY + j > WELL_Y) continue;

				if (wellInfo[idX + i][idY + j] == wellInfo[idX][idY] && check[idX + i][idY + j] == false)
				{
					// 방문체크
					check[idX + i][idY + j] = true;
					// 다음 체크할 값 확인
					int value = (idY + j) * WELL_X + (idX + i);
					// q에 푸시백
					q.push(value);
				}
			}
		}
	}
}
