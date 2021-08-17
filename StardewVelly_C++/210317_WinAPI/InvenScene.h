#pragma once
#include "GameNode.h"
#include <Vector>

#define STORESIZE_X 796
#define STORESIZE_Y 78

#define ICONSIZE 88

#define INVENTORY_ITEM_SIZE 22

class PlayerShip;
class Image;
class InvenScene : public GameNode
{
private:
	Image* InvenBg;
	Image* ExitIcon;
	Image* ISelectImg;
	Image* StoreList[7];
	Image* itemInfoStatus;
	Image* InventoryItem;

	Image* UpIcon;
	Image* DownIcon;

	RECT rcMouseIn;
	RECT rcStoreList[7];

	RECT rcUp;
	RECT rcDown;

	POINT selectPos;
	POINT store;
	POINT storeTile;

	INVEN_INFO invenInfo[STORESIZE_Y][STORESIZE_X];
	vector<vector<INVEN_INFO>> vInvenToryInfo;

	char szText[128] = "";

	int maxListSize;
	int listItem;
	int selectItem;

	bool isMouseIn;
	bool isBreak;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void ClickIcon();
	inline vector<vector<INVEN_INFO>>* GetInven() {return &vInvenToryInfo;}

	virtual ~InvenScene() {};
};