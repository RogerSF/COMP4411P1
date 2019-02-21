//
// PointBrush.h
//
// The header file for Point Brush. 
//

#ifndef SCATTERPOINTBRUSH_H
#define SCATTERPOINTBRUSH_H

#include "PointBrush.h"

class ScatterPointBrush : public PointBrush 
{
public:
	ScatterPointBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target) override;
	void BrushMove(const Point source, const Point target) override;

	int randomCountFactor = 5;
};

#endif