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

#ifndef OFXUI_TEXT_INPUT
#define OFXUI_TEXT_INPUT

#include "ofxUIWidgetWithLabel.h"

class ofxUITextInput : public ofxUIWidgetWithLabel
{
public:
    ofxUITextInput(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM)
    {
        init(_name, _textstring, w, h, x, y, _size);
    }
    
    // DON'T USE THE NEXT CONSTRUCTORS
    // This is maintained for backward compatibility and will be removed on future releases
    
    ofxUITextInput(float x, float y, float w, string _name, string _textstring, int _size, float h = 0)
    {
        init(_name, _textstring, w, h, x, y, _size);
        ofLogWarning("OFXUITEXTINPUT: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUITextInput(float w, string _name, string _textstring, int _size, float h = 0)
    {
        init(_name, _textstring, w, h, 0, 0, _size);
        ofLogWarning("OFXUITEXTINPUT: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }    
    
    void init(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
		name = _name; 		
		kind = OFX_UI_WIDGET_TEXTINPUT; 		
		textstring = _textstring; 
		defaultstring = _textstring; 
		displaystring = _textstring; 
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, padding*2.0);
		paddedRect->setParent(rect); 
        
		clicked = false;                                            //the widget's value
        autoclear = true; 
		
		label = new ofxUILabel(padding*2.0,0,(name+" LABEL"), _size); 
		label->setParent(label); 
		label->setRectParent(rect); 
        label->setEmbedded(true);
        
		triggerType = OFX_UI_TEXTINPUT_ON_FOCUS;
		cursorWidth = 0; spaceOffset = 0; 		
		theta = 0;         
    }
    
    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
        label->setDrawPadding(false);
	}
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline; 
        label->setDrawPaddingOutline(false);
	}  
    
    virtual void drawFill() 
    {
        if(draw_fill)
        {
            ofFill(); 
            ofSetColor(color_fill); 
            rect->draw(); 
        }
        if(clicked)
		{
            ofNoFill();
            ofSetColor(color_outline_highlight);
            rect->draw();
            
			float h = label->getRect()->height; 
			
			float ph = rect->getHeight(); 
			label->getRect()->y = ph/2.0 - h/2.0; 
			
            ofFill(); 
			ofSetColor(label->getColorFillHighlight(), 255.0*fabs(cos(theta))); 
			theta +=0.05; 
			
			spaceOffset = label->getStringWidth(displaystring+".")-cursorWidth; 
            if(spaceOffset > rect->width-padding*4.0)
            {
                spaceOffset = rect->width-padding*4.0; 
            }
			float x = label->getRect()->getX()+spaceOffset;			
			float y = label->getRect()->getY()-padding; 
			float t = label->getRect()->height+padding*2.0; 			
			ofRect(x, y, cursorWidth, t); 
		}
		
		if(textstring.size() == 0 && !clicked)
		{
			ofFill(); 
            ofSetColor(color_fill); 
			label->drawString(rect->getX()+defaultX, rect->getY()+defaultY, defaultstring); 
		}        
    }
	
    void mouseMoved(int x, int y ) 
    {
        if(rect->inside(x, y))
        {
            state = OFX_UI_STATE_OVER;         			
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;
        }
        stateChange();         
    }
    
    void mouseDragged(int x, int y, int button) 
    {
        if(hit)
        {
            state = OFX_UI_STATE_DOWN;         
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;  
        }
        stateChange();     
    }
    
    void mousePressed(int x, int y, int button) 
    {
        if(rect->inside(x, y))
        {
			if(state == OFX_UI_STATE_OVER)
			{
				clicked = true; 
				theta = 0; 
                hit = true; 
			}
#ifdef TARGET_OPENGLES
			clicked = true;
			theta = 0;
			hit = true;
#endif
            state = OFX_UI_STATE_DOWN;     
			triggerType = OFX_UI_TEXTINPUT_ON_FOCUS; 
			triggerEvent(this); 			
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;
            if(clicked)
            {
                unClick();  
            }
        }
        stateChange();         
    }
    
    void mouseReleased(int x, int y, int button) 
    {
        if(hit)
        {
#ifdef TARGET_OPENGLES
            state = OFX_UI_STATE_NORMAL;        
#else            
            state = OFX_UI_STATE_OVER; 
#endif 
//			triggerType = OFX_UI_TEXTINPUT_ON_UNFOCUS; 
//			triggerEvent(this); 
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;         
        }
        hit = false; 
        stateChange();         
    }
	
    void keyPressed(int key) 
    {
    	ofLog(OF_LOG_VERBOSE, "openframeworks Drawnetic ofxUI keyPressed: %i", key);
		if(clicked)            
		{
            switch (key) 
			{
				case OF_KEY_BACKSPACE:
					if (textstring.size() > 0) 
					{
						textstring.erase(textstring.size()-1); 
                        displaystring = textstring;                         
                        while(label->getStringWidth(displaystring) > rect->width-padding*4.0)
                        {
                            string::iterator it;
                            it=displaystring.begin();
                            displaystring.erase (it);                    
                        }
						label->setLabel(displaystring);                           
					}
					break;
					
				case OF_KEY_RETURN:
					triggerType = OFX_UI_TEXTINPUT_ON_ENTER; 					
					triggerEvent(this); 			
					if(autoclear)
					{
						textstring.clear(); 
                        displaystring = textstring;                         
						label->setLabel(displaystring); 
					}
                    clicked = false; 
					break;
					
				case OF_KEY_RIGHT:
                    
					break;					
                    
				case OF_KEY_LEFT:
					
					break;					
                    
				case OF_KEY_UP:
					
					break;					
                    
				case OF_KEY_DOWN:
					
					break;					
	
				default:
                {
                    textstring+=key; 
                    displaystring+=key; 
                    while(label->getStringWidth(displaystring) > rect->width-padding*4.0)
                    {
                        string::iterator it;
                        it=displaystring.begin();
                        displaystring.erase (it);                    
                    }
                    label->setLabel(displaystring);                         
                }
					break;
			}
		}
    }
        
    void unClick()
    {
        if(clicked)
        {
            clicked = false;          
			triggerType = OFX_UI_TEXTINPUT_ON_UNFOCUS; 
			triggerEvent(this);             
        }
    }
    void stateChange()
    {        
        switch (state) {
            case OFX_UI_STATE_NORMAL:
            {            
                draw_fill_highlight = false;             
                draw_outline_highlight = false;  
				label->unfocus(); 								
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = true;  
				label->focus(); 								
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = true;             
				label->focus(); 					
            }
                break;
            case OFX_UI_STATE_SUSTAINED:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = false;                         
				label->unfocus(); 								
            }
                break;                            
            default:
                break;
        }        
    }
	
