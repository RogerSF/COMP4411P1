//
// BlurBrush.cpp
//
// The implementation of Blur Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "BlurBrush.h"

extern float frand();

BlurBrush::BlurBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void BlurBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize((float)size);

	BrushMove(source, target);
}

void BlurBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("BlurBrush::BrushMove, document is NULL\n");
		return;
	}

	glBegin(GL_POINTS);

		setColorWithFilter(source);
		glVertex2d(target.x, target.y);

	glEnd();
}

void BlurBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void BlurBrush::setColorWithFilter(const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte color[4];

	memcpy(color, pDoc->GetOriginalPixel(source), 3);
	color[0] = pDoc->blurFilter->filterPixel(pDoc, 0, source, pDoc->m_nWidth, pDoc->m_nHeight);
	color[1] = pDoc->blurFilter->filterPixel(pDoc, 1, source, pDoc->m_nWidth, pDoc->m_nHeight);
	color[2] = pDoc->blurFilter->filterPixel(pDoc, 2, source, pDoc->m_nWidth, pDoc->m_nHeight);

	color[0] = color[0] * pDoc->m_pUI->getRedChannelRatio();
	color[1] = color[1] * pDoc->m_pUI->getBlueChannelRatio();
	color[2] = color[2] * pDoc->m_pUI->getGreenChannelRatio();
	color[3] = GLubyte(int(pDoc->m_pUI->getAlpha() * 255));

	glColor4ubv(color);
}

