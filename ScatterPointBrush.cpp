//
// ScatterPointBrush.cpp
//
// The implementation of Scatter Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "ScatterPointBrush.h"
#include <ctime>

extern float frand();

ScatterPointBrush::ScatterPointBrush(ImpressionistDoc* pDoc, char* name) : PointBrush(pDoc, name)
{
	srand(time(nullptr));
}

void ScatterPointBrush::BrushBegin(const Point source, const Point target)
{
	glPointSize(1);  // A scatter point brush scatter very small points within size square

	BrushMove(source, target);
}

void ScatterPointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatterPointBrush::BrushMove, document is NULL\n" );
		return;
	}

	int bound = pDoc->getSize();
	int pointCount = this->randomCountFactor * bound; // Scale random point count by size

	for(int i = 0; i < pointCount; i++)
	{
		// Random the point within center +- bound / 2
		int randomX = (rand() % (bound + 1)) - (bound / 2);
		int randomY = (rand() % (bound + 1)) - (bound / 2);

		Point randSource = Point(source.x + randomX, source.y + randomY);
		Point randTarget = Point(target.x + randomX, target.y + randomY);

		PointBrush::BrushMove(randSource, randTarget);
	}
}

