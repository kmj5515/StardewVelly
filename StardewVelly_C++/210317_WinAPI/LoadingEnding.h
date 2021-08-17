#pragma once
#include "GameNode.h"

class Image;
class LoadingEnding : public GameNode
{
private:
	Image* LoadingEndingImg;

public:
	virtual HRESULT Init();
	virtual	void Release();
	virtual	void Update();
	virtual	void Render(HDC hdc);

	virtual ~LoadingEnding() {};
};