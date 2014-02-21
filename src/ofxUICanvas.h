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

#pragma once

#include "ofxUIWidget.h"
#include "ofxUIDefines.h"
#include "ofxUIEventArgs.h"
#include "ofxUIWidgets.h"
#include "ofxUISlider.h"
#include <vector>
#include <map>

class ofxUICanvas : public ofxUIWidget, public ofxUIAppCBGlue
{
public:
    ~ofxUICanvas();
    ofxUICanvas(float defaultWidthSize = OFX_UI_GLOBAL_CANVAS_WIDTH, float defaultHeightSize = OFX_UI_GLOBAL_CANVAS_WIDTH);
    ofxUICanvas(const ofxUICanvas &other);              // Mitchell Nordine 2/2/14
    ofxUICanvas& operator=(const ofxUICanvas &other);   // Mitchell Nordine 2/2/14
    ofxUICanvas(ofxUIRectangle r);
    ofxUICanvas(float x, float y, float w, float h);
    ofxUICanvas(float x, float y, float w, float h, ofxUICanvas *sharedResources);
    ofxUICanvas(ofxUICanvas *sharedResources, float defaultWidthSize = OFX_UI_GLOBAL_CANVAS_WIDTH, float defaultHeightSize = OFX_UI_GLOBAL_CANVAS_WIDTH);
    ofxUICanvas(string title);
    
    void init(int x, int y, int w, int h, ofxUICanvas *sharedResources = NULL);
    void copyCanvasStyle(ofxUICanvas *styler);
    void copyCanvasProperties(ofxUICanvas *styler);
#ifndef OFX_UI_NO_XML
    virtual void saveSettings(string fileName);
    virtual void loadSettings(string fileName);
    void setTriggerWidgetsUponLoad(bool _bTriggerWidgetsUponLoad);
    bool getTriggerWidgetsUponLoad();
#endif
    ofxUIFont *getFontLarge();
    ofxUIFont *getFontMedium();
    ofxUIFont *getFontSmall();
    bool setFont(string filename, bool _bAntiAliased=true, bool _bFullCharacterSet=true, bool makeContours=false, float simplifyAmt=0.0, int dpi=OFX_UI_FONT_RESOLUTION);
    void setFontSize(ofxUIWidgetFontType _kind, int _size, int _resolution = OFX_UI_FONT_RESOLUTION);
    void setWidgetSpacing(float _widgetSpacing);
    float getWidgetSpacing();
    bool isEnabled();
    void setVisible(bool _visible);
	void toggleVisible();
    bool hasKeyboardFocus();
	void enable();
	void disable();
    virtual void update();
    virtual void draw();
    void exit();
    
#ifdef OFX_UI_TARGET_TOUCH
    virtual void canvasTouchDown(float x, float y, int id);
    virtual void canvasTouchMoved(float x, float y, int id);
    virtual void canvasTouchUp(float x, float y, int id);
    virtual void canvasTouchDoubleTap(float x, float y, int id);
    virtual void canvasTouchCancelled(float x, float y, int id);
    virtual void touchDown(float x, float y, int id);
	virtual void touchMoved(float x, float y, int id);
	virtual void touchUp(float x, float y, int id);
	virtual void touchDoubleTap(float x, float y, int id);
	virtual void touchCancelled(float x, float y, int id);
#else
	virtual void mouseMoved(int x, int y );
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void windowResized(int w, int h);
#endif	

    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual bool isHit(int x, int y);
    ofxUIWidget *getWidgetHit(float x, float y);
    
    void stateChange();
    virtual void autoSizeToFitWidgets();
    virtual void centerWidgetsOnCanvas(bool centerHorizontally=true, bool centerVertically=true);
    virtual void centerWidgetsHorizontallyOnCanvas();
    virtual void centerWidgetsVerticallyOnCanvas();
    virtual void centerWidgets();
    virtual void addModalWidget(ofxUIWidget *widget);
    virtual void removeModalWidget(ofxUIWidget *widget);
    virtual void removeWidgets();
    virtual void clearWidgets();  // Mitchell Nordine 2/2/14
    void removeWidget(ofxUIWidget *widget);
    void addWidget(ofxUIWidget *widget);
	
