// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "Impressionist.h"
#include "Bitmap.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType
	void	setStrokeDirection(int type);			// called by the UI to set the strokeDirection
	int		getSize();						// get the UI size
	void	setSize(int size);				// set the UI size
	char*	getImageName();					// get the current image name
	

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting. 
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;

	Vector** CursorHisPos;


	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	

	//The current stroke direction
	int m_pCurrentDirection = 0;
	
	// brush parameters
	int m_nSize;	
	int m_nLineWidth;
	int m_nLineAngle;
	float m_nAlpha;

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  

	


private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
