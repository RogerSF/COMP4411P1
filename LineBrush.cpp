//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "LineBrush.h"
#include <cmath>
#include <iostream>
using namespace std;


extern float frand();

LineBrush::LineBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void LineBrush::BrushBegin( const Point source, const Point target )
{
	BrushMove( source, target );
}

void LineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "LineBrush::BrushMove, document is NULL\n" );
		return;
	}

	int lineHalfSize = pDoc->getSize() / 2;
	int lineWidth = dlg->getLineWidth();
	int direction = pDoc->m_pCurrentDirection;
	float angle = 0;
	Vector* grad;

	switch (direction) {
		case SLIDER: 
			angle = dlg->getLineAngle() * M_PI / 180;
			break;
		case RIGHTMOUSE: 
			grad = new Vector( pDoc->rightMousePos[0]->x - pDoc->rightMousePos[1]->x, pDoc->rightMousePos[0]->y - pDoc->rightMousePos[1]->y );			
			// cout<< "Indicated direction X: " << grad->x <<" Y: " << grad->y <<endl;
			angle = atan2( -1 * grad->y, grad->x);
			
			// angle = dlg->getLineAngle() * M_PI / 180;
			break;
		case GRADIENT: 	
			grad = GetGradient(source);
			// cout<<"Gradient X: "<<grad->x <<" Y: " << grad->y <<endl;
			angle = atan2( grad->x, grad->y);
			//angle = dlg->getLineAngle() * M_PI / 180;
			break;
		case DIFFPICGRADIENT: 	
			grad = GetGradient(source);
			// cout<<"Gradient X: "<<grad->x <<" Y: " << grad->y <<endl;
			angle = atan2( grad->x, grad->y);
			//angle = dlg->getLineAngle() * M_PI / 180;
			break;
		case BRUSH_DIRECTION: 
			grad = new Vector( pDoc->CursorHisPos[0]->x - pDoc->CursorHisPos[1]->x, pDoc->CursorHisPos[0]->y - pDoc->CursorHisPos[1]->y );			
			// cout<<"Moving Direction X: "<<grad->x <<" Y: " << grad->y <<endl;
			angle = atan2( grad->y, grad->x);
			break;
	}
	// cout<<"Angle: "<<angle* M_PI / 180 <<endl;


	double xOffset= angle == 0 ? lineHalfSize : cos(angle) * lineHalfSize;
	double yOffset = angle == 0 ? 0 : sin(angle) * lineHalfSize;


	glLineWidth(float(lineWidth));

	glBegin( GL_LINE_STRIP );
		SetColor( source );
		glVertex2i(target.x - xOffset, target.y - yOffset);
		glVertex2i(target.x + xOffset, target.y + yOffset);

	glEnd();
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}
