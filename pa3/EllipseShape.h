#pragma once
#include "Shape.h"

class EllipseShape : public Shape
{
public:
	EllipseShape(const wxPoint& start);

	void Draw(wxDC& dc) const override;
}; 