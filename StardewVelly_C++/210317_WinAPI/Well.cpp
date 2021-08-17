#include "Well.h"
#include "CommonFunction.h"

WELL_INFO Well::wellInfo[WELL_X][WELL_Y];

HRESULT Well::Init()
{
	for (int i = 0; i < WELL_X; i++)
	{
		for (int j = 0; j < WELL_Y; j++)
		{
			wellInfo[i][j].rcTile.left = 0;
			wellInfo[i][j].rcTile.top = 0;
			wellInfo[i][j].rcTile.right = 
				(wellInfo[i][j].rcTile.left + WELL_SIZE);
			wellInfo[i][j].rcTile.bottom = 
				(wellInfo[i][j].rcTile.top + WELL_SIZE);
			wellInfo[i][j].wellNumber = 0;
		}
	}

	color = RGB(100,100, 255);
	hBrush = CreateSolidBrush(color);

	return S_OK;
}

void Well::Release()
{
}

void Well::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		for (int i = 0; i < WELL_X; i++)
		{
			for (int j = 0; j < WELL_Y; j++)
			{
				if (divisionX < i)
				{
					wellInfo[i][j].wellNumber++;
				}
				if (divisionY < j)
				{

				}
			}
		}
	}
}

void Well::Render(HDC hdc)
{
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	for (int i = 0; i < WELL_X; i++)
	{
		for (int j = 0; j < WELL_Y; j++)
		{
			
		}
	}
}
