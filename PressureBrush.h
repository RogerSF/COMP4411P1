//
// PressureBrush.h
//
// The header file for Pressure Brush. 
//

#ifndef PRESSUREBRUSH_H
#define PRESSUREBRUSH_H

#include "ImpBrush.h"
#include "list"

class PressureBrush : public ImpBrush
{
public:
	PressureBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );

private:
	static const int pointHistoryCount = 5;
	const float radiusFactor = 1.5;
	std::list<Point> pointHistory;
};

#endif