#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"

HRESULT Enemy::Init(int posX, int posY)
{
    image = ImageManager::GetSingleton()->FindImage("Enemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, 
            "Enemy�� �ش��ϴ� �̹����� �߰����� �ʾ���!", "���", MB_OK);
        return E_FAIL;
    }

    currFrameX = 0;
    updateCount = 0;

    pos.x =  posX;
    pos.y = posY;
    size = 80;
    name = "NormalEnemy";
    shape = { 0, 0, 0, 0 };
    moveSpeed = 3.3f;
    isAlive = true;
    angle = 0.0f;
    target = nullptr;
    dir = 1;

    fireCount = 0;

    return S_OK;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
    if (isAlive)
    {
        //HorizonMove();
        //Move();

        // �ִϸ��̼� ������
        updateCount++;
        if (updateCount == 5)
        {
            currFrameX++;
            if (currFrameX >= 10)
            {
                currFrameX = 0;
            }

            updateCount = 0;
        }

    }
}

void Enemy::Render(HDC hdc)
{
    if (isAlive)
    {
        RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);

        if (image)
        {
            image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
        }
    }
}

void Enemy::Move()
{

}

void Enemy::HorizonMove()
{
    if (pos.x > WINSIZE_X || pos.x < 0)
    {
        dir *= -1;
    }
    pos.x += moveSpeed * dir;
}
