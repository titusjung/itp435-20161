#include "SetPenCommand.h"
#include "PaintModel.h"
void SetPenCommand::Update(const wxPoint & newPoint)
{

}
void SetPenCommand::Finalize(std::shared_ptr<PaintModel> model)
{
	mShape = model->GetSelectedShape(); 
	mPen = mShape->GetPen();
	mShape->SetPen(model->GetPen()); 
}
// Used to "undo" the command
void SetPenCommand::Undo(std::shared_ptr<PaintModel> model)
{
	wxPen oldPen = mShape->GetPen();
	mShape->SetPen(mPen); 
	mPen = oldPen; 
}
// Used to "redo" the command
void SetPenCommand::Redo(std::shared_ptr<PaintModel> model)
{
	wxPen oldPen = mShape->GetPen();
	mShape->SetPen(mPen);
	mPen = oldPen;
}