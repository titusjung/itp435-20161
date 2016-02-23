#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(const wxPoint& start);

	void Draw(wxDC& dc);


};