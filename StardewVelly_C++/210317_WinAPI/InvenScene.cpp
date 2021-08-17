#include "InvenScene.h"
#include "Image.h"
#include "Clock.h"
#include "SmallInven.h"

HRESULT InvenScene::Init()
{
	InvenBg = new Image();
	InvenBg->Init("Image/BigInven.bmp", 912, 256, true, RGB(255, 255, 255));

	ISelectImg = new Image();
	ISelectImg->Init("Image/SelectInven.bmp", 64, 64, true, RGB(255, 0, 255));

	ExitIcon = new Image;
	ExitIcon-> Init("Image/exitIcon.bmp", INVEN_SIZE, INVEN_SIZE, true, RGB(255, 0, 255));

	UpIcon = new Image;
	UpIcon->Init("Image/Up.bmp", ICONSIZE, ICONSIZE, true, RGB(255, 0, 255));

	DownIcon = new Image;
	DownIcon->Init("Image/Down.bmp", ICONSIZE, ICONSIZE, true, RGB(255, 0, 255));

	itemInfoStatus = new Image;
	itemInfoStatus->Init("Image/itemInfo.bmp", 2065, 202, 7, 1, true, RGB(255, 0, 255));

	InventoryItem = new Image;
	InventoryItem->Init("Image/inventoryItem.bmp", INVENTORY_ITEM_SIZE * 8, INVENTORY_ITEM_SIZE, 8, 1, true, RGB(255, 0, 255));


	for (int k = 0; k < 7; k++)
	{
		StoreList[k] = new Image;
		StoreList[k]->Init("Image/storelist.bmp", STORESIZE_X, STORESIZE_Y * 7, 1, 7, true, RGB(255, 0, 255));

		rcStoreList[k].left = 130;
		rcStoreList[k].top = 150 + (STORESIZE_Y * k);
		rcStoreList[k].right = rcStoreList[k].left + STORESIZE_X;
		rcStoreList[k].bottom = rcStoreList[k].top + STORESIZE_Y;
	}

	for (int i = 0; i < INVEN_Y; i++)
	{
		for (int j = 0; j < INVEN_X; j++)
		{
			invenInfo[i][j].rcInven.left = 156 + INVEN_SIZE * j;
			invenInfo[i][j].rcInven.top = 465 + INVEN_SIZE * i;
			invenInfo[i][j].rcInven.right = invenInfo[i][j].rcInven.left + INVEN_SIZE;
			invenInfo[i][j].rcInven.bottom = invenInfo[i][j].rcInven.top + INVEN_SIZE;
		}
	}

	rcUp.left = WINSIZE_X - 150;
	rcUp.top = WINSIZE_Y / 2 - 250;
	rcUp.right = rcUp.left + ICONSIZE;
	rcUp.bottom = rcUp.top + ICONSIZE;

	rcDown.left = WINSIZE_X - 150;
	rcDown.top = WINSIZE_Y / 2 - 130;
	rcDown.right = rcDown.left + ICONSIZE;
	rcDown.bottom = rcDown.top + ICONSIZE;

	rcMouseIn.left = 130;
	rcMouseIn.top = 150;
	rcMouseIn.right = rcMouseIn.left + STORESIZE_X;
	rcMouseIn.bottom = rcMouseIn.top + (STORESIZE_Y * 3);

	selectPos = { -100, 100 };
	storeTile = { 0, 0 };

	maxListSize = 3;
	listItem = 0;
	selectItem = 0;

	isMouseIn = false;
	isBreak = false;

	for (int i = 0; i < INVEN_Y; i++)
	{
		vInvenToryInfo.resize(INVEN_Y);
		for (int j = 0; j < INVEN_X; j++)
		{
			INVEN_INFO info;
			info.glowDay = 0;
			info.price = 0;
			info.rcInven = RECT{ 
				invenInfo[i][j].rcInven.left = 156 + INVEN_SIZE * j,
				invenInfo[i][j].rcInven.top = 465 + INVEN_SIZE * i,
				invenInfo[i][j].rcInven.right = invenInfo[i][j].rcInven.left + INVEN_SIZE,
				invenInfo[i][j].rcInven.bottom = invenInfo[i][j].rcInven.top + INVEN_SIZE
				};

			info.invenType = BLANK;
			vInvenToryInfo[i].push_back(info);
		}
	}
	
	return S_OK;
}

void InvenScene::Release()
{
}

