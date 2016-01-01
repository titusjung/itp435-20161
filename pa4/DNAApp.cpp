//
//  DNAApp.cpp
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "DNAApp.h"
#include "DNAFrame.h"

wxIMPLEMENT_APP(DNAApp);

bool DNAApp::OnInit()
{
	mFrame = new DNAFrame( "DNAwx", wxPoint(50, 50), wxSize(1024, 768) );
	
	return true;
}
