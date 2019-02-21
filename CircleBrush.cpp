//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
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

	float radius = float(pDoc->getSize()) / 2;

	glBegin( GL_TRIANGLE_FAN );

		SetColor( source, dlg->getAlpha() );

		glVertex2d(target.x, target.y);
		for (int i = 0; i < 360; i++) {
			float angle = i * M_PI / 180;
			glVertex2f(target.x + radius * cos(angle), target.y + radius * sin(angle));
		}

	glEnd();
}

void CircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

