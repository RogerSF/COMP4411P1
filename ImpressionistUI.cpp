//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.H>

#include <math.h>

#include "ImpressionistUI.h"
#include "ImpressionistDoc.h"
#include "ImpBrush.h"
#include <iostream>
using namespace std;

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image with the canvas unchanged
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_mural(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->muralImage(newfile);
	}
}

//------------------------------------------------------------------
// Automatically paint a graph
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_auto_paint(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();
	ImpressionistUI * ui = whoami(o);
	// to be implemented 
	// cout<< "Auto paint is called without implementation"<< endl;
	// pDoc -> autoPaint();
	ui -> m_paintView -> autoPaint();
	
}


//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	ImpressionistUI * ui = whoami(o);
	ui->m_mainWindow->hide();
	ui->m_brushDialog->hide();
	ui->m_colorChannelsDialog->hide();
}

//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_swapImages(Fl_Menu_* o, void* v)
{
	ImpressionistUI * ui = whoami(o);
	ImpressionistDoc * pDoc = ui->getDocument();
	unsigned char* tempPointer = pDoc->m_ucBitmap;
	pDoc->m_ucBitmap = pDoc->m_ucPainting;
	pDoc->m_ucPainting = tempPointer;

	ui->m_origView->refresh();
	ui->m_paintView->refresh();
}

void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v)
{
	ImpressionistUI * ui = whoami(o);
	ImpressionistDoc * pDoc = ui->getDocument();
	if (!pDoc->historyManager->isUndoAvailable()) return;
	unsigned char* history = pDoc->historyManager->undo();
	if(history != nullptr)
	{
		pDoc->m_ucPainting = history;
		ui->m_paintView->refresh();
	}
}

void ImpressionistUI::cb_redo(Fl_Menu_* o, void* v)
{
	ImpressionistUI * ui = whoami(o);
	ImpressionistDoc * pDoc = ui->getDocument();
	unsigned char* history = pDoc->historyManager->redo();
	if (history != nullptr)
	{
		pDoc->m_ucPainting = history;
		ui->m_paintView->refresh();
	}
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_colorChannels(class Fl_Menu_* o, void* v)
{
	ImpressionistUI * ui = whoami(o);

	ui->m_colorChannelsDialog->show();
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;

	switch (type) {
		// Disable brush size slider when using pressure brush
		case BRUSH_PRESSURE:
			pUI->m_LineWidthSlider->deactivate();
			pUI->m_LineAngleSlider->deactivate();
			pUI->m_BrushSizeSlider->deactivate();
			pUI->setSize(0);
			break;
		case BRUSH_POINTS:
		case BRUSH_SCATTERED_POINTS:
		case BRUSH_CIRCLES:
		case BRUSH_SCATTERED_CIRCLES:
		case BRUSH_BLUR:
			pUI->m_LineWidthSlider->deactivate();
			pUI->m_LineAngleSlider->deactivate();
			pUI->m_BrushSizeSlider->activate();
			pUI->m_StrokeDirectionChoice->deactivate();
			break;
		case BRUSH_LINES:
		case BRUSH_SCATTERED_LINES:
			pUI->m_LineWidthSlider->activate();
			pUI->m_LineAngleSlider->activate();
			pUI->m_BrushSizeSlider->activate();
			pUI->m_StrokeDirectionChoice->activate();
			break;
	}

	pDoc->setBrushType(type);
}

//-------------------------------------------------------------
// Sets the stroke direction to use 
// Called by the UI when a line brush and a stroke direction are chosen 
//-------------------------------------------------------------
void ImpressionistUI::cb_strokeDirectionChoice(Fl_Widget* o, void* v)
{	

	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;
	pDoc->setStrokeDirection(type);
	if (type == DIFFPICGRADIENT) {
		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->muralImage(newfile);
		}
	}

	
	// cout<<"Current Stroke Direction is "<<type<<endl;
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
	((ImpressionistUI*)(o->user_data()))->m_origView->setBrushSize(int(((Fl_Slider *)o)->value()));
}

