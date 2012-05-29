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

#ifndef OFXUI_DROP_DOWN_LIST
#define OFXUI_DROP_DOWN_LIST

#include "ofxUIWidget.h"

class ofxUIDropDownList : public ofxUIToggle
{
public:    
    ofxUIDropDownList(float x, float y, float w, string _name, vector<string> items, int _size)
    {
        rect = new ofxUIRectangle(x,y,w,0);                     
        autoSize = false;         
        init(_name, items, _size);         
    }
    
    ofxUIDropDownList(float w, string _name, vector<string> items, int _size)
    {
        rect = new ofxUIRectangle(0,0,w,0);                     
        autoSize = false;         
        init(_name, items, _size);         
    }    
    
    ofxUIDropDownList(float x, float y, string _name, vector<string> items, int _size)
    {
        rect = new ofxUIRectangle(x,y,0,0); 
        autoSize = true; 
        init(_name, items, _size);         
    }
    
    ofxUIDropDownList(string _name, vector<string> items, int _size)
    {
        rect = new ofxUIRectangle(0,0,0,0); 
        autoSize = true; 
        init(_name, items, _size);         
    }    
    
    void init(string _name, vector<string> items, int _size)
    {
		name = _name; 		        
		kind = OFX_UI_WIDGET_DROPDOWNLIST; 		        
		paddedRect = new ofxUIRectangle(-padding, -padding, padding*2.0, padding*2.0);
		paddedRect->setParent(rect);     
        
        size = _size; 
        label = new ofxUILabel(0,0,(name+" LABEL"), name, _size); 
		label->setParent(label); 
		label->setRectParent(rect);
        label->setEmbedded(true);
        value = false;                                               //the widget's value
        draw_fill = value; 
        allowMultiple = false; 
        initToggles(items, _size);         
        autoClose = false; 
    }

    void clearToggles()
    {        
        while(toggles.size())
		{
			ofxUILabelToggle *t = toggles[0]; 			
            removeToggle(t->getName());
        }
    }    
    
    
    void addToggle(string toggleName)
    {        
        float yt = rect->getHeight();
        
		for(int i = 0; i < toggles.size(); i++)
		{
			ofxUILabelToggle *t = toggles[i]; 			
            yt +=t->getRect()->getHeight();         
		}	
        
        ofxUILabelToggle *ltoggle;         
        if(autoSize)
        {
            ltoggle = new ofxUILabelToggle(0, yt, false, toggleName, size);                 
        }
        else
        {
            ltoggle = new ofxUILabelToggle(0, yt, rect->getWidth(), rect->getHeight(), false, toggleName, size);                 
        }        
        ltoggle->setParent(this);
        ltoggle->getRect()->setParent(this->getRect());
        ltoggle->getRect()->y = rect->y+yt; 			        
        ltoggle->getRect()->x = rect->x; 			        
        ltoggle->setVisible(value); 
        ltoggle->setLabelVisible(value);             
        toggles.push_back(ltoggle);         
        
        parent->addWidget(ltoggle);
    }    
    
    void removeToggle(string toggleName)
    {
        ofxUILabelToggle *t = NULL; 
        for(int i = 0; i < toggles.size(); i++)
        {
            ofxUILabelToggle *other = (ofxUILabelToggle *)toggles[i];
            if(other->getName() == toggleName)
            {
                t = other;
                toggles.erase(toggles.begin()+i);                                             
                break; 
            }
        }
        if(t != NULL)
        {
            parent->removeWidget(t);
            
            float yt = rect->getHeight();
            for(int i = 0; i < toggles.size(); i++)
            {
                ofxUILabelToggle *t = toggles[i]; 			
                t->setParent(this); 
                t->getRect()->setParent(this->getRect());                 
                t->getRect()->y = yt; 
                t->getRect()->x = 0; 
                yt +=t->getRect()->getHeight();         
            }		            
            
        }
        
    }
    
    vector<ofxUIWidget *> & getSelected()
    {                 
        return selected;         
    }
    
    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
        label->setDrawPadding(false);
//        for(int i = 0; i < toggles.size(); i++)s
//        {
//            ofxUILabelToggle * toggle = (ofxUILabelToggle *) toggles[i];
//            toggle->setDrawPadding(false);
//        }
	}
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline; 
        label->setDrawPaddingOutline(false);
