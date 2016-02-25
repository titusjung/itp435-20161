#include "Shape.h"

Shape::Shape(const wxPoint& start)
	:mStartPoint(start)
	,mEndPoint(start)
	,mTopLeft(start)
	,mBotRight(start)
	, mSelected(false)
	
{

	mOffSet.x = 0;
	mOffSet.y = 0; 
}

// Tests whether the provided point intersects
// with this shape
bool Shape::Intersects(const wxPoint& point) const
{
	wxPoint topleft;
	wxPoint botright;
	GetBounds(topleft, botright);
	if (point.x >= topleft.x +mOffSet.x && point.x <= botright.x + mOffSet.x &&
		point.y >= topleft.y + mOffSet.y && point.y <= botright.y + mOffSet.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Update shape with new provided point
void Shape::Update(const wxPoint& newPoint)
{
	mEndPoint = newPoint;

	// For most shapes, we only have two points - start and end
	// So we can figure out the top left/bottom right bounds
	// based on this.
	mTopLeft.x = std::min(mStartPoint.x, mEndPoint.x);
	mTopLeft.y = std::min(mStartPoint.y, mEndPoint.y);
	mBotRight.x = std::max(mStartPoint.x, mEndPoint.x);
	mBotRight.y = std::max(mStartPoint.y, mEndPoint.y);
}

void Shape::Finalize()
{
	// Default finalize doesn't do anything
}

void Shape::GetBounds(wxPoint& topLeft, wxPoint& botRight) const
{
	topLeft = mTopLeft;
	botRight = mBotRight;
}

void Shape::DrawSelection(wxDC& dc)
{
	dc.SetPen(*wxBLACK_DASHED_PEN);
	dc.SetBrush	(*wxTRANSPARENT_BRUSH); 
	wxPoint topLeft = mTopLeft + mOffSet;
	topLeft.x--;
	topLeft.y++;
	wxPoint botRight = mBotRight + mOffSet;
	botRight.y--;
	botRight.x++;
	dc.DrawRectangle(wxRect(topLeft, botRight));
}
void  Shape::Move(const wxPoint& moveLoc) 
{ 

	mOffSet = moveLoc;
}