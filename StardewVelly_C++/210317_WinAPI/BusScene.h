#pragma once
#include "GameNode.h"

class PlayerShip;
class Image;
class BusScene : public GameNode
{
private:
	Image* busBg;	
	Image* busBody;
	Image* busDoor;

	PlayerShip* player;

	POINT busPos;
	POINT busDoorPos;
	int moveBus;
	int moveDoor;

	bool closeDoor;

	int count;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~BusScene() {};
};

