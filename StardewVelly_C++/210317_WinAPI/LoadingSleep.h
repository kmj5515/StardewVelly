#pragma once
#include "GameNode.h"

class Image;
class LoadingSleep : public GameNode
{
private:
	Image* LoadingSleepImg;

public:
	virtual HRESULT Init();
	virtual	void Release();
	virtual	void Update();
	virtual	void Render(HDC hdc);

	virtual ~LoadingSleep() {};
};