    void setVisible(bool _visible)
    {
        visible = _visible; 
        label->setVisible(visible); 
    }
    
	bool isClicked()
	{
		return clicked; 
	}
	
	ofxUILabel *getLabel()
	{
		return label; 
	}
	
	string getTextString()
	{
		return textstring; 
	}
	
	int getTriggerType()
	{
		return triggerType; 
	}
	
	void setTextString(string s)	
	{
		textstring = ""; 
		string temp = ""; 
		
        int length = s.length(); 
        
        if(length > 0)
        {
            for(int i = 0; i < length; i++)
            {
                temp+=s.at(i); 
                float newWidth = label->getStringWidth(temp); 
                
                if(newWidth < rect->width-padding*4.0)
                {
                    textstring+=s.at(i); 
                    label->setLabel(textstring); 
                }				
            }		
        }
        else
        {
            textstring = s; 
            label->setLabel(textstring);                
        }
        displaystring = textstring; 
	}
	
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
        if(rect->height == 0)
        {
            rect->height = label->getPaddingRect()->height+padding*2.0; 
        }
        label->setLabel(textstring);
		ofxUIRectangle *labelrect = label->getRect(); 
		float h = labelrect->getHeight(); 
		float ph = rect->getHeight(); 	
		
		labelrect->y = ph/2.0 - h/2.0; 
		defaultY = labelrect->y+labelrect->getHeight(); 
		defaultX = labelrect->x; 
 		
		paddedRect->height = rect->height+padding*2.0; 
		
		cursorWidth = label->getStringWidth("."); 
        
        while(label->getStringWidth(textstring) > rect->width-padding*4.0)
        {
            string::iterator it;
            it=textstring.begin();
            textstring.erase (it);                    
        }        
        
        defaultstring = textstring; 
		displaystring = textstring; 
        setTextString(textstring);        
	}	
	
	void setAutoClear(bool _autoclear)
	{
		autoclear = _autoclear; 
	}

    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	string textstring; 
	string defaultstring; 
    string displaystring; 
	bool clicked; 
	float theta; 
	float cursorWidth; 
	float spaceOffset;		
	bool autoclear; 
	float defaultY, defaultX; 	
	int triggerType;
    int maxsize; 
}; 

#endif
