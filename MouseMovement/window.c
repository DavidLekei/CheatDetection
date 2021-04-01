#include <stdlib.h>
#include <stdio.h>

#include "ezgui.h"

DWORD WINAPI StartWindowThread(LPVOID lpParameter)
{
    printf("[+] StartWindowThread\n");

    MSG msg;

    if(lpParameter == NULL)
    {
        printf("[x] ERROR: Window passed to StartWindowThread() is NULL.\n");
        return 0;
    }

    ezWindow* Window = lpParameter;

    printf("[-] StartWindowThread(): Window->hInstance is SET to %d\n", (int)Window->hInstance);
    ezBuildWindow(Window);
    SuspendThread(Window->WindowThread);

    if(ShowWindow(Window->WindowHandle, SW_SHOW) == 0)
    {
        printf("[+] StartWindowThread(): Set Window to VISIBLE\n");
    }
    UpdateWindow(Window->WindowHandle);

    printf("[-] StartWindowThread(): Running on Thread %d\n", (int)GetCurrentThreadId());
    while (GetMessage(&msg, Window->WindowHandle, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

void ezShowWindow(ezWindow* Window)
{
    if(Window == NULL)
    {
        printf("[x] ezShowWindow(): ERROR: Window is NULL\n");
    }
    if(Window->WindowThread == NULL)
    {
        printf("[x] ezShowWindow(): ERROR: WindowThread within ezWindow structure is NULL\n");
    }
    ResumeThread(Window->WindowThread);
}

void ezBuildWindow(ezWindow* Window)
{
    printf("[+] ezBuildWindow(): Creating a New Window\n");
    
    HWND WindowHandle;
    WNDCLASSW wc;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.lpszClassName = L"Window";
    wc.hInstance     = Window->hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName  = NULL;
    wc.lpfnWndProc   = WindowProc;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  
    RegisterClassW(&wc);
    WindowHandle = CreateWindowW(wc.lpszClassName, L"Window",
                WS_OVERLAPPEDWINDOW,
                100, 100, 350, 250, NULL, NULL, Window->hInstance, NULL);  

    if(WindowHandle == NULL)
    {
        printf("[x] ezBuildWindow(): Failed to Create Window.\n");
        //TODO: free(Window);
        //      exit(0);
    }
    else
    {
        printf("[+] ezBuildWindow(): Succesfully Created Window.\n");
    }

    Window->WindowHandle = WindowHandle;
}

ezWindow* ezCreateWindow(HINSTANCE hInstance)
{
    ezWindow* Window;
    HANDLE thread;
    PDWORD threadId;

    Window = malloc(sizeof(ezWindow));
    Window->hInstance = hInstance;
    threadId = 0;

    printf("[-] ezCreateWindow(): hInstance: %d\n", (int)hInstance);
    thread = CreateThread(
        NULL,                               //LPSECURITY_ATTRIBUTES   lpThreadAttributes,
        0,                                  //SIZE_T                  dwStackSize, if 0, uses default value
        StartWindowThread,                  //LPTHREAD_START_ROUTINE  lpStartAddress,
        (void*)Window,//(void*)Window,                               //__drv_aliasesMem LPVOID lpParameter, pointer to parameter passed to the thread TODO: Change to window info
        0,                                  //DWORD                   dwCreationFlags, if 0, thread runs immediately after creation
        threadId);                         //LPDWORD                 lpThreadId

    if(thread == NULL)
    {
        printf("[x] ERROR: ezCreateWindow(): CreateThread() Failed.\n");
        free(Window);
        return  NULL;
    }

    Window->WindowHandle = NULL;
    Window->WindowThread = thread;

    //Wait for WindowThread to set Window->WindowHandle
    while(Window->WindowHandle == NULL)
    {

    }

    printf("[+] ezCreateWindow(): Window Handle set!\n");
    return Window;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, 
    WPARAM wParam, LPARAM lParam) {

    //printf("[+] WindowProc(): msg: %d\n", msg);
    printf("[-] WindowProc(): Running on Thread %d\n", (int)GetCurrentThreadId());

    
    switch(msg) {
  
        case WM_SIZE:
            printf("WM_SIZE\n");
            break;
        case WM_CLOSE:
            printf("WM_CLOSE\n");
            break;
        case WM_ACTIVATEAPP:
            printf("WM_ACTIVATEAPP\n");
            break;
        case WM_DESTROY:
            printf("WM_DESTROY\n");
            PostQuitMessage(0);
            break;
        case WM_MOUSEMOVE:
            printf("WM_MOUSEMOVE\n");
            break;
        default:
            //printf("UNHANDLED MESSAGE\n");
            DefWindowProcW(hwnd, msg, wParam, lParam);
            break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}