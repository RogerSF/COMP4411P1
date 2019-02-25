//
// SharpenBrush.h
//
// The header file for Blur Brush. 
//

#ifndef SHARPENBRUSH_H
#define SHARPENBRUSH_H

#include "ImpBrush.h"

class SharpenBrush : public ImpBrush
{
public:
	SharpenBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

	void setColorWithFilter(const Point source);
};

#endif#pragma once
