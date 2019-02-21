//
// ScatterPointBrush.h
//
// The header file for Scatter Point Brush. 
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

	float randomCountFactor = 5;
};

#endif