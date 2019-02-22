//
// originalview.cpp
//
// The code maintaining the original view of the input images
//

#include "Impressionist.h"
#include "ImpressionistDoc.h"
#include "OriginalView.h"
#include <cmath>

#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#endif

OriginalView::OriginalView(int			x, 
						   int			y, 
						   int			w, 
						   int			h, 
						   const char*	l)
							: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}

void OriginalView::draw()
{
	if(!valid())
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		// Tell openGL to read from the front buffer when capturing
		// out paint strokes 
		glReadBuffer( GL_FRONT );
		ortho();

	}

	glClear( GL_COLOR_BUFFER_BIT );

	if ( m_pDoc->m_ucBitmap ) 
	{
		// note that both OpenGL pixel storage and the Windows BMP format
		// store pixels left-to-right, BOTTOM-to-TOP!!  thus all the fiddling
		// around with startrow.

		m_nWindowWidth=w();
		m_nWindowHeight=h();

		int drawWidth, drawHeight;
		GLvoid* bitstart;

		// we are not using a scrollable window, so ignore it
		Point scrollpos;	// = GetScrollPosition();
		scrollpos.x=scrollpos.y=0;

		drawWidth	= min( m_nWindowWidth, m_pDoc->m_nWidth );
		drawHeight	= min( m_nWindowHeight, m_pDoc->m_nHeight );

		int	startrow	= m_pDoc->m_nHeight - (scrollpos.y + drawHeight);
		if ( startrow < 0 ) 
			startrow = 0;


		bitstart = m_pDoc->m_ucBitmap + 3 * ((m_pDoc->m_nWidth * startrow) + scrollpos.x);

		// just copy image to GLwindow conceptually
		glRasterPos2i( 0, m_nWindowHeight - drawHeight );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
		glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nWidth );
		glDrawBuffer( GL_BACK );
		glDrawPixels( drawWidth, drawHeight, GL_RGB, GL_UNSIGNED_BYTE, bitstart );
		drawMarker(); // Draw the marker
	}
			
	glFlush();
}

void OriginalView::refresh()
{
	redraw();
}

void OriginalView::resizeWindow(int	width, 
								int	height)
{
	resize(x(), y(), width, height);
}

void OriginalView::setMarkerPoint(const Point& marker)
{
	this->marker = marker;
	redraw(); // Trigger redraw to draw the marker on top of the original image
}

void OriginalView::setBrushSize(const int size)
{
	this->brushSize = size;
	redraw();
}


void OriginalView::drawMarker()
{
	float correctedY = m_nWindowHeight - this->marker.y;

	// Draw the marker dot
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(255, 0, 0);
	glVertex2d(this->marker.x, correctedY);
	for (int i = 0; i < 360; i++) {
		float angle = i * M_PI / 180;
		glVertex2f(this->marker.x + this->markerRadius * cos(angle), correctedY + this->markerRadius * sin(angle));
	}
	glEnd();

	// Draw the brush size indicator
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		float angle = i * M_PI / 180;
		glVertex2f(this->marker.x + this->brushSize * cos(angle), correctedY + this->brushSize * sin(angle));
	}
	glEnd();
}
