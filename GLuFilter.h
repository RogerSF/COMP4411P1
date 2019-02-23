#ifndef GLUFILTER_H
#define GLUFILTER_H

//
// GluFilter.h
//
// This is the header filter for GLuFilter

#include "ImpressionistDoc.h"

static float blurMatrix[9] =
{
	0.0625, 0.125, 0.0625,
	0.125, 0.250, 0.125,
	0.0625, 0.125, 0.0625
};

static float sharpenMatrix[9] =
{
	0, -1, 0,
	-1, 5, -1,
	0, -1, 0
};

class GLuFilter
{
public:
	GLuFilter(float* matrix, int width = 3, int height = 3);
	float filterPixel(const GLubyte* source, Point origin, int sourceWidth, int sourceHeight);
	
private:
	float* matrix;
	int filterWidth;
	int filterHeight;
};

#endif