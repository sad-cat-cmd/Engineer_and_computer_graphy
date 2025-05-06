// WindowsProject1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

double movex = 0, movey = 0, scale = 0.6;
double cre_s = -2, cre_f = 2, cim_s = -2, cim_f = 2;
int scr_x = 500, scr_y = 500;

RECT clientRect;
void ComplexPower8(double& z, double& iz)
{
    double z2 = z * z - iz * iz;       // z^2
    double iz2 = 2 * z * iz;           // iz^2

    double z4 = z2 * z2 - iz2 * iz2;   // z^4
    double iz4 = 2 * z2 * iz2;         // iz^4

    double z8 = z4 * z4 - iz4 * iz4;   // z^8
    double iz8 = 2 * z4 * iz4;         // iz^8

    z = z8;
    iz = iz8;
}
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
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
   CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

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
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
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
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case WM_SIZE:
        {
            GetClientRect(hWnd, &clientRect);
            scr_x = clientRect.right - clientRect.left;
            scr_y = clientRect.bottom - clientRect.top;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case VK_ESCAPE:
        {
            DestroyWindow(hWnd);
            break;
        }
        case VK_NUMPAD8: {
            movey -= (0.05 / scale);
            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;
        }
        case VK_NUMPAD2: {
            movey += (0.05 / scale);
            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;
        }
        case VK_NUMPAD6: {
            movex += (0.05 / scale);
            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;
        }
        case VK_NUMPAD4: {
            movex -= (0.05 / scale);
            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;
        }
        case VK_NUMPAD5: {
            movex = 0;
            movey = 0;
            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;
        }
        case VK_ADD:
        {
            scale /= 1.5;
            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;
        }
        case VK_SUBTRACT:
        {
            scale *= 1.5;
            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;
        }
        }
        break;
    case WM_PAINT:
        {
        hdc = BeginPaint(hWnd, &ps);
        double step_x = (cre_f - cre_s) / scr_x;
        double step_y = (cim_f - cim_s) / scr_y;
        double c, ic;
        for (int x = 0; x < scr_x; ++x) {
            c = (cre_s + step_x * x + movex) * scale;
            for (int y = 0; y < scr_y; ++y) {
                ic = (cim_s + step_y * y + movey) * scale;
                double z = 0;
                double iz = 0;
                int i = 0;

                while (i < 255) {
                    ComplexPower8(z, iz);  // z = z^8
                    z += c;               // z = z^8 + c
                    iz += ic;             // iz = iz^8 + ic

                    i++;
                    if ((z * z + iz * iz) > 4)
                        break;
                }
                if (i < 255) {
                    float r = (i * 9) % 255;
                    float g = (i * 3) % 255;
                    float b = (i * 8) % 255;
                    SetPixel(hdc, x, y, RGB(r, g, b));
                }
                else
                    SetPixel(hdc, x, y, RGB(0, 0, 0));
            }
        }
        EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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
