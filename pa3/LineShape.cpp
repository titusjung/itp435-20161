#include "LineShape.h"

LineShape::LineShape(const wxPoint & start):Shape(start)
{
}

void LineShape::Draw(wxDC & dc) const
{
	dc.DrawLine(mStartPoint, mEndPoint); 

}
