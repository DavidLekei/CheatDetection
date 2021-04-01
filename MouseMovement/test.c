#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	// Register the window class.
	const wchar_t CLASS_NAME[]  = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = CLASS_NAME;

	HWND hwnd = CreateWindowEx(
    0,                              // Optional window styles.
    CLASS_NAME,                     // Window class
    L"Learn to Program Windows",    // Window text
    WS_OVERLAPPEDWINDOW,            // Window style

    // Size and position
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

    NULL,       // Parent window    
    NULL,       // Menu
    hInstance,  // Instance handle
    NULL        // Additional application data
    );

	if (hwnd == NULL)
	{
		printf("\nFailed to create window.");
	    return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	
	printf("\nEnd of Processing.");
	return 0;
}