//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_widthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_angleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineAngle=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//--------------------------------------------------------z---
void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAlpha=float( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates red color channels
//-----------------------------------------------------------
void ImpressionistUI::cb_redChannelSlide(class Fl_Widget* o, void* v)
{
	ImpressionistUI* ui = ((ImpressionistUI*)(o->user_data()));
	ui->m_redChannel = int(((Fl_Slider *)o)->value());
	ui->updateColorChannels();
}

//-----------------------------------------------------------
// Updates green color channels
//-----------------------------------------------------------
void ImpressionistUI::cb_greenChannelSlide(class Fl_Widget* o, void* v)
{
	ImpressionistUI* ui = ((ImpressionistUI*)(o->user_data()));
	ui->m_greenChannel = int(((Fl_Slider *)o)->value());
	ui->updateColorChannels();
}

//-----------------------------------------------------------
// Updates blue color channels
//-----------------------------------------------------------
void ImpressionistUI::cb_blueChannelSlide(class Fl_Widget* o, void* v)
{
	ImpressionistUI* ui = ((ImpressionistUI*)(o->user_data()));
	ui->m_blueChannel = int(((Fl_Slider *)o)->value());
	ui->updateColorChannels();
}



//-----------------------------------------------------------
// Updates the CursorHisPos Vector array
// Called by the UI when mouse moves over the window
//--------------------------------------------------------z---
// void ImpressionistUI::cb_cursor_pos(GLFWwindow* window, double xpos, double ypos)
// {

// 	//Vector* temp = m_pDoc->CursorHisPos[0];
// 	m_pDoc->CursorHisPos[1] = m_pDoc->CursorHisPos[0];
// 	m_pDoc->CursorHisPos[0] = new Vector(xpos, ypos);

// 	

// }




//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;
	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	if (size >= 0 && size <= 40)
	{
		m_nSize = size;
		m_origView->setBrushSize(size);
		m_BrushSizeSlider->value(m_nSize);
	}
}

//------------------------------------------------
// Return the line brush width
//------------------------------------------------
int ImpressionistUI::getLineWidth()
{
	return m_nLineWidth;
}

//-------------------------------------------------
// Set the line brush width
//-------------------------------------------------
void ImpressionistUI::setLineWidth( int width )
{
	m_nLineWidth = width;

	if (width<=40) 
		m_LineWidthSlider->value(m_nLineWidth);
}


//------------------------------------------------
// Return the line brush angle
//------------------------------------------------
int ImpressionistUI::getLineAngle()
{
	return m_nLineAngle;
}

//-------------------------------------------------
// Set the line brush angle
//-------------------------------------------------
void ImpressionistUI::setLineAngle( int angle )
{
	m_nLineAngle = angle;

	if (angle<=359) 
		m_LineAngleSlider->value(m_nLineAngle);
}

//------------------------------------------------
// Return the brush alpha
//------------------------------------------------
float ImpressionistUI::getAlpha()
{
	return m_nAlpha;
}

//-------------------------------------------------
// Set the brush alpha
//-------------------------------------------------
void ImpressionistUI::setAlpha( int alpha )
{
	m_nAlpha = alpha;

	if (alpha<=1.0) 
		m_BrushAlphaSlider->value(m_nAlpha);
}

float ImpressionistUI::getRedChannelRatio()
{
	return float(m_redChannel) / 100;
}

float ImpressionistUI::getGreenChannelRatio()
{
	return float(m_greenChannel) / 100;
}


float ImpressionistUI::getBlueChannelRatio()
{
	return float(m_blueChannel) / 100;
}

//-------------------------------------------------
// Update color channels
//-------------------------------------------------
void ImpressionistUI::updateColorChannels()
{
	
}


// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Mural...",	FL_ALT + 'm', (Fl_Callback *)ImpressionistUI::cb_mural },
		{ "&Auto-paint...",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_auto_paint },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		{ "&Color channels", FL_ALT + 'o', (Fl_Callback *)ImpressionistUI::cb_colorChannels, 0, FL_MENU_DIVIDER },
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Edit",		0, 0, 0, FL_SUBMENU },
		{ "&Undo",	FL_CTRL + 'z', (Fl_Callback *)ImpressionistUI::cb_undo },
		{ "&Redo",	FL_CTRL + FL_ALT + 'z', (Fl_Callback *)ImpressionistUI::cb_redo },
		{ 0 },

	{ "&Display",		0, 0, 0, FL_SUBMENU },
		{ "&Swap images",	FL_ALT + 'w', (Fl_Callback *)ImpressionistUI::cb_swapImages },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",					FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",						FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",					FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Pressure",				FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_PRESSURE},
  {"Blur",						FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_BLUR},
  {"Sharpen",					FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SHARPEN},
  {0}
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::strokeDirectionMenu[NUM_DIRECTION+1] = {
  {"Slider",					FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)SLIDER},
  {"Right Mouse",			FL_ALT+'k', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)RIGHTMOUSE},
  {"Gradient",				FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)GRADIENT},
  {"Diff Pic Gradient",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)DIFFPICGRADIENT},
  {"Brush Direction",		FL_ALT+'b', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)BRUSH_DIRECTION},
  {0}
};