void InvenScene::Update()
{
	store.x = g_ptMouse.x - invenInfo[0][0].rcInven.left;
	store.y = g_ptMouse.y - invenInfo[0][0].rcInven.top;
	storeTile.x = (store.x / INVEN_SIZE);
	storeTile.y = (store.y / INVEN_SIZE);

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		ClickIcon();

		if (storeTile.x == 12 && storeTile.y == 0)
		{
			SceneManager::GetSingleton()->ChangeScene("»óÁ¡¾À", "·Îµù¾À_1");
		}

		for (int k = 0; k < maxListSize; k++)
		{
			if (g_ptMouse.x >= rcStoreList[k].left && g_ptMouse.x <= rcStoreList[k].right &&
				g_ptMouse.y >= rcStoreList[k].top && g_ptMouse.y <= rcStoreList[k].bottom)
			{
				selectItem = listItem + k;

				for (int i = 0; i < INVEN_Y; i++)
				{
					for (int j = 0; j < INVEN_X; j++)
					{
						if (vInvenToryInfo[i][j].invenType == BLANK)
						{
							switch (selectItem + 1)
							{
							case AXE: case HOE: case WATERING:
								if (Clock::GetSingleton()->GetCurrentGold() >= 100)
								{
									Clock::GetSingleton()->SetCurrentGold(Clock::GetSingleton()->GetCurrentGold() - 100);
									vInvenToryInfo[i][j].invenType = (INVENTYPE)(selectItem + 1);
								}
								break;

							case EGGPLANT:
								if (Clock::GetSingleton()->GetCurrentGold() >= 1000)
								{
									Clock::GetSingleton()->SetCurrentGold(Clock::GetSingleton()->GetCurrentGold() - 1000);
									vInvenToryInfo[i][j].invenType = (INVENTYPE)(selectItem + 1);
								}
								break;

							case PEPPER:
								if (Clock::GetSingleton()->GetCurrentGold() >= 2500)
								{
									Clock::GetSingleton()->SetCurrentGold(Clock::GetSingleton()->GetCurrentGold() - 2500);
									vInvenToryInfo[i][j].invenType = (INVENTYPE)(selectItem + 1);
								}
								break;

							case PEACH:
								if (Clock::GetSingleton()->GetCurrentGold() >= 5000)
								{
									Clock::GetSingleton()->SetCurrentGold(Clock::GetSingleton()->GetCurrentGold() - 5000);
									vInvenToryInfo[i][j].invenType = (INVENTYPE)(selectItem + 1);
								}
								break;

							case TICKET:
								if (Clock::GetSingleton()->GetCurrentGold() >= 10000)
								{
									Clock::GetSingleton()->SetCurrentGold(Clock::GetSingleton()->GetCurrentGold() - 10000);
									vInvenToryInfo[i][j].invenType = (INVENTYPE)(selectItem + 1);
								}
								break;

							}
							SmallInven::GetSingleton()->SetInputItemType(vInvenToryInfo[0][j], j);
							isBreak = true;
							break;
						}
					}
					if (isBreak) break;
				}
				isBreak = false;
			}
		}
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RBUTTON))
	{
		vInvenToryInfo[storeTile.y][storeTile.x].invenType = BLANK;
		SmallInven::GetSingleton()->SetInputItemType(vInvenToryInfo[0][storeTile.x], storeTile.x);
	}

	for (int k = 0; k < maxListSize; k++)
	{
		if (g_ptMouse.x >= rcStoreList[k].left && g_ptMouse.x <= rcStoreList[k].right &&
			g_ptMouse.y >= rcStoreList[k].top && g_ptMouse.y <= rcStoreList[k].bottom)
		{
			selectItem = listItem + k;
		}
	}

	if (g_ptMouse.x >= rcMouseIn.left && g_ptMouse.x <= rcMouseIn.right &&
		g_ptMouse.y >= rcMouseIn.top && g_ptMouse.y <= rcMouseIn.bottom)
	{
		isMouseIn = true;
	}
	else
	{
		isMouseIn = false;
	}
	
	selectPos.x = 188 + (INVEN_SIZE * storeTile.x);
	selectPos.y = 496 + (INVEN_SIZE * storeTile.y);
}

void InvenScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	if (InvenBg)
	{
		InvenBg->Render(hdc, WINSIZE_X / 2 - 30, WINSIZE_Y / 2 + 150, true);
	}
	if (ISelectImg)
	{
		if (storeTile.x >= 0 && storeTile.x < 12 &&
			storeTile.y >= 0 && storeTile.y < 3)
		{
			ISelectImg->Render(hdc, selectPos.x, selectPos.y, true);
		}
	}
	if (ExitIcon)
	{
		ExitIcon->Render(hdc, WINSIZE_X - 150, WINSIZE_Y / 2 + 50, false);
	}

	if (StoreList)
	{
		for (int i = 0; i < maxListSize; i++)
		{
			StoreList[i]->FrameRender(hdc, 130, 150 + (78 * i), 0, listItem + i, false, 1);
		}
	}

	if (UpIcon)
	{
		UpIcon->Render(hdc, rcUp.left, rcUp.top, false);
	}
	if (DownIcon)
	{
		DownIcon->Render(hdc, rcDown.left, rcDown.top, false);
	}

	if (itemInfoStatus && isMouseIn)
	{
		itemInfoStatus->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, selectItem, 0, false, 1);
	}

	if (InventoryItem)
	{
		for (int i = 0; i < INVEN_Y; i++)
		{
			for (int j = 0; j < INVEN_X; j++)
			{
				InventoryItem->FrameRender(hdc, vInvenToryInfo[i][j].rcInven.left, vInvenToryInfo[i][j].rcInven.top, vInvenToryInfo[i][j].invenType, 0, false, 3);
			}
		}
	}

	//wsprintf(szText, "x = %d, y = %d", g_ptMouse.x, g_ptMouse.y);
	//TextOut(hdc, WINSIZE_X - 220, 310, szText, strlen(szText));
	//wsprintf(szText, "store = %d, store = %d", store.x, store.y);
	//TextOut(hdc, WINSIZE_X - 220, 330, szText, strlen(szText));
	//wsprintf(szText, "storeTile = %d, storeTile = %d", storeTile.x, storeTile.y);
	//TextOut(hdc, WINSIZE_X - 220, 350, szText, strlen(szText));
	//
	//wsprintf(szText, "selectItem = %d", selectItem);
	//TextOut(hdc, WINSIZE_X - 220, 400, szText, strlen(szText));
}

void InvenScene::ClickIcon()
{
	if (g_ptMouse.x >= rcUp.left && g_ptMouse.x <= rcUp.right &&
		g_ptMouse.y >= rcUp.top && g_ptMouse.y <= rcUp.bottom)
	{
		if (listItem > 0) listItem -= 1;
		else listItem;
	}

	if (g_ptMouse.x >= rcDown.left && g_ptMouse.x <= rcDown.right &&
		g_ptMouse.y >= rcDown.top && g_ptMouse.y <= rcDown.bottom)
	{
		if (listItem < maxListSize + 1) listItem += 1;
		else listItem;
	}
}
