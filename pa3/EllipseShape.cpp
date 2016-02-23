#include "EllipseShape.h"

EllipseShape::EllipseShape(const wxPoint& start):Shape(start)
{

}

void EllipseShape::Draw(wxDC & dc) const
{
	dc.DrawEllipse(wxRect(mStartPoint, mEndPoint));

}
