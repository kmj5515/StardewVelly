#include "StartScene.h"
#include "Image.h"
#include "Button.h"
#include "Clock.h"
#include "Energy.h"
#include "SmallInven.h"
#include "TilemapTool.h"

HRESULT StartScene::Init()
{
	startBG = new Image();
	startBG->Init("Image/startMenu/stardewPanorama.bmp", WINSIZE_X, WINSIZE_Y);

	startLogo = new Image();
	startLogo->Init("Image/startMenu/logo.bmp", 880, 400, true, RGB(0, 0, 0));

	newBt = new Button();
	newBt->Init("newBt", WINSIZE_X * 1 / 5, WINSIZE_Y - 100);
	newBt->SetFunc(SetChangeScene, 1);

	loadBt = new Button();
	loadBt->Init("loadBt", WINSIZE_X * 2 / 5, WINSIZE_Y - 100);
	loadBt->SetFunc(SetChangeScene, 2);

	coopBt = new Button();
	coopBt->Init("coopBt", WINSIZE_X * 3 / 5, WINSIZE_Y - 100);
	coopBt->SetFunc(SetChangeScene, 3);

	exitBt = new Button();
	exitBt->Init("exitBt", WINSIZE_X * 4 / 5, WINSIZE_Y - 100);
	exitBt->SetFunc(SetChangeScene, 4);

	return S_OK;
}

void StartScene::Release()
{
	SAFE_RELEASE(startBG);
	SAFE_RELEASE(startLogo);

	SAFE_RELEASE(newBt);
	SAFE_RELEASE(loadBt);
	SAFE_RELEASE(coopBt);
	SAFE_RELEASE(exitBt);
}

void StartScene::Update()
{
	if (newBt)     newBt->Update();
	if (loadBt)    loadBt->Update();
	if (coopBt)    coopBt->Update();
	if (exitBt)    exitBt->Update();
}

void StartScene::Render(HDC hdc)
{
	if (startBG)
	{
		startBG->Render(hdc);
	}

	if (startLogo)
	{
		startLogo->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 3, true);
	}

	if (newBt)     newBt->Render(hdc);
	if (loadBt)    loadBt->Render(hdc);
	if (coopBt)    coopBt->Render(hdc);
	if (exitBt)    exitBt->Render(hdc);
}

void StartScene::SetChangeScene(int key)
{
	switch (key)
	{
	case 1:
		SceneManager::GetSingleton()->ChangeScene("MyHome", "·Îµù¾À_1");
		Clock::GetSingleton()->Init();
		SmallInven::GetSingleton()->Init();
		Energy::GetSingleton()->Init();
		//return;		// ¹Ø¿¡ ¸í·É¾î°¡ ¾ø´Ù¸é return ÇÊ¿ä x
		break;
	case 2:
		SceneManager::GetSingleton()->ChangeScene("µ¿±¼¾À", "·Îµù¾À_1");
		break;
	case 3:
		SceneManager::GetSingleton()->ChangeScene("Å¸ÀÏ¸ÊÅø", "·Îµù¾À_1");
		break;
	case 4:
		PostQuitMessage(0);
		break;
	}	
	
}

