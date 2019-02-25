//
// GLuFilter.cpp
//
// Implementation of the GLuFilter
//

#include "GLuFilter.h"
#include <cmath>
#include "impressionistDoc.h"

GLuFilter::GLuFilter(float* matrix, int width, int height)
{
	this->matrix = new float[width * height];
	for (int i = 0; i < width*height; i++)
	{
		this->matrix[i] = matrix[i];
	}
	filterWidth = width;
	filterHeight = height;
}

float GLuFilter::filterPixel(ImpressionistDoc* doc, int rgbOffset, Point origin, int sourceWidth, int sourceHeight)
{
	int centerX = origin.x - (filterWidth / 2);
	int centerY = origin.y - (filterHeight / 2);

	float filteredValue = 0;

	for (int i = 0; i < filterWidth; i++)
	{
		for (int j = 0; j < filterHeight; j++)
		{
			// Clamp the pixel matrix inbound
			int x = (centerX + i < sourceWidth) ? abs(centerX + i) : 2 * (sourceWidth - 1) - (centerX + i);
			int y = (centerY + j < sourceHeight) ? abs(centerY + j) : 2 * (sourceHeight - 1) - (centerY + j);

			// Get index for 1D array
			int filterPosition = j * filterWidth + i;
			filteredValue += float(doc->GetOriginalPixel(x, y)[rgbOffset] * this->matrix[filterPosition]);
		}
	}

	return filteredValue;
}