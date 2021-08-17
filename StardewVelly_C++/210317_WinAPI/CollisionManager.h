#pragma once
#include "config.h"
#include "Singleton.h"

class PlayerShip;
class CollisionManager : public Singleton<CollisionManager>
{
public:
	enum MOTION { DOWN, RIGHT, UP, LEFT, STAY };
private:
	PlayerShip* player;

	RECT tmpRect;

	char szText[128] = "";

	string sceneName = "";
	
public:
	void playerToDoor(PlayerShip* player);
	void playerToWall(PlayerShip* player);

	HRESULT Init();
	void Render(HDC hdc);
	void Release();
};

