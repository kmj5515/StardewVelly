#include "TalkScene.h"
#include "Image.h"
#include "Clock.h"

HRESULT TalkScene::Init()
{
    talkBoxImg = new Image();
    talkBoxImg->Init("Image/TalkBox.bmp", 743, 254, true, RGB(255, 0, 255));

    exitIconImg = new Image();
    exitIconImg->Init("Image/exitIcon.bmp", INVEN_SIZE, INVEN_SIZE, true, RGB(255, 0, 255));

    rcExitIcon.left = WINSIZE_X - 120;
    rcExitIcon.top = WINSIZE_Y / 2 + 80;
    rcExitIcon.right = rcExitIcon.left + INVEN_SIZE;
    rcExitIcon.bottom = rcExitIcon.top + INVEN_SIZE;

    return S_OK;
}

void TalkScene::Release()
{
}

void TalkScene::Update()
{
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
    {
        if (g_ptMouse.x >= rcExitIcon.left && g_ptMouse.x <= rcExitIcon.right &&
            g_ptMouse.y >= rcExitIcon.top && g_ptMouse.y <= rcExitIcon.bottom)
        {
            SceneManager::GetSingleton()->ChangeScene("MyHome");
        }
    }
}

void TalkScene::Render(HDC hdc)
{
    if (talkBoxImg)
    {
        talkBoxImg->Render(hdc, WINSIZE_X / 2, WINSIZE_Y * 4 / 5 - 30, true);
    }

    if (exitIconImg)
    {
        exitIconImg->Render(hdc, WINSIZE_X - 120, WINSIZE_Y / 2 + 80, false);
    }
}
