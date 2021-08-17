#include "MyHouseScene.h"
#include "Image.h"
#include "PlayerShip.h"
#include "TileMapTool.h"
#include "CollisionManager.h"
#include "Clock.h"
#include "Energy.h"

HRESULT MyHouseScene::Init()
{
	CollisionManager::GetSingleton()->Init();

	ImageManager::GetSingleton()->AddImage(
		"»ùÇÃÅ¸ÀÏ", "Image/House.bmp", 448, 448,
		SAMPLE_TILE_X, SAMPLE_TILE_Y, false, RGB(181, 184, 182));
	myHomeBg = ImageManager::GetSingleton()->FindImage("»ùÇÃÅ¸ÀÏ");

	myHomeBgImg = ImageManager::GetSingleton()->AddImage("Áý ¹è°æ", "Image/House.bmp", 896, 896);

	player = new PlayerShip();
	player->Init();

	talkIconImg = new Image();
	talkIconImg->Init("Image/talkIcon.bmp", 33, 33, true, RGB(255, 0, 255));

	sleepMsgImg = new Image();
	sleepMsgImg->Init("Image/loadingSleep.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

	rcTalkIcon.left = WINSIZE_X - 300;
	rcTalkIcon.top = 0;
	rcTalkIcon.right = rcTalkIcon.left + 33;
	rcTalkIcon.bottom = rcTalkIcon.top + 33;

	player->SetTilePos({ 13, 18 });

	tilemapTool->Load(1);

	dayCount = 0;
	IsSleep = false;

	return S_OK;
}

void MyHouseScene::Release()
{
	SAFE_RELEASE(player);
	CollisionManager::GetSingleton()->Release();
}

void MyHouseScene::Update()
{
	if (player)
	{
		player->Update();
		if (TilemapTool::tileInfo[player->GetTilePos().y][player->GetTilePos().x].tileType
			== TILETYPE::BED && !IsSleep)
		{
			Clock::GetSingleton()->ClockReset();
			Energy::GetSingleton()->SetResetEnergy(true);
			IsSleep = true;
			player->SetPos({ player->GetPos().x + 100, player->GetPos().y });
		}

		CollisionManager::GetSingleton()->playerToWall(player);
		CollisionManager::GetSingleton()->playerToDoor(player);
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		if (g_ptMouse.x >= rcTalkIcon.left && g_ptMouse.x <= rcTalkIcon.right &&
			g_ptMouse.y >= rcTalkIcon.top && g_ptMouse.y <= rcTalkIcon.bottom)
		{
			SceneManager::GetSingleton()->ChangeScene("´ëÈ­Ã¢¾À");
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		IsSleep = false;
	}
	if (Clock::GetSingleton()->GetIsDayLater() == true)
	{
		dayCount++;
		Clock::GetSingleton()->SetDayCount(dayCount);
		Clock::GetSingleton()->SetIsDayLater(false);
	}
}

void MyHouseScene::Render(HDC hdc)
{
	if (sleepMsgImg && IsSleep)
	{
		sleepMsgImg->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, true);
	}
	else
	{
		PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

		/*if (myHomeBg)
		{
			for (int i = 0; i < TILE_Y; i++)
			{
				for (int j = 0; j < TILE_X; j++)
				{
					myHomeBg->FrameRender(hdc,
						TilemapTool::tileInfo[i][j].rcTile.left,
						TilemapTool::tileInfo[i][j].rcTile.top,
						TilemapTool::tileInfo[i][j].frameX,
						TilemapTool::tileInfo[i][j].frameY
					);
				}
			}
		}*/

		if (myHomeBgImg)
		{
			myHomeBgImg->Render(hdc);
		}
		if (talkIconImg)
		{
			talkIconImg->Render(hdc, rcTalkIcon.left, rcTalkIcon.top, false);
		}
		if (player)
		{
			player->Render(hdc);
		}
	}

	//wsprintf(szText, "x = %d, y = %d", g_ptMouse.x, g_ptMouse.y);
	//TextOut(hdc, WINSIZE_X - 120, 210, szText, strlen(szText));
	//wsprintf(szText, "%d, %d", player->GetTilePos().x, player->GetTilePos().y);
	//TextOut(hdc, WINSIZE_X - 120, 185, szText, strlen(szText));
	//wsprintf(szText, "%d", dayCount);
	//TextOut(hdc, WINSIZE_X - 120, 240, szText, strlen(szText));
	
	CollisionManager::GetSingleton()->Render(hdc);
}
