#include "PaintFrame.h"
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/toolbar.h>
#include <wx/image.h>
#include <wx/colordlg.h>
#include <wx/textdlg.h>
#include <wx/filedlg.h>
#include "PaintDrawPanel.h"
#include "PaintModel.h"
#include <string>
#include <wx/wfstream.h>
wxBEGIN_EVENT_TABLE(PaintFrame, wxFrame)
	EVT_MENU(wxID_EXIT, PaintFrame::OnExit)
	EVT_MENU(wxID_NEW, PaintFrame::OnNew)
	EVT_MENU(ID_Import, PaintFrame::OnImport)
	EVT_TOOL(ID_Import, PaintFrame::OnImport)
	EVT_MENU(ID_Export, PaintFrame::OnExport)
	EVT_TOOL(ID_Export, PaintFrame::OnExport)
	EVT_MENU(wxID_UNDO, PaintFrame::OnUndo)
	EVT_TOOL(wxID_UNDO, PaintFrame::OnUndo)
	EVT_MENU(wxID_REDO, PaintFrame::OnRedo)
	EVT_TOOL(wxID_REDO, PaintFrame::OnRedo)
	EVT_MENU(ID_Unselect, PaintFrame::OnUnselect)
	EVT_MENU(ID_Delete, PaintFrame::OnDelete)
	EVT_MENU(ID_SetPenColor, PaintFrame::OnSetPenColor)
	EVT_MENU(ID_SetPenWidth, PaintFrame::OnSetPenWidth)
	EVT_MENU(ID_SetBrushColor, PaintFrame::OnSetBrushColor)
	// The different draw modes
	EVT_TOOL(ID_Selector, PaintFrame::OnSelectTool)
	EVT_TOOL(ID_DrawLine, PaintFrame::OnSelectTool)
	EVT_TOOL(ID_DrawEllipse, PaintFrame::OnSelectTool)
	EVT_TOOL(ID_DrawRect, PaintFrame::OnSelectTool)
	EVT_TOOL(ID_DrawPencil, PaintFrame::OnSelectTool)
wxEND_EVENT_TABLE()	

PaintFrame::PaintFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	// Initialize image handlers to support BMP, PNG, JPEG
	wxImage::AddHandler(new wxPNGHandler());
	wxImage::AddHandler(new wxJPEGHandler());

	SetupMenu();
	
	SetupToolbar();

	SetupModelAndView();

	Show(true);
	
	SetMinSize(GetSize());
	SetMaxSize(GetSize());
}

void PaintFrame::SetupMenu()
{
	// File menu
	mFileMenu = new wxMenu();
	mFileMenu->Append(wxID_NEW);
	mFileMenu->Append(ID_Export, "Export...",
		"Export current drawing to image file.");
	mFileMenu->AppendSeparator();
	mFileMenu->Append(ID_Import, "Import...",
		"Import image into file.");
	mFileMenu->Append(wxID_EXIT);

	// Edit menu
	mEditMenu = new wxMenu();
	mEditMenu->Append(wxID_UNDO);
	mEditMenu->Append(wxID_REDO);
	mEditMenu->AppendSeparator();
	mEditMenu->Append(ID_Unselect, "Unselect",
		"Unselect the current selection");
	mEditMenu->AppendSeparator();
	mEditMenu->Append(ID_Delete, "Delete\tDel",
		"Delete the current selection");
	
	mEditMenu->Enable(wxID_UNDO, false);
	mEditMenu->Enable(wxID_REDO, false);
	mEditMenu->Enable(ID_Unselect, false);
	mEditMenu->Enable(ID_Delete, false);

	// Colors menu
	mColorMenu = new wxMenu();
	mColorMenu->Append(ID_SetPenColor, "Pen Color...", "Set the pen color.");
	mColorMenu->Append(ID_SetPenWidth, "Pen Width...", "Set the pen width.");
	mColorMenu->AppendSeparator();
	mColorMenu->Append(ID_SetBrushColor, "Brush Color...", "Set brush color");

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(mFileMenu, "&File");
	menuBar->Append(mEditMenu, "&Edit");
	menuBar->Append(mColorMenu, "&Colors");
	SetMenuBar(menuBar);
	CreateStatusBar();
}

