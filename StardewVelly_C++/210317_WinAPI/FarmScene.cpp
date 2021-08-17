#include "FarmScene.h"
#include "Image.h"
#include "PlayerShip.h"
#include "TileMapTool.h"
#include "CollisionManager.h"
#include "Energy.h"
#include "SmallInven.h"
#include "Clock.h"
#include "MyHouseScene.h"
#include "FloodFillAlgorithm.h"

HRESULT FarmScene::Init()
{
	CollisionManager::GetSingleton()->Init();
	FloodFillAlgorithm::GetSingleton()->Init();

	ZoomSize = 3.0f;

	ImageManager::GetSingleton()->AddImage(
		"샘플타일1", "Image/SpringFarm1.bmp", 896 * ZoomSize, 896 * ZoomSize,
		SAMPLE_TILE_X, SAMPLE_TILE_Y, false, RGB(255, 0, 255));

	farmBg = ImageManager::GetSingleton()->FindImage("샘플타일1");

	gameFarmBg = new Image;
	gameFarmBg->Init("Image/SpringFarm1.bmp", 896 * ZoomSize, 896 * ZoomSize, false, RGB(255, 0, 255));

	plowImg = new Image;
	plowImg->Init("Image/TileSet.bmp", 64, 128, 4, 8, true, RGB(255, 0, 255));

	farmSheet = new Image;
	farmSheet->Init("Image/farmSheet.bmp", 132, 66, 6, 3, true, RGB(255, 0, 255));

	endingMsgImg = new Image;
	endingMsgImg->Init("Image/endingMessage.bmp", 454, 99, true, RGB(255, 0, 255));

	notTicketMsgImg = new Image;
	notTicketMsgImg->Init("Image/notTicketMessage.bmp", 453, 99, true, RGB(255, 0, 255));

	pondSizeX = FloodFillAlgorithm::GetSingleton()->GetGap().x;
	pondSizeY = FloodFillAlgorithm::GetSingleton()->GetGap().y;

	pond = new Image;
	pond->Init("Image/Pond.bmp", 146 * pondSizeX, 146 * pondSizeY, false, RGB(255, 0, 255));

	player = new PlayerShip();
	player->Init();

	cameraPos.x = WINSIZE_X / 2 + 1000;
	cameraPos.y = WINSIZE_Y / 2;

	// 각 포탈을 이용시 해당 포탈의 위치가 아닌 초기값으로 시작하는걸 해결해야한다.
	
	switch (GameData::GetSingleton()->GetLastSceneID())
	{
	case MYHOUSE:
		cameraPos.x = WINSIZE_X / 2 + 1000;		//1540
		cameraPos.y = WINSIZE_Y / 2;			//410

		FocusPx = WINSIZE_X / 2 - 20;			//520	- 1020
		FocusPy = WINSIZE_Y / 2 - 40;			//370	- 40
		break;

	case STORE:
		cameraPos.x = 50;
		cameraPos.y = 300;

		FocusPx = 520;
		FocusPy = 370;
		break;
	}

	player->SetPos({ FocusPx, FocusPy });

	IsCamera = true;
	camSpeed = 2.0f; //5

	SetLeftDown = false;
	SetRightDown = false;
	SetTopDown = false;
	SetBottomDown = false;

	loadStageNum = 2;
	tilemapTool->Load(loadStageNum);
	AdjustTileUpScale(3);

	size = 3;
	plowFrame = 2;

	haveTicket = false;
	IsEnding = false;
	IsNotEnding = false;
	
	CameraShape = {
		TilemapTool::tileInfo[5][6].rcTile.left,
		TilemapTool::tileInfo[5][6].rcTile.top,
		TilemapTool::tileInfo[5][6].rcTile.right,
		TilemapTool::tileInfo[5][6].rcTile.bottom };

	return S_OK;
}

void FarmScene::Release()
{
	SAFE_RELEASE(player);
	CollisionManager::GetSingleton()->Release();
	//AdjustTileDownScale(3);
	//TilemapTool::Save(2);
}

