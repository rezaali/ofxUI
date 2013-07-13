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

#ifndef OFXUI_TOGGLE_MATRIX
#define OFXUI_TOGGLE_MATRIX

#include "ofxUIWidgetWithLabel.h"
#include "ofxUIToggle.h"

class ofxUIToggleMatrix : public ofxUIWidget
{
public:
    ofxUIToggleMatrix(float x, float y, float w, float h, int _rows, int _cols, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h, _rows, _cols, _name, _size);
    }
    
    ofxUIToggleMatrix(float w, float h, int _rows, int _cols, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h, _rows, _cols, _name, _size);
    }    
    
    void init(float w, float h, int _rows, int _cols, string _name, int _size = OFX_UI_FONT_SMALL)
    {
        name = string(_name);  		
		kind = OFX_UI_WIDGET_TOGGLEMATRIX; 		
		rows = _rows; 
        cols = _cols; 
        draw_back = false;  
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect); 
        		
        toggleWidth = w;
        toggleHeight = h;
                
        ofPoint pos = ofPoint(0,0); 
        for(int j = 0; j < rows; j++)
        {
            for(int i = 0; i < cols; i++)
            {
                ofxUIToggle *toggle = new ofxUIToggle(pos.x,pos.y, toggleWidth, toggleHeight, false, (name+"("+ofxUIToString(i,0)+","+ofxUIToString(j,0)+")"));
                toggle->setLabelVisible(false);
                toggle->setEmbedded(true); 
                toggles.push_back(toggle);                 
                pos.x += toggleWidth+padding;
            }
            pos.y += toggleHeight+padding;
            pos.x = 0;
        }
        allowMultiple = true;  
    }
	
    void setVisible(bool _visible)
    {
        visible = _visible;   
		for(unsigned int i = 0; i < toggles.size(); i++)
		{
			ofxUIToggle *t = toggles[i]; 			
            t->setVisible(visible);
            t->getLabelWidget()->setVisible(false);
        }
    }
    
	void activateToggle(string _name)
	{
		for(unsigned int i = 0; i < toggles.size(); i++)
		{
			ofxUIToggle *t = toggles[i]; 			
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
	
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
        
        float tWidth = cols*(toggles[0]->getRect()->width)+cols*padding;
		float tHeight = rows*(toggles[0]->getRect()->height)+rows*padding;


        ofPoint pos = ofPoint(0,0);
        for(int j = 0; j < rows; j++)
        {
            for(int i = 0; i < cols; i++)
            {
                int index = i+j*cols; 
                ofxUIToggle *t = toggles[index];
                t->setParent(this);
                t->getRect()->setParent(this->getRect());                
                t->getRect()->setX(pos.x);
                t->getRect()->setY(pos.y);
                t->setLabelVisible(false);
                pos.x += toggleWidth+padding;
            }
            pos.y += toggleHeight+padding;
            pos.x = 0;            
        }
                    
        rect->setWidth(tWidth);
        rect->setHeight(tHeight); 
		paddedRect->width = rect->getWidth()+padding*2;
		paddedRect->height = rect->getHeight()+padding*2;
	}	
    
    void setAllToggles(bool _value)
    {
		for(unsigned int i = 0; i < toggles.size(); i++)
		{
			ofxUIToggle *t = toggles[i]; 			
            t->setValue(_value);
        }        
    }
    
    void setAllTogglesAndTrigger(bool _value)
    {
		for(unsigned int i = 0; i < toggles.size(); i++)
		{
			ofxUIToggle *t = toggles[i]; 			
            t->setValue(_value);
        }        
        
        for(unsigned int i = 0; i < toggles.size(); i++)
		{
            triggerEvent(toggles[i]); 
        }        
    }
    
    void setToggle(unsigned int x, unsigned int y, bool _value)
    {
        if(x*y < toggles.size())
        {
            toggles[x+y*rows]->setValue(_value);
        }
    }
	
    void setToggleAndTrigger(int x, int y, bool _value)
    {
        setToggle(x,y,_value); 
        triggerEvent(toggles[x+y*rows]); 
        
    }

	vector<ofxUIToggle *> getToggles()
	{
		return toggles;
	}

	vector<ofxUIToggle *> *getTogglesPtr()
	{
		return &toggles;
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
    
    void setAllowMultiple(bool _allowMultiple)
    {
        allowMultiple = _allowMultiple; 
    }
    
    virtual void mouseDragged(int x, int y, int button)
    {
        if(hit)
        {
            bool tv = false;
            if(ofGetKeyPressed())
            {
                tv = true;
            }
            
            for(vector<ofxUIToggle *>::iterator it = toggles.begin(); it != toggles.end(); ++it)
            {
                if((*it)->isHit(x, y))
                {
                    (*it)->setValue(tv);
                }
            }
        }
    }
    
    virtual void mousePressed(int x, int y, int button)
    {
        if(rect->inside(x, y))
        {
            hit = true;
            state = OFX_UI_STATE_DOWN;
        }
        else
        {
            state = OFX_UI_STATE_NORMAL;
        }
        stateChange();
    }
    
    virtual void mouseReleased(int x, int y, int button)
    {
        if(hit)
        {
            hit = false;
        }
    }
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	vector<ofxUIToggle *> toggles; 		   
    int rows, cols;
    float toggleWidth, toggleHeight; 
    bool allowMultiple;     
};

#endif
