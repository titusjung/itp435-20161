//
//  DNAFrame.h
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/menu.h>
#include <memory>

class DNAFrame : public wxFrame
{
public:
	DNAFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnExit(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
	void OnAminoHist(wxCommandEvent& event);
	
	wxDECLARE_EVENT_TABLE();
private:
	// Panel for drawing
	class DNADrawPanel* mPanel;
	
	// Variables here
};
