#include "LoadingSleep.h"
#include "Image.h"

HRESULT LoadingSleep::Init()
{
	LoadingSleepImg = new Image();
	LoadingSleepImg->Init("Image/loadingSleep.bmp", 852, 480, true, RGB(255, 0, 255));

	return S_OK;
}

void LoadingSleep::Release()
{

}

void LoadingSleep::Update()
{
}

void LoadingSleep::Render(HDC hdc)
{
	if (LoadingSleepImg)
	{
		LoadingSleepImg->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, true);
	}
}
