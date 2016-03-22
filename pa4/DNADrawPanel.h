//
//  DNADrawPanel.h
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <string>
#include <memory>
#include "DNATranslator.h"
#include "DNAModel.h"
class DNADrawPanel : public wxPanel
{
public:
	DNADrawPanel(wxFrame* parent);
	void PaintNow();
	void SetTranslator(std::shared_ptr<class DNATranslator> dnaTranslator); 
	void SetModel(std::shared_ptr<class DNAModel> dnaModel); 

protected:
	void PaintEvent(wxPaintEvent & evt);
	void Render(wxDC& dc);
	DECLARE_EVENT_TABLE()
	
public:
	// Variables here
	//std::shared_ptr<class FastaReader> mFastaReader;
	//DNATranslator mDNATranslator; 
	//std::shared_ptr<class DNATranslator> mDNATranslator;
	std::shared_ptr<class DNAModel> mDNAModel;
};