void FarmScene::Update()
{
	camTilePos.x = ((cameraPos.x / 3) / TILESIZE) + 6;
	camTilePos.y = ((cameraPos.y / 3) / TILESIZE) + 5;

	plow.x = cameraPos.x + g_ptMouse.x;
	plow.y = cameraPos.y + g_ptMouse.y;
	plowTile.x = ((plow.x / 3) / TILESIZE);
	plowTile.y = ((plow.y / 3) / TILESIZE);

	if (player)
	{
		if (IsCamera)
		{
			player->SetMoveSpeed(0);
			CameraMove(1);
			if (player->GetMoveSpeed() == 0)
			{
				player->SetPos({ FocusPx, FocusPy });
			}
		}
		else
		{
			player->SetMoveSpeed(2);
			CameraMove(0);
			CollisionManager::GetSingleton()->playerToWall(player);
		}
		player->Update();
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{			
				if (camTilePos.y + i == plowTile.y && camTilePos.x + j == plowTile.x)
				{
					if (TilemapTool::tileInfo[plowTile.y][plowTile.x].plowType == DRYPLOW &&
						SmallInven::GetSingleton()->GetInputItemType().invenType == WATERING)
					{
						TilemapTool::tileInfo[plowTile.y][plowTile.x].plowType = WETPLOW;
					}
					else if (TilemapTool::tileInfo[plowTile.y][plowTile.x].plowType == WETPLOW)
					{
						if (SmallInven::GetSingleton()->GetInputItemType().invenType == EGGPLANT)
						{
							TilemapTool::tileInfo[plowTile.y][plowTile.x].seedType = EGGPLANTSEED_0;
						}
						else if (SmallInven::GetSingleton()->GetInputItemType().invenType == PEPPER)
						{
							TilemapTool::tileInfo[plowTile.y][plowTile.x].seedType = PEPPERSEED_0;
						}
						else if (SmallInven::GetSingleton()->GetInputItemType().invenType == PEACH)
						{
							TilemapTool::tileInfo[plowTile.y][plowTile.x].seedType = PEACHSEED_0;
						}
						else {}
					}
					else if (TilemapTool::tileInfo[plowTile.y][plowTile.x].tileType == ROAD &&
						SmallInven::GetSingleton()->GetInputItemType().invenType == HOE)
					{
						TilemapTool::tileInfo[plowTile.y][plowTile.x].plowType = DRYPLOW;
					}
					UseEnergy();
				}
			}
		}
	}

	CheckBlockCollision();
	DayPlowCollision();

	if (SmallInven::GetSingleton()->GetHaveTicket())
	{
		haveTicket = true;
	}
}

void FarmScene::Render(HDC hdc)
{
	if (endingMsgImg && IsEnding)
	{
		endingMsgImg->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, true);
	}
	else if (endingMsgImg && IsNotEnding)
	{
		notTicketMsgImg->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, true);
	}
	else
	{
		PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
		if (gameFarmBg)
		{
			gameFarmBg->RenderBg(hdc, 0, 0, 
				cameraPos.x, cameraPos.y);
		}
		if (farmBg)
		{
			//for (int i = camTilePos.y - 6; i < camTilePos.y + 6; i++)
			//{
			//	for (int j = camTilePos.x - 6; j < camTilePos.x + 8; j++)
			//	{
			//		farmBg->FrameRender(hdc,
			//			TilemapTool::tileInfo[i][j].rcTile.left - cameraPos.x,
			//			TilemapTool::tileInfo[i][j].rcTile.top - cameraPos.y,
			//			TilemapTool::tileInfo[i][j].frameX,
			//			TilemapTool::tileInfo[i][j].frameY
			//		);
			//	}
			//}

			if (pond)
			{
				pond->Render(hdc, 
					TilemapTool::tileInfo[26][12].rcTile.left - cameraPos.x,
					TilemapTool::tileInfo[26][12].rcTile.top - cameraPos.y,
					true);
			}
			for (int i = camTilePos.y - 6; i < camTilePos.y + 6; i++)
			{
				for (int j = camTilePos.x - 6; j < camTilePos.x + 8; j++)
				{
					if (TilemapTool::tileInfo[i][j].plowType == DRYPLOW)
					{
						plowImg->FrameRender(hdc,
							TilemapTool::tileInfo[i][j].rcTile.left - cameraPos.x,
							TilemapTool::tileInfo[i][j].rcTile.top - cameraPos.y,
							0, plowFrame, false, 5);
					}
					else if (TilemapTool::tileInfo[i][j].plowType == WETPLOW)
					{
						plowImg->FrameRender(hdc,
							TilemapTool::tileInfo[i][j].rcTile.left - cameraPos.x,
							TilemapTool::tileInfo[i][j].rcTile.top - cameraPos.y,
							0, plowFrame + 3, false, 5);
					}

					if (TilemapTool::tileInfo[i][j].seedType == PEACHSEED_0)
					{
						farmSheet->FrameRender(hdc,
							TilemapTool::tileInfo[i][j].rcTile.left - cameraPos.x,
							TilemapTool::tileInfo[i][j].rcTile.top - cameraPos.y,
							TilemapTool::tileInfo[i][j].glowTime, 0, false, 4);
					}
					else if (TilemapTool::tileInfo[i][j].seedType == EGGPLANTSEED_0)
					{
						farmSheet->FrameRender(hdc,
							TilemapTool::tileInfo[i][j].rcTile.left - cameraPos.x,
							TilemapTool::tileInfo[i][j].rcTile.top - cameraPos.y,
							TilemapTool::tileInfo[i][j].glowTime, 1, false, 4);
					}
					else if (TilemapTool::tileInfo[i][j].seedType == PEPPERSEED_0)
					{
						farmSheet->FrameRender(hdc,
							TilemapTool::tileInfo[i][j].rcTile.left - cameraPos.x,
							TilemapTool::tileInfo[i][j].rcTile.top - cameraPos.y,
							TilemapTool::tileInfo[i][j].glowTime, 2, false, 4);
					}
				}
			}
		}

		//Rectangle(hdc, CameraShape.left, CameraShape.top, CameraShape.right, CameraShape.bottom);

		if (player)
		{
			player->Render(hdc);
		}
	}	

	wsprintf(szText, "%d, %d", camTilePos.x, camTilePos.y);
	TextOut(hdc, WINSIZE_X - 120, 185, szText, strlen(szText));
	wsprintf(szText, "x = %d, y = %d", g_ptMouse.x, g_ptMouse.y);
	TextOut(hdc, WINSIZE_X - 120, 210, szText, strlen(szText));
	wsprintf(szText, "px = %d, py = %d", plow.x, plow.y);
	TextOut(hdc, WINSIZE_X - 120, 230, szText, strlen(szText));
	wsprintf(szText, "ptx = %d, pty = %d", plowTile.x, plowTile.y);
	TextOut(hdc, WINSIZE_X - 120, 250, szText, strlen(szText));
	wsprintf(szText, "tiletype = %d", TilemapTool::tileInfo[plowTile.y][plowTile.x].tileType);
	TextOut(hdc, WINSIZE_X - 120, 270, szText, strlen(szText));
	wsprintf(szText, "%d, %d", cameraPos.x, cameraPos.y);
	TextOut(hdc, WINSIZE_X - 120, 300, szText, strlen(szText));
}

