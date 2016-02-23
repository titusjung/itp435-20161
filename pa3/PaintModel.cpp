#include "PaintModel.h"
#include <algorithm>
#include <wx/dcmemory.h>
#include "Command.h"
PaintModel::PaintModel()
{
	mCurrentCommand = nullptr;
}

// Draws any shapes in the model to the provided DC (draw context)
void PaintModel::DrawShapes(wxDC& dc, bool showSelection)
{
	// TODO
	for each (std::shared_ptr<Shape> shape in mShapes)
	{
		shape->Draw(dc); 
	}
}

// Clear the current paint model and start fresh
void PaintModel::New()
{
	// TODO
	mCurrentCommand = nullptr;
	while (!mRedoStack.empty())
	{
		mRedoStack.pop();
	}
	while (!mUndoStack.empty())
	{
		mUndoStack.pop();
	}
	mShapes.clear(); 
}

// Add a shape to the paint model
void PaintModel::AddShape(std::shared_ptr<Shape> shape)
{
	mShapes.emplace_back(shape);
}

// Remove a shape from the paint model
void PaintModel::RemoveShape(std::shared_ptr<Shape> shape)
{
	auto iter = std::find(mShapes.begin(), mShapes.end(), shape);
	if (iter != mShapes.end())
	{
		mShapes.erase(iter);
	}
}
bool PaintModel::HasActiveCommand() const
{
	return mCurrentCommand != nullptr;
}
void PaintModel::CreateCommand(CommandType type, const wxPoint& start)
{
	mCurrentCommand = CommandFactory::Create(shared_from_this(), type, start);
}
void PaintModel::UpdateCommand(wxPoint& newPoint)
{
	mCurrentCommand->Update(newPoint);
}
void PaintModel::Finalize()
{
	mCurrentCommand->Finalize( shared_from_this());
	mUndoStack.push(mCurrentCommand);
	mCurrentCommand = nullptr;
	while (!mRedoStack.empty())
	{
		mRedoStack.pop(); 
	}
}
void PaintModel::Undo()
{
	
	mUndoStack.top()->Undo(shared_from_this()); 
	mRedoStack.push(mUndoStack.top()); 
	mUndoStack.pop(); 
	//mUndoStack.pop(); 

}

void PaintModel::Redo()
{
	mRedoStack.top()->Redo(shared_from_this());
	mUndoStack.push(mRedoStack.top());
	mRedoStack.pop(); 
}
