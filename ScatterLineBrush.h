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

	void BrushMove(const Point source, const Point target) override;

	float randomCountFactor = 0.2;
};

#endif