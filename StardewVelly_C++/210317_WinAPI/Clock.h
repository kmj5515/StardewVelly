#pragma once
#include "config.h"
#include "Singleton.h"

class Image;
class Clock : public Singleton<Clock>
{
private:
	// CLOCK UI
	Image* ClockImg;
	Image* DayFontImg;

	Image* HourHand;

	Image* DayNumImg_1;
	Image* DayNumImg_10;

	Image* HourNumImg_1;
	Image* HourNumImg_10;

	Image* MinNumImg_1;
	Image* MinNumImg_10;

	int hourHandKey;
	int hourHandValue;

	int Dnum1;
	int Dnum10;

	int Hnum1;
	int Hnum10;

	int Mnum1;
	int Mnum10;

	float clockCount;
	int clockCounting;

	// GOLD UI
	Image* Gimg_1;
	Image* Gimg_10;
	Image* Gimg_100;
	Image* Gimg_1000;
	Image* Gimg_10000;

	int G_1;
	int G_10;
	int G_100;
	int G_1000;
	int G_10000;

	bool IsStopTime;
	bool IsDayLater;
	int dayCount;

	int currentGold;
 
	char szText[128] = "";
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void ClockInit();
	void ClockRelease();
	void ClockCount();
	void ClockReset();
	void ClockImageRender(HDC hdc);

	void GoldInit();
	void GoldRelease();
	void GoldCount();
	void GoldImageRender(HDC hdc);

	inline void SetCurrentGold(int currentGold) { this->currentGold = currentGold; }
	inline int GetCurrentGold() { return this->currentGold; }

	inline void SetIsDayLater(bool IsDayLater) { this->IsDayLater = IsDayLater; }
	inline bool GetIsDayLater() { return this->IsDayLater; }

	inline void SetDayCount(int dayCount) { this->dayCount = dayCount; }
	inline int GetDayCount() { return this->dayCount; }

	virtual ~Clock() {};
};

