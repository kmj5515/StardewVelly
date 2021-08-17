#include "LoadingEnding.h"
#include "Image.h"

HRESULT LoadingEnding::Init()
{
	LoadingEndingImg = new Image();
	LoadingEndingImg->Init("Image/loadingEnding.bmp", 852, 480, true, RGB(255, 0, 255));

	return S_OK;
}

void LoadingEnding::Release()
{

}

void LoadingEnding::Update()
{
}

void LoadingEnding::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	if (LoadingEndingImg)
	{
		LoadingEndingImg->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, true);
	}
}
