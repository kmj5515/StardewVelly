#include "StoreScene.h"
#include "Image.h"
#include "PlayerShip.h"
#include "TileMapTool.h"
#include "CollisionManager.h"
#include "FarmScene.h"

HRESULT StoreScene::Init()
{
	CollisionManager::GetSingleton()->Init();

	ImageManager::GetSingleton()->AddImage(
		"»óÁ¡¾À", "Image/Store1.bmp", 896, 896, SAMPLE_TILE_X, SAMPLE_TILE_Y);
	
	storeImg = ImageManager::GetSingleton()->FindImage("»óÁ¡¾À");

	player = new PlayerShip();
	player->Init();

	player->SetTilePos({ 13, 18 });
	player->SetMoveSpeed(0.6f);

	tilemapTool->Load(3);

	return S_OK;
}

void StoreScene::Release()
{
	SAFE_RELEASE(player);
	CollisionManager::GetSingleton()->Release();
}

void StoreScene::Update()
{
	if (player)
	{
		player->Update();
	}

	CollisionManager::GetSingleton()->playerToWall(player);
	CollisionManager::GetSingleton()->playerToDoor(player);
}

void StoreScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	if (storeImg)
	{
		storeImg->Render(hdc);
	}

	Rectangle(hdc, CameraShape.left, CameraShape.top, CameraShape.right, CameraShape.bottom);

	if (player)
	{
		player->Render(hdc);
	}
}
