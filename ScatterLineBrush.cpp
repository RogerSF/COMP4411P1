//
// ScatterLineBrush.cpp
//
// The implementation of Scatter Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "ScatterLineBrush.h"
#include <ctime>

extern float frand();

ScatterLineBrush::ScatterLineBrush(ImpressionistDoc* pDoc, char* name) : LineBrush(pDoc, name)
{
	srand(time(nullptr));
}

void ScatterLineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();

	if ( pDoc == NULL ) {
		printf( "ScatterPointBrush::BrushMove, document is NULL\n" );
		return;
	}

	int bound = pDoc->getSize();
	int pointCount = int(this->randomCountFactor * bound); // Scale random point count by size

	for(int i = 0; i < pointCount; i++)
	{
		// Random the point within center +- bound / 2
		int randomX = (rand() % (bound + 1)) - (bound / 2);
		int randomY = (rand() % (bound + 1)) - (bound / 2);

		Point randSource = Point(source.x + randomX, source.y + randomY);
		Point randTarget = Point(target.x + randomX, target.y + randomY);

		LineBrush::BrushMove(randSource, randTarget);
	}
}

