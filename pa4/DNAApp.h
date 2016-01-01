//
//  DNAApp.h
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <wx/app.h>

class DNAApp : public wxApp
{
public:
	virtual bool OnInit();
private:
	class DNAFrame* mFrame;
};