void FarmScene::CheckBlockCollision()
{	
	if (TilemapTool::tileInfo[camTilePos.y][camTilePos.x].tileType == TILETYPE::GOTOHOME)
	{
		AdjustTileDownScale(3);
		TilemapTool::Save(2);
		SceneManager::GetSingleton()->ChangeScene("MyHome", "로딩씬_1");
		return;
	}
	if (TilemapTool::tileInfo[camTilePos.y][camTilePos.x].tileType == TILETYPE::GOTOSTORE)
	{
		AdjustTileDownScale(3);
		TilemapTool::Save(2);
		SceneManager::GetSingleton()->ChangeScene("상점씬", "로딩씬_1");
		return;
	}
	if (TilemapTool::tileInfo[camTilePos.y][camTilePos.x].tileType == TILETYPE::GOTOBUS && haveTicket)	// 버스티켓 조건문도 추가해야해
	{
		AdjustTileDownScale(3);
		TilemapTool::Save(2);
		IsEnding = true;
		SceneManager::GetSingleton()->ChangeScene("버스엔딩씬", "로딩엔딩씬");
		return;
	}
	if (TilemapTool::tileInfo[camTilePos.y][camTilePos.x].tileType == TILETYPE::GOTOBUS && !haveTicket)
	{	
		SetTopDown = true;
		IsNotEnding = true;
	}
	else
	{
		IsNotEnding = false;
		SetTopDown = false;
	}

	// 벽충돌 처리
	if (TilemapTool::tileInfo[camTilePos.y][camTilePos.x].tileType == TILETYPE::WALL)
	{
		if (player->GetMotion() == LEFT)	SetLeftDown = true;
		if (player->GetMotion() == UP)		SetTopDown = true;
	}
	else if (TilemapTool::tileInfo[camTilePos.y + 1][camTilePos.x + 1].tileType == TILETYPE::WALL)
	{
		if (player->GetMotion() == RIGHT)	SetRightDown = true;
		if (player->GetMotion() == DOWN)	SetBottomDown = true;
	}
	else
	{
		SetLeftDown = false;
		SetTopDown = false;
		SetRightDown = false;
		SetBottomDown = false;
	}
}

void FarmScene::CameraMove(float moveSpeed)
{
	moveSpeed = camSpeed;

	if (KeyManager::GetSingleton()->IsStayKeyDown('A') && !SetLeftDown)
	{
		cameraPos.x -= 0.5 * moveSpeed;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('W') && !SetTopDown)
	{
		cameraPos.y -= 0.5 * moveSpeed;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('D') && !SetRightDown)
	{
		cameraPos.x += 0.5 * moveSpeed;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('S') && !SetBottomDown)
	{
		cameraPos.y += 0.5 * moveSpeed;
	}
}

