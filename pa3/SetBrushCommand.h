#pragma once
#include "Command.h"
#include <wx/bitmap.h>

class SetBrushCommand : public Command
{
public:
	SetBrushCommand(const wxPoint& start, std::shared_ptr<Shape> shape) :Command(start, shape){}
	void Update(const wxPoint& newPoint) override {}
	// Called when the command is completed
	void Finalize(std::shared_ptr<PaintModel> model) override;
	// Used to "undo" the command
	void Undo(std::shared_ptr<PaintModel> model) override;
	// Used to "redo" the commandS
	void Redo(std::shared_ptr<PaintModel> model) override;
private:
	std::shared_ptr<Shape> mShape;
	wxBrush mBrush; 
};