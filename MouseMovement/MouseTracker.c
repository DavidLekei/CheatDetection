#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windowsx.h>


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

HWND createButton(HWND parentWindow, int x, int y)
{
 HWND hwndButton = CreateWindow( 
    "BUTTON",  // Predefined class; Unicode assumed 
    "OK",      // Button text 
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
    x,         // x position 
    y,         // y position 
    100,        // Button width
    100,        // Button height
    parentWindow,     // Parent window
    NULL,       // No menu.
    (HINSTANCE)GetWindowLongPtr(parentWindow, GWLP_HINSTANCE), 
    NULL);      // Pointer not needed.

    return hwndButton;
}

int ezShowWindow(HINSTANCE hInstance, int nCmdShow)
{
    MSG  msg;    
    HWND WindowHandle;
    HWND leftButton;
    HWND rightButton;
    WNDCLASSW wc;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.lpszClassName = L"Window";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName  = NULL;
    wc.lpfnWndProc   = WindowProc;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  
    RegisterClassW(&wc);
    WindowHandle = CreateWindowW(wc.lpszClassName, L"Window",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                100, 100, 800, 600, NULL, NULL, hInstance, NULL);  

    leftButton = createButton(WindowHandle, 10, 10);
    rightButton = createButton(WindowHandle, 690, 10);

    ShowWindow(WindowHandle, nCmdShow);
    UpdateWindow(WindowHandle);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR pCmdLine, int nCmdShow) {

    printf("\npCmdLine: %s", pCmdLine);
    
    ezShowWindow(hInstance, nCmdShow);
}

void ButtonPressed(WPARAM wParam, LPARAM lParam)
{
    printf("\nButton was pressed!");
    DWORD id = LOWORD(wParam);
    DWORD code = HIWORD(wParam);
    if(code == BN_CLICKED)
    {
        printf("\n***BN_CLICKED***");
    }
    //HANDLE button = lParam;
    printf("\nID = %d code = %d", id, code);
}

void MouseDown(POINT* cursorPos)
{
    MOUSEINPUT mouseDown = {cursorPos->x, cursorPos->y, 0, MOUSEEVENTF_LEFTDOWN, 0, 0};
    INPUT down = {INPUT_MOUSE, mouseDown};

    INPUT inputs[1] = {down};
    SendInput(1, inputs, sizeof(INPUT));
}

void MouseUp(POINT* cursorPos)
{
    MOUSEINPUT mouseUp = {cursorPos->x, cursorPos->y, 0, MOUSEEVENTF_LEFTUP, 0, 0};
    INPUT up = {INPUT_MOUSE, mouseUp};

    INPUT inputs[1] = {up};
    SendInput(1, inputs, sizeof(INPUT));
}

void MouseClick()
{
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    printf("\nCursor X = %d Y = %d", cursorPos.x, cursorPos.y);
    
    MouseDown(&cursorPos);
    MouseUp(&cursorPos);

}

void RecordMouseLocation(UINT msg, LPARAM lParam)
{
    short x = GET_X_LPARAM(lParam);
    short y = GET_Y_LPARAM(lParam);

    printf("\nX = %d Y = %d", x, y);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, 
    WPARAM wParam, LPARAM lParam) {

//    printf("WindowProc");
    
    switch(msg) {
      case WM_MOUSEMOVE:
        RecordMouseLocation(msg, lParam);
        break;
      case WM_COMMAND:
        ButtonPressed(wParam, lParam);
        break;
      case WM_KEYUP:
        switch(wParam){
            case VK_SPACE:
                MouseClick();
                break;
        }
        break;
      case WM_DESTROY:
          PostQuitMessage(0);
          break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}