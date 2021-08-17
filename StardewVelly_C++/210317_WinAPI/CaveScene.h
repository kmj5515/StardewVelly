#pragma once
#include "GameNode.h"

class PlayerShip;
//class EnemyManager;
class Image;
class CaveScene : public GameNode
{
private:
	Image* caveBg;	//caveBg
	//EnemyManager* enemyMgr;
	PlayerShip* playerShip;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~CaveScene() {};
};



