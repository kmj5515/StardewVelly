#include "PlayerShip.h"
#include "Image.h"
#include "CommonFunction.h"
#include "CollisionManager.h"

HRESULT PlayerShip::Init()
{
	image = ImageManager::GetSingleton()->AddImage("플레이어", "Image/Abigail.bmp",
		64, 160, 4, 5, true, RGB(255, 0, 255));

	if (image == nullptr)
	{
		MessageBox(g_hWnd, "플레이어 우주선 이미지 로드 실패", "초기화 실패", MB_OK);
		return E_FAIL;
	}

	pos.x = WINSIZE_X / 3 - 100;
	pos.y = WINSIZE_Y / 2 + 50;

	shape = { 0,0,0,0 };

	moveSpeed = 1.0f;
	Moveframe = 0;

	tilePos.x = (pos.x / TILESIZE);
	tilePos.y = (pos.y / TILESIZE);

	leftDown = false;		// test
	rightDown = false;
	topDown = false;
	bottomDown = false;

	playerSize = 5;
	autoMove = false;

	return S_OK;
}

void PlayerShip::Release()
{
}

void PlayerShip::Update()
{
	MovePlayer();
}

void PlayerShip::Render(HDC hdc)
{
	if (image)
	{
		image->FrameRender(hdc, pos.x, pos.y, Moveframe, motion, true, playerSize);
		//Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void PlayerShip::MovePlayer()
{
	if (!autoMove)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('A') && !leftDown)
		{
			AddFrame(20, 3);
			pos.x -= moveSpeed;
			motion = LEFT;

			if (pos.x < 0)
			{
				pos.x = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('D') && !rightDown)
		{
			AddFrame(20, 3);
			pos.x += moveSpeed;
			motion = RIGHT;

			if (pos.x > 1200)
			{
				pos.x = 1200;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('W') && !topDown)
		{
			AddFrame(20, 3);
			pos.y -= moveSpeed;
			motion = UP;

			if (pos.y < 0)
			{
				pos.y = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('S') && !bottomDown)
		{
			AddFrame(20, 3);
			pos.y += moveSpeed;
			motion = DOWN;

			if (pos.y > 1200)
			{
				pos.y = 1200;
			}
		}
	}
	
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD0))
	{
		AddFrame(10, 3);
		motion = STAY;
	}

	if (autoMove)
	{
		AddFrame(200, 3);
		pos.y -= moveSpeed / 10;
		motion = UP;
	}

	tilePos.x = ((pos.x) / TILESIZE) + 1;
	tilePos.y = ((pos.y) / TILESIZE) + 4;
}

void PlayerShip::AddFrame(int Maxframe, int MaxMoveframe)
{
	frame++;
	if (frame >= Maxframe)
	{
		frame = 0;
		Moveframe += 1;
		if (Moveframe > MaxMoveframe)
		{
			Moveframe = 0;
		}
	}
}

