#include "RectShape.h"

RectShape::RectShape(const wxPoint & start) :Shape(start)
{
}

void RectShape::Draw(wxDC & dc) const 
{
	dc.DrawRectangle( wxRect(mStartPoint, mEndPoint)); 
}
