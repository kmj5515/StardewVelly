#pragma once
#include "GameNode.h"

class Image;
class TalkScene : public GameNode
{
private:
	Image* talkBoxImg;
	Image* exitIconImg;

	RECT rcExitIcon;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~TalkScene() {};
};

