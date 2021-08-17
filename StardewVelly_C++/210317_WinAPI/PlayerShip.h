#pragma once
#include "GameNode.h"

class Image;
class PlayerShip : public GameNode
{
private:
	Image* image;
	FPOINT pos;
	POINT tilePos;
	
	RECT shape;
	int size;
	MOTION motion;

	float moveSpeed;
	int frame;
	int Moveframe;

	bool playerToWall;

	bool leftDown;
	bool rightDown;
	bool topDown;
	bool bottomDown;

	int playerSize;
	bool autoMove;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void MovePlayer();
	void AddFrame(int Maxframe, int MaxMoveframe);

	inline RECT& GetShape() { return shape; }
	inline MOTION GetMotion() { return this->motion; }

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline void SetTilePos(POINT tilePos) { this->tilePos = tilePos; }
	inline POINT GetTilePos() { return this->tilePos; }

	inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
	inline float GetMoveSpeed() { return this->moveSpeed; }

	inline void SetAutoMove(bool autoMove) { this->autoMove = autoMove; }

	inline void SetPlayerSize(float playerSize) { this->playerSize = playerSize; }

	inline void SetLeftDown(bool leftDown) { this->leftDown = leftDown; }
	inline void SetRightDown(bool rightDown) { this->rightDown = rightDown; }
	inline void SetTopDown(bool topDown) { this->topDown = topDown; }
	inline void SetBottomDown(bool bottomDown) { this->bottomDown = bottomDown; }
};

