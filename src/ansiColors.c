#include "ansiColors.h"
#include <stdio.h>

#ifdef _WIN32

#include <windows.h>

void ansiInit (void) 
{
 	HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode;

	// verify handle is valid
 	if(stdoutHandle == INVALID_HANDLE_VALUE) {
 	 	exit(GetLastError());
 	}

	// get current console mode
 	if(!GetConsoleMode(stdoutHandle, &consoleMode)) {
 	 	exit(GetLastError());
 	}

  // enable ANSI escape bit
 	consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	// update header
 	if(!SetConsoleMode(stdoutHandle, consoleMode)) {
 	 	exit(GetLastError());
 	}	
}

#else

void ansiInit(void) {}

#endif
