#pragma once
#include "Shape.h"

class LineShape : public Shape
{
public:
	LineShape(const wxPoint& start);

	virtual void Draw( wxDC& dc) const;
};