#include "MainGame.h"
#include "Image.h"
#include "TilemapTool.h"
#include "AstarScene.h"
#include "StartScene.h"
#include "LoadingScene.h"
#include "LoadingSleep.h"
#include "LoadingEnding.h"
#include "MyHouseScene.h"
#include "CaveScene.h"
#include "FarmScene.h"
#include "StoreScene.h"
#include "BusScene.h"
#include "InvenScene.h"
#include "Clock.h"
#include "SmallInven.h"
#include "Energy.h"
#include "TalkScene.h"
#include "FloodFillAlgorithm.h"

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	FloodFillAlgorithm::GetSingleton()->Init();

	// ¸ÞÀÎ°ÔÀÓÀÇ ÃÊ±âÈ­ ÇÔ¼ö
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 1, NULL);

	// ¹é¹öÆÛ ÀÌ¹ÌÁö
	int maxWidth, maxHeight;
	maxWidth = max(WINSIZE_X, TILEMAPTOOLSIZE_X);
	maxHeight = max(WINSIZE_Y, TILEMAPTOOLSIZE_Y);

	backBuffer = new Image();
	backBuffer->Init(maxWidth, maxHeight);

	//UI Button
	ImageManager::GetSingleton()->AddImage("newBt",  "Image/startMenu/stBt1.bmp", 212, 181, 1, 2);
	ImageManager::GetSingleton()->AddImage("loadBt", "Image/startMenu/stBt2.bmp", 212, 181, 1, 2);
	ImageManager::GetSingleton()->AddImage("coopBt", "Image/startMenu/stBt3.bmp", 212, 181, 1, 2);
	ImageManager::GetSingleton()->AddImage("exitBt", "Image/startMenu/stBt4.bmp", 212, 181, 1, 2);

	SceneManager::GetSingleton()->AddScene("½ÃÀÛÈ­¸é", new StartScene());
	SceneManager::GetSingleton()->AddScene("MyHome", new MyHouseScene());
	SceneManager::GetSingleton()->AddScene("µ¿±¼¾À", new CaveScene());
	SceneManager::GetSingleton()->AddScene("³óÀå¾À", new FarmScene());
	SceneManager::GetSingleton()->AddScene("»óÁ¡¾À", new StoreScene());
	SceneManager::GetSingleton()->AddScene("¹ö½º¿£µù¾À", new BusScene());
	SceneManager::GetSingleton()->AddScene("Ã¢°í¾À", new InvenScene());
	SceneManager::GetSingleton()->AddScene("Å¸ÀÏ¸ÊÅø", new TilemapTool());
	SceneManager::GetSingleton()->AddScene("´ëÈ­Ã¢¾À", new TalkScene());
	SceneManager::GetSingleton()->AddScene("A*", new AstarScene());
	
	SceneManager::GetSingleton()->AddLoadingScene("·Îµù¾À_1", new LoadingScene());
	SceneManager::GetSingleton()->AddLoadingScene("·Îµù½½¸³¾À", new LoadingSleep());
	SceneManager::GetSingleton()->AddLoadingScene("·Îµù¿£µù¾À", new LoadingEnding());

	SceneManager::GetSingleton()->ChangeScene("½ÃÀÛÈ­¸é");

	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->Release();
	Clock::GetSingleton()->Release();
	SmallInven::GetSingleton()->Release();
	Energy::GetSingleton()->Release();

	SAFE_RELEASE(backBuffer);

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SceneManager::GetSingleton()->Update();
	Clock::GetSingleton()->Update();
	SmallInven::GetSingleton()->Update();
	Energy::GetSingleton()->Update();
	FloodFillAlgorithm::GetSingleton()->Update();

}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();

	SceneManager::GetSingleton()->Render(hBackDC);
	Clock::GetSingleton()->Render(hBackDC);
	SmallInven::GetSingleton()->Render(hBackDC);
	Energy::GetSingleton()->Render(hBackDC);
	TimerManager::GetSingleton()->Render(hBackDC);

	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
