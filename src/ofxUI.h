/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef OFXUI
#define OFXUI

#include "ofMain.h"

#ifndef OFX_UI_NO_XML
	#include "ofxXmlSettings.h"                                             //Using ofxXmlSettings to save and load state
#endif

#define OFX_UI_STATE_NORMAL 0
#define OFX_UI_STATE_OVER 1
#define OFX_UI_STATE_DOWN 2
#define OFX_UI_STATE_SUSTAINED 3

#define OFX_UI_GLOBAL_PADDING 4
#define OFX_UI_GLOBAL_WIDGET_SPACING 8

#define OFX_UI_COLOR_BACK ofColor(0, 25)                                //the rect's back color
#define OFX_UI_COLOR_OUTLINE ofColor(255, 255, 255, 100)                //the rect's outline color 
#define OFX_UI_COLOR_OUTLINE_HIGHLIGHT ofColor(255, 255, 255, 200)      //the rect's onMouseOver outline highlight color         
#define OFX_UI_COLOR_FILL ofColor(255, 255, 255, 200)                   //the rect's fill color 
#define OFX_UI_COLOR_FILL_HIGHLIGHT ofColor(255, 255, 255, 255)         //the rect's onMouseDown highlight color 

#define OFX_UI_COLOR_PADDED ofColor(0, 100)                             //the rect's padded color
#define OFX_UI_COLOR_PADDED_OUTLINE ofColor(255, 200)         //the rect's padded outline color 

#define OFX_UI_DRAW_PADDING false
#define OFX_UI_DRAW_PADDING_OUTLINE false

#define OFX_UI_TEXTINPUT_ON_ENTER 0 
#define OFX_UI_TEXTINPUT_ON_FOCUS 1
#define OFX_UI_TEXTINPUT_ON_UNFOCUS 2

enum ofxWidgetType
{
	OFX_UI_WIDGET_LABEL = 0,
	OFX_UI_WIDGET_CANVAS = 1,
	OFX_UI_WIDGET_TOGGLE = 2,
	OFX_UI_WIDGET_BUTTON = 3,
	OFX_UI_WIDGET_SLIDER_H = 4,
	OFX_UI_WIDGET_SLIDER_V = 5,
	OFX_UI_WIDGET_RSLIDER_H = 6,
	OFX_UI_WIDGET_RSLIDER_V = 7,	
	OFX_UI_WIDGET_NUMBERDIALER = 8,
	OFX_UI_WIDGET_RADIO = 9,
	OFX_UI_WIDGET_FPS = 10,
	OFX_UI_WIDGET_2DPAD = 11, 
	OFX_UI_WIDGET_TEXTINPUT = 12, 
	OFX_UI_WIDGET_WAVEFORM = 13,
	OFX_UI_WIDGET_SPECTRUM = 14,
	OFX_UI_WIDGET_IMAGE = 15, 
    OFX_UI_WIDGET_LABELBUTTON = 16, 
    OFX_UI_WIDGET_LABELTOGGLE = 17,
    OFX_UI_WIDGET_TOGGLEMATRIX = 18,
    OFX_UI_WIDGET_IMAGEBUTTON = 19, 
    OFX_UI_WIDGET_IMAGETOGGLE = 20,
    OFX_UI_WIDGET_ROTARYSLIDER = 21, 
    OFX_UI_WIDGET_DROPDOWNLIST = 22, 
    OFX_UI_WIDGET_SPACER = 23, 
    OFX_UI_WIDGET_MOVINGGRAPH = 24,
    OFX_UI_WIDGET_MINIMALSLIDER = 25,
    OFX_UI_WIDGET_BILABELSLIDER = 26,
    OFX_UI_WIDGET_CIRCLESLIDER = 27, 
    OFX_UI_WIDGET_IMAGESAMPLER = 28,
	OFX_UI_WIDGET_SCROLLABLECANVAS = 29, 
    OFX_UI_WIDGET_MULTIIMAGEBUTTON = 30,
    OFX_UI_WIDGET_MULTIIMAGETOGGLE = 31,
    OFX_UI_WIDGET_MULTIIMAGESLIDER_H = 32,
    OFX_UI_WIDGET_MULTIIMAGESLIDER_V = 33,
    OFX_UI_WIDGET_IMAGESLIDER_H = 34,
    OFX_UI_WIDGET_IMAGESLIDER_V = 35, 
    OFX_UI_WIDGET_CUSTOMIMAGEBUTTON = 36,
    OFX_UI_WIDGET_TEXTAREA = 37,
    OFX_UI_WIDGET_CUSTOMWIDGET = 38,
    OFX_UI_WIDGET_BASE_DRAWS = 39
};

enum ofxWidgetOrientation
{
	OFX_UI_ORIENTATION_VERTICAL = 0, 
	OFX_UI_ORIENTATION_HORIZONTAL = 1
};

enum ofxWidgetInputDirection
{
	OFX_UI_DIRECTION_NORTHSOUTH = 0,
	OFX_UI_DIRECTION_SOUTHNORTH = 1,    
	OFX_UI_DIRECTION_EASTWEST = 2,
	OFX_UI_DIRECTION_WESTEAST = 3
};

enum ofxWidgetAlignment
{
	OFX_UI_ALIGN_LEFT = 0,
	OFX_UI_ALIGN_FREE = 1,
	OFX_UI_ALIGN_RIGHT = 2,    
    OFX_UI_ALIGN_TOP = 3, 
    OFX_UI_ALIGN_BOTTOM = 4
};

