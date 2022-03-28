// F19621327TEST1.cpp : Defines the entry point for the application.
//
// TEST 1 na Mihail Stoqnov 
// Fakulteten Nomer 19621327
#include "framework.h"
#include "F19621327TEST1.h"
#include "strsafe.h"
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    MathDialog(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_F19621327TEST1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_F19621327TEST1));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_F19621327TEST1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_F19621327TEST1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HMENU hMenu, hSubMenu;
    DWORD dwRes;
    BOOL bRes;
    UINT uRes;
    switch (message)
    {
    case WM_RBUTTONDOWN:
    {
        hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_POPUP));
        hSubMenu = GetSubMenu(hMenu, 0);
        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        ClientToScreen(hWnd, &pt);
        TrackPopupMenu(hSubMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
        DestroyMenu(hMenu);
        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_POPUP_WARNINGMESSAGE:
                MessageBox(hWnd, L"Warning from the POPUP menu!", L"Warning message", MB_OK);
                break;

            case ID_GARBAGE:
                    MessageBox(hWnd, L"This is Garbage!", L"Garbage",MB_ICONWARNING | MB_OK);
                    break;

            case ID_REMOVEGARBAGE:
                hMenu = GetMenu(hWnd);
                bRes = DeleteMenu(hMenu, ID_GARBAGE, MF_BYCOMMAND);
                break;

            case ID_CHECK:
                hMenu = GetMenu(hWnd);
                uRes = GetMenuState(hMenu, ID_SHOWDIALOG, MF_BYCOMMAND);
                dwRes = CheckMenuItem(hMenu, ID_SHOWDIALOG,
                    uRes & MF_CHECKED ? MF_UNCHECKED : MF_CHECKED);
                break;

            case ID_ERRORMESSAGE:
                MessageBox(hWnd, L"Error message with ALT-M!", L"Error", MB_OK);
                break;

            case ID_SHOWDIALOG:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_MATH), hWnd, MathDialog);
                break;

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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
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


INT_PTR CALLBACK MathDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    WCHAR szText[MAX_LOADSTRING];
    int a, b, result;
    std::string::size_type sz;

    UINT add, sub;
    double c, d, e, CDE;

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDC_BUTTON1:
            try {
                if (!GetDlgItemText(hDlg, IDC_EDIT_A, szText, MAX_LOADSTRING))
                    *szText = 0;
                a = std::stod(szText, &sz);
            }
            catch (std::exception& e) {
                MessageBox(hDlg, L"Error! You can only type numbers!", L"Error!", MB_ICONERROR | MB_OK);
                SetFocus(GetDlgItem(hDlg, IDC_EDIT_A));
                return (INT_PTR)TRUE;
            }
            try {
                if (!GetDlgItemText(hDlg, IDC_EDIT_B, szText, MAX_LOADSTRING))
                    *szText = 0;
                b = std::stod(szText, &sz);
            }
            catch (std::exception& e) {
                MessageBox(hDlg, L"Error! You can only type numbers!", L"Error!", MB_ICONERROR | MB_OK);
                SetFocus(GetDlgItem(hDlg, IDC_EDIT_B));
                return (INT_PTR)TRUE;
            }

            if (a <= -1000 || a > 1000 || b <= -1000 || b > 1000)
            {
                MessageBox(hDlg, L"The numbers has to be between -1000 and 1000!", L"Error!", MB_OK);
                return (INT_PTR)TRUE;
            }
                
            result = a + b;

            StringCbPrintf(szText, ARRAYSIZE(szText), L"%i", result);
            SetDlgItemText(hDlg, IDC_EDIT_AB, szText);
            return (INT_PTR)TRUE;

        case IDC_BUTTON2:
            add = IsDlgButtonChecked(hDlg, IDC_CHECKBOX1);
            sub = IsDlgButtonChecked(hDlg, IDC_CHECKBOX2);

            try {
                if (!GetDlgItemText(hDlg, IDC_EDIT_C, szText, MAX_LOADSTRING))
                    *szText = 0;
                c = std::stod(szText, &sz);
            }
            catch (std::exception& e) {
                MessageBox(hDlg, L"Error! You can only type numbers!", L"Error!", MB_ICONERROR | MB_OK);
                SetFocus(GetDlgItem(hDlg, IDC_EDIT_C));
                return (INT_PTR)TRUE;
            }
            try {
                if (!GetDlgItemText(hDlg, IDC_EDIT_D, szText, MAX_LOADSTRING))
                    *szText = 0;
                d = std::stod(szText, &sz);
            }
            catch (std::exception& e) { 
                MessageBox(hDlg, L"Error! You can only type numbers!", L"Error!", MB_ICONERROR | MB_OK);
                SetFocus(GetDlgItem(hDlg, IDC_EDIT_D));
                return (INT_PTR)TRUE;
            }
            try {
                if (!GetDlgItemText(hDlg, IDC_EDIT_E, szText, MAX_LOADSTRING))
                    *szText = 0;
                e = std::stod(szText, &sz);
            }
            catch (std::exception& e) {
                MessageBox(hDlg, L"Error! You can only type numbers!", L"Error!", MB_ICONERROR | MB_OK);
                SetFocus(GetDlgItem(hDlg, IDC_EDIT_E));
                return (INT_PTR)TRUE;
            }
            if (c <= -1000 || c > 1000 || d <= -1000 || d > 1000 || e <= -1000 || e > 1000)
            {
                MessageBox(hDlg, L"The numbers has to be between -1000 and 1000!", L"Error!", MB_OK);
                return (INT_PTR)TRUE;
            }

            else if (e == 0)
            {
                MessageBox(hDlg, L"You cannot divide by 0!\nPlease enter a new value for the third number!", L"Error!", MB_OK);
                SetFocus(GetDlgItem(hDlg, IDC_EDIT_E));
                return (INT_PTR)TRUE;
            }

            if (add == BST_CHECKED) {
                CDE = c + (d / e);
            }
            else if (sub == BST_CHECKED) {
                CDE = c - (d / e);
            }

            StringCbPrintf(szText, ARRAYSIZE(szText), L"%f", CDE);
            SetDlgItemText(hDlg, IDC_EDIT_RESULT, szText);
            return (INT_PTR)TRUE;

        case IDOK:
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
    }
    return (INT_PTR)FALSE;
}