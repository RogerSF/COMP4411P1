//
// paintview.h
//
// The header file for painting view of the input images
//

#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <gl/GLU.h>
#include <stdlib.h>

class ImpressionistDoc;

class PaintView : public Fl_Gl_Window
{
public:
	PaintView(int x, int y, int w, int h, const char* l); //x,y gives position; w,h gives size
	void draw();
	int handle(int event);
	void autoPaint();

	void refresh();
	
	void resizeWindow(int width, int height);

	void SaveCurrentContent();

	void RestoreContent(); 

	ImpressionistDoc *m_pDoc;

private:
	GLvoid* m_pPaintBitstart;
	int		m_nDrawWidth,
			m_nDrawHeight,
			m_nStartRow, 
			m_nEndRow,
			m_nStartCol, 
			m_nEndCol,
			m_nWindowWidth, 
			m_nWindowHeight;

};

#endif