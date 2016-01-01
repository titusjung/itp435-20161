//
//  DNAAlignDlg.h
//  DNAwx
//
//  Created by Sanjay Madhav on 12/31/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <wx/dialog.h>
#include <string>

class DNAAlignDlg : public wxDialog
{
public:
	DNAAlignDlg();
	
	void OnInputABtn(wxCommandEvent& event);
	void OnInputBBtn(wxCommandEvent& event);
	void OnOutputBtn(wxCommandEvent& event);
	
	const std::string& GetInputAPath() const
	{
		return mInputAPath;
	}
	
	const std::string& GetInputBPath() const
	{
		return mInputBPath;
	}
	
	const std::string& GetOutputPath() const
	{
		return mOutputPath;
	}
	
	wxDECLARE_EVENT_TABLE();
private:
	class wxButton* mOkBtn;
	class wxTextCtrl* mInputATxt;
	class wxTextCtrl* mInputBTxt;
	class wxTextCtrl* mOutputTxt;
	
	std::string mInputAPath;
	std::string mInputBPath;
	std::string mOutputPath;
};
