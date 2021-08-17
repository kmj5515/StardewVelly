#include "BusScene.h"
#include "Image.h"
#include "PlayerShip.h"
#include "Clock.h"
#include "TilemapTool.h"
#include "FarmScene.h"

HRESULT BusScene::Init()
{
	Sleep(500);

	busBg = new Image();
	busBg->Init("Image/ending/BusStop.bmp", WINSIZE_X, WINSIZE_Y);

	busBody = new Image();
	busBody->Init("Image/ending/BusBody.bmp", 128 * 3, 64 * 3, true, RGB(255, 0, 255));
	
	busDoor = new Image();
	busDoor->Init("Image/ending/BusDoor.bmp", 96, 39, 6, 1, true, RGB(255, 0, 255));

	player = new PlayerShip();
	player->Init();

	busPos.x = 380;
	busPos.y = 50;

	busDoorPos.x = busPos.x + 50;	
	busDoorPos.y = busPos.y + 80;	

	moveBus = 0;
	moveDoor = 0;

	player->SetPlayerSize(4);
	player->SetPos({ 430, WINSIZE_Y - 30});

	closeDoor = false;
	count = 0;

	return S_OK;
}

void BusScene::Release()
{
	SAFE_RELEASE(player);
}
 
void BusScene::Update()
{
	player->SetAutoMove(true);

	if (player->GetPos().y < 150)
	{
		player->SetAutoMove(false);
		closeDoor = true;
		if (TimerManager::GetSingleton()->GetCurrTime())
		{
			count++;
			if (count % 100 == 0)
			{
				moveDoor++;
				
			}
		}
		if (moveDoor > 6)
		{
			if (closeDoor) moveBus += 1;

			if (busPos.x - moveBus + (WINSIZE_X / 2) < 0)
			{
				TilemapTool::ResetLoad(2);
				TilemapTool::Save(2);
				PostQuitMessage(0);
			}
		}
	}

	if (player)
	{
		player->Update();
	}

	// 버스가 x축어느정도를 넘어갔을떄 알파 블랜드
}

void BusScene::Render(HDC hdc)
{
	if (busBg)
	{
		busBg->Render(hdc, 0, 0, false);
	}
	if (busBody)
	{
		busBody->Render(hdc, busPos.x - moveBus, busPos.y, false);
	}
	if (busDoor)
	{
		busDoor->FrameRender(hdc, busDoorPos.x, busDoorPos.y, moveDoor, 0, false, 3);
	}
	if (player && !closeDoor)
	{
		player->Render(hdc);
	}
}
