#include "CaveScene.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Image.h"
#include "PlayerShip.h"
#include "FloodFillAlgorithm.h"

HRESULT CaveScene::Init()
{
	FloodFillAlgorithm::GetSingleton()->Init();

	caveBg = new Image();
	caveBg->Init("Image/Cave.bmp", WINSIZE_X, WINSIZE_Y);

	//enemyMgr = new EnemyManager();
	//enemyMgr->Init();

	//playerShip = new PlayerShip();
	//playerShip->Init();

	return S_OK;
}

void CaveScene::Release()
{
	FloodFillAlgorithm::GetSingleton()->Release();

	//SAFE_RELEASE(playerShip);
	//SAFE_RELEASE(enemyMgr);
}

void CaveScene::Update()
{
	FloodFillAlgorithm::GetSingleton()->Update();

	//if (enemyMgr)
	//{
		//enemyMgr->Update();
	//}

	//if (playerShip)
	//{
		//playerShip->Update();
	//}

}

void CaveScene::Render(HDC hdc)
{
	FloodFillAlgorithm::GetSingleton()->Render(hdc);

	/*if (enemyMgr)
	{
		enemyMgr->Render(hdc);
	}*/

	//if (playerShip)
	//{
		//playerShip->Render(hdc);
	//}

}

