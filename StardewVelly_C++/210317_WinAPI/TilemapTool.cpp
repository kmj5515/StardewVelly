#include "TilemapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"

TILE_INFO TilemapTool::tileInfo[TILE_Y][TILE_X];

HRESULT TilemapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);

    sampleTile = ImageManager::GetSingleton()->AddImage(
        "샘플타일1", "Image/SpringFarm1.bmp", 896, 896,
        SAMPLE_TILE_X, SAMPLE_TILE_Y, false, RGB(181,184,182));

    hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

    // 메인 공간 렉트 설정
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            tileInfo[i][j].frameX = j;
            tileInfo[i][j].frameY = i;

            tileInfo[i][j].rcTile.left = TILESIZE * j;
            tileInfo[i][j].rcTile.top = TILESIZE * i;
            tileInfo[i][j].rcTile.right = 
                (tileInfo[i][j].rcTile.left + TILESIZE);
            tileInfo[i][j].rcTile.bottom =
                (tileInfo[i][j].rcTile.top + TILESIZE);
            tileInfo[i][j].tileType = ROAD;
        }
    }

    // 샘플 공간 렉트 설정
    for (int i = 0; i < SAMPLE_TILE_Y; i++)
    {
        for (int j = 0; j < SAMPLE_TILE_X; j++)
        {
            SetRect(&sampleTileInfo[i][j].rcTile,
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j), 
                (TILESIZE * i),
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j) + TILESIZE, 
                (TILESIZE * i) + TILESIZE);

            sampleTileInfo[i][j].frameX = j;
            sampleTileInfo[i][j].frameY = i;
        }
    }

    // UI Button
    ImageManager::GetSingleton()->AddImage("저장버튼", "Image/button.bmp",
        122, 62, 1, 2);
    ImageManager::GetSingleton()->AddImage("불러오기버튼", "Image/button.bmp",
        122, 62, 1, 2);

    btnSave = new Button();
    btnSave->Init("저장버튼", TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
        TILEMAPTOOLSIZE_Y - 100);
    btnSave->SetFunc(Save, 1);

    btnLoad = new Button();
    btnLoad->Init("불러오기버튼", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + 170,
        TILEMAPTOOLSIZE_Y - 100);
    btnLoad->SetFunc(Load, 1);

    return S_OK;
}

void TilemapTool::Release()
{
    SAFE_RELEASE(btnSave);
    SAFE_RELEASE(btnLoad);
}

