//
// ScatterCircleBrush.h
//
// The header file for Scatter Circle Brush. 
//

#ifndef SCATTERCIRCLEBRUSH_H
#define SCATTERCIRCLEBRUSH_H

#include "CircleBrush.h"

class ScatterCircleBrush : public CircleBrush 
{
public:
	ScatterCircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushMove(const Point source, const Point target) override;

	float randomCountFactor = 0.2;
};

#endif