#include "SetBrushCommand.h"
#include "PaintModel.h"
void SetBrushCommand::Finalize(std::shared_ptr<PaintModel> model)
{
	mShape = model->GetSelectedShape();
	mBrush = mShape->GetBrush();
	mShape->SetBrush(model->GetBrush());
}
void SetBrushCommand::Undo(std::shared_ptr<PaintModel> model)
{
	wxBrush oldBrush = mShape->GetBrush();
	mShape->SetBrush(mBrush);
	mBrush = oldBrush;

}
// Used to "redo" the commandS
void SetBrushCommand::Redo(std::shared_ptr<PaintModel> model)
{
	wxBrush oldBrush = mShape->GetBrush();
	mShape->SetBrush(mBrush);
	mBrush = oldBrush;
}