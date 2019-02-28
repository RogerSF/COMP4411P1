//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "Impressionist.h"
#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "PaintView.h"
#include "ImpBrush.h"
#include <iostream>
using namespace std;


#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}


void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA

	if(!valid())
	{

		glClearColor( 0.7f, 0.7f, 0.7f, 1.0 );

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		glClear( GL_COLOR_BUFFER_BIT );

		// Enable transparency
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow			= startrow + drawHeight;
	m_nStartCol			= scrollpos.x;
	m_nEndCol			= m_nStartCol + drawWidth;

	if ( m_pDoc->m_ucPainting && !isAnEvent) 
	{
		RestoreContent();

	}

	if ( m_pDoc->m_ucPainting && isAnEvent) 
	{

		// Clear it after processing.
		isAnEvent	= 0;	

		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );
		
		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			m_pDoc->m_pCurrentBrush->BrushBegin( source, target );
			// cout<<"Point coord: "<<coord.x<<" , " << coord.y <<endl;//"; target: " << target.x <<" , "<<target.y<<endl;
			break;
		case LEFT_MOUSE_DRAG:
			m_pDoc->m_pCurrentBrush->BrushMove( source, target );
			break;
		case LEFT_MOUSE_UP:
			m_pDoc->m_pCurrentBrush->BrushEnd( source, target );
			// Clipping the brush stroke as they are painted
			SaveCurrentContent();
			RestoreContent();
			break;
		case RIGHT_MOUSE_DOWN:
			m_pDoc->rightMousePos[1]->x = coord.x;
			m_pDoc->rightMousePos[1]->y = coord.y;
			cout<<m_pDoc->rightMousePos[0]->x <<" , "<< m_pDoc->rightMousePos[0]->y <<" , "<< m_pDoc->rightMousePos[1]->x << " , " << m_pDoc->rightMousePos[1]->y << " ---> ";
			break;
		case RIGHT_MOUSE_DRAG:

			break;
		case RIGHT_MOUSE_UP:
			m_pDoc->rightMousePos[0]->x = coord.x;
			m_pDoc->rightMousePos[0]->y = coord.y;
			cout<<m_pDoc->rightMousePos[0]->x <<" , "<< m_pDoc->rightMousePos[0]->y <<" , "<< m_pDoc->rightMousePos[1]->x << " , " << m_pDoc->rightMousePos[1]->y << endl;
			
			break;

		default:
			printf("Unknown event!!\n");		
			break;
		}
	}

	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA

}


int PaintView::handle(int event)
{
	switch(event)
	{
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		// Draw the marker on top of the original image view
		m_pDoc->m_pUI->m_origView->setMarkerPoint(coord);
		redraw();
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();

		m_pDoc->CursorHisPos[1] = m_pDoc->CursorHisPos[0];
		m_pDoc->CursorHisPos[0] = new Vector(coord.x, coord.y);
		// cout<<"CursorPos[0]: ( " << m_pDoc->CursorHisPos[0]->x << " , " << m_pDoc->CursorHisPos[0]->y << " ); CursorPos[1]: ( " << m_pDoc->CursorHisPos[1]->x << " , " << m_pDoc->CursorHisPos[1]->y << " ). "<<endl;

		// Draw the marker on top of the original image view
		m_pDoc->m_pUI->m_origView->setMarkerPoint(coord);
		break;
	case FL_MOUSEWHEEL:
		// Fancy function to increment or decrement the brush size using mouse wheel
		m_pDoc->m_pUI->setSize(m_pDoc->m_pUI->getSize() - Fl::event_dy());
		break;
	default:
		return 0;
		break;

	}

	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}


void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

//	glDrawBuffer(GL_FRONT);
}

void PaintView::autoPaint() {

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA

	if(!valid())
	{

		glClearColor( 0.7f, 0.7f, 0.7f, 1.0 );

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		glClear( GL_COLOR_BUFFER_BIT );

		// Enable transparency
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow			= startrow + drawHeight;
	m_nStartCol			= scrollpos.x;
	m_nEndCol			= m_nStartCol + drawWidth;

	for (int x = 1; x < drawWidth; x += 30) {
		for (int y = 1; y < drawHeight; y += 30) {
			Point source( x + m_nStartCol, m_nEndRow - y );
			Point target( x , m_nWindowHeight - y );
			
			for (int delta_x = 0; delta_x <= 5; delta_x++) {
				for (int delta_y = 0; delta_y < 5; delta_y++) {
					source.x += delta_x;
					source.y += delta_x;
					target.x += delta_y;
					target.y += delta_y;
					// cout<<source.x<<", "<<source.y<<"; "<<target.x<<", "<<target.y<<endl;
					m_pDoc->m_pCurrentBrush->BrushBegin( source, target );
					m_pDoc->m_pCurrentBrush->BrushMove( source, target );	
					m_pDoc->m_pCurrentBrush->BrushEnd( source, target );
					SaveCurrentContent();
				} 
			} 			
		}
	}

	// Point source( 50 + m_nStartCol, m_nEndRow - 40 );
	// Point target( 50 , m_nWindowHeight - 40 );	

	// Point source1( 70 + m_nStartCol, m_nEndRow - 40 + 20 );
	// Point target1( 70 , m_nWindowHeight - 40 + 20 );	


	// m_pDoc->m_pCurrentBrush->BrushBegin( source, target );
	// m_pDoc->m_pCurrentBrush->BrushMove( source1, target1 );
	
	// m_pDoc->m_pCurrentBrush->BrushEnd( source1, target1 );
	// SaveCurrentContent();
	// RestoreContent();
	// m_pDoc->m_pCurrentBrush->BrushEnd( source, target );
	// for (int x = 1; x < drawWidth; x+= 40 ){
	// 	for (int y = 1; y < drawHeight; y += 40) {
	// 		Point source( x + m_nStartCol, m_nEndRow - y );
	// 		Point target( x + m_nStartCol + 20, m_nEndRow - y + 20);
	// 		m_pDoc->m_pCurrentBrush->BrushBegin( source, source );
	// 		m_pDoc->m_pCurrentBrush->BrushMove( target, target );
	// 		// Clipping the brush stroke as they are painted
	// 		SaveCurrentContent();
	// 		RestoreContent();
	// 		m_pDoc->m_pCurrentBrush->BrushEnd( source, target );
	// 	}
	// }


	
}
