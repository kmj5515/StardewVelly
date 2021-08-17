#include "SmallInven.h"
#include "Image.h"
#include "InvenScene.h"

HRESULT SmallInven::Init()
{
	SInvenImg = new Image();
	SInvenImg->Init("Image/SmallInven.bmp", 800, 96);

	SelectImg = new Image();
	SelectImg->Init("Image/SelectInven.bmp", 64, 64, true, RGB(255, 0, 255));

	ItemImg = new Image;
	ItemImg->Init("Image/inventoryItem.bmp", INVENTORY_ITEM_SIZE * 8, INVENTORY_ITEM_SIZE, 8, 1, true, RGB(255, 0, 255));

	selectX = 0;

	//vInvenToryInfo = 

	for (int i = 0; i < INVEN_INFO_SIZE; i++)
	{
		invenItem[i].invenType = BLANK;
	}

	haveTicket = false;

	return S_OK;
}

void SmallInven::Release()
{
	SAFE_RELEASE(SelectImg);
}

void SmallInven::Update()
{
	// 각 키를 누를때 마다 아이템 선택
	if (KeyManager::GetSingleton()->IsOnceKeyDown('1'))
	{
		selectX = 0;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('2'))
	{
		selectX = 1;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('3'))
	{
		selectX = 2;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('4'))
	{
		selectX = 3;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('5'))
	{
		selectX = 4;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('6'))
	{
		selectX = 5;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('7'))
	{
		selectX = 6;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('8'))
	{
		selectX = 7;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('9'))
	{
		selectX = 8;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('0'))
	{
		selectX = 9;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_OEM_MINUS))
	{
		selectX = 10;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_OEM_PLUS))
	{
		selectX = 11;
	}

	for (int i = 0; i < INVEN_INFO_SIZE; i++)
	{
		if (invenItem[i].invenType == TICKET)
		{
			haveTicket = true;
		}
	}
}

void SmallInven::Render(HDC hdc)
{
	if (SInvenImg)
	{
		SInvenImg->Render(hdc, WINSIZE_X / 2, WINSIZE_Y - 30, true);
	}

	if (ItemImg)
	{
		for (int i = 0; i < INVEN_INFO_SIZE; i++)
		{
			ItemImg->FrameRender(hdc, 153 + (64 * i), WINSIZE_Y - 60, invenItem[i].invenType, 0, false, 3);
		}
	}

	if (SelectImg)
	{
		SelectImg->Render(hdc, 190 + (64 * selectX), WINSIZE_Y - 30, true);
	}
}