enum ofxWidgetPosition
{
	OFX_UI_WIDGET_POSITION_DOWN = 0,
	OFX_UI_WIDGET_POSITION_UP = 1,
	OFX_UI_WIDGET_POSITION_LEFT = 2,
	OFX_UI_WIDGET_POSITION_RIGHT = 3
};

enum ofxWidgetFontType 
{
	OFX_UI_FONT_LARGE = 0, 
	OFX_UI_FONT_MEDIUM = 1, 
	OFX_UI_FONT_SMALL = 2 	
};

enum ofxWidgetColorType
{
	OFX_UI_WIDGET_COLOR_BACK = 0, 
	OFX_UI_WIDGET_COLOR_OUTLINE = 1,
	OFX_UI_WIDGET_COLOR_OUTLINE_HIGHLIGHT = 2, 
	OFX_UI_WIDGET_COLOR_FILL = 3, 
	OFX_UI_WIDGET_COLOR_FILL_HIGHLIGHT = 4, 
    OFX_UI_WIDGET_COLOR_PADDED = 5, 
	OFX_UI_WIDGET_COLOR_PADDED_OUTLINE = 6 
    
}; 

enum ofxUIThemeType
{
    OFX_UI_THEME_DEFAULT = 0,
    OFX_UI_THEME_HACKER,
    OFX_UI_THEME_HIPSTER,
    OFX_UI_THEME_DIETER,
    OFX_UI_THEME_BARBIE,
    OFX_UI_THEME_WINDOWS,
    OFX_UI_THEME_MACOSX,
    OFX_UI_THEME_ZOOLANDER,
    OFX_UI_THEME_VEGAN,
    OFX_UI_THEME_BERLIN,
    OFX_UI_THEME_METALGEAR,
    OFX_UI_THEME_TEALLIME,
    OFX_UI_THEME_VEGAN2,
    OFX_UI_THEME_RUSTIC,
    OFX_UI_THEME_MIDNIGHT,
    OFX_UI_THEME_MINBLUE,
    OFX_UI_THEME_LIMESTONE,
    OFX_UI_THEME_SPEARMINT,
    OFX_UI_THEME_MINPINK,
    OFX_UI_THEME_PEPTOBISMOL, 
    OFX_UI_THEME_BILEBLUE,
    OFX_UI_THEME_COOLCLAY,
    OFX_UI_THEME_BLUEBLUE,
    OFX_UI_THEME_PINKPANTHER,
    OFX_UI_THEME_MAROON,
    OFX_UI_THEME_PINKLATTE,
    OFX_UI_THEME_MINGREEN,
    OFX_UI_THEME_HELLOYELLOW,
    OFX_UI_THEME_TEALTEAL,
    OFX_UI_THEME_RUSTICORANGE,
    OFX_UI_THEME_TEALSALMON,
    OFX_UI_THEME_CITRUSBLUE,
    OFX_UI_THEME_LIMEPURPLE,
    OFX_UI_THEME_LIMESTONE2,
    OFX_UI_THEME_COOLPURPLE,
    OFX_UI_THEME_GRAYRED,
    OFX_UI_THEME_METALGEAR2,
    OFX_UI_THEME_LIGHTPINK,
    OFX_UI_THEME_MINPINK2,
    OFX_UI_THEME_MAXPINK,
    OFX_UI_THEME_MINYELLOW,
    OFX_UI_THEME_MINLIME,
    OFX_UI_THEME_MINORANGE,
    OFX_UI_THEME_GRAYDAY,
    OFX_UI_THEME_MINBLACK
};



//#ifdef TARGET_ANDROID
//#define OFX_UI_FONT_NAME "newmediafett.ttf"
//#else
#define OFX_UI_FONT_NAME "GUI/NewMedia Fett.ttf"
//#endif

#define OFX_UI_FONT_RESOLUTION 150
#define OFX_UI_FONT_LARGE_SIZE 10
#define OFX_UI_FONT_MEDIUM_SIZE 8
#define OFX_UI_FONT_SMALL_SIZE 6

#define OFX_UI_LABEL_DRAW_BACK false

#include "ofxUIRectangle.h"
#include "ofxUIWidget.h"
#include "ofxUIWidgetWithLabel.h"
#include "ofxUIEventArgs.h"
#include "ofxUILabel.h"
#include "ofxUIFPS.h"
#include "ofxUISlider.h"
#include "ofxUIMultiImageSlider.h"
#include "ofxUIImageSlider.h"
#include "ofxUIFPSSlider.h"
#include "ofxUIMinimalSlider.h"
#include "ofxUICircleSlider.h"
#include "ofxUIBiLabelSlider.h"
#include "ofxUIRangeSlider.h"
#include "ofxUIToggle.h"
#include "ofxUIButton.h"
#include "ofxUICustomImageButton.h"
#include "ofxUIMultiImageButton.h"
#include "ofxUIMultiImageToggle.h"
#include "ofxUIRadio.h"
#include "ofxUI2DPad.h"
#include "ofxUITextInput.h"
#include "ofxUITextArea.h"
#include "ofxUINumberDialer.h"
#include "ofxUILabelButton.h"
#include "ofxUILabelToggle.h"
#include "ofxUIToggleMatrix.h"
#include "ofxUIImageButton.h"
#include "ofxUIImageToggle.h"
#include "ofxUIRotarySlider.h"
#include "ofxUISpacer.h"
#include "ofxUIDropDownList.h"
#include "ofxUIWaveform.h"
#include "ofxUISpectrum.h"
#include "ofxUIMovingGraph.h"
#include "ofxUIImage.h"
#include "ofxUIBaseDraws.h"
#include "ofxUIImageSampler.h"
#include "ofxUICanvas.h"
#include "ofxUIScrollableCanvas.h"


#endif
