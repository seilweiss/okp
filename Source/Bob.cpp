#include <windows.h>
#include <stdio.h>
#include <string.h>

int dword_4E1CFC;

HWND hWnd;
char Str[32];
HINSTANCE hInstance;
DWORD dword_4E1E50;
DWORD dword_4E1E54;
HWND dword_4E1E64;

LRESULT WINAPI sub_405B3E(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // STUB
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void sub_40861D(const char*, ...);
void sub_408622(const char*, ...);
void sub_40862C();

int sub_406232(HINSTANCE hInstance, int nShowCmd)
{
    ::hInstance = hInstance;

    WNDCLASS WndClass;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = sub_405B3E;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(105));
    WndClass.hCursor = NULL;
    WndClass.hbrBackground = NULL;
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = "SpongeBob";

    if (!RegisterClass(&WndClass))
    {
        return 0;
    }

    hWnd = CreateWindowEx(
        WS_EX_TOPMOST,
        "SpongeBob",
        "SpongeBob SquarePants",
        WS_POPUP | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        640,
        480,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        return 0;
    }

    HDC hdc = GetDC(hWnd);
    int v4 = GetDeviceCaps(hdc, NUMCOLORS);

    if (v4 > -1 && v4 <= 16)
    {
        char Caption[80];
        sprintf(Caption, "DETECTED %d COLORS", v4);
        MessageBox(NULL, "MUST BE IN 256 COLOR OR HIGHER MODE", Caption, MB_OK);

        return 0;
    }

    CloseWindow(hWnd);
    dword_4E1CFC = 1;
    return 1;
}

INT_PTR WINAPI DialogFunc(HWND hWnd, UINT a2, WPARAM a3, LPARAM a4)
{
    // STUB
    return FALSE;
}

void MainLoop()
{
    // STUB
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    if (CreateMutex(NULL, TRUE, "SpongeBobSquarePants") == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
    {
        return 0;
    }

    remove("debug.log");
    sub_408622("WinMain()");

    dword_4E1E50 = GetTickCount();

    char v10[] = { 'd', 'e', 'v', 'm', 'o', 'd', 'e', '\0' };
    char* String = _strdup(lpCmdLine);
    _strlwr(String);

    if (!sub_406232(hInstance, nShowCmd))
    {
        sub_40862C();
        return 0;
    }

    memset(Str, 0, sizeof(Str));

    DWORD v14 = GetLogicalDrives();
    int v9 = 1;

    for (unsigned int i = 0; i < 32; i++)
    {
        if (v9 & v14)
        {
            char RootPathName[8];
            sprintf(RootPathName, "%c:\\", i + 'A');

            if (GetDriveType(RootPathName) == DRIVE_CDROM)
            {
                char FileName[32];

                strcpy(Str, RootPathName);
                sprintf(FileName, "%sbob.ico", Str);

                OFSTRUCT ReOpenBuff;

                if (OpenFile(FileName, &ReOpenBuff, OF_EXIST) == HFILE_ERROR)
                {
                    strcpy(Str, "");
                }
                else
                {
                    break;
                }
            }
        }

        v9 <<= 1;
    }

    if (strlen(Str) == 0)
    {
        dword_4E1E64 = CreateDialogParam(::hInstance, MAKEINTRESOURCE(106), hWnd, DialogFunc, NULL);
    }

    MainLoop();

    if (dword_4E1E54)
    {
        char Buffer[256];
        LoadString((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 10153, Buffer, sizeof(Buffer));
        ShowWindow(hWnd, SW_HIDE);
        MessageBox(NULL, Buffer, "SpongeBob SquarePants", MB_OK);
    }

    sub_40861D("DestroyWindow()");
    DestroyWindow(hWnd);
    sub_40861D("DestroyWindow() done");
    sub_40861D("bCDEjected=%d", dword_4E1E54);
    sub_40862C();

    return 0;
}

void sub_40861D(const char*, ...)
{
}

void sub_408622(const char*, ...)
{
}

void sub_40862C()
{
}