//        for(int i = 0; i < toggles.size(); i++)
//        {
//            ofxUILabelToggle * toggle = (ofxUILabelToggle *) toggles[i];
//            toggle->setDrawPaddingOutline(false);
//        }
    }  

    void initToggles(vector<string> &items, int _size)
    {
        float ty = 20;
		for(int i = 0; i < items.size(); i++)
		{
			string tname = items[i]; 
			ofxUILabelToggle *ltoggle; 
            if(autoSize)
            {
                ltoggle = new ofxUILabelToggle(0, ty, false, tname, _size);                 
            }
            else
            {
                ltoggle = new ofxUILabelToggle(0, ty, rect->getWidth(), false, tname, _size);                 
            }
            ltoggle->setVisible(value); 
            ltoggle->setLabelVisible(value);             
			toggles.push_back(ltoggle); 
            ty+=20; 
		}        
    }
    
    void setParent(ofxUIWidget *_parent)
	{
		parent = _parent;         
        rect->height = label->getPaddingRect()->height+padding*2.0; 
		ofxUIRectangle *labelrect = label->getRect(); 
        if(autoSize)
        {
            rect->width = label->getPaddingRect()->width+padding*2.0;             
        }
        else
        {
            while(labelrect->width+padding*4.0 > rect->width)
            {
                string labelstring = label->getLabel();
                string::iterator it;
                it=labelstring.end();
                it--; 
                labelstring.erase (it); 
                label->setLabel(labelstring);
            }             
        }

		float h = labelrect->getHeight(); 
		float ph = rect->getHeight(); 	        
        float w = labelrect->getWidth(); 
        float pw = rect->getWidth(); 
        
		labelrect->y = (int)(ph*.5 - h*.5);
        labelrect->x = (int)(pw*.5 - w*.5-padding*.5); 
		paddedRect->height = rect->height+padding*2.0;  
        paddedRect->width = rect->width+padding*2.0;          
                    
		float yt = rect->height;
		for(int i = 0; i < toggles.size(); i++)
		{
			ofxUILabelToggle *t = toggles[i]; 			
			t->setParent(this); 
			t->getRect()->setParent(this->getRect()); 
        
            t->getRect()->y = yt; 			
            yt +=t->getRect()->getHeight();         
            if(autoSize)
            {
                t->getRect()->setWidth(rect->getWidth());
            }
            t->getPaddingRect()->setWidth(paddedRect->getWidth()); 
		}			
	}	    
    
    void mouseReleased(int x, int y, int button) 
    {
        if(rect->inside(x, y) && hit)
        {
            setValue(!value);
            setToggleVisibility(value); 
#ifdef TARGET_OPENGLES
            state = OFX_UI_STATE_NORMAL;        
#else            
            state = OFX_UI_STATE_OVER; 
#endif 
			triggerEvent(this); 
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;         
        }
        stateChange();     
        hit = false; 
    }
        
    void setAutoClose(bool _autoClose)
    {
        autoClose = _autoClose; 
    }
    
    void open()
    {
        value = true; 
        setToggleVisibility(value); 
    }
    
    void close()
    {
        value = false; 
        setToggleVisibility(value); 
    }
    
    void setVisible(bool _visible)
    {
        visible = _visible; 
        label->setVisible(visible); 
        for(int i = 0; i < toggles.size(); i++)
        {
            ofxUILabelToggle * toggle = (ofxUILabelToggle *) toggles[i];
            toggle->setVisible(visible); 
        }
    }
    
    void setToggleVisibility(bool _value)
    {
        for(int i = 0; i < toggles.size(); i++)
        {
            ofxUILabelToggle * toggle = (ofxUILabelToggle *) toggles[i];
            toggle->setVisible(_value); 
            toggle->setLabelVisible(_value); 
        }
    }
    
    vector<ofxUILabelToggle *> &getToggles()
	{
		return toggles; 
	}

    void triggerEvent(ofxUIWidget *child)
	{        
        if(child == this)
        {
            parent->triggerEvent(child); 
            return; 
        }

        if(autoClose)
        {
            setValue(!value);
        }        
        setToggleVisibility(value);         

        
        if(!allowMultiple)
        {
            activateToggle(child->getName().c_str()); 
        }
        
        selected.clear();
        for(int i = 0; i < toggles.size(); i++)
		{
			ofxUILabelToggle *t = toggles[i]; 		
            if(t->getValue())
            {
                selected.push_back(t);
            }                           
        }        
            
        
		if(parent != NULL)
		{
            parent->triggerEvent(this);
			parent->triggerEvent(child); 
		}        
	}	    
    
	void activateToggle(string _name)
	{
		for(int i = 0; i < toggles.size(); i++)
		{
			ofxUILabelToggle *t = toggles[i]; 			
			if(!(t->getName().compare(_name.c_str())))
			{
				t->setValue(true); 					
			}
			else 
			{
                t->setValue(false); 
			}			
		}
	}    
    
    void setAllowMultiple(bool _allowMultiple)
    {
        allowMultiple = _allowMultiple; 
    }
    
    bool isOpen()
    {
        return value; 
    }
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    bool autoSize; 
    bool autoClose; 
    vector<ofxUILabelToggle *> toggles; 
    vector<ofxUIWidget *> selected; 
    bool allowMultiple; 
    int size;     
}; 

#endif
