// RandomPasswordGenerator.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "RandomPasswordGenerator.h"
#include "GenerateRandomPassword.h"
#include "DatabaseConnAndDataInsertion.h"
#include <tchar.h>
#include <Uxtheme.h>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];     // the main window class name


// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_RANDOMPASSWORDGENERATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RANDOMPASSWORDGENERATOR));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RANDOMPASSWORDGENERATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_RANDOMPASSWORDGENERATOR);
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
      CW_USEDEFAULT, 0, 450, 380, nullptr, nullptr, hInstance, nullptr);

   

   // SetWindowTheme(hWnd, L" ", L" ");

   if (!hWnd)
   {
      return FALSE;
   }
   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

HWND dataListHwnd;

#define ID_BUTTON 1
#define ID_EDIT 2
#define ID_GROUPBOX 3
#define ID_RADIOBUTTON1 4
#define ID_RADIOBUTTON2 5
#define ID_STATICTEXTFIELD1 6
#define ID_STATICTEXTFIELD2 7
#define ID_EDIT2 8
#define ID_STATIC2 9
#define ID_STATIC3 10
#define ID_STATIC4 11
#define ID_EDIT3 12
#define ID_BUTTON2 13


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

    switch (message)
    {
    case WM_CREATE: {

         CreateWindow(TEXT("STATIC"), TEXT("Random Password Generator and Manager"),
            WS_VISIBLE | WS_CHILD,
            75, 10, 300, 20,
            hWnd, (HMENU)ID_STATICTEXTFIELD2, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Generate!"),
            WS_VISIBLE | WS_CHILD | WS_BORDER, 
             10, 200, 80, 20,
            hWnd, (HMENU) ID_BUTTON, NULL, NULL);

        CreateWindow(TEXT("STATIC"), TEXT("Password Length:"),
            WS_VISIBLE | WS_CHILD,
            10, 60, 120, 25,
            hWnd, (HMENU)ID_STATICTEXTFIELD1, NULL, NULL);
        
        CreateWindow(TEXT("STATIC"), TEXT("Website/ App Name"),
            WS_VISIBLE | WS_CHILD,
            150, 80, 140, 15,
            hWnd, (HMENU) ID_STATIC4, NULL, NULL);

        CreateWindow(TEXT("STATIC"), TEXT("Email:"),
            WS_VISIBLE | WS_CHILD,
            150, 140, 50, 15,
            hWnd, (HMENU) ID_STATIC2, NULL, NULL);

        CreateWindow(TEXT("STATIC"), TEXT("Password:"),
            WS_VISIBLE | WS_CHILD,
            150, 200, 75, 15,
            hWnd, (HMENU)ID_STATIC3, NULL, NULL);

        CreateWindow(TEXT("EDIT"), NULL,
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            150, 100, 200, 25,
            hWnd, (HMENU)ID_EDIT3, NULL, NULL);

        CreateWindow(TEXT("EDIT"), NULL, 
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            150, 225, 150, 25,
            hWnd, (HMENU) ID_EDIT, NULL, NULL);

        CreateWindow(TEXT("EDIT"), NULL,
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            150, 165, 200, 25,
            hWnd, (HMENU)ID_EDIT2, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT(""),
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
            10, 80, 100, 100, 
            hWnd, (HMENU)ID_GROUPBOX, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("12"),
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON |WS_GROUP | WS_BORDER,
            15, 100, 50, 30,
            hWnd, (HMENU) ID_RADIOBUTTON1, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("16"),
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER,
            15, 140, 50, 30,
            hWnd, (HMENU)ID_RADIOBUTTON2, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Add"),
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            170, 270, 80, 20,
            hWnd, (HMENU)ID_BUTTON2, NULL, NULL);

        

        
        break;
    }

     
    case WM_COMMAND:
        {   
            
            HWND hwndEdit = GetDlgItem(hWnd, ID_EDIT);
            int wmId = LOWORD(wParam);
            int tempPassLength = 0;
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_BUTTON: {
                    
                    
                
                    if (IsDlgButtonChecked(hWnd, ID_RADIOBUTTON1) || IsDlgButtonChecked(hWnd, ID_RADIOBUTTON2)) {

                        if (IsDlgButtonChecked(hWnd, ID_RADIOBUTTON1)) {
                            tempPassLength = 12;

                        }
                        else if (IsDlgButtonChecked(hWnd, ID_RADIOBUTTON2)) {
                            tempPassLength = 16;

                        }

                    }
                    else {
                        MessageBox(hWnd, L"Please select the length of your password", L"Error", MB_OK);
                        
                    }
                
                int passLength = tempPassLength;
                std::wstring str;
                if (passLength != 0) {
                    while (true) {
                        std::wstring tempStr = s2ws(generateRandomPassword(passLength));
                        if (tempStr.size() == passLength) {
                            str = tempStr;
                            break;
                        }
                        else
                            continue;

                    }
                }
                SetWindowText(hwndEdit, (LPCWSTR)str.c_str());
                

                break;
            }

            case ID_BUTTON2: {

                HWND hwndEdit = GetDlgItem(hWnd, ID_EDIT);
                HWND hwndEmailEdit = GetDlgItem(hWnd, ID_EDIT2);
                HWND hwndNameEdit = GetDlgItem(hWnd, ID_EDIT3);

                TCHAR buff1[1024];
                TCHAR buff2[1024];
                TCHAR buff3[1024];

                GetWindowText(hwndNameEdit, buff1, 1024);
                GetWindowText(hwndEmailEdit, buff2, 1024);
                GetWindowText(hwndEdit, buff3, 1024);

                if ((buff1[0] == _T('\0')) || (buff2[0] == _T('\0')) || (buff3[0] == _T('\0'))) {

                    MessageBox(hWnd, L"Please enter Site/ App Name, Email & generate a password", L"Error", MB_OK);
                }
                else {
                    insertDataInDatabase(buff1, buff2, buff3);
                }


                
                

                break;
            }

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


