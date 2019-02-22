//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "ImpBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, char* name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source, const float alpha)
{
	ImpressionistDoc* pDoc = GetDocument();


	GLubyte color[4];

	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
	color[3] = GLubyte(int(alpha*255));

	glColor4ubv( color );

}

//----------------------------------------------------
// Return the gradient at the source point
// returned point.x is x gradient point.y is the y gradient
//----------------------------------------------------
Vector* ImpBrush::GetGradient (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();

	//0.299R + 0.587G + 0.144B
	GLubyte color_source[3];
	memcpy ( color_source, pDoc->GetOriginalPixel( source ), 3 );
	float grayintense_source = 0.299 * color_source[0] + 0.587 * color_source[1] + 0.144 * color_source[2] ;

	GLubyte color1[3];
	memcpy ( color1, pDoc->GetOriginalPixel( source.x-1, source.y-1 ), 3 );
	float grayintense1 = 0.299 * color1[0] + 0.587 * color1[1] + 0.144 * color1[2] ;

	GLubyte color2[3];
	memcpy ( color2, pDoc->GetOriginalPixel( source.x, source.y-1 ), 3 );
	float grayintense2 = 0.299 * color2[0] + 0.587 * color2[1] + 0.144 * color2[2] ;

	GLubyte color3[3];
	memcpy ( color3, pDoc->GetOriginalPixel( source.x+1, source.y-1 ), 3 );
	float grayintense3 = 0.299 * color3[0] + 0.587 * color3[1] + 0.144 * color3[2] ;

	GLubyte color4[3];
	memcpy ( color4, pDoc->GetOriginalPixel( source.x+2, source.y-1 ), 3 );
	float grayintense4 = 0.299 * color4[0] + 0.587 * color4[1] + 0.144 * color4[2] ;

	GLubyte color5[3];
	memcpy ( color5, pDoc->GetOriginalPixel( source.x-1, source.y ), 3 );
	float grayintense5 = 0.299 * color5[0] + 0.587 * color5[1] + 0.144 * color5[2] ;

	GLubyte color6[3];
	memcpy ( color6, pDoc->GetOriginalPixel( source.x+1, source.y ), 3 );
	float grayintense6 = 0.299 * color6[0] + 0.587 * color6[1] + 0.144 * color6[2] ;

	GLubyte color7[3];
	memcpy ( color7, pDoc->GetOriginalPixel( source.x+2, source.y ), 3 );
	float grayintense7 = 0.299 * color7[0] + 0.587 * color7[1] + 0.144 * color7[2] ;

	GLubyte color8[3];
	memcpy ( color8, pDoc->GetOriginalPixel( source.x-1, source.y+1 ), 3 );
	float grayintense8 = 0.299 * color8[0] + 0.587 * color8[1] + 0.144 * color8[2] ;

	GLubyte color9[3];
	memcpy ( color9, pDoc->GetOriginalPixel( source.x, source.y+1 ), 3 );
	float grayintense9 = 0.299 * color9[0] + 0.587 * color9[1] + 0.144 * color9[2] ;

	GLubyte color10[3];
	memcpy ( color10, pDoc->GetOriginalPixel( source.x+1, source.y+1 ), 3 );
	float grayintense10 = 0.299 * color10[0] + 0.587 * color10[1] + 0.144 * color10[2] ;

	GLubyte color11[3];
	memcpy ( color11, pDoc->GetOriginalPixel( source.x+2, source.y+1 ), 3 );
	float grayintense11 = 0.299 * color11[0] + 0.587 * color11[1] + 0.144 * color11[2] ;

	GLubyte color12[3];
	memcpy ( color12, pDoc->GetOriginalPixel( source.x-1, source.y+2 ), 3 );
	float grayintense12 = 0.299 * color12[0] + 0.587 * color12[1] + 0.144 * color12[2] ;

	GLubyte color13[3];
	memcpy ( color13, pDoc->GetOriginalPixel( source.x, source.y+2 ), 3 );
	float grayintense13 = 0.299 * color13[0] + 0.587 * color13[1] + 0.144 * color13[2] ;

	GLubyte color14[3];
	memcpy ( color14, pDoc->GetOriginalPixel( source.x+1, source.y+2 ), 3 );
	float grayintense14 = 0.299 * color14[0] + 0.587 * color14[1] + 0.144 * color14[2] ;

	float blurred_source = grayintense1 / 16 + grayintense2 / 8 + grayintense3 / 16 + grayintense5 / 8 + grayintense_source /4 + grayintense6 / 8 + grayintense8 / 16 + grayintense9 / 8 + grayintense10 / 16;
	float blurred_xneighbour = grayintense2 / 16 + grayintense3 / 8 + grayintense4 / 16 + grayintense_source / 8 + grayintense6 / 4 + grayintense7 / 8 + grayintense9 / 16 + grayintense10 / 8 + grayintense11 / 16;
	float blurred_yneighbour = grayintense5 / 16 + grayintense_source / 8 + grayintense6 / 16 + grayintense8 / 8 + grayintense9 / 4 + grayintense10 / 8 + grayintense12 / 16 + grayintense13 / 8 + grayintense14 / 16;
	
	Vector* result = new Vector(blurred_xneighbour - blurred_source, blurred_source - blurred_yneighbour);	
	
	return result;
}