//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
		// Create the main window
		m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    	m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_nLineWidth = 0;
	m_nLineAngle = 0;
	m_nAlpha = 1.0;

	m_redChannel = 100;
	m_greenChannel = 100;
	m_blueChannel = 100;

	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);
		
		// Add a clear canvas button
		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);

		// Add a stroke direction choice to the dialog
		m_StrokeDirectionChoice = new Fl_Choice(110,60,150,25,"&Stroke Direction");
		m_StrokeDirectionChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_StrokeDirectionChoice->menu(strokeDirectionMenu);
		m_StrokeDirectionChoice->callback(cb_strokeDirectionChoice);
		m_StrokeDirectionChoice->deactivate(); // Deactivate slider first because the initial brush selection is not line

		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Add line width slider to the dialog 
		m_LineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
        m_LineWidthSlider->labelfont(FL_COURIER);
        m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_nLineWidth);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->callback(cb_widthSlides);
		m_LineWidthSlider->deactivate(); // Deactivate slider first because the initial brush selection is not line

		// Add line angle slider to the dialog 
		m_LineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
		m_LineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
        m_LineAngleSlider->labelfont(FL_COURIER);
        m_LineAngleSlider->labelsize(12);
		m_LineAngleSlider->minimum(0);
		m_LineAngleSlider->maximum(359);
		m_LineAngleSlider->step(1);
		m_LineAngleSlider->value(m_nLineAngle);
		m_LineAngleSlider->align(FL_ALIGN_RIGHT);
		m_LineAngleSlider->callback(cb_angleSlides);
		m_LineAngleSlider->deactivate(); // Deactivate slider first because the initial brush selection is not line

		// Add alpha slider to the dialog 
		m_BrushAlphaSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		m_BrushAlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushAlphaSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushAlphaSlider->labelfont(FL_COURIER);
        m_BrushAlphaSlider->labelsize(12);
		m_BrushAlphaSlider->minimum(0);
		m_BrushAlphaSlider->maximum(1.00);
		m_BrushAlphaSlider->step(0.01);
		m_BrushAlphaSlider->value(m_nAlpha);
		m_BrushAlphaSlider->align(FL_ALIGN_RIGHT);
		m_BrushAlphaSlider->callback(cb_alphaSlides);

		//Try to capture cursor movement within the UI Initializer
		// glfwSetCursorPosCallback(m_mainWindow, cb_cursor_pos);

    m_brushDialog->end();

	// Init color channel window
	m_colorChannelsDialog = new Fl_Window(380, 100, "Color Channel Dialog");

		m_redChannelSlider = new Fl_Value_Slider(10, 10, 300, 20, "Red");
		m_redChannelSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_redChannelSlider->type(FL_HOR_NICE_SLIDER);
		m_redChannelSlider->labelfont(FL_COURIER);
		m_redChannelSlider->labelsize(12);
		m_redChannelSlider->minimum(0);
		m_redChannelSlider->maximum(100);
		m_redChannelSlider->step(1);
		m_redChannelSlider->value(m_redChannel);
		m_redChannelSlider->align(FL_ALIGN_RIGHT);
		m_redChannelSlider->callback(cb_redChannelSlide);

		m_greenChannelSlider = new Fl_Value_Slider(10, 40, 300, 20, "Green");
		m_greenChannelSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_greenChannelSlider->type(FL_HOR_NICE_SLIDER);
		m_greenChannelSlider->labelfont(FL_COURIER);
		m_greenChannelSlider->labelsize(12);
		m_greenChannelSlider->minimum(0);
		m_greenChannelSlider->maximum(100);
		m_greenChannelSlider->step(1);
		m_greenChannelSlider->value(m_greenChannel);
		m_greenChannelSlider->align(FL_ALIGN_RIGHT);
		m_greenChannelSlider->callback(cb_greenChannelSlide);

		m_blueChannelSlider = new Fl_Value_Slider(10, 70, 300, 20, "Blue");
		m_blueChannelSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_blueChannelSlider->type(FL_HOR_NICE_SLIDER);
		m_blueChannelSlider->labelfont(FL_COURIER);
		m_blueChannelSlider->labelsize(12);
		m_blueChannelSlider->minimum(0);
		m_blueChannelSlider->maximum(100);
		m_blueChannelSlider->step(1);
		m_blueChannelSlider->value(m_blueChannel);
		m_blueChannelSlider->align(FL_ALIGN_RIGHT);
		m_blueChannelSlider->callback(cb_blueChannelSlide);

	m_colorChannelsDialog->end();
}
