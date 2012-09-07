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

#ifndef OFXUI_WIDGET
#define OFXUI_WIDGET

class ofxUIWidget           
{
public:
    ofxUIWidget() 
    {        
        name = "base"; 
        ID = -1;
        hit = false; 
        visible = true; 
#ifdef TARGET_OPENGLES
        touchId = -1; 
#endif
        
        state = OFX_UI_STATE_NORMAL; 
        draw_back = true; 
        draw_outline = false; 
        draw_fill = false; 
        draw_fill_highlight = false;
        draw_outline_highlight = false;         

        padding = OFX_UI_GLOBAL_PADDING; 
		draw_padded_rect = OFX_UI_DRAW_PADDING; 						
		draw_padded_rect_outline = OFX_UI_DRAW_PADDING_OUTLINE; 						        
        
        color_back = OFX_UI_COLOR_BACK;								//the rect's back color
        color_outline = OFX_UI_COLOR_OUTLINE;						//the rect's outline color 
        color_outline_highlight = OFX_UI_COLOR_OUTLINE_HIGHLIGHT;   //the rect's onMouseOver outline highlight color         
		color_fill = OFX_UI_COLOR_FILL;								//the rect's fill color 
        color_fill_highlight = OFX_UI_COLOR_FILL_HIGHLIGHT;         //the rect's onMouseDown highlight color 

        color_padded_rect = OFX_UI_COLOR_PADDED;
        color_padded_rect_outline = OFX_UI_COLOR_PADDED_OUTLINE;     
        
        dead = false;
        embedded = false;
		modal = false;
    }
    
    virtual ~ofxUIWidget() 
    {
        if(rect != NULL)
        {
            delete rect; 
        }
        if(paddedRect != NULL)
        {
            delete paddedRect; 
        }
    }
    
    virtual void update() {}
    virtual void draw() 
    {
        ofPushStyle(); 
        
        ofEnableBlendMode(OF_BLENDMODE_ALPHA); 
        
        drawPadded();
        drawPaddedOutline();        

        drawBack();
        
        drawOutline();
        drawOutlineHighlight();
        
        drawFill();
        drawFillHighlight();
        
        ofPopStyle();
    }
    
    virtual void drawBack() 
    {
        if(draw_back)
        {
            ofFill(); 
            ofSetColor(color_back); 
            rect->draw(); 
        }
    }
    
    virtual void drawOutline() 
    {
        if(draw_outline)
        {
            ofNoFill();
            ofSetColor(color_outline); 
            rect->draw(); 
        } 
    }
    
    virtual void drawOutlineHighlight() 
    {
        if(draw_outline_highlight)
        {
            ofNoFill();
            ofSetColor(color_outline_highlight); 
            rect->draw();          
        }
    }    
    
    virtual void drawFill() 
    {
        if(draw_fill)
        {
            ofFill(); 
            ofSetColor(color_fill); 
            rect->draw(); 
        }
    }
    
    virtual void drawFillHighlight() 
    {
        if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
            rect->draw(); 
        }    
    }
    
    virtual void drawPadded()
    {
		if(draw_padded_rect && !embedded)
		{
            ofFill();
            ofSetColor(color_padded_rect); 
			paddedRect->draw(); 
		}                
    }
    
    virtual void drawPaddedOutline()
    {
        if(draw_padded_rect_outline && !embedded)
		{
            ofNoFill();
            ofSetColor(color_padded_rect_outline); 
			paddedRect->draw(); 
		}                
    }     
    
    
