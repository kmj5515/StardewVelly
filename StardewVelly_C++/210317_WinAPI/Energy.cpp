#include "Energy.h"
#include "Image.h"

HRESULT Energy::Init()
{
	energySize = 4;
	useEnergy = 0;
	resetEnergy = false;

	energyPos.x = 12 * energySize;
	energyPos.y = 56 * energySize;

	Egage.left = WINSIZE_X - energyPos.x + 10;
	Egage.top = WINSIZE_Y - energyPos.y + 50;
	Egage.right = WINSIZE_X - 10;
	Egage.bottom = WINSIZE_Y - 5;

	energyImg = new Image();
	energyImg->Init("Image/energy.bmp", energyPos.x, energyPos.y, true, RGB(255, 0, 255));

	isGage = true;
	isTired = false;

	return E_NOTIMPL;
}

void Energy::Release()
{
	SAFE_RELEASE(energyImg);
}

void Energy::Update()
{
	Egage.top = WINSIZE_Y - energyPos.y + 50 + (useEnergy * 7);

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD6))
	{
		useEnergy++;
	}
	
	if (isGage)
	{
		if (useEnergy >= 0 && useEnergy < 10)
		{
			energyWarning = GREEN;
		}
		else if (useEnergy >= 10 && useEnergy < 20)
		{
			energyWarning = YELLOW;
		}
		else if (useEnergy >= 20 && useEnergy < 30)
		{
			energyWarning = RED;
		}

		if (Egage.bottom < Egage.top)
		{
			Egage.bottom = Egage.top;

			PlayerTired(true);
		}

		if (resetEnergy)
		{
			useEnergy = 0;
			resetEnergy = false;
		}
	}
}

void Energy::Render(HDC hdc)
{
	if (energyImg)
	{
		energyImg->Render(hdc, WINSIZE_X - energyPos.x, WINSIZE_Y - energyPos.y, false);
		
		switch (energyWarning)
		{
		case Energy::GREEN:
			hBrush = CreateSolidBrush(RGB(0, 200, 0));
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			break;
		case Energy::YELLOW:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			break;
		case Energy::RED:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			break;
		default:
			break;
		}

		Rectangle(hdc, Egage.left, Egage.top, Egage.right, Egage.bottom);
		
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);
	}
}

void Energy::PlayerTired(bool isTired)
{
	if (isTired)
	{
		MessageBox(g_hWnd, "사유 : 과로사", "죽었습니다.", MB_OK);
		resetEnergy = true;
		SceneManager::GetSingleton()->ChangeScene("MyHome", "로딩씬_1");
		isTired = false;
	}
	
}
