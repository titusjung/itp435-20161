#include "MoveCommand.h"

MoveCommand::MoveCommand(const wxPoint& start, std::shared_ptr<Shape> shape) : Command(start, shape)
{
	assert(shape != nullptr);
	mOldOffSet = shape->GetOffSets(); 
	mStartPoint = start; 
	mShape = shape; 
}

void MoveCommand::Update(const wxPoint & newPoint)
{
	assert(mShape != nullptr);

	wxPoint potPoint = newPoint-mStartPoint; 
	mShape->Move(potPoint);
}
void  MoveCommand::Finalize(std::shared_ptr<PaintModel> model)
{
}
// Used to "undo" the command
void  MoveCommand::Undo(std::shared_ptr<PaintModel> model)
{
	wxPoint oldOffset = mShape->GetOffSets();
	mShape->Move(mOldOffSet); 
	mOldOffSet = oldOffset;
}
// Used to "redo" the commandS
void  MoveCommand::Redo(std::shared_ptr<PaintModel> model)
{
	wxPoint oldOffset = mShape->GetOffSets();
	mShape->Move(mOldOffSet);
	mOldOffSet = oldOffset;

}