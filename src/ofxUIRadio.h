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

#ifndef OFXUI_RADIO
#define OFXUI_RADIO

#include "ofxUIWidgetWithLabel.h"
#include "ofxUIToggle.h"

class ofxUIRadio : public ofxUIWidgetWithLabel
{
public:
    ofxUIRadio(string _name, vector<string> names, int _orientation, float w, float h, float x = 0, float y = 0)
    {
        init(_name, names, _orientation, w, h, x, y);
    }
    
    // DON'T USE THE NEXT CONSTRUCTORS
    // This is maintained for backward compatibility and will be removed on future releases
    
    ofxUIRadio(float x, float y, float w, float h, string _name, vector<string> names, int _orientation)
    {
        init(_name, names, _orientation, w, h, x, y);
        ofLogWarning("OFXUIRADIO: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }

    ofxUIRadio(float w, float h, string _name, vector<string> names, int _orientation)
    {
        init(_name, names, _orientation, w, h, 0, 0);
        ofLogWarning("OFXUIRADIO: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }    
    
    void init(string _name, vector<string> names, int _orientation, float w, float h, float x = 0, float y = 0)
    {
        rect = new ofxUIRectangle(x,y,w,h);
		name = _name; 		
		kind = OFX_UI_WIDGET_RADIO; 		
        
        draw_back = false; 
        orientation = _orientation; 
		
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect); 
		
		label = new ofxUILabel(0,0,(name+" LABEL"), name, OFX_UI_FONT_MEDIUM); 
		label->setParent(label); 
		label->setRectParent(rect); 
        label->setEmbedded(true);
        
		for(int i = 0; i < names.size(); i++)
		{
			string tname = names[i]; 
			ofxUIToggle *toggle = new ofxUIToggle(0,0, w, h, false, tname); 
			toggles.push_back(toggle); 
		}
        active = NULL; 
        allowMultiple = false; 
    }
        
    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
        label->setDrawPadding(false);
		for(int i = 0; i < toggles.size(); i++)
		{
			ofxUIToggle *t = toggles[i]; 			
            t->setDrawPadding(false);             
        }           
	}
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline; 
        label->setDrawPaddingOutline(false);
		for(int i = 0; i < toggles.size(); i++)
		{
			ofxUIToggle *t = toggles[i]; 			
            t->setDrawPaddingOutline(false);             
        }        
	}  
    
	ofxUILabel *getLabel()
	{
		return label; 
	}
	    
    void setVisible(bool _visible)
    {
        visible = _visible; 
        label->setVisible(visible); 
		for(int i = 0; i < toggles.size(); i++)
		{
			ofxUIToggle *t = toggles[i]; 			
            t->setVisible(visible);             
        }
    }
	void activateToggle(string _name)
	{
		for(int i = 0; i < toggles.size(); i++)
		{
			ofxUIToggle *t = toggles[i]; 			
			if(!(t->getName().compare(_name.c_str())))
			{
				t->setValue(true); 			
                active = t; 
			}
			else 
			{
				t->setValue(false); 
			}			
		}
	}
    
    void triggerSelf()
    {
		if(parent != NULL)
		{
			parent->triggerEvent(active); 
		}        
    }
	
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
		
		float tWidth = label->getPaddingRect()->width; 
		float tHeight = label->getPaddingRect()->height; 

		float xt = 0; 
		float yt = label->getPaddingRect()->height;
		
		for(int i = 0; i < toggles.size(); i++)
		{
			ofxUIToggle *t = toggles[i]; 			
			t->setParent(this); 
			t->getRect()->setParent(this->getRect()); 
			
			
			if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
			{
				t->getRect()->x = xt; 
				t->getRect()->y = yt; 				
				xt+=t->getPaddingRect()->width; 
				tHeight = label->getPaddingRect()->height+t->getPaddingRect()->height; 								
			}			
			else 
			{
				xt+=t->getPaddingRect()->width; 				
				t->getRect()->y = yt; 			
				if(t->getPaddingRect()->width > tWidth)
				{
					tWidth = t->getPaddingRect()->width; 
				}
				tHeight+=t->getPaddingRect()->height; 				
				yt +=t->getPaddingRect()->getHeight(); 
			}			
		}
        
        if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
        {            
            if(xt > tWidth)
            {
                tWidth = xt; 
            }
        }
        rect->setHeight(tHeight);
		tHeight += padding; 
		paddedRect->width = tWidth; 	
		paddedRect->height = tHeight; 			
	}	
	
	vector<ofxUIToggle *> getToggles()
	{
		return toggles; 
	}
	
	void triggerEvent(ofxUIWidget *child)
	{
        if(!allowMultiple)
        {
            activateToggle(child->getName().c_str()); 
        }
		if(parent != NULL)
		{
			parent->triggerEvent(child); 
		}
	}	
    
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	int orientation; 
	vector<ofxUIToggle *> toggles; 		
    ofxUIToggle *active; 
    bool allowMultiple;
}; 

#endif