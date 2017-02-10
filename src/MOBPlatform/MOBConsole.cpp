//------------------------------------------------------------------
// KB Article ID: Q126628
// "How to Spawn a Console App and Redirect Standard Handles"
//
// KB Article ID: Q150956
// "Redirection  Issues on Windows 95 MS-DOS  Apps and Batch Files"
//------------------------------------------------------------------
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <windows.h>
#include "MOBConsole.h"

using namespace std;

CMOBConsole* CMOBConsole::instance = 0;

CMOBConsole::CMOBConsole()
{
    numColumns = 0;
    numLines = 0;
    numVisibleLines = 0;
	
    AllocateConsole();
}

CMOBConsole:: ~CMOBConsole()
{
    RemoveConsole ();
}

CMOBConsole* CMOBConsole::Instance()
{
	if (CMOBConsole::instance == 0x00)
		CMOBConsole::instance = new CMOBConsole;
	return CMOBConsole::instance;
}

bool CMOBConsole::AllocateConsole()
{
    if (!AllocConsole()) //Just call the Console allocation API
    {
        cerr << "Cannot allocate the console." << endl;
        return false;
    }
    else
    {
        numLines = GetConsoleParam(NUM_LINES);
        numColumns = GetConsoleParam(NUM_COLUMNS);
        numVisibleLines = GetConsoleParam(NUM_VISIBLE_LINES);
		
        SetNumberOfLines(300);
        SetNumberOfColumns(80);
        SetNumVisibleLines(25);
        RedirectToConsole();
		
        return true;
    }
}

void CMOBConsole::RemoveConsole()
{
    if (!FreeConsole())
    {
        cerr << "Cannot free the console." << endl;
    }
}

int CMOBConsole::SetNumberOfLines(int lines)
{
    int prevNumLines = numLines;
    numLines = lines;
    SetConsoleParam(NUM_LINES);
    return prevNumLines;
}

int CMOBConsole::SetNumberOfColumns(int columns)
{
    int prevNumColumns = columns;
    numColumns = columns;
    SetConsoleParam(NUM_COLUMNS);
    return prevNumColumns;
}

int CMOBConsole::SetNumVisibleLines(int lines)
{
    int prevNumVisibleLines = numVisibleLines;
    numVisibleLines = lines;
    SetConsoleParam (NUM_VISIBLE_LINES);
    return prevNumVisibleLines;
}

void CMOBConsole::RedirectToConsole()
{
    int                        consoleHandle;
    HANDLE                     stdHandle;
    FILE                       *fp;
	
    // redirect unbuffered STDOUT to the console
    stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    consoleHandle = _open_osfhandle(reinterpret_cast<long>(stdHandle), _O_TEXT);
    fp = _fdopen(consoleHandle, "w");
    *stdout = *fp;
    setvbuf(stdout, 0, _IONBF, 0);
	
    // redirect unbuffered STDIN to the console
    stdHandle = GetStdHandle(STD_INPUT_HANDLE);
    consoleHandle = _open_osfhandle(reinterpret_cast<long>(stdHandle), _O_TEXT);
    fp = _fdopen(consoleHandle, "r");
    *stdin = *fp;
    setvbuf(stdin, 0, _IONBF, 0);
	
    // redirect unbuffered STDERR to the console
    stdHandle = GetStdHandle(STD_ERROR_HANDLE);
    consoleHandle = _open_osfhandle(reinterpret_cast<long>(stdHandle), _O_TEXT);
    fp = _fdopen(consoleHandle, "w");
    *stderr = *fp;
    setvbuf(stderr, 0, _IONBF, 0);
	
    ios::sync_with_stdio();
}

bool CMOBConsole::SetConsoleParam(ConsoleParam param)
{
	
    HANDLE                     stdHandle;
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenInfo;
	
    if ((stdHandle = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
    {
        return false;
    }
	
    GetConsoleScreenBufferInfo(stdHandle, &consoleScreenInfo);
	
    if (param == NUM_LINES || param == NUM_COLUMNS)
    {
        if (numLines > 0)
        {
            consoleScreenInfo.dwSize.Y = numLines;
        }
		
        if (numColumns > 0)
        {
            consoleScreenInfo.dwSize.X = numColumns;
        }
		
        SetConsoleScreenBufferSize(stdHandle, consoleScreenInfo.dwSize);
    }
	
    if (param == NUM_VISIBLE_LINES)
    {
        SMALL_RECT rect;
		
        rect.Bottom = (numVisibleLines > 0) ? numVisibleLines : consoleScreenInfo.dwMaximumWindowSize.Y;
		
        rect.Right = (numColumns > 0) ? numColumns : consoleScreenInfo.dwMaximumWindowSize.X;
        
        rect.Top = rect.Left = 0;
		
        SetConsoleWindowInfo(stdHandle, TRUE, &rect);
    }
	
    return true;
}

int CMOBConsole::GetConsoleParam(ConsoleParam param)
{
    HANDLE                     stdHandle;
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenInfo;
	
    stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(stdHandle, &consoleScreenInfo);
	
    switch (param)
    {
	case NUM_LINES:
		return consoleScreenInfo.dwSize.Y;
		break;
	case NUM_VISIBLE_LINES:
		return consoleScreenInfo.dwMaximumWindowSize.Y;
		break;
	case NUM_COLUMNS:
		return consoleScreenInfo.dwSize.X;
		break;
    }
	
    return 0;
}

