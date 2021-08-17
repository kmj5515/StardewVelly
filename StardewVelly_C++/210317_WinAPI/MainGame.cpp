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

	// ���ΰ����� �ʱ�ȭ �Լ�
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 1, NULL);

	// ����� �̹���
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

	SceneManager::GetSingleton()->AddScene("����ȭ��", new StartScene());
	SceneManager::GetSingleton()->AddScene("MyHome", new MyHouseScene());
	SceneManager::GetSingleton()->AddScene("������", new CaveScene());
	SceneManager::GetSingleton()->AddScene("�����", new FarmScene());
	SceneManager::GetSingleton()->AddScene("������", new StoreScene());
	SceneManager::GetSingleton()->AddScene("����������", new BusScene());
	SceneManager::GetSingleton()->AddScene("â���", new InvenScene());
	SceneManager::GetSingleton()->AddScene("Ÿ�ϸ���", new TilemapTool());
	SceneManager::GetSingleton()->AddScene("��ȭâ��", new TalkScene());
	SceneManager::GetSingleton()->AddScene("A*", new AstarScene());
	
	SceneManager::GetSingleton()->AddLoadingScene("�ε���_1", new LoadingScene());
	SceneManager::GetSingleton()->AddLoadingScene("�ε�������", new LoadingSleep());
	SceneManager::GetSingleton()->AddLoadingScene("�ε�������", new LoadingEnding());

	SceneManager::GetSingleton()->ChangeScene("����ȭ��");

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
