#include "CollisionManager.h"
#include "TileMapTool.h"
#include "PlayerShip.h"

void CollisionManager::playerToDoor(PlayerShip* player)
{
	if (TilemapTool::tileInfo[player->GetTilePos().y][player->GetTilePos().x].tileType == TILETYPE::GOTOFARM)
	{
		SceneManager::GetSingleton()->ChangeScene("³óÀå¾À", "·Îµù¾À_1");
		return;
	}
	if (TilemapTool::tileInfo[player->GetTilePos().y][player->GetTilePos().x].tileType == TILETYPE::INVENTORYSTORE)
	{
		SceneManager::GetSingleton()->ChangeScene("Ã¢°í¾À", "·Îµù¾À_1");
		return;
	}
}

void CollisionManager::playerToWall(PlayerShip* player)
{
	if (TilemapTool::tileInfo[player->GetTilePos().y][player->GetTilePos().x].tileType == TILETYPE::WALL)
	{
		if (player->GetMotion() == LEFT)
		{
			player->SetLeftDown(true);
			player->SetPos({ player->GetPos().x + 1, player->GetPos().y });
		}
		else if (player->GetMotion() == RIGHT)
		{
			player->SetRightDown(true);
			player->SetPos({ player->GetPos().x - 1, player->GetPos().y });
		}
		else if (player->GetMotion() == UP)
		{
			player->SetTopDown(true);
			player->SetPos({ player->GetPos().x, player->GetPos().y + 1 });
		}
		else if (player->GetMotion() == DOWN)
		{
			player->SetBottomDown(true);
			player->SetPos({ player->GetPos().x, player->GetPos().y - 1 });
		}
	}
	else
	{
		player->SetLeftDown(false);
		player->SetRightDown(false);
		player->SetTopDown(false);
		player->SetBottomDown(false);
	}
}

HRESULT CollisionManager::Init()
{
	return S_OK;
}

void CollisionManager::Render(HDC hdc)
{
}

void CollisionManager::Release()
{
	ReleaseSingleton();
}
