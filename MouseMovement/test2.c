#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windowsx.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int ezShowWindow(HINSTANCE hInstance, int nCmdShow)
{
    MSG  msg;    
    HWND WindowHandle;
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
    
    ezShowWindow(hInstance, nCmdShow);
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
      case WM_DESTROY:
      
          PostQuitMessage(0);
          break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}