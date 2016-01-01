//
//  DNAAlignDlg.cpp
//  DNAwx
//
//  Created by Sanjay Madhav on 12/31/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "DNAAlignDlg.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/filedlg.h>

enum
{
	ID_INPUT_A_TEXT = 2000,
	ID_INPUT_A_BUTTON,
	ID_INPUT_B_TEXT,
	ID_INPUT_B_BUTTON,
	ID_OUTPUT_TEXT,
	ID_OUTPUT_BUTTON,
};
wxBEGIN_EVENT_TABLE(DNAAlignDlg, wxDialog)
	EVT_BUTTON(ID_INPUT_A_BUTTON, DNAAlignDlg::OnInputABtn)
	EVT_BUTTON(ID_INPUT_B_BUTTON, DNAAlignDlg::OnInputBBtn)
	EVT_BUTTON(ID_OUTPUT_BUTTON, DNAAlignDlg::OnOutputBtn)
wxEND_EVENT_TABLE()

DNAAlignDlg::DNAAlignDlg()
: wxDialog(NULL, -1, "Pairwise Sequence Alignment...", wxPoint(100,100), wxSize(500,300))
{
	// Input A
	wxBoxSizer* inputASizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* inputALabel = new wxStaticText(this, -1, "Input FASTA A:");
	inputALabel->SetMinSize(wxSize(125, inputALabel->GetMinSize().y));
	mInputATxt = new wxTextCtrl(this, ID_INPUT_A_TEXT);
	mInputATxt->SetEditable(false);
	mInputATxt->SetMinSize(wxSize(250, mInputATxt->GetMinSize().y));
	wxButton* inputABtn = new wxButton(this, ID_INPUT_A_BUTTON, "...");
	inputABtn->SetMinSize(wxSize(30, inputABtn->GetMinSize().y));
	
	inputASizer->Add(inputALabel, 1);
	inputASizer->Add(mInputATxt, 2);
	inputASizer->AddSpacer(5);
	inputASizer->Add(inputABtn);
	
	// Input B
	wxBoxSizer* inputBSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* inputBLabel = new wxStaticText(this, -1, "Input FASTA B:");
	inputBLabel->SetMinSize(inputALabel->GetMinSize());
	mInputBTxt = new wxTextCtrl(this, ID_INPUT_B_TEXT);
	mInputBTxt->SetEditable(false);
	mInputBTxt->SetMinSize(mInputATxt->GetMinSize());
	wxButton* inputBBtn = new wxButton(this, ID_INPUT_B_BUTTON, "...");
	inputBBtn->SetMinSize(inputABtn->GetMinSize());
	
	inputBSizer->Add(inputBLabel, 1);
	inputBSizer->Add(mInputBTxt, 2);
	inputBSizer->AddSpacer(5);
	inputBSizer->Add(inputBBtn);
	
	// Output
	wxBoxSizer* outputSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* outputLabel = new wxStaticText(this, -1, "Output File:");
	outputLabel->SetMinSize(inputALabel->GetMinSize());
	mOutputTxt = new wxTextCtrl(this, ID_OUTPUT_TEXT);
	mOutputTxt->SetEditable(false);
	wxButton* outputBtn = new wxButton(this, ID_OUTPUT_BUTTON, "...");
	outputBtn->SetMinSize(inputABtn->GetMinSize());
	
	outputSizer->Add(outputLabel, 1);
	outputSizer->Add(mOutputTxt, 2);
	outputSizer->AddSpacer(5);
	outputSizer->Add(outputBtn);
	
	// Buttons
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	mOkBtn = new wxButton(this, wxID_OK, "Go!");
	mOkBtn->Enable(false);
	wxButton* btnCancel = new wxButton(this, wxID_CANCEL, "Cancel");
	
	btnSizer->Add(mOkBtn);
	btnSizer->AddSpacer(50);
	btnSizer->Add(btnCancel);
	
	// Dialog Sizer
	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);
	dialogSizer->Add(inputASizer, 0, wxALIGN_CENTER|wxALL, 10);
	dialogSizer->AddSpacer(10);
	dialogSizer->Add(inputBSizer, 0, wxALIGN_CENTER|wxALL, 10);
	dialogSizer->AddSpacer(10);
	dialogSizer->Add(outputSizer, 0, wxALIGN_CENTER|wxALL, 10);
	dialogSizer->AddSpacer(10);
	dialogSizer->Add(btnSizer, 0, wxALIGN_CENTER|wxALL, 10);
	
	dialogSizer->RecalcSizes();
	dialogSizer->SetSizeHints(this);
	SetSizer(dialogSizer);
}

void DNAAlignDlg::OnInputABtn(wxCommandEvent& event)
{
	wxFileDialog fileDlg(this, "Load a FASTA file...",
						 "./data", "", "FASTA Files|*.fasta",
						 wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	
	if (fileDlg.ShowModal() == wxID_OK)
	{
		mInputAPath = fileDlg.GetPath();
		mInputATxt->WriteText(fileDlg.GetPath());
		
		if (mInputAPath.size() != 0 &&
			mInputBPath.size() != 0 &&
			mOutputPath.size() != 0)
		{
			mOkBtn->Enable(true);
		}
	}
}

void DNAAlignDlg::OnInputBBtn(wxCommandEvent& event)
{
	wxFileDialog fileDlg(this, "Load a FASTA file...",
						 "./data", "", "FASTA Files|*.fasta",
						 wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	
	if (fileDlg.ShowModal() == wxID_OK)
	{
		mInputBPath = fileDlg.GetPath();
		mInputBTxt->WriteText(fileDlg.GetPath());
		
		if (mInputAPath.size() != 0 &&
			mInputBPath.size() != 0 &&
			mOutputPath.size() != 0)
		{
			mOkBtn->Enable(true);
		}
	}
}

void DNAAlignDlg::OnOutputBtn(wxCommandEvent& event)
{
	wxFileDialog fileDlg(this, "Save alignment results...",
						 ".", "out.result", "Result Files|*.result",
						 wxFD_SAVE);
	
	if (fileDlg.ShowModal() == wxID_OK)
	{
		mOutputPath = fileDlg.GetPath();
		mOutputTxt->WriteText(fileDlg.GetPath());
		
		if (mInputAPath.size() != 0 &&
			mInputBPath.size() != 0 &&
			mOutputPath.size() != 0)
		{
			mOkBtn->Enable(true);
		}
	}
}