    ofxUIWidget* addWidgetPosition(ofxUIWidget *widget, 
                                   ofxUIWidgetPosition position = OFX_UI_WIDGET_POSITION_DOWN,
                                   ofxUIWidgetAlignment align = OFX_UI_ALIGN_LEFT,
                                   bool reAdd = false);
    
	ofxUIWidget* addWidgetDown(ofxUIWidget *widget, ofxUIWidgetAlignment align = OFX_UI_ALIGN_LEFT, bool reAdd = false);
	ofxUIWidget* addWidgetUp(ofxUIWidget *widget, ofxUIWidgetAlignment align = OFX_UI_ALIGN_LEFT, bool reAdd = false);
	ofxUIWidget* addWidgetRight(ofxUIWidget *widget, ofxUIWidgetAlignment align = OFX_UI_ALIGN_FREE, bool reAdd = false);
    ofxUIWidget* addWidgetLeft(ofxUIWidget *widget, ofxUIWidgetAlignment align = OFX_UI_ALIGN_FREE, bool reAdd = false);
    ofxUIWidget* addWidgetSouthOf(ofxUIWidget *widget, string referenceName, bool reAdd = false);
    ofxUIWidget* addWidgetNorthOf(ofxUIWidget *widget, string referenceName, bool reAdd = false);
    ofxUIWidget* addWidgetWestOf(ofxUIWidget *widget, string referenceName, bool reAdd = false);
    ofxUIWidget* addWidgetEastOf(ofxUIWidget *widget, string referenceName, bool reAdd = false);

    ofxUISpacer* addSpacer(float h = OFX_UI_GLOBAL_SPACING_HEIGHT);
    ofxUISpacer* addSpacer(string name, float h = OFX_UI_GLOBAL_SPACING_HEIGHT);
    ofxUISpacer* addSpacer(float w, float h);
    ofxUISpacer* addSpacer(float w, float h, string name);
    
    ofxUILabel *addLabel(string name, int size = OFX_UI_FONT_MEDIUM);
    ofxUILabel *addLabel(string name, string label, int size = OFX_UI_FONT_MEDIUM);
    
    ofxUIFPS *addFPS(int size = OFX_UI_FONT_MEDIUM);
    
    ofxUISlider* addSlider(string _name, float _min, float _max, float _value);
    ofxUISlider* addSlider(string _name, float _min, float _max, float _value, float w, float h, float x = 0, float y = 0);
    ofxUISlider* addSlider(string _name, float _min, float _max, float *_value);
    ofxUISlider* addSlider(string _name, float _min, float _max, float *_value, float w, float h, float x = 0, float y = 0);
    
    ofxUIIntSlider* addIntSlider(string _name, int _min, int _max, int _value);
    ofxUIIntSlider* addIntSlider(string _name, int _min, int _max, int _value, float w, float h, float x = 0, float y = 0);
    ofxUIIntSlider* addIntSlider(string _name, int _min, int _max, int *_value);
    ofxUIIntSlider* addIntSlider(string _name, int _min, int _max, int *_value, float w, float h, float x = 0, float y = 0);

    ofxUIDoubleSlider* addDoubleSlider(string _name, double _min, double _max, double _value);
    ofxUIDoubleSlider* addDoubleSlider(string _name, double _min, double _max, double _value, float w, float h, float x = 0, float y = 0);
    ofxUIDoubleSlider* addDoubleSlider(string _name, double _min, double _max, double *_value);
    ofxUIDoubleSlider* addDoubleSlider(string _name, double _min, double _max, double *_value, float w, float h, float x = 0, float y = 0);
    
