#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <windowsx.h>

#define WINDOW_X 0
#define WINDOW_Y 0
#define BUTTON_OFFSET 50
#define BUTTON_DISTANCE 600

HWND WindowHandle;
HWND leftButton;
HWND rightButton;

int recording;
char is_ai;
FILE* out;
FILE* labels;


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void RecordMouseLocation(UINT msg, LPARAM lParam);
void ButtonPressed(WPARAM wParam, LPARAM lParam);
void MouseClick();

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
    //HWND WindowHandle;
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
                WINDOW_X, WINDOW_Y, 800, 600, NULL, NULL, hInstance, NULL);  

    leftButton = createButton(WindowHandle, 10, 10);
    rightButton = createButton(WindowHandle, 680, 10);
    EnableWindow(rightButton, FALSE);

    printf("\nleftButton = %d", leftButton);
    printf("\nrightButton = %d", rightButton);

    ShowWindow(WindowHandle, nCmdShow);
    UpdateWindow(WindowHandle);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        usleep(17000)
    }

    return (int) msg.wParam;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR pCmdLine, int nCmdShow) {

    recording = 0;
    
    if(strcmp(pCmdLine, "-ai") == 0)
    {
        out = fopen("AI_MouseData.csv", "w+");
        labels = fopen("AI_MouseLabels.csv", "w+");
        is_ai = '1';
    }
    else
    {
        out = fopen("HUMAN_MouseData.csv", "w+");
        labels = fopen("HUMAN_MouseLabels.csv", "w+");
        is_ai = '0';
    }

    ezShowWindow(hInstance, nCmdShow);
}


void RecordMouseLocation(UINT msg, LPARAM lParam)
{
    short x = GET_X_LPARAM(lParam);
    short y = GET_Y_LPARAM(lParam);

    char str[5];
    sprintf(str, "%d, %d\n", x, y);

    //fwrite(str, 1, sizeof(str), out);
    fprintf(out, "%s", str);
    printf("Coords: %s", str);
}


void ButtonPressed(WPARAM wParam, LPARAM lParam)
{
    DWORD id = LOWORD(wParam);
    DWORD code = HIWORD(wParam);
    if(code == BN_CLICKED)
    {
        if((int)lParam == (int)leftButton)
        {
            printf("\nLeft Button Pressed.");
            EnableWindow(leftButton, FALSE);
            EnableWindow(rightButton, TRUE);
            recording = 1;
            fputc('/', out);
            fputc('\n', out);
            fputc(is_ai, out);
            fputc('\n', out);
        }
        else if((int)lParam == (int)rightButton)
        {
            printf("\nRight Button Pressed.");
            EnableWindow(rightButton, FALSE);
            EnableWindow(leftButton, TRUE);
            recording = 0;
        }
        else
        {
            printf("\nUnknown Error.");
            exit(0);
        }
    }
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, 
    WPARAM wParam, LPARAM lParam) {

//    printf("WindowProc");
    
    switch(msg) {
      case WM_MOUSEMOVE:
        if(recording == 1)
        {
            RecordMouseLocation(msg, lParam);
        }
        break;
      case WM_COMMAND:
        ButtonPressed(wParam, lParam);
        break;
      case WM_KEYUP:
        printf("\nKEY UP");
        switch(wParam){
            case VK_SPACE:
                printf("\nSPACEBAR");
                break;
        }
        break;
      case WM_DESTROY:
          fclose(out);
          PostQuitMessage(0);
          break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}