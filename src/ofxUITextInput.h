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
    ofxUITextInput(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL) : ofxUIWidgetWithLabel()
    {
        init(_name, _textstring, w, h, x, y, _size);
    }
    
    // DON'T USE THE NEXT CONSTRUCTORS
    // This is maintained for backward compatibility and will be removed on future releases
    
    ofxUITextInput(float x, float y, float w, string _name, string _textstring, int _size, float h = 0) : ofxUIWidgetWithLabel() 
    {
        init(_name, _textstring, w, h, x, y, _size);
//        ofLogWarning("OFXUITEXTINPUT: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUITextInput(float w, string _name, string _textstring, int _size, float h = 0) : ofxUIWidgetWithLabel()
    {
        init(_name, _textstring, w, h, 0, 0, _size);
//        ofLogWarning("OFXUITEXTINPUT: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    void init(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
		name = string(_name);  		
		kind = OFX_UI_WIDGET_TEXTINPUT; 		
		textstring = _textstring; 
		defaultstring = _textstring;
		displaystring = _textstring;
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, padding*2.0);
		paddedRect->setParent(rect); 
        
		clicked = false;                                            //the widget's value
        autoclear = true;
        triggerOnClick = true;
		
		label = new ofxUILabel(padding*2.0,0,(name+" LABEL"), _size); 
		label->setParent(label); 
		label->setRectParent(rect); 
        label->setEmbedded(true);
        
		triggerType = OFX_UI_TEXTINPUT_ON_FOCUS;
		cursorWidth = 0; spaceOffset = 0; 		
		theta = 0;

        cursorPosition = 0;
        firstVisibleCharacterIndex = 0;
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
            ofxUIFill(); 
            ofxUISetColor(color_fill); 
            rect->draw(); 
        }
        if(clicked)
		{
            ofNoFill();
            ofxUISetColor(color_outline_highlight);
            rect->draw();
            
			float h = label->getRect()->height; 
			
			float ph = rect->getHeight(); 
			label->getRect()->y = ph/2.0 - h/2.0; 
			
            ofxUIFill(); 
			ofxUISetColor(label->getColorFillHighlight(), 255.0*fabs(cos(theta))); 
			theta +=0.05; 
			
            int displayCursorPosition = cursorPosition - firstVisibleCharacterIndex;
            string displayStringBeforeCursor = displaystring.substr(0, displayCursorPosition);
			spaceOffset = label->getStringWidth(displayStringBeforeCursor);

			float x = label->getRect()->getX()+spaceOffset;			
			float y = label->getRect()->getY()-padding; 
			float t = label->getRect()->height+padding*2.0; 			
			ofxUIDrawRect(x, y, cursorWidth, t); 
		}
		
		if(textstring.size() == 0 && !clicked)
		{
			ofxUIFill(); 
            ofxUISetColor(color_fill); 
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
            cursorPosition = label->getLabel().length();
            
            state = OFX_UI_STATE_DOWN;     
			triggerType = OFX_UI_TEXTINPUT_ON_FOCUS;
            
            if(triggerOnClick)
            {
                triggerEvent(this);
            }
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
		if(clicked)            
		{
            switch (key) 
			{
				case OF_KEY_BACKSPACE:
					if (textstring.size() > 0 && cursorPosition > 0)
					{
                        cursorPosition --;
                        textstring.erase(cursorPosition, 1);
                        
                        // when we're deleting the first visible character, shift the string to the right
                        if(firstVisibleCharacterIndex == cursorPosition)
                            firstVisibleCharacterIndex = 0;
                        recalculateDisplayString();
					}
					break;

                case OF_KEY_DEL:
					if (textstring.size() > 0 && cursorPosition < textstring.length())
					{
                        textstring.erase(cursorPosition, 1);
                        recalculateDisplayString();
					}
					break;
					
				case OF_KEY_RETURN:

                    triggerType = OFX_UI_TEXTINPUT_ON_ENTER;
					triggerEvent(this);
					if(autoclear)
					{
						textstring.clear(); 
                        recalculateDisplayString();
					}
                    clicked = false;
					break;
					
				case OF_KEY_RIGHT:
                case OF_KEY_DOWN:
                    if(cursorPosition < textstring.length())
                    {
                        cursorPosition ++;
                        recalculateDisplayString();
                    }
					break;					
                    
				case OF_KEY_LEFT:
                case OF_KEY_UP:
                    if(cursorPosition > 0)
                    {
                        cursorPosition --;
                        recalculateDisplayString();
                    }
					break;

#if (OF_VERSION_MINOR > 7)
                case OF_KEY_TAB:
                case OF_KEY_COMMAND:
                case OF_KEY_CONTROL:
                case OF_KEY_LEFT_SHIFT:
                case OF_KEY_RIGHT_SHIFT:
                case OF_KEY_LEFT_CONTROL:
                case OF_KEY_RIGHT_CONTROL:
                case OF_KEY_LEFT_ALT:
                case OF_KEY_RIGHT_ALT:
                case OF_KEY_LEFT_SUPER:
                case OF_KEY_RIGHT_SUPER:					
#endif
                case OF_KEY_F1:
                case OF_KEY_F2:
                case OF_KEY_F3:
                case OF_KEY_F4:
                case OF_KEY_F5:
                case OF_KEY_F6:
                case OF_KEY_F7:
                case OF_KEY_F8:
                case OF_KEY_F9:
                case OF_KEY_F10:
                case OF_KEY_F11:
                case OF_KEY_F12:
                case OF_KEY_PAGE_UP:
                case OF_KEY_PAGE_DOWN:
                case OF_KEY_HOME:
                case OF_KEY_END:
                case OF_KEY_INSERT:
                case OF_KEY_ALT:
                case OF_KEY_SHIFT:
                break;
                    
				default:
                {
                    textstring.insert(cursorPosition, 1, key);
                    cursorPosition++;
                    recalculateDisplayString();
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
	
    void setTriggerType(int _triggerType)
    {
        triggerType = _triggerType; 
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
        if(rect->height == 0 || rect->height < label->getPaddingRect()->height+padding*2.0)
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
    
    void setTriggerOnClick(bool _triggerOnClick)
    {
        triggerOnClick = _triggerOnClick;
    }
    
    void recalculateDisplayString()
    {
        // the maximum width of the displaystring
        float maxWidth = rect->width-padding*4.0;
        
        displaystring = textstring;
        string stringBeforeCursor = displaystring.substr(0, cursorPosition);
        string stringBeforeLabel =  displaystring.substr(0, firstVisibleCharacterIndex);
        
        // if the cursoroffset - length of the (invisible) string before the label < 0, we have to shift our string to the left to get our cursor in the label
        while(label->getStringWidth(stringBeforeCursor) - label->getStringWidth(stringBeforeLabel) < 0){
            firstVisibleCharacterIndex --;
            stringBeforeLabel =  displaystring.substr(0, firstVisibleCharacterIndex);
        }

        // if the cursoroffset - length of the (invisible) string before the label is > maximum width, we have to shift to the right
        while(label->getStringWidth(stringBeforeCursor) - label->getStringWidth(stringBeforeLabel) > maxWidth){
            firstVisibleCharacterIndex ++;
            stringBeforeLabel =  displaystring.substr(0, firstVisibleCharacterIndex);
        }
        
        // we now know how long the string before the label should be, so trim it off
        displaystring = displaystring.substr(MIN(firstVisibleCharacterIndex, displaystring.length()));
        
        // trim off the end of the string until it fits
        while(label->getStringWidth(displaystring) > maxWidth && displaystring.length() > 0)
        {
            displaystring = displaystring.substr(0, displaystring.size()-1);
        }
        
        label->setLabel(displaystring);
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
    bool triggerOnClick;
    
    unsigned int cursorPosition;
    unsigned int firstVisibleCharacterIndex;
}; 

#endif