    ofxUIRotarySlider* addRotarySlider(string _name, float _min, float _max, float _value, int _size = OFX_UI_FONT_SMALL);
    ofxUIRotarySlider* addRotarySlider(string _name, float _min, float _max, float _value, float w, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIRotarySlider* addRotarySlider(string _name, float _min, float _max, float *_value, int _size = OFX_UI_FONT_SMALL);
    ofxUIRotarySlider* addRotarySlider(string _name, float _min, float _max, float *_value, float w, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    
    ofxUIImageSlider* addImageSlider(string _name, string _pathURL, float _min, float _max, float _value);
    ofxUIImageSlider* addImageSlider(string _name, string _pathURL, float _min, float _max, float _value, float w, float h, float x = 0, float y = 0);
    ofxUIImageSlider* addImageSlider(string _name, string _pathURL, float _min, float _max, float *_value);
    ofxUIImageSlider* addImageSlider(string _name, string _pathURL, float _min, float _max, float *_value, float w, float h, float x = 0, float y = 0);
    
    ofxUINumberDialer *addNumberDialer(string _name, float _min, float _max, float _value, int _precision);
    ofxUINumberDialer *addNumberDialer(string _name, float _min, float _max, float *_value, int _precision);
    
    ofxUIMinimalSlider* addMinimalSlider(string _name, float _min, float _max, float _value, int size = OFX_UI_FONT_SMALL);
    ofxUIMinimalSlider* addMinimalSlider(string _name, float _min, float _max, float _value, float w, float h, float x = 0, float y = 0, int size = OFX_UI_FONT_SMALL);
    ofxUIMinimalSlider* addMinimalSlider(string _name, float _min, float _max, float *_value, int size = OFX_UI_FONT_SMALL);
    ofxUIMinimalSlider* addMinimalSlider(string _name, float _min, float _max, float *_value, float w, float h, float x = 0, float y = 0, int size = OFX_UI_FONT_SMALL);

    ofxUIRangeSlider* addRangeSlider(string _name, float _min, float _max, float _valuelow, float _valuehigh);
    ofxUIRangeSlider* addRangeSlider(string _name, float _min, float _max, float _valuelow, float _valuehigh, float w, float h, float x = 0, float y = 0);
    ofxUIRangeSlider* addRangeSlider(string _name, float _min, float _max, float *_valuelow, float *_valuehigh);
    ofxUIRangeSlider* addRangeSlider(string _name, float _min, float _max, float *_valuelow, float *_valuehigh, float w, float h, float x = 0, float y = 0);
    
    ofxUIFPSSlider* addFPSSlider(string _name, float _max = 400);
    ofxUIFPSSlider* addFPSSlider(string _name, float w, float h, float _max = 400, float x = 0, float y = 0);
    
    ofxUIRadio* addRadio(string _name, vector<string> names, int _orientation = OFX_UI_ORIENTATION_VERTICAL, int _size = OFX_UI_FONT_SMALL);
    ofxUIRadio* addRadio(string _name, vector<string> names, int _orientation, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    
    ofxUIButton* addButton(string _name, bool _value);
    ofxUIButton* addButton(string _name, bool _value, float w, float h, float x = 0, float y = 0);
    ofxUIButton* addButton(string _name, bool *_value);
    ofxUIButton* addButton(string _name, bool *_value, float w, float h, float x = 0, float y = 0);
    
    ofxUIToggle* addToggle(string _name, bool _value);
    ofxUIToggle* addToggle(string _name, bool _value, float w, float h, float x = 0, float y = 0);
    ofxUIToggle* addToggle(string _name, bool *_value);
    ofxUIToggle* addToggle(string _name, bool *_value, float w, float h, float x = 0, float y = 0);
    
    ofxUIToggleMatrix* addToggleMatrix(string _name, int _rows, int _cols);
    ofxUIToggleMatrix* addToggleMatrix(string _name, int _rows, int _cols, float w, float h);

    ofxUI2DPad* add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f _value);
    ofxUI2DPad* add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f _value, float w, float h, float x = 0, float y = 0);
    ofxUI2DPad* add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f *_value);
    ofxUI2DPad* add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f *_value, float w, float h, float x = 0, float y = 0);
        
    ofxUITextInput* addTextInput(string _name, string _textstring, int _size = -1);
    ofxUITextInput* addTextInput(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = -1);
    
    ofxUILabelToggle* addLabelToggle(string _name, bool _value, bool _justifyLeft = false);
    ofxUILabelToggle* addLabelToggle(string _name, bool _value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false);
    ofxUILabelToggle* addLabelToggle(string _name, bool *_value, bool _justifyLeft = false);
    ofxUILabelToggle* addLabelToggle(string _name, bool *_value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false);

    ofxUILabelButton* addLabelButton(string _name, bool _value, bool _justifyLeft = false);
    ofxUILabelButton* addLabelButton(string _name, bool _value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false);
    ofxUILabelButton* addLabelButton(string _name, bool *_value, bool _justifyLeft = false);
    ofxUILabelButton* addLabelButton(string _name, bool *_value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false);

    ofxUIDropDownList* addDropDownList(string _name, vector<string> items);
    ofxUIDropDownList* addDropDownList(string _name, vector<string> items, float w, float x = 0, float y = 0);

    ofxUIWaveform* addWaveform(string _name, float *_buffer, int _bufferSize, float _min = -1.0, float _max = 1.0, float _h = OFX_UI_GLOBAL_GRAPH_HEIGHT);
    ofxUIWaveform* addWaveform(string _name, float *_buffer, int _bufferSize, float _min, float _max, float _w, float _h);
    
    ofxUISpectrum* addSpectrum(string _name, float *_buffer, int _bufferSize, float _min = 0.0, float _max = 1.0, float _h = OFX_UI_GLOBAL_GRAPH_HEIGHT);
    ofxUISpectrum* addSpectrum(string _name, float *_buffer, int _bufferSize, float _min, float _max, float _w, float _h);
    
    ofxUIMovingGraph* addMovingGraph(string _name, vector<float> _buffer, int _bufferSize, float _min, float _max, float _h = OFX_UI_GLOBAL_GRAPH_HEIGHT);
    ofxUIMovingGraph* addMovingGraph(string _name, vector<float> _buffer, int _bufferSize, float _min, float _max, float _w, float _h);

    ofxUIImage *addImage(string _name, ofImage *_image, float _w, float _h, bool _showLabel = false);
    ofxUIImage *addImage(string _name, ofImage *_image, bool _showLabel = false);

    ofxUIBaseDraws *addBaseDraws(string _name, ofBaseDraws *_base, float _w, float _h, bool _showLabel = false);
    ofxUIBaseDraws *addBaseDraws(string _name, ofBaseDraws *_base, bool _showLabel = false);

    ofxUIImageSampler *addImageSampler(string _name, ofImage *_image, float _w, float _h);
    ofxUIImageSampler *addImageSampler(string _name, ofImage *_image);
    
    ofxUIBiLabelSlider *addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float _value, int _size = OFX_UI_FONT_SMALL);
    ofxUIBiLabelSlider *addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float *_value, int _size = OFX_UI_FONT_SMALL);
    ofxUIBiLabelSlider *addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float _value, float _w, float _h, int _size = OFX_UI_FONT_SMALL);
    ofxUIBiLabelSlider *addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float *_value, float _w, float _h, int _size = OFX_UI_FONT_SMALL);
    
    ofxUICircleSlider* addCircleSlider(string _name, float _min, float _max, float _value);
    ofxUICircleSlider* addCircleSlider(string _name, float _min, float _max, float _value, float w, float x = 0, float y = 0);
    ofxUICircleSlider* addCircleSlider(string _name, float _min, float _max, float *_value);
    ofxUICircleSlider* addCircleSlider(string _name, float _min, float _max, float *_value, float w, float x = 0, float y = 0);

    ofxUIValuePlotter* addValuePlotter(string _name, int _bufferSize, float _min, float _max, float *_value, float _h = OFX_UI_GLOBAL_GRAPH_HEIGHT);
    ofxUIValuePlotter* addValuePlotter(string _name, int _bufferSize, float _min, float _max, float *_value, float _w, float _h);
    
    ofxUI2DGraph *add2DGraph(string _name, ofxUIVec2f _rangeX, ofxUIVec2f _rangeY, int _bufferSize, float * _xValues, float * _yValues);
    ofxUI2DGraph *add2DGraph(string _name, ofxUIVec2f _rangeX, ofxUIVec2f _rangeY, int _bufferSize, float * _xValues, float * _yValues, float _w, float _h, float _x = 0, float _y = 0);

    ofxUIImageToggle *addImageToggle(string _name, string _path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIImageToggle *addImageToggle(string _name, string _path, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIImageToggle *addImageToggle(string _name, string _path, bool *_value, int _size = OFX_UI_FONT_SMALL);
    ofxUIImageToggle *addImageToggle(string _name, string _path, bool _value, int _size = OFX_UI_FONT_SMALL);

    ofxUIImageButton *addImageButton(string _name, string _path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIImageButton *addImageButton(string _name, string _path, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIImageButton *addImageButton(string _name, string _path, bool *_value, int _size = OFX_UI_FONT_SMALL);
    ofxUIImageButton *addImageButton(string _name, string _path, bool _value, int _size = OFX_UI_FONT_SMALL);
    
    ofxUIMultiImageButton *addMultiImageButton(string _name, string _path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIMultiImageButton *addMultiImageButton(string _name, string _path, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIMultiImageButton *addMultiImageButton(string _name, string _path, bool *_value, int _size = OFX_UI_FONT_SMALL);
    ofxUIMultiImageButton *addMultiImageButton(string _name, string _path, bool _value, int _size = OFX_UI_FONT_SMALL);
    
    ofxUIMultiImageToggle *addMultiImageToggle(string _name, string _path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIMultiImageToggle *addMultiImageToggle(string _name, string _path, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIMultiImageToggle *addMultiImageToggle(string _name, string _path, bool *_value, int _size = OFX_UI_FONT_SMALL);
    ofxUIMultiImageToggle *addMultiImageToggle(string _name, string _path, bool _value, int _size = OFX_UI_FONT_SMALL);
    
    ofxUITextArea* addTextArea(string _name, string _textstring, int _size = OFX_UI_FONT_MEDIUM);
    
    ofxUISortableList *addSortableList(string _name, vector<std::string> _items, int _size = -1);
    
    void resetPlacer();
    void setPlacer(ofxUIWidget *referenceWidget);
	void setLabelFont(ofxUILabel *label);
    void setRetinaResolution();
    void setGlobalSliderHeight(float _globalSliderHeight);
    void setGlobalGraphHeight(float _globalGraphHeight);
    void setGlobalButtonDimension(float _globalButtonDimension);
    void setGlobalSpacerHeight(float _globalSpacerHeight);
    float getGlobalSliderHeight();
    float getGlobalGraphHeight();
    float getGlobalButtonDimension();
    float getGlobalSpacerHeight();
    void setGlobalCanvasWidth(float _globalCanvasWidth);
    float getGlobalCanvasWidth();
	void setWidgetPosition(ofxUIWidgetPosition _position, int _align = -1);
    void setWidgetFontSize(ofxUIWidgetFontType _widgetFontSize);
    
    ofxUIWidgetPosition getWidgetPosition();
    ofxUIWidgetFontType getWidgetFontSize();
	void triggerEvent(ofxUIWidget *child);
    void setUIColors(ofxUIColor &cb, ofxUIColor &co, ofxUIColor &coh, ofxUIColor &cf, ofxUIColor &cfh, ofxUIColor &cp, ofxUIColor &cpo);
    void setTheme(int theme);
    ofxUIColor& getWidgetColorPadded();
	ofxUIColor& getWidgetColorPaddedOutline();
	ofxUIColor& getWidgetColorBack();
	ofxUIColor& getWidgetColorOutline();
	ofxUIColor& getWidgetColorOutlineHighlight();
	ofxUIColor& getWidgetColorFill();
	ofxUIColor& getWidgetColorFillHighlight();
    void setWidgetDrawingProperties(ofxUIWidget *widget);
    void setWidgetColor(ofxUIWidget *widget);
	void setWidgetColor(int _target, ofxUIColor _color);
    ofxUIWidget *getWidget(string _name, int widgetID = -1);
    void removeWidget(string _name);
    virtual void setAutoUpdate(bool _autoUpdate);
    virtual void setAutoDraw(bool _autoDraw);
    virtual void setPosition(int x, int y);
    virtual void setHeight(float _height);
    virtual void setWidth(float _width);
    virtual void setDimensions(float _width, float _height);
	void setDrawPadding(bool _draw_padded_rect);
    void setDrawWidgetPadding(bool _draw_padded_rect);
    bool getDrawWidgetPadding();
	void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    void setDrawWidgetPaddingOutline(bool _draw_padded_rect_outline);
    bool getDrawWidgetPaddingOutline();
    vector<ofxUIWidget*> getWidgets();
    vector<ofxUIWidget*> getWidgetsOfType(ofxUIWidgetType type);
	ofEvent<ofxUIEventArgs> newGUIEvent;

protected:
    void pushbackWidget(ofxUIWidget *widget, bool addWidgetToFront = false);
    //Easy Font setting contributed from Colin Duffy (colin@tomorrowevening.com)
    bool updateFont(ofxUIWidgetFontType _kind, string filename, int fontsize, bool _bAntiAliased=true, bool _bFullCharacterSet=false, bool makeContours=false, float simplifyAmt=0.3, int dpi=0);
    void checkForKeyFocus(ofxUIWidget *child);

	ofxUIFont *font_large;
	ofxUIFont *font_medium; 		
	ofxUIFont *font_small;
    bool bInsideCanvas;
 	
	ofxUIEventArgs *GUIevent; 
    int state;
    bool hasSharedResources;
    bool autoDraw;
    bool autoUpdate;
    
    multimap<string, ofxUIWidget*> widgets_map;
	vector<ofxUIWidget*> widgets;
    map<string, ofxUIWidget*> widgetsAreModal;
	vector<ofxUIWidget*> widgetsWithState;
	vector<ofxUIWidget*> lastAddeds; 
	ofxUIWidget *activeFocusedWidget; 
	bool enable_highlight_outline; 
	bool enable_highlight_fill;
	bool enabled;
    bool bTriggerWidgetsUponLoad;
    int uniqueIDs; 
    bool hasKeyBoard; 
    
    float widgetSpacing;
    float globalCanvasWidth;
    float globalSliderHeight;
    float globalGraphHeight;
    float globalButtonDimension;
    float globalSpacerHeight;
    
    string fontName;

    ofxUIWidgetPosition widgetPosition;
    ofxUIWidgetAlignment widgetAlign;
    ofxUIWidgetFontType widgetFontSize;
    
	ofxUIColor widget_color_back;
	ofxUIColor widget_color_outline;
	ofxUIColor widget_color_outline_highlight;
	ofxUIColor widget_color_fill;
	ofxUIColor widget_color_fill_highlight;
    ofxUIColor widget_color_padded_rect;
	ofxUIColor widget_color_padded_rect_outline;
    
    bool bDrawWidgetPadding;
    bool bDrawWidgetPaddingOutline;    
};