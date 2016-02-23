#pragma once
#include <memory>
#include <vector>
#include "Shape.h"
#include "Command.h"
#include <wx/bitmap.h>
#include <stack>

class PaintModel : public std::enable_shared_from_this<PaintModel>
{
public:
	PaintModel();
	
	// Draws any shapes in the model to the provided DC (draw context)
	void DrawShapes(wxDC& dc, bool showSelection = true);

	// Clear the current paint model and start fresh
	void New();

	// Add a shape to the paint model
	void AddShape(std::shared_ptr<Shape> shape);
	// Remove a shape from the paint model
	void RemoveShape(std::shared_ptr<Shape> shape);

	bool HasActiveCommand() const; 
	void CreateCommand(CommandType type, const wxPoint& start);
	void UpdateCommand(wxPoint& newPoint);
	void Finalize(); 
	void Undo();
	void Redo(); 
	bool CanUndo() const { return !mUndoStack.empty(); }
	bool CanRedo() const { return !mRedoStack.empty();  }

private:
	// Vector of all the shapes in the model
	std::vector<std::shared_ptr<Shape>> mShapes;
	std::shared_ptr<Command> mCurrentCommand; 
	std::stack<std::shared_ptr<Command>> mUndoStack; 
	std::stack<std::shared_ptr<Command>> mRedoStack;

};
