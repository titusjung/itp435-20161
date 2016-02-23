#pragma once
#include "Shape.h"
#include <vector>
class PencilShape : public Shape
{
public:
	PencilShape(const wxPoint& start);
	void Update(const wxPoint& newPoint) override;
	// Finalize the shape -- when the user has finished drawing the shape
	void Finalize() override;
	void Draw(wxDC& dc) const override;
private:
	std::vector<wxPoint> mPointVector; 
};