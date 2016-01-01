//
//  app.h
//  zombiewx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <wx/app.h>

class ZomApp : public wxApp
{
public:
	virtual bool OnInit();
private:
	class ZomFrame* mFrame;
};
