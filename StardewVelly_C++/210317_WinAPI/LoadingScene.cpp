#include "LoadingScene.h"
#include "Image.h"

HRESULT LoadingScene::Init()
{
	LoadingImg = new Image();
	LoadingImg->Init("Image/loading.bmp", 852, 480, true, RGB(255, 0, 255));

	return S_OK;
}

void LoadingScene::Release()
{

}

void LoadingScene::Update()
{
}

void LoadingScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	if (LoadingImg)
	{
		LoadingImg->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, true);
	}
}
