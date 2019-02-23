//
// PressureBrush.cpp
//
// The implementation of Pressure Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//
// Pressure brush will simulate a brush's pressure by the moving speed of the brush
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "PressureBrush.h"
#include <numeric>
#include <iostream>

extern float frand();

PressureBrush::PressureBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void PressureBrush::BrushBegin( const Point source, const Point target )
{
	BrushMove( source, target );
}

void PressureBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PressureBrush::BrushMove, document is NULL\n" );
		return;
	}

	// Push the current target into the back stack
	this->pointHistory.push_back(target);

	// If history size exceed our desired count, pop the first one (most outdated one)
	if(this->pointHistory.size() > pointHistoryCount)
	{
		this->pointHistory.pop_front();
	}

	// Compute the mean of distance of the point history
	float mean = 0;
	std::list<Point>::const_iterator it;
	for (it = this->pointHistory.begin(); it != this->pointHistory.end(); ++it) {
		auto nextIt = std::next(it, 1);
		if (nextIt != this->pointHistory.end())
		{
			mean += sqrt(pow((it->x - nextIt->x), 2) + pow((it->y - nextIt->y), 2));
		}
	}
	mean /= this->pointHistory.size();

	// Set the mean as the radius size, factored by 
	float radius = mean * this->radiusFactor;
	dlg->setSize(int(radius));

	glBegin( GL_TRIANGLE_FAN );

		SetColor( source );

		glVertex2d(target.x, target.y);
		for (int i = 0; i < 360; i++) {
			float angle = i * M_PI / 180;
			glVertex2f(target.x + radius * cos(angle), target.y + radius * sin(angle));
		}

	glEnd();
}

void PressureBrush::BrushEnd( const Point source, const Point target )
{
	// Clear the point history when brush finishes
	this->pointHistory.clear();
}

