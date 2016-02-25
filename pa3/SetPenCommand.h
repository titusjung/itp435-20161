#pragma once
#include "Command.h"
#include "Shape.h"
#include <wx/bitmap.h>

class SetPenCommand : public Command
{
public:
	SetPenCommand(const wxPoint& start, std::shared_ptr<Shape> shape) :Command(start, shape) {}

	void Update(const wxPoint& newPoint) override;
	// Called when the command is completed
	void Finalize(std::shared_ptr<PaintModel> model) override;
	// Used to "undo" the command
	void Undo(std::shared_ptr<PaintModel> model) override;
	// Used to "redo" the command
	void Redo(std::shared_ptr<PaintModel> model) override;
private:
	std::shared_ptr<Shape> mShape;

	wxPen mPen; 

};