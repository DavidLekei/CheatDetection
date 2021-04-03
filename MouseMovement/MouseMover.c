#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <windowsx.h>
#include <time.h>
#include <unistd.h>

#define WINDOW_X 0
#define WINDOW_Y 0
#define BUTTON_OFFSET 50
#define BUTTON_DISTANCE 680


int recording;
FILE* out;

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

void run(int runs)
{
	srand(time(NULL));
    printf("\nRunning as AI");
    int j = 0;
    int x, y = 0;
    int random_offset = 0;
    while(j < runs)
    {
	    SetCursorPos(WINDOW_X + BUTTON_OFFSET, WINDOW_Y + BUTTON_OFFSET);
	    MouseClick();
	    int i = 0;
	    for(i = 0; i < BUTTON_DISTANCE; i++)
	    {
	    	random_offset = rand() % 5;
	    	x = WINDOW_X + BUTTON_OFFSET + i;
	    	y = WINDOW_Y + BUTTON_OFFSET;
	    	if(random_offset % 2 == 0)
	    	{
	    		y = y + random_offset;
	    	}
	    	else
	    	{
	    		y = y - random_offset;
	    	}
	        SetCursorPos(x, y);
	        usleep(2000);
	    }
	    MouseClick();
	    j++;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	int runs = atoi(pCmdLine);
	run(runs);
}