void TilemapTool::Update()
{
    // 세이브 F1 F2 F3 ...
    //int stageNum = VK_F1;
    //int currInputKey;

    if (btnSave)    btnSave->Update();
    if (btnLoad)    btnLoad->Update();

    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_CONTROL))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            Load(1);
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
        {
            Load(2);
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
        {
            Load(3);
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F4))
        {
            Load(4);
        }
    }
    else
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            Save(1);
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
        {
            Save(2);
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
        {
            Save(3);
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F4))
        {
            Save(4);
        }
    }

    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_BACK))
    {
        SceneManager::GetSingleton()->ChangeScene("시작화면");
    }

    // 메인 영역 계산
    rcMain.left = 0;
    rcMain.top = 0;
    rcMain.right = rcMain.left + (TILESIZE * TILE_X);
    rcMain.bottom = rcMain.top + (TILESIZE * TILE_Y);

    // 샘플 영역 계산
    rcSample.left = TILEMAPTOOLSIZE_X - sampleTile->GetWidth();
    rcSample.top = 0;
    rcSample.right = TILEMAPTOOLSIZE_X;
    rcSample.bottom = sampleTile->GetHeight();

    if (PtInRect(&rcMain, g_ptMouse))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RBUTTON))
        {
            for (int i = 0; i < TILE_Y; i++)
            {
                for (int j = 0; j < TILE_X; j++)
                {
                    if ((ptStartSelectedFrame.x == 0) && (ptStartSelectedFrame.y == 0))
                    {
                        tileInfo[i][j].tileType = TILETYPE::GOTOFARM;
                    }
                }
            }
        }
        // 마우스 왼쪽 버튼 클릭시 좌표 사용
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)
            || KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            for (int i = 0; i < TILE_Y; i++)
            {
                for (int j = 0; j < TILE_X; j++)
                {
                    if (PtInRect(&(tileInfo[i][j].rcTile), g_ptMouse))
                    {
                        tileInfo[i][j].tileType = WALL;
                        //selectedFrameX = i % TILE_X;
                        //selectedFrameY = i / TILE_X;                  

                        tileInfo[i][j].frameX = ptStartSelectedFrame.x;
                        tileInfo[i][j].frameY = ptStartSelectedFrame.y;

                        if ((ptStartSelectedFrame.x == 0) && (ptStartSelectedFrame.y == 0))
                        {
                            tileInfo[i][j].tileType = TILETYPE::WALL;
                        }
                        else if ((ptStartSelectedFrame.x == 1) && (ptStartSelectedFrame.y == 0))
                        {
                            tileInfo[i][j].tileType = TILETYPE::GOTOFARM;
                        }
                        else if ((ptStartSelectedFrame.x == 2) && (ptStartSelectedFrame.y == 0))
                        {
                            tileInfo[i][j].tileType = TILETYPE::GOTOHOME;
                        }
                        else if ((ptStartSelectedFrame.x == 3) && (ptStartSelectedFrame.y == 0))
                        {
                            tileInfo[i][j].tileType = TILETYPE::GOTOSTORE;
                        }
                        else if ((ptStartSelectedFrame.x == 4) && (ptStartSelectedFrame.y == 0))
                        {
                            tileInfo[i][j].tileType = TILETYPE::GOTOBUS;
                        }
                        else if ((ptStartSelectedFrame.x == 5) && (ptStartSelectedFrame.y == 0))
                        {
                            tileInfo[i][j].tileType = TILETYPE::INVENTORYSTORE;
                        }
                        else if ((ptStartSelectedFrame.x == 6) && (ptStartSelectedFrame.y == 0))
                        {
                            tileInfo[i][j].tileType = TILETYPE::BED;
                        }
                        else
                        {
                            tileInfo[i][j].tileType = TILETYPE::ROAD;
                        }

                        int ptSelectFrameY = ptEndSelectedFrame.y - ptStartSelectedFrame.y;
                        int ptSelectFrameX = ptEndSelectedFrame.x - ptStartSelectedFrame.x;                       

                        for (int l = 0; l <= ptSelectFrameY; l++)
                        {
                            for (int k = 0; k <= ptSelectFrameX; k++)
                            {
                                if (j + k >= TILE_X) continue;
                                if (i + l >= TILE_Y) continue;

                                tileInfo[i + l][j + k].frameX = ptStartSelectedFrame.x + k;
                                tileInfo[i + l][j + k].frameY = ptStartSelectedFrame.y + l;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    else if (PtInRect(&rcSample, g_ptMouse))
    {
        // 마우스 왼쪽 버튼 클릭시 좌표 사용
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            // 2) 마우스 좌표로 인덱스 계산
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptStartSelectedFrame.x = posX / TILESIZE;
            ptStartSelectedFrame.y = posY / TILESIZE;

            ptSelected[0] = g_ptMouse;
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
        {
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptEndSelectedFrame.x = posX / TILESIZE;
            ptEndSelectedFrame.y = posY / TILESIZE;

            // 선택영역 초기화
            ptSelected[0].x = -1;
            ptSelected[0].y = -1;
            ptSelected[1].x = -1;
            ptSelected[1].y = -1;
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            ptSelected[1] = g_ptMouse;
        }
    }

}

void TilemapTool::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0,
        TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    // 샘플타일 전체
    sampleTile->Render(hdc, TILEMAPTOOLSIZE_X - (sampleTile->GetWidth()), 0);

    // 선택 영역 표시
    hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);
    Rectangle(hdc, ptSelected[0].x, ptSelected[0].y, ptSelected[1].x, ptSelected[1].y);
    SelectObject(hdc, hOldSelectedBrush);

    // UI Button
    if (btnSave)    btnSave->Render(hdc);
    if (btnLoad)    btnLoad->Render(hdc);

    // 메인영역 전체
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            sampleTile->FrameRender(hdc,
                tileInfo[i][j].rcTile.left,
                tileInfo[i][j].rcTile.top,
                tileInfo[i][j].frameX,
                tileInfo[i][j].frameY
            );

            /*if (tileInfo[i][j].tileType == WALL)
            {
                Rectangle(hdc, tileInfo[i][j].rcTile.left,
                    tileInfo[i][j].rcTile.top,
                    tileInfo[i][j].rcTile.right,
                    tileInfo[i][j].rcTile.bottom);
            }  */
              
            
        }
    }

    // 선택된 타일
    if (ptStartSelectedFrame.x == ptEndSelectedFrame.x &&
        ptStartSelectedFrame.y == ptEndSelectedFrame.y)
    {
        sampleTile->FrameRender(hdc, 
            TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
            sampleTile->GetHeight() + 50, 
            ptStartSelectedFrame.x, ptStartSelectedFrame.y , false, 3);
    }
    else
    {
        for (int i = 0; i <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; i++)
        {
            for (int j = 0; j <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; j++)
            {
                sampleTile->FrameRender(hdc,
                    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (j * TILESIZE),
                    sampleTile->GetHeight() + 50 + (i * TILESIZE),
                    ptStartSelectedFrame.x + j, ptStartSelectedFrame.y + i , false, 1);

            }
        }
    }

    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            if (tileInfo[i][j].tileType == WALL)
            {
                tileTypeNum = 0;
            }   
            else if (tileInfo[i][j].tileType == ROAD)
            {
                tileTypeNum = 1;
            }
            else if (tileInfo[i][j].tileType == GOTOFARM)
            {
                tileTypeNum = 2;
            }
            else if (tileInfo[i][j].tileType == GOTOHOME)
            {
                tileTypeNum = 3;
            }
            else if (tileInfo[i][j].tileType == GOTOSTORE)
            {
                tileTypeNum = 4;
            }
            else if (tileInfo[i][j].tileType == GOTOBUS)
            {
                tileTypeNum = 5;
            }
            else if (tileInfo[i][j].tileType == INVENTORYSTORE)
            {
                tileTypeNum = 6;
            }
            else if (tileInfo[i][j].tileType == BED)
            {
                tileTypeNum = 7;
            }

            wsprintf(szText, "%d", tileTypeNum);
            TextOut(hdc, WINSIZE_X - 120 + (j * 15), 85 + (i * 15), szText, strlen(szText));
        }
    }
   
}

void TilemapTool::Save(int stageNum)
{
    string fileName = "Save/saveMapData";  // 1.map";
    fileName += to_string(stageNum) + ".map";

    DWORD writtenBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0,
        0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
        &writtenBytes, NULL);

    CloseHandle(hFile);
}

void TilemapTool::Load(int stageNum)
{
    string fileName = "Save/saveMapData";  // 1.map";
    fileName += to_string(stageNum) + ".map";

    DWORD readBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0,
        0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
        &readBytes, NULL))
    {
    }
    else
    {
        MessageBox(g_hWnd, "저장파일 로드 실패", "실패", MB_OK);
    }

    CloseHandle(hFile);
}

void TilemapTool::ResetLoad(int stageNuml)
{
    string fileName = "backup/saveMapData";  // 1.map";
    fileName += to_string(stageNuml) + ".map";

    DWORD readBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0,
        0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
        &readBytes, NULL))
    {
    }
    else
    {
        MessageBox(g_hWnd, "저장파일 로드 실패", "실패", MB_OK);
    }

    CloseHandle(hFile);
}