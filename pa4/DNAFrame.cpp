//
//  DNAFrame.cpp
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "DNAFrame.h"
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/busyinfo.h>
#include "DNADrawPanel.h"
#include "Exceptions.h"
#include "DNAAlignDlg.h"
#include "Timer.h"
enum
{
	ID_AMINO_HIST = 1000,
	ID_ON_COMPARE = 2000
};

wxBEGIN_EVENT_TABLE(DNAFrame, wxFrame)
	EVT_MENU(wxID_EXIT, DNAFrame::OnExit)
	EVT_MENU(wxID_NEW, DNAFrame::OnNew)
	EVT_MENU(ID_AMINO_HIST, DNAFrame::OnAminoHist)
	EVT_MENU(ID_ON_COMPARE, DNAFrame::OnCompare)
wxEND_EVENT_TABLE()

DNAFrame::DNAFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	// File menu
	mDNAModel = std::make_shared<DNAModel>(); 
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_NEW);
	menuFile->Append(ID_AMINO_HIST, "Amino Acid Histogram...",
					 "Create a histogram from a FASTA file.");
	menuFile->Append(ID_ON_COMPARE, "Compare two DNA sequences..", " "); 
	menuFile->Append(wxID_EXIT);
	
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	SetMenuBar(menuBar);
	CreateStatusBar();
	
	// Prepare the draw panel and show this frame
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	mPanel = new DNADrawPanel(this);
	sizer->Add(mPanel, 1, wxEXPAND);
	mPanel->SetModel(mDNAModel); 

	SetSizer(sizer);
	SetAutoLayout(true);
	Show(true);
	
	SetMinSize(GetSize());
	SetMaxSize(GetSize());
	///mFastaReader = mDNAModel->GetReader();
	//mDNATranslator = mDNAModel->GetTranslator(); 
}

void DNAFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void DNAFrame::OnNew(wxCommandEvent& event)
{
	// Doesn't do anything...
}

void DNAFrame::OnAminoHist(wxCommandEvent& event)
{
	// TODO: Implement (File>Amino Acid Histogram...)

	wxFileDialog loadDialog(this, "Save File", "", "",
		"JPG files (*.jpg)|", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (loadDialog.ShowModal() == wxID_OK)
	{
		std::string filename = loadDialog.GetPath().ToStdString();
		try {
			/*
			std::shared_ptr<class DNATranslator> dnaTranslator = mDNAModel->GetTranslator();
			std::shared_ptr<class FastaReader> fastaReader = mDNAModel->GetReader();
			fastaReader->LoadFile(filename); 
			dnaTranslator->Load(fastaReader->GetBody());*/
			mDNAModel->Load(filename); 
			//mDNAModel->Loaded(); 
		}
		catch (FileLoadExcept)
		{
			wxMessageBox("FastaFile is Invalid", "Error", wxOK | wxICON_ERROR); 
			mDNAModel->Loaded(false); 
		}
		//mModel->FileLoad(filename);
		//wxFileOutputStream output_stream(saveDialog.GetPath());
		//UpdateUndoRedo();
		mPanel->PaintNow();
	}	
}

void DNAFrame::OnCompare(wxCommandEvent & event)
{
	DNAAlignDlg dnaDialog;
	Timer timer; 
	double time;
	if (dnaDialog.ShowModal() == wxID_OK)
	{
		timer.Start(); 
		mNWAlgo.Load(dnaDialog.GetInputAPath(), dnaDialog.GetInputBPath());
		wxBusyInfo info("Calculating pairwise match...", this); 
		mNWAlgo.Process(); 
		mNWAlgo.Print(dnaDialog.GetOutputPath());
		time = timer.GetElapsed(); 
	}
	wxMessageBox("time to complete is: " + std::to_string(time), "Time to completion");
}
