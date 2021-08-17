#include "Clock.h"
#include "Image.h"
#include "Energy.h"

HRESULT Clock::Init()
{
	ClockImg = new Image();
	ClockImg->Init("Image/clock/UIClock.bmp", 71 * 3, 59 * 3, true, RGB(255, 0, 255));

	ClockInit();
	GoldInit();

	hourHandKey = 0;
	hourHandValue = Hnum10 * 10 + Hnum1;

	dayCount = 0;

	return E_NOTIMPL;
}

void Clock::Release()
{
	SAFE_RELEASE(ClockImg);
	ClockRelease();
	GoldRelease();
}

void Clock::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD9))
	{
		currentGold += 1;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('Q'))
	{
		Mnum1 += 1;
	}

	hourHandKey = 0;
	hourHandValue = Hnum10 * 10 + Hnum1;

	ClockCount();
	GoldCount();
}

void Clock::Render(HDC hdc)
{
	if (ClockImg)
	{
		ClockImg->Render(hdc, WINSIZE_X - (71 * 3), 0, false);
	}
	if (DayFontImg)
	{
		DayFontImg->Render(hdc, WINSIZE_X - 130, 15, false);
	}

	ClockImageRender(hdc);
	GoldImageRender(hdc);

	//wsprintf(szText, "%d", TimerManager::GetSingleton()->GetElapsedTime());
	//TextOut(hdc, 120, 250, szText, strlen(szText));
	//wsprintf(szText, "%d", TimerManager::GetSingleton()->GetCurrTime());
	//TextOut(hdc, 120, 280, szText, strlen(szText));
	//wsprintf(szText, "%d, %d", clockCounting, clockCount);
	//TextOut(hdc, 120, 310, szText, strlen(szText));
	//wsprintf(szText, "%d", TimerManager::GetSingleton()->GetClockCount());
	//TextOut(hdc, 120, 340, szText, strlen(szText));
	//
	//wsprintf(szText, "%d, %d, %d, %d, %d", G_10000, G_1000, G_100, G_10, G_1);
	//TextOut(hdc, 120, 380, szText, strlen(szText));
}

void Clock::ClockInit()
{
	DayFontImg = new Image();
	DayFontImg->Init("Image/clock/Font_Day.bmp", 24 * 2, 12 * 2, true, RGB(255, 0, 255));

	HourHand = new Image();
	HourHand->Init("Image/clock/hourhand.bmp", 95, 38, 5, 1, true, RGB(255, 0, 255));	//95 * 38

	DayNumImg_1 = new Image();
	DayNumImg_1->Init("Image/clock/font_num.bmp", 80, 11, 10, 1, true, RGB(255, 0, 255));

	DayNumImg_10 = new Image();
	DayNumImg_10->Init("Image/clock/font_num.bmp", 80, 11, 10, 1, true, RGB(255, 0, 255));

	HourNumImg_1 = new Image();
	HourNumImg_1->Init("Image/clock/font_num.bmp", 80, 11, 10, 1, true, RGB(255, 0, 255));

	HourNumImg_10 = new Image();
	HourNumImg_10->Init("Image/clock/font_num.bmp", 80, 11, 10, 1, true, RGB(255, 0, 255));

	MinNumImg_1 = new Image();
	MinNumImg_1->Init("Image/clock/font_num.bmp", 80, 11, 10, 1, true, RGB(255, 0, 255));

	MinNumImg_10 = new Image();
	MinNumImg_10->Init("Image/clock/font_num.bmp", 80, 11, 10, 1, true, RGB(255, 0, 255));
	
	hourHandKey = 0;

	Dnum1 = 1;
	Dnum10 = 0;

	Hnum1 = 5;
	Hnum10 = 0;

	Mnum1 = 0;
	Mnum10 = 0;

	clockCounting = 0;
	dayCount = 0;

	IsDayLater = false;
}

void Clock::ClockRelease()
{
	SAFE_RELEASE(DayFontImg);
	SAFE_RELEASE(HourHand);
	SAFE_RELEASE(DayNumImg_1);
	SAFE_RELEASE(DayNumImg_10);
	SAFE_RELEASE(HourNumImg_1);
	SAFE_RELEASE(HourNumImg_10);
	SAFE_RELEASE(MinNumImg_1);
	SAFE_RELEASE(MinNumImg_10);
}

void Clock::ClockCount()
{
	// clock count
	if (hourHandValue < 6)  hourHandKey = 0;
	else if (hourHandValue >= 6 && hourHandValue < 12)  hourHandKey = 1;
	else if (hourHandValue >= 12 && hourHandValue < 18)  hourHandKey = 2;
	else if (hourHandValue >= 18 && hourHandValue < 23)  hourHandKey = 3;
	else if (hourHandValue >= 23) hourHandKey = 4;

	// timecount
	// 시간을 고쳐야해
	
	if (TimerManager::GetSingleton()->GetClockCount())
	{
		clockCounting++;
	}
	if (clockCounting / 500 == 1)
	{
		Mnum1 += 5;
		clockCounting = 0;
	}
	if (Mnum1 > 9)
	{
		Mnum1 = 0;
		Mnum10++;
	}
	if (Mnum10 > 5)
	{
		Mnum10 = 0;
		Hnum1++;
	}
	if (Hnum1 > 9)
	{
		Hnum1 = 0;
		Hnum10++;
	}
	if (Hnum10 > 1 && Hnum1 > 3)
	{
		Hnum10 = 0;
		Hnum1 = 0;
		Dnum1++;
		//IsDayLater = true;
		Energy::GetSingleton()->SetResetEnergy(true);
	}
	else if (Hnum10 == 0 && Hnum1 == 5 && Mnum10 == 0 && Mnum1 == 5 && clockCounting == 0)
	{
		IsDayLater = true;
	}
	else
	{
		IsDayLater = false;
	}
	if (Dnum1 > 9)
	{
		Dnum1 = 0;
		Dnum10++;
		if (Dnum10 > 9)
		{
			Dnum10 = 9;
			Dnum1 = 9;
		}
	}
}

