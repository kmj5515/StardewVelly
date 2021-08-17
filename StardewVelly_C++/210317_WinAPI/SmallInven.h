#pragma once
#include "config.h"
#include "Singleton.h"

#define INVENTORY_ITEM_SIZE 22
#define INVEN_INFO_SIZE 12

class Image;
class SmallInven : public Singleton<SmallInven>
{
private:
	Image* SInvenImg;
	Image* SelectImg;
	Image* ItemImg;

	INVEN_INFO invenItem[INVEN_INFO_SIZE];
	vector<vector<INVEN_INFO>>* vInvenToryInfo;

	int selectX;
	bool haveTicket;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	inline void SetInputItemType(INVEN_INFO info, int index) { this->invenItem[index] = info; }

	inline INVEN_INFO GetInputItemType() { return this->invenItem[selectX]; }

	inline void SetHaveTicket(bool haveTicket) { this->haveTicket = haveTicket; }
	inline bool GetHaveTicket() { return this->haveTicket; }

	virtual ~SmallInven() {};
};