void FarmScene::AdjustTileUpScale(int size)
{
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			TilemapTool::tileInfo[i][j].rcTile.left = TilemapTool::tileInfo[i][j].rcTile.left * size;
			TilemapTool::tileInfo[i][j].rcTile.top = TilemapTool::tileInfo[i][j].rcTile.top * size;
			TilemapTool::tileInfo[i][j].rcTile.right = TilemapTool::tileInfo[i][j].rcTile.right * size;
			TilemapTool::tileInfo[i][j].rcTile.bottom = TilemapTool::tileInfo[i][j].rcTile.bottom * size;
		}
	}
}

void FarmScene::AdjustTileDownScale(int size)
{
	for (int i = 0; i < TILE_X; i++)
	{
		for (int j = 0; j < TILE_Y; j++)
		{
			TilemapTool::tileInfo[i][j].rcTile.left = TilemapTool::tileInfo[i][j].rcTile.left / size;
			TilemapTool::tileInfo[i][j].rcTile.top = TilemapTool::tileInfo[i][j].rcTile.top / size;
			TilemapTool::tileInfo[i][j].rcTile.right = TilemapTool::tileInfo[i][j].rcTile.right / size;
			TilemapTool::tileInfo[i][j].rcTile.bottom = TilemapTool::tileInfo[i][j].rcTile.bottom / size;
		}
	}
}

void FarmScene::UseEnergy()
{
	Energy::GetSingleton()->SetUseEnergy(Energy::GetSingleton()->GetUseEnergy() + 1);
}

void FarmScene::DayPlowCollision()
{
	if (Clock::GetSingleton()->GetDayCount() > 0)	// 집에서 하루 지날때
	{
		for (int k = 0; k < Clock::GetSingleton()->GetDayCount() + 1; k++)
		{
			for (int i = 0; i < TILE_Y; i++)
			{
				for (int j = 0; j < TILE_X; j++)
				{
					if (TilemapTool::tileInfo[i][j].seedType >= PEACHSEED_0 &&
						TilemapTool::tileInfo[i][j].seedType <= PEPPERSEED_5)
					{
						TilemapTool::tileInfo[i][j].glowTime++;
					}
					if (TilemapTool::tileInfo[i][j].glowTime == 6)
					{
						if (TilemapTool::tileInfo[i][j].seedType == EGGPLANTSEED_0)
						{
							Clock::GetSingleton()->SetCurrentGold(Clock::GetSingleton()->GetCurrentGold() + 1500);
							TilemapTool::tileInfo[i][j].seedType = NOTSEED;
							TilemapTool::tileInfo[i][j].glowTime = 0;
						}
						if (TilemapTool::tileInfo[i][j].seedType == PEPPERSEED_0)
						{
							Clock::GetSingleton()->SetCurrentGold(Clock::GetSingleton()->GetCurrentGold() + 3500);
							TilemapTool::tileInfo[i][j].seedType = NOTSEED;
							TilemapTool::tileInfo[i][j].glowTime = 0;
						}
						if (TilemapTool::tileInfo[i][j].seedType == PEACHSEED_0)
						{
							Clock::GetSingleton()->SetCurrentGold(Clock::GetSingleton()->GetCurrentGold() + 10000);
							TilemapTool::tileInfo[i][j].seedType = NOTSEED;
							TilemapTool::tileInfo[i][j].glowTime = 0;
						}
					}
				}
			}
		}
		Clock::GetSingleton()->SetDayCount(0);
	}

	if (Clock::GetSingleton()->GetIsDayLater() == true)	// 농장에서 하루 지날때
	{
		for (int i = 0; i < TILE_Y; i++)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				if (TilemapTool::tileInfo[i][j].seedType >= PEACHSEED_0 &&
					TilemapTool::tileInfo[i][j].seedType <= PEPPERSEED_5)
				{
					TilemapTool::tileInfo[i][j].glowTime++;

					if (TilemapTool::tileInfo[i][j].glowTime == 6)
					{
						if (TilemapTool::tileInfo[i][j].seedType == EGGPLANTSEED_0)
						{
							Clock::GetSingleton()->SetCurrentGold(Clock::GetSingleton()->GetCurrentGold() + 1500);
							TilemapTool::tileInfo[i][j].seedType = NOTSEED;
							TilemapTool::tileInfo[i][j].glowTime = 0;
						}
						if (TilemapTool::tileInfo[i][j].seedType == PEPPERSEED_0)
						{
							Clock::GetSingleton()->SetCurrentGold(Clock::GetSingleton()->GetCurrentGold() + 3500);
							TilemapTool::tileInfo[i][j].seedType = NOTSEED;
							TilemapTool::tileInfo[i][j].glowTime = 0;
						}
						if (TilemapTool::tileInfo[i][j].seedType == PEACHSEED_0)
						{
							Clock::GetSingleton()->SetCurrentGold(Clock::GetSingleton()->GetCurrentGold() + 10000);
							TilemapTool::tileInfo[i][j].seedType = NOTSEED;
							TilemapTool::tileInfo[i][j].glowTime = 0;
						}
					}
				}
			}
		}
	}
}