void Clock::ClockReset()
{
	Dnum1++;
	Hnum1 = 5;
	Hnum10 = 0;

	Mnum1 = 0;
	Mnum10 = 0;

	clockCounting = 0;
}

void Clock::ClockImageRender(HDC hdc)
{
	if (HourHand)
	{
		HourHand->FrameRender(hdc, WINSIZE_X - 190, 5, hourHandKey, 0, false, 3);
	}

	if (DayNumImg_10)
	{
		DayNumImg_10->FrameRender(hdc, WINSIZE_X - 60, 15, Dnum10, 0, false, 2);
	}
	if (DayNumImg_1)
	{
		DayNumImg_1->FrameRender(hdc, WINSIZE_X - 40, 15, Dnum1, 0, false, 2);
	}

	if (HourNumImg_10)
	{
		HourNumImg_10->FrameRender(hdc, WINSIZE_X - 120, 85, Hnum10, 0, false, 2);
	}
	if (HourNumImg_1)
	{
		HourNumImg_1->FrameRender(hdc, WINSIZE_X - 100, 85, Hnum1, 0, false, 2);
	}

	if (MinNumImg_10)
	{
		MinNumImg_10->FrameRender(hdc, WINSIZE_X - 60, 85, Mnum10, 0, false, 2);
	}
	if (MinNumImg_1)
	{
		MinNumImg_1->FrameRender(hdc, WINSIZE_X - 40, 85, Mnum1, 0, false, 2);
	}
}

void Clock::GoldInit()
{
	Gimg_1 = new Image();
	Gimg_1->Init("Image/clock/font_num.bmp", 80, 11, 10, 1, true, RGB(255, 0, 255));
	Gimg_10 = new Image();
	Gimg_10->Init("Image/clock/font_num.bmp", 80, 11, 10, 1, true, RGB(255, 0, 255));
	Gimg_100 = new Image();
	Gimg_100->Init("Image/clock/font_num.bmp", 80, 11, 10, 1, true, RGB(255, 0, 255));
	Gimg_1000 = new Image();
	Gimg_1000->Init("Image/clock/font_num.bmp", 80, 11, 10, 1, true, RGB(255, 0, 255));
	Gimg_10000 = new Image();
	Gimg_10000->Init("Image/clock/font_num.bmp", 80, 11, 10, 1, true, RGB(255, 0, 255));

	currentGold = 25000;

	G_1 = 0;
	G_10 = 0;
	G_100 = 0;
	G_1000 = 1;
	G_10000 = 0;
}

void Clock::GoldRelease()
{
	SAFE_RELEASE(Gimg_10000);
	SAFE_RELEASE(Gimg_1000);
	SAFE_RELEASE(Gimg_100);
	SAFE_RELEASE(Gimg_10);
	SAFE_RELEASE(Gimg_1);
}

void Clock::GoldCount()
{
	G_10000 = currentGold / 10000;
	G_1000 = (currentGold % 10000) / 1000;
	G_100 = (currentGold % 1000) / 100;
	G_10 = (currentGold % 100) / 10;
	G_1 = (currentGold % 10);

	if (G_1 > 9)
	{
		G_1 = 0;
		G_10++;	
	}
	if (G_10 > 9)
	{
		G_10 = 0;
		G_100++;
	}
	if (G_100 > 9)
	{
		G_100 = 0;
		G_1000++;
	}
	if (G_1000 > 9)
	{
		G_1000 = 0;
		G_10000++;
	}
	if (G_10000 > 9)
	{
		G_1 = 9;
		G_10 = 9;
		G_100 = 9;
		G_1000 = 9;
		G_10000 = 9;
	}
	if (G_10000 < 0)
	{
		G_10000 = - 1;
	}
}

void Clock::GoldImageRender(HDC hdc)
{
	if (Gimg_1)
	{
		Gimg_1->FrameRender(hdc, WINSIZE_X - 36, 145, G_1, 0, false, 2);  // x - 18
	}
	if (Gimg_10)
	{
		Gimg_10->FrameRender(hdc, WINSIZE_X - 54, 145, G_10, 0, false, 2);
	}
	if (Gimg_100)
	{
		Gimg_100->FrameRender(hdc, WINSIZE_X - 72, 145, G_100, 0, false, 2);
	}
	if (Gimg_1000)
	{
		Gimg_1000->FrameRender(hdc, WINSIZE_X - 90, 145, G_1000, 0, false, 2);
	}
	if (Gimg_10000)
	{
		Gimg_10000->FrameRender(hdc, WINSIZE_X - 108, 145, G_10000, 0, false, 2);
	}
}

