//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

	// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;
	Fl_Choice*			m_StrokeDirectionChoice;

	Fl_Slider*			m_BrushSizeSlider;
	Fl_Slider*			m_LineWidthSlider;
	Fl_Slider*			m_LineAngleSlider;
	Fl_Slider*			m_BrushAlphaSlider;

	Fl_Button*          m_ClearCanvasButton;

	// Color channel dialog
	Fl_Window*			m_colorChannelsDialog;

	Fl_Slider*			m_redChannelSlider;
	Fl_Slider*			m_greenChannelSlider;
	Fl_Slider*			m_blueChannelSlider;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);
	void				updateColorChannels();

	// Interface to get attribute

	int				getSize();
	void				setSize(int size);

	int				getLineWidth();
	void				setLineWidth(int width);

	int				getLineAngle();
	void				setLineAngle(int angle);

	float				getAlpha();
	void				setAlpha(int angle);

	float				getRedChannelRatio();
	float				getGreenChannelRatio();
	float				getBlueChannelRatio();

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int m_nSize;
	int m_nLineWidth;
	int m_nLineAngle;
	float m_nAlpha;

	// Color Channels
	int m_redChannel;
	int m_greenChannel;
	int m_blueChannel;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		strokeDirectionMenu[NUM_DIRECTION+1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	
	//call back function to record cursor positions
	// static void 	cb_cursor_pos(GLFWwindow* window, double xpos, double ypos);
	
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_mural(Fl_Menu_* o, void* v);
	static void	cb_auto_paint(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_colorChannels(Fl_Menu_* o, void* v);
	static void	cb_swapImages(Fl_Menu_* o, void* v);
	static void	cb_undo(Fl_Menu_* o, void* v);
	static void	cb_redo(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_strokeDirectionChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void	cb_widthSlides(Fl_Widget* o, void* v);
	static void	cb_angleSlides(Fl_Widget* o, void* v);
	static void	cb_alphaSlides(Fl_Widget* o, void* v);

	static void	cb_redChannelSlide(Fl_Widget* o, void* v);
	static void	cb_greenChannelSlide(Fl_Widget* o, void* v);
	static void	cb_blueChannelSlide(Fl_Widget* o, void* v);

};

#endif