void PaintFrame::SetupToolbar()
{
	// Create the toolbar
	mToolbar = CreateToolBar();
	mToolbar->AddTool(wxID_NEW, "New",
		wxBitmap("Icons/New.png", wxBITMAP_TYPE_PNG),
		"New");
	mToolbar->AddTool(ID_Export, "Export",
		wxBitmap("Icons/Save.png", wxBITMAP_TYPE_PNG),
		"Export");
	mToolbar->AddTool(ID_Import, "Import",
		wxBitmap("Icons/Import.png", wxBITMAP_TYPE_PNG),
		"Import");
	mToolbar->AddSeparator();

	mToolbar->AddTool(wxID_UNDO, "Undo",
		wxBitmap("Icons/Undo.png", wxBITMAP_TYPE_PNG),
		"Undo");
	mToolbar->AddTool(wxID_REDO, "Redo",
		wxBitmap("Icons/Redo.png", wxBITMAP_TYPE_PNG),
		"Redo");
	mToolbar->AddSeparator();

	mToolbar->AddTool(ID_Selector, "Selector",
		wxBitmap("Icons/Cursor.png", wxBITMAP_TYPE_PNG),
		"Selector", wxITEM_CHECK);
	mToolbar->AddTool(ID_DrawLine, "Draw Line",
		wxBitmap("Icons/Line.png", wxBITMAP_TYPE_PNG),
		"Draw Line", wxITEM_CHECK);
	mToolbar->AddTool(ID_DrawEllipse, "Draw Ellipse",
		wxBitmap("Icons/Ellipse.png", wxBITMAP_TYPE_PNG),
		"Draw Ellipse", wxITEM_CHECK);
	mToolbar->AddTool(ID_DrawRect, "Draw Rectangle",
		wxBitmap("Icons/Rectangle.png", wxBITMAP_TYPE_PNG),
		"Draw Rectangle", wxITEM_CHECK);
	mToolbar->AddTool(ID_DrawPencil, "Pencil",
		wxBitmap("Icons/Pencil.png", wxBITMAP_TYPE_PNG),
		"Pencil", wxITEM_CHECK);

	mToolbar->Realize();

	ToggleTool(ID_Selector);

	// Both undo and redo are disabled initially
	mToolbar->EnableTool(wxID_UNDO, false);
	mToolbar->EnableTool(wxID_REDO, false);
}

void PaintFrame::SetupModelAndView()
{
	// Prepare the draw panel and show this frame
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	mPanel = new PaintDrawPanel(this);
	sizer->Add(mPanel, 1, wxEXPAND);

	// Programatically bind the mouse events on the draw panel to us
	mPanel->Bind(wxEVT_LEFT_DOWN, &PaintFrame::OnMouseButton, this);
	mPanel->Bind(wxEVT_LEFT_UP, &PaintFrame::OnMouseButton, this);
	mPanel->Bind(wxEVT_MOTION, &PaintFrame::OnMouseMove, this);

	// Create the model
	mModel = std::make_shared<PaintModel>();
	mPanel->SetModel(mModel);
	SetSizer(sizer);

	SetAutoLayout(true);
}

void PaintFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void PaintFrame::OnNew(wxCommandEvent& event)
{
	mModel->New();
	mPanel->PaintNow();
	UpdateUndoRedo();

}

void PaintFrame::OnExport(wxCommandEvent& event)
{
	// TODO
	wxFileDialog saveDialog(this, "Save File", "", "",
		"JPG files (*.jpg)|", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveDialog.ShowModal() == wxID_OK)
	{
		std::string filename = saveDialog.GetPath().ToStdString();
		mModel->FileSave(filename, mPanel->GetSize());
		//wxFileOutputStream output_stream(saveDialog.GetPath());
	}
}

