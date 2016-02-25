#include "DeleteCommand.h"
#include "PaintModel.h"
void DeleteCommand::Finalize(std::shared_ptr<PaintModel> model)
{
	mShape = model->GetSelectedShape();
	model->RemoveShape(mShape);
}
// Used to "undo" the command
void DeleteCommand::Undo(std::shared_ptr<PaintModel> model)
{
	model->AddShape(mShape);
}
// Used to "redo" the commandS
void DeleteCommand::Redo(std::shared_ptr<PaintModel> model)
{
	model->RemoveShape(mShape);

}