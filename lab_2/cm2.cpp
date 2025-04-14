// cm2.cpp : Определяет точку входа для приложения.
//


#include "framework.h"
#include "cm2.h"

#define MAX_LOADSTRING 100

HBITMAP background = (HBITMAP)LoadImage(NULL, L"background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP rocket[5] = { (HBITMAP)LoadImage(NULL, L"move_rocket_1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"move_rocket_2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"move_rocket_3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"move_rocket_4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"move_rocket_5.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE) };

HBITMAP move_demon[18] = { (HBITMAP)LoadImage(NULL, L"demon_1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_5.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_6.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_7.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_8.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_9.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_10.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_11.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_12.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_13.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_14.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_15.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_16.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_17.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
                     (HBITMAP)LoadImage(NULL, L"demon_18.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)
};

void rokect_animation(HDC memdc, HDC hdc, HWND hWnd);
void demon_animation(HDC memdc, HDC hdc, HWND hWnd);

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного 
PAINTSTRUCT ps;
HDC hdc;
HDC memdc;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CM2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CM2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CM2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CM2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            memdc = CreateCompatibleDC(hdc);
            
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            rokect_animation(memdc, hdc, hWnd);
            
            RECT rect;
            GetClientRect(hWnd, &rect);
            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

            demon_animation(memdc, hdc, hWnd);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        DeleteObject(background);
        DeleteObject(rocket);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void rokect_animation(HDC memdc, HDC hdc, HWND hWnd) {
    const int ROCKET_W = 95;
    const int ROCKET_H = 146;
    const int SPEED = 5;
    const int FRAMES = 5;
    const int LEFT_MARGIN = 10;

    RECT rect;
    GetClientRect(hWnd, &rect);

    int x = LEFT_MARGIN;
    int y = rect.bottom - ROCKET_H;

    for (int frame = 0; y > -ROCKET_H; frame++) {
        SelectObject(memdc, background);
        BitBlt(hdc, 0, 0, rect.right, rect.bottom, memdc, 0, 0, SRCCOPY);

        SelectObject(memdc, rocket[frame % FRAMES]);
        BitBlt(hdc, x, y, ROCKET_W, ROCKET_H, memdc, 0, 0, SRCCOPY);

        y -= SPEED;

        Sleep(50);
    }

    SelectObject(memdc, background);
    BitBlt(hdc, 0, 0, rect.right, rect.bottom, memdc, 0, 0, SRCCOPY);
}

void demon_animation(HDC memdc, HDC hdc, HWND hWnd) {
    int i = 0;
    while (true) {
        SelectObject(memdc, move_demon[i]);
        BitBlt(hdc, 0, 0, 360, 360, memdc, 0, 0, SRCCOPY);
        Sleep(100);
        i++;
        if (i == 19) i = 0;
    }
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