#ifdef TARGET_OPENGLES          //iOS Mode
    void touchDown(ofTouchEventArgs& touch)
    {
        if(touchId == -1)
        {    
            this->mousePressed(touch.x, touch.y, 0);
            if(hit)
            {
                touchId = touch.id;    
            }            
        }    
    }
    
    void touchMoved(ofTouchEventArgs& touch) 
    {
        if(touchId == touch.id)
        {
            this->mouseDragged(touch.x, touch.y, 0); 
        }       
    }
    
    void touchUp(ofTouchEventArgs& touch) 
    {
        if(touchId == touch.id)
        {
            this->mouseReleased(touch.x, touch.y, 0); 
            touchId = -1;                      
        }
    }
    
    void touchCancelled(ofTouchEventArgs& touch) 
    {
        if(touchId == touch.id)
        {
            this->mouseReleased(touch.x, touch.y, 0); 
            touchId = -1;                
        }
    }         
    
    void touchDoubleTap(ofTouchEventArgs& touch)
    {
        
    }
#endif

	virtual void mouseMoved(int x, int y ) {}
	virtual void mouseDragged(int x, int y, int button) {}
	virtual void mousePressed(int x, int y, int button) {}
	virtual void mouseReleased(int x, int y, int button) {}
    
	virtual void keyPressed(int key) {}
	virtual void keyReleased(int key) {}
	virtual void windowResized(int w, int h) {}           		
    
	virtual void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
	}
	
	virtual void setRectParent(ofxUIRectangle *_prect)
	{
		rect->setParent(_prect); 
	}

	virtual ofxUIWidget *getParent()
	{
		return parent; 
	}

	virtual ofxUIRectangle* getRect()
	{
		return rect; 
	}
	
	virtual void setName(string _name)
	{
		name = _name; 
	}
    
	virtual void setState(int _state)
    {
        state = _state; 
    }
    
	virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
	}
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline; 
	}    
    
	virtual void setDrawBack(bool _draw_back)
	{
		draw_back = _draw_back; 
	}

	virtual void setDrawOutline(bool _draw_outline)
	{
		draw_outline = _draw_outline; 
	}

	virtual void setDrawFill(bool _draw_fill)
	{
		draw_fill = _draw_fill; 
	}
	
	virtual void setDrawFillHighLight(bool _draw_fill_highlight)
	{
		draw_fill_highlight = _draw_fill_highlight; 
	}
	
	virtual void setDrawOutlineHighLight(bool _draw_outline_hightlight)
	{
		draw_outline_highlight = draw_outline_highlight; 
	}
	
	virtual void setColorBack(ofColor _color_back)
	{
		color_back = _color_back; 
	}
		
	virtual void setColorOutline(ofColor _color_outline)
	{
		color_outline = _color_outline; 
	}
	
	virtual void setColorOutlineHighlight(ofColor _color_outline_highlight)
	{
		color_outline_highlight = _color_outline_highlight; 
	}	

	virtual void setColorFill(ofColor _color_fill)
	{
		color_fill = _color_fill; 
	}
	
	virtual void setColorFillHighlight(ofColor _color_fill_highlight)
	{
		color_fill_highlight = _color_fill_highlight; 
	}
	
    virtual void setColorPadded(ofColor _color_padded_rect)
    {
        color_padded_rect = _color_padded_rect; 
    }
    
    virtual void setColorPaddedOutline(ofColor _color_padded_rect_outline)
    {
        color_padded_rect_outline = _color_padded_rect_outline; 
    }
    
	ofColor& getColorPadded()
	{
        return color_padded_rect;
	}

	ofColor& getColorPaddedOutline()
	{
        return color_padded_rect_outline;
	}
    
	ofColor& getColorBack()
	{
		return color_back; 
	}
	
	ofColor& getColorOutline()
	{
		return color_outline; 
	}
	
	ofColor& getColorOutlineHighlight()
	{
		return color_outline_highlight; 
	}	
	
	ofColor& getColorFill()
	{
		return color_fill; 
	}
	
	ofColor& getColorFillHighlight()
	{
		return color_fill_highlight; 
	}
	

	
    virtual int getKind()
	{
		return kind; 
	}
    
	virtual void setFont(ofTrueTypeFont *_font)
	{
		font = _font; 
	}
	
    virtual void setVisible(bool _visible)
    {
        visible = _visible; 
    }
    
    virtual bool isVisible()
    {
        return visible; 
    }
    
    virtual void toggleVisible()
    {
        visible =! visible; 
    }
    
    virtual bool isHit(float x, float y)
    {
        if(visible)
        {
            return rect->inside(x, y);
        }
        else
        {
            return false; 
        }
    }
    
	virtual string getName()
	{
		return name; 
	}
	
	virtual void triggerEvent(ofxUIWidget *child)
	{
		if(parent != NULL)
		{
			parent->triggerEvent(child); 
		}
	}
    
    virtual void triggerSelf()
    {
		if(parent != NULL)
		{
			parent->triggerEvent(this); 
		}        
    }
	
	virtual void setPadding(float _padding)
	{
		padding = _padding; 
		paddedRect->set(-padding, -padding, rect->getWidth()+padding*2.0, rect->getHeight()+padding*2.0);
	}
	
	virtual float getPadding()
	{
		return padding; 
	}
	
	virtual ofxUIRectangle *getPaddingRect()
	{
		return paddedRect; 
	}

    virtual void stateChange()
    { 
        
    }
    
    virtual bool isDraggable()
    {
        return false; 
    }
    
    virtual bool isEmbedded()
    {
        return embedded; 
    }
    
    virtual void setEmbedded(bool _embedded)
    {
        embedded = _embedded; 
    }
    
    void setID(int _id)
    {
        ID = _id;
    }
    
    int getID()
    {
        return ID;
    }
    
    virtual void addWidget(ofxUIWidget *widget)
    {
        //Experimental
    }    

    virtual void removeWidget(ofxUIWidget *widget)
    {
        //Experimental
    }    
    
    virtual bool hasLabel()
    {
        return false; 
    }
    
    virtual bool isModal()
    {
        return modal;
    }
    
    virtual void setModal(bool _modal)      //allows for piping mouse/touch input to widgets that are outside of parent's rect/canvas
    {
        modal = _modal; 
        if(modal == true)
        {
            if(parent != NULL)
            {
                parent->addModalWidget(this);
            }
        }
        else
        {
            if(parent != NULL)
            {
                parent->removeModalWidget(this);
            }
        }
    }

    virtual void addModalWidget(ofxUIWidget *widget)
    {
        
    }
    
    virtual void removeModalWidget(ofxUIWidget *widget)
    {
        
    }
    
    virtual void addEmbeddedWidget(ofxUIWidget *widget)
    {
        widget->setEmbedded(true);
        embeddedWidgets.push_back(widget);        
    }
    
    virtual int getEmbeddedWidgetsSize()
    {
        return embeddedWidgets.size();
    }
    
    ofxUIWidget *getEmbeddedWidget(int index)
    {
        return embeddedWidgets[index%embeddedWidgets.size()];
    }
    
    virtual void clearEmbeddedWidgets()
    {
        embeddedWidgets.clear();        //does not deallocate widgets, just deletes the pointers and sets the size to zero
    }
    
protected:    
	ofxUIWidget *parent; 
	ofxUIRectangle *rect; 	
	ofTrueTypeFont *font; 	
	
    string name;            //State Properties
	int kind; 
	bool visible;
    int ID;
    bool hit; 
    int state; 
    bool embedded;
    bool modal;
    
	bool draw_back;         //Rendering Properties 
	bool draw_outline; 
	bool draw_outline_highlight; 
	bool draw_fill; 
	bool draw_fill_highlight; 

	ofColor color_back; 
	ofColor color_outline; 
	ofColor color_outline_highlight;	
	ofColor color_fill; 
	ofColor color_fill_highlight; 

	float padding;          //Spacing/Padding Purposes
	ofxUIRectangle *paddedRect; 	

	bool draw_padded_rect; 
	bool draw_padded_rect_outline;     
    ofColor color_padded_rect; 
	ofColor color_padded_rect_outline;
    
    vector<ofxUIWidget *> embeddedWidgets; 
    
#ifdef TARGET_OPENGLES          //iOS Mode
    int touchId;     
#endif
    
    bool dead; 
};

#endif
