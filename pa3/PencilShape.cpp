#include "PencilShape.h"

PencilShape::PencilShape(const wxPoint & start): Shape(start)
{
	mPointVector.push_back(start); 
}

void PencilShape::Update(const wxPoint & newPoint)
{
	mPointVector.push_back(newPoint);

}

void PencilShape::Finalize()
{
	//int mostRight, mostLeft, mostTop, mostBot;
	mStartPoint = mPointVector.front(); 
	mEndPoint = mPointVector.back(); 
	/*
	mostBot = firstPoint.y;
	mostTop = firstPoint.y;
	mostRight = firstPoint.x;
	mostLeft = firstPoint.y; */
	mTopLeft.y = mStartPoint.y;
	mBotRight.y = mStartPoint.y;

	mBotRight.x = mStartPoint.x;
	mTopLeft.x = mStartPoint.x;
	for each(wxPoint wPoint in mPointVector)
	{
		if (wPoint.x > mBotRight.x)
		{
			//mostRight = wPoint.x;
			mBotRight.x = wPoint.x;
		}
		if (wPoint.x < mTopLeft.x)
		{
			//mostLeft = wPoint.x;
			mTopLeft.x = wPoint.x;
		}
		if (wPoint.y < mTopLeft.y)
		{
			mTopLeft.y = wPoint.y; 
		}
		if (wPoint.y > mBotRight.y)
		{
			mBotRight.y = wPoint.y; 
		}
	}
}

void PencilShape::Draw(wxDC & dc) const
{
	if (mPointVector.size()>1)
	{
		std::vector<wxPoint> withOffSetVector = mPointVector;
		for each (wxPoint point in withOffSetVector)
		{
			point+=mOffSet;
		}
		dc.DrawLines(mPointVector.size(), withOffSetVector.data());
	}
	else
	{
		dc.DrawPoint(mPointVector.front()+mOffSet); 
	}
}
