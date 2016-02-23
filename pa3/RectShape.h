#pragma once
#include "Shape.h"

class RectShape : public Shape
{
public:
	RectShape(const wxPoint& start);

	void Draw(wxDC& dc) const override;

	//void Update(const wxPoint& newPoint);
	// Finalize the shape -- when the user has finished drawing the shape
	//void Finalize();

};