void PaintFrame::OnImport(wxCommandEvent& event)
{
	// TODO
	wxFileDialog loadDialog(this, "Save File", "", "",
		"JPG files (*.jpg)|", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (loadDialog.ShowModal() == wxID_OK)
	{
		std::string filename = loadDialog.GetPath().ToStdString();
		mModel->FileLoad(filename);
		//wxFileOutputStream output_stream(saveDialog.GetPath());
		UpdateUndoRedo();
		mPanel->PaintNow();
	}
}


void PaintFrame::OnUndo(wxCommandEvent& event)
{
	// TODO
	mModel->Undo(); 
	UpdateUndoRedo(); 
	mPanel->PaintNow();

}

void PaintFrame::OnRedo(wxCommandEvent& event)
{
	// TODO
	mModel->Redo(); 
	UpdateUndoRedo();
	mPanel->PaintNow();

}

void PaintFrame::OnUnselect(wxCommandEvent& event)
{
	// TODO
	mModel->Unselect(); 
	mPanel->PaintNow();
	UpdateSelectDelete();

	UpdateUndoRedo();
}

void PaintFrame::OnDelete(wxCommandEvent& event)
{
	// TODO
	mModel->CreateCommand(CM_Delete, wxPoint(0, 0));
	mModel->Finalize();
	mModel->Unselect(); 
	mPanel->PaintNow();
	UpdateSelectDelete();

	UpdateUndoRedo();
}

void PaintFrame::OnSetPenColor(wxCommandEvent& event)
{
	// TODO
	wxColourData data;
	data.SetColour(mModel->GetPenColor());

	wxColourDialog dialog(this, &data);
	if (dialog.ShowModal() == wxID_OK)
	{
		mModel->SetPenColor(dialog.GetColourData().GetColour());
		if (mModel->HasSelection())
		{
			mModel->CreateCommand(CM_SetPen, wxPoint(0, 0));
			mModel->Finalize();
		}
	}
	mPanel->PaintNow();

	UpdateUndoRedo();
}

void PaintFrame::OnSetPenWidth(wxCommandEvent& event)
{
	// TODO
	wxTextEntryDialog textEntry(this,"enter pen width");

	if (textEntry.ShowModal() == wxID_OK)
	{
		std::string entryString = textEntry.GetValue();
		if (!entryString.empty())
		{
			try 
			{
				int width = std::stoi(entryString);
				if (width <= 10 && width > 0)
				{
					mModel->SetPenWidth(width);
					if (mModel->HasSelection())
					{
						mModel->CreateCommand(CM_SetPen, wxPoint(0, 0));
						mModel->Finalize();
					}
				}
			}
			catch (std::invalid_argument)
			{

			}

		}
	}
	mPanel->PaintNow();

	UpdateUndoRedo();
}

void PaintFrame::OnSetBrushColor(wxCommandEvent& event)
{
	// TODO
	wxColourData data;
	data.SetColour(mModel->GetBrushColor());

	wxColourDialog dialog(this, &data);
	if (dialog.ShowModal() == wxID_OK)
	{
		mModel->SetBrushColor(dialog.GetColourData().GetColour());
		if (mModel->HasSelection())
		{
			mModel->CreateCommand(CM_SetBrush, wxPoint(0, 0));
			mModel->Finalize();
		}
	}
	mPanel->PaintNow();

	UpdateUndoRedo();
}

void PaintFrame::OnMouseButton(wxMouseEvent& event)
{
	if (event.LeftDown())
	{
		// TODO: This is when the left mouse button is pressed
		if (!mModel->IsMoveMode())
		{
			mModel->Unselect();
			switch (mCurrentTool)
			{
			case ID_DrawRect:
				mModel->CreateCommand(CM_DrawRect, event.GetPosition());
				break;
			case ID_DrawEllipse:
				mModel->CreateCommand(CM_DrawEllipse, event.GetPosition());
				break;
			case ID_DrawLine:
				mModel->CreateCommand(CM_DrawLine, event.GetPosition());
				break;
			case ID_DrawPencil:
				mModel->CreateCommand(CM_DrawPencil, event.GetPosition());
				break;
			case ID_Selector:
				mModel->SelectionAtPoint(event.GetPosition());
				UpdateSelectDelete();
				break;
			}
		}
		else
		{
			if (!mModel->IsMoveAndCommandMode())
			{
				mModel->CreateCommand(CM_Move, event.GetPosition());
				mModel->SetMoveAndCommand(true);
			}
			else if(mModel->HasSelection() && mModel->HasActiveCommand())
			{
				mModel->UpdateCommand(event.GetPosition());

			}


		
		}
	}
	else if (event.LeftUp())
	{
		// TODO: This is when the left mouse button is released
		if (mModel->HasActiveCommand())
		{
			mModel->UpdateCommand(event.GetPosition());
			mModel->Finalize();
		}
		mModel->SetMoveAndCommand(false);

	}
	mPanel->PaintNow();

	UpdateUndoRedo();

}

void PaintFrame::OnMouseMove(wxMouseEvent& event)
{
	// TODO: This is when the mouse is moved inside the drawable area
	if (mModel->HasActiveCommand())
	{
		mModel->UpdateCommand(event.GetPosition());
	}
	if (mModel->IsIntersectWithSelection(event.GetPosition()))
	{
		//std::cout << "intersect" << std::endl;
		SetCursor(CU_Move);
		mModel->SetMoveMode(true);
	}
	else
	{
		SetCursor(CU_Default);
		mModel->SetMoveMode(false);

	}
	mPanel->PaintNow();
}

void PaintFrame::ToggleTool(EventID toolID)
{
	// Deselect everything
	for (int i = ID_Selector; i <= ID_DrawPencil; i++)
	{
		mToolbar->ToggleTool(i, false);
	}
	if (mModel != nullptr)
	{
		mModel->Unselect();
	}
	// Select the new tool
	mToolbar->ToggleTool(toolID, true);

	mCurrentTool = toolID;
}

void PaintFrame::SetCursor(CursorType type)
{
	wxCursor* cursor = mCursors.GetCursor(type);
	if (cursor != nullptr)
	{
		mPanel->SetCursor(*cursor);
	}
}

void PaintFrame::OnSelectTool(wxCommandEvent& event)
{
	EventID id = static_cast<EventID>(event.GetId());
	ToggleTool(id);

	// Select appropriate cursor
	switch (id)
	{
	case ID_DrawLine:
	case ID_DrawEllipse:
	case ID_DrawRect:
		SetCursor(CU_Cross);
		break;
	case ID_DrawPencil:
		SetCursor(CU_Pencil);
		break;
	default:
		SetCursor(CU_Default);
		break;
	}
}
void PaintFrame::UpdateUndoRedo()
{
	mEditMenu->Enable(wxID_UNDO, mModel->CanUndo());
	mEditMenu->Enable(wxID_REDO, mModel->CanRedo());
	mToolbar->EnableTool(wxID_UNDO, mModel->CanUndo());
	mToolbar->EnableTool(wxID_REDO, mModel->CanRedo());
}

void PaintFrame::UpdateSelectDelete()
{
	mEditMenu->Enable(ID_Unselect, mModel->HasSelection());
	mEditMenu->Enable(ID_Delete, mModel->HasSelection());


}
