//
//  DNADrawPanel.cpp
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "DNADrawPanel.h"
#include <wx/dcclient.h>
#include <wx/sizer.h>
#include <array>
#include <sstream>
#include <iomanip>


BEGIN_EVENT_TABLE(DNADrawPanel, wxPanel)
	EVT_PAINT(DNADrawPanel::PaintEvent)
END_EVENT_TABLE()

DNADrawPanel::DNADrawPanel(wxFrame* parent)
: wxPanel(parent)
{
	
}

void DNADrawPanel::PaintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	Render(dc);
}

void DNADrawPanel::PaintNow()
{
	wxClientDC dc(this);
	Render(dc);
}

void DNADrawPanel::SetTranslator(std::shared_ptr<class DNATranslator> dnaTranslator)
{
	//mDNATranslator = dnaTranslator; 
}

void DNADrawPanel::Render(wxDC& dc)
{
	// Clear
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	
	// TODO: Draw histogram, if one has been generated
	if (!mDNAModel->IsLoaded()) return; 
	std::shared_ptr<class FastaReader> fastaReader = mDNAModel->GetReader();
	std::shared_ptr<class DNATranslator> dnaTranslator = mDNAModel->GetTranslator();

	dc.SetPen(*wxBLACK_PEN); 
	dc.SetBrush(*wxBLUE_BRUSH); 
	dc.DrawText(fastaReader->GetHeader(), wxPoint(10,10));  
	double total = static_cast<double>(dnaTranslator->GetTotal()); 
	int tablestart = 170; 
	int tablewidth = 20; 
	std::string percent = std::to_string(dnaTranslator->GetAlanine() / total);
	std::string amount = std::to_string(dnaTranslator->GetAlanine());
	std::string printString = "Alanine " +percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 20));
	dc.DrawRectangle(tablestart, 30, dnaTranslator->GetAlanine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetCysteine() / total);
	amount = std::to_string(dnaTranslator->GetCysteine());
	printString = "Cysteine " +percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 50));
	dc.DrawRectangle(tablestart, 50, dnaTranslator->GetCysteine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetAspartic_Acid() / total);
	amount = std::to_string(dnaTranslator->GetAspartic_Acid());
	printString = "Aspartic Acid " +percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 80));
	dc.DrawRectangle(tablestart, 80, dnaTranslator->GetAspartic_Acid(), tablewidth);

	percent = std::to_string(dnaTranslator->GetGlutamic_Acid() / total);
	amount = std::to_string(dnaTranslator->GetGlutamic_Acid());
	printString = "Glutamic Acid " +percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 110));
	dc.DrawRectangle(tablestart, 110,  dnaTranslator->GetGlutamic_Acid(), tablewidth);

	percent = std::to_string(dnaTranslator->GetPhenylalanine() / total);
	amount = std::to_string(dnaTranslator->GetPhenylalanine());
	printString = "Phenylalanine " +percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 140));
	dc.DrawRectangle(tablestart, 140, dnaTranslator->GetPhenylalanine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetGlycine() / total);
	amount = std::to_string(dnaTranslator->GetGlycine());
	printString = "Glycine " +percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 170));
	dc.DrawRectangle(tablestart, 170,  dnaTranslator->GetGlycine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetHistidine() / total);
	amount = std::to_string(dnaTranslator->GetHistidine());
	printString = "Histidine " +percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 200));
	dc.DrawRectangle(tablestart, 200, dnaTranslator->GetHistidine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetIsoleucine() / total);
	amount = std::to_string(dnaTranslator->GetIsoleucine());
	printString = "Isoleucine " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 230));
	dc.DrawRectangle(tablestart, 230,  dnaTranslator->GetIsoleucine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetLysine() / total);
	amount = std::to_string(dnaTranslator->GetLysine());
	printString = "Lysine " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 260));
	dc.DrawRectangle(tablestart, 260, dnaTranslator->GetLysine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetLeucine() / total);
	amount = std::to_string(dnaTranslator->GetLeucine());
	printString = "Leucine " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 290));
	dc.DrawRectangle(tablestart, 290,  dnaTranslator->GetLeucine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetMethionine() / total);
	amount = std::to_string(dnaTranslator->GetMethionine());
	printString = "Methionine " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 320));
	dc.DrawRectangle(tablestart, 320,  dnaTranslator->GetMethionine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetAsparagine() / total);
	amount = std::to_string(dnaTranslator->GetAsparagine());
	printString = "Asparagine " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 350));
	dc.DrawRectangle(tablestart, 350,  dnaTranslator->GetAsparagine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetProline() / total);
	amount = std::to_string(dnaTranslator->GetProline());
	printString = "Proline " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 380));
	dc.DrawRectangle(tablestart, 380,  dnaTranslator->GetProline(), tablewidth);

	percent = std::to_string(dnaTranslator->GetGlutamine() / total);
	amount = std::to_string(dnaTranslator->GetGlutamine());
	printString = "Glutamine " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 410));
	dc.DrawRectangle(tablestart, 410,  dnaTranslator->GetGlutamine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetArginine() / total);
	amount = std::to_string(dnaTranslator->GetArginine());
	printString = "Arginine " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 440));
	dc.DrawRectangle(tablestart, 440,  dnaTranslator->GetArginine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetThreonine() / total);
	amount = std::to_string(dnaTranslator->GetThreonine());
	printString = "Threonine " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 470));
	dc.DrawRectangle(tablestart, 470, dnaTranslator->GetThreonine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetValine() / total);
	amount = std::to_string(dnaTranslator->GetValine());
	printString = "Valine " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 500));
	dc.DrawRectangle(tablestart, 500,  dnaTranslator->GetValine(), tablewidth);

	percent = std::to_string(dnaTranslator->GetTryptophan() / total);
	amount = std::to_string(dnaTranslator->GetTryptophan());
	printString = "Tryptophan " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 530));
	dc.DrawRectangle(tablestart, 530, dnaTranslator->GetTryptophan(), tablewidth);

	percent = std::to_string(dnaTranslator->GetTyrosine() / total);
	amount = std::to_string(dnaTranslator->GetTyrosine());
	printString = "Tyrosine " + percent + " (" + amount + ")";
	dc.DrawText(printString, wxPoint(10, 560));
	dc.DrawRectangle(tablestart, 560, dnaTranslator->GetTyrosine(), tablewidth);

}

void DNADrawPanel::SetModel(std::shared_ptr<class DNAModel> dnaModel)
{
	mDNAModel = dnaModel;
}

