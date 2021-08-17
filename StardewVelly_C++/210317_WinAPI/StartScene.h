#pragma once
#include "GameNode.h"

class Button;
class Image;
class StartScene : public GameNode
{
private:
	Image* startBG;
	Image* startLogo;

	Button* newBt;
	Button* loadBt;
	Button* coopBt;
	Button* exitBt;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static void SetChangeScene(int key);

	virtual ~StartScene() {};
};

