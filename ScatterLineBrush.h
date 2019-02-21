//
// ScatterLineBrush.h
//
// The header file for Scatter Line Brush. 
//

#ifndef SCATTERLINEBRUSH_H
#define SCATTERLINEBRUSH_H

#include "LineBrush.h"

class ScatterLineBrush : public LineBrush 
{
public:
	ScatterLineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target) override;
	void BrushMove(const Point source, const Point target) override;

	int randomCountFactor = 5;
};

#endif