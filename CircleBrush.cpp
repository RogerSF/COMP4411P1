//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include <cmath>
#include <iostream>

extern float frand();

CircleBrush::CircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void CircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize( (float)size );

	BrushMove( source, target );
}

void CircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "CircleBrush::BrushMove, document is NULL\n" );
		return;
	}

	int lineHalfSize = pDoc->getSize() / 2;
	int lineWidth = dlg->getLineWidth();
	float angle = dlg->getLineAngle() * M_PI / 180;


	double xOffset= angle == 0 ? lineHalfSize : cos(angle) * lineHalfSize;
	double yOffset = angle == 0 ? 0 : sin(angle) * lineHalfSize;


	glLineWidth(float(lineWidth));

	glBegin( GL_LINE_STRIP );
		SetColor( source, dlg->getAlpha() );
		glVertex2i(target.x - xOffset, target.y - yOffset);
		glVertex2i(target.x + xOffset, target.y + yOffset);

	glEnd();
}

void CircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

