//
//  app.cpp
//  zombiewx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "ZomApp.h"
#include "ZomFrame.h"

#ifdef _WIN32
void RedirectIOToConsole()
{
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	
	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
		&coninfo);
	coninfo.dwSize.Y = 1000;

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),
		coninfo.dwSize);

	// Redirect stdio
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();
}
#else
// On Mac, no need for this to do anything
void RedirectIOToConsole() { }
#endif

wxIMPLEMENT_APP(ZomApp);

bool ZomApp::OnInit()
{
	// If needed, create a console to redirect to
	RedirectIOToConsole();

	mFrame = new ZomFrame( "Zombie Apocalypse Simulator", wxPoint(50, 50), wxSize(800, 700) );
	
	return true;
}
