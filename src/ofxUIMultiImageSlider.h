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

#ifndef OFXUI_MULTI_IMAGE_SLIDER
#define OFXUI_MULTI_IMAGE_SLIDER

#include "ofxUISlider.h"
#include "ofxUIRectangle.h"

class ofxUIMultiImageSlider : public ofxUISlider
{
public:    
    ofxUIMultiImageSlider(float x, float y, float w, float h, float _min, float _max, float _value, string _pathURL, string _name, int _size = OFX_UI_FONT_SMALL)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h, _min, _max, _value, _pathURL, _name, _size); 		
    }
    
    ofxUIMultiImageSlider(float w, float h, float _min, float _max, float _value, string _pathURL, string _name, int _size = OFX_UI_FONT_SMALL)
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h, _min, _max, _value, _pathURL, _name, _size); 
    }    
    
    virtual void init(float w, float h, float _min, float _max, float _value, string _pathURL, string _name, int _size)
    {
        name = _name; 				
		if(w > h)
		{
			kind = OFX_UI_WIDGET_MULTIIMAGESLIDER_H;  			
		}
		else 
		{
			kind = OFX_UI_WIDGET_MULTIIMAGESLIDER_V;  			
		}
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect);     
        
        draw_fill = true; 
        
        value = _value;                                               //the widget's value
		max = _max; 
		min = _min; 
        labelPrecision = 2;
        
		if(value > max)
		{
			value = max; 
		}
		if(value < min)
		{
			value = min; 
		}
		
		value = ofMap(value, min, max, 0.0, 1.0, true); 
        
		if(kind == OFX_UI_WIDGET_MULTIIMAGESLIDER_H)
		{
			label = new ofxUILabel(0,h+padding,(name+" LABEL"), (name + ": " + ofToString(max,labelPrecision)), _size); 
		}
		else 
		{
			label = new ofxUILabel(0,h+padding,(name+" LABEL"), name, _size); 	
		}
        
		label->setParent(label); 
		label->setRectParent(rect); 
        label->setEmbedded(true);
        increment = fabs(max - min) / 10.0;
        
        string coreURL = _pathURL;
        string extension = "";
        string period (".");
        size_t found;        
        
        found=_pathURL.find(period);
        if (found!=string::npos)        
        {
            coreURL = _pathURL.substr(0,found);
            extension = _pathURL.substr(found);
        }
        
        track = new ofImage();         //back
        track->loadImage(coreURL+"track"+extension);
        
        progress = new ofImage();      //fill
        progress->loadImage(coreURL+"progress"+extension);        
        
        handle = new ofImage();        //handle
        handle->loadImage(coreURL+"handle"+extension);
        
        handleDown = new ofImage();    //handleOver State                        
        handleDown->loadImage(coreURL+"handledown"+extension);        
        
        if(kind == OFX_UI_WIDGET_MULTIIMAGESLIDER_H)
        {
            if(handle->getHeight() > rect->getHeight())
            {
                float hh = handle->getHeight(); 
                float hw = handle->getWidth();
                float aspect = hh/hw; 
                handle->resize(rect->getHeight()/aspect,rect->getHeight());
                handleDown->resize(rect->getHeight()/aspect,rect->getHeight());
            }
        }
        else
        {
            if(handle->getWidth() > rect->getWidth())
            {
                float hh = handle->getHeight(); 
                float hw = handle->getWidth();
                float aspect = hh/hw; 
                handle->resize(rect->getWidth(),rect->getWidth()*aspect);
                handleDown->resize(rect->getWidth(),rect->getWidth()*aspect);
            }            
        }
        
        handleHalfWidth = handle->getWidth()*.5;
        handleHalfHeight = handle->getHeight()*.5;
        
        if(kind == OFX_UI_WIDGET_MULTIIMAGESLIDER_H)
        {
            imageRect = new ofxUIRectangle(handleHalfWidth,0,rect->getWidth()-handle->getWidth(), rect->getHeight());
        }
        else
        {
            imageRect = new ofxUIRectangle(0,handleHalfHeight,rect->getWidth(), rect->getHeight()-handle->getHeight());            
        }
        imageRect->setParent(rect);     
    }
    
    ~ofxUIMultiImageSlider()
    {
        delete track; 
        delete progress; 
        delete handle; 
        delete handleDown;
        delete imageRect; 
    }
    
    
    virtual void drawBack() 
    {
        if(draw_back)
        {
            ofSetColor(255); 
            track->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight()); 
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
        
    }    
    
    virtual void drawFill() 
    {
        if(draw_fill)
        {			 
            ofSetColor(255); 
			if(kind == OFX_UI_WIDGET_MULTIIMAGESLIDER_H)
			{	
                progress->drawSubsection(rect->getX(), rect->getY(), rect->getWidth()*value, rect->getHeight(), 0,0, rect->getWidth()*value, rect->getHeight());
                ofSetRectMode(OF_RECTMODE_CENTER);
                handle->draw(imageRect->getX()+imageRect->getWidth()*value, imageRect->getY()+rect->getHalfHeight());                    
                ofSetRectMode(OF_RECTMODE_CORNER);
			}
			else 
			{

                progress->drawSubsection(rect->getX(), rect->getY()+(1.0-value)*rect->getHeight(), rect->getWidth(), rect->getHeight(), 0, (1.0-value)*rect->getHeight(), rect->getWidth(), value*rect->getHeight());
                ofSetRectMode(OF_RECTMODE_CENTER);                
                handle->draw(imageRect->getX()+rect->getHalfWidth(), imageRect->getY()+imageRect->getHeight()-imageRect->getHeight()*value);                                            
                ofSetRectMode(OF_RECTMODE_CORNER);            
			}
        }
    }
    
    virtual void drawFillHighlight() 
    {
        if(draw_fill_highlight)
        {
            ofSetColor(255); 
			if(kind == OFX_UI_WIDGET_MULTIIMAGESLIDER_H)
			{			   
                progress->drawSubsection(rect->getX(), rect->getY(), rect->getWidth()*value, rect->getHeight(), 0,0);
                ofSetRectMode(OF_RECTMODE_CENTER);
                handleDown->draw(imageRect->getX()+imageRect->getWidth()*value, imageRect->getY()+imageRect->getHalfHeight());                    
                ofSetRectMode(OF_RECTMODE_CORNER);
			}
			else 
			{
                progress->drawSubsection(rect->getX(), rect->getY()+(1.0-value)*rect->getHeight(), rect->getWidth(), rect->getHeight(), 0, (1.0-value)*rect->getHeight());                
                ofSetRectMode(OF_RECTMODE_CENTER);                
                handleDown->draw(imageRect->getX()+imageRect->getHalfWidth(), imageRect->getY()+imageRect->getHeight()-imageRect->getHeight()*value);                                            
                ofSetRectMode(OF_RECTMODE_CORNER);            
			}	
			if(kind == OFX_UI_WIDGET_MULTIIMAGESLIDER_V)
			{
				label->drawString(imageRect->getX()+imageRect->getWidth()+padding, label->getRect()->getHeight()/2.0+imageRect->getY()+imageRect->getHeight()-imageRect->getHeight()*value, ofToString(getScaledValue(),labelPrecision)); 
			}
        }        
    }
    
    virtual void stateChange()
    {                
        switch (state) {
            case OFX_UI_STATE_NORMAL:
            {            
                draw_back = true; 
                draw_fill = true; 
                draw_fill_highlight = false;             
                draw_outline_highlight = false;             
				label->unfocus(); 				
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_back = true;       
                draw_fill = true;                
                draw_fill_highlight = false;            
                draw_outline_highlight = false;    
				label->unfocus(); 
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
                draw_back = true;   
                draw_fill = false;                
                draw_fill_highlight = true;            
                draw_outline_highlight = false;             
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
    
    virtual void input(float x, float y)
	{
		if(kind == OFX_UI_WIDGET_MULTIIMAGESLIDER_H)
		{
			value = imageRect->percentInside(x, y).x;             
		}
		else 
		{
			value = 1.0-imageRect->percentInside(x, y).y; 
		}	
        
        if(value > 1.0)
        {
            value = 1.0;
        }
        else if(value < 0.0)
        {
            value = 0.0;
        }                      
		updateLabel(); 
	}
    
	virtual void updateLabel()
	{
		if(kind == OFX_UI_WIDGET_MULTIIMAGESLIDER_H)
		{
			label->setLabel(name + ": " + ofToString(getScaledValue(),labelPrecision)); 		
		}		
	}
    
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    ofImage *track;         //back
    ofImage *progress;      //fill
    ofImage *handle;        //handle
    ofImage *handleDown;    //handleOver State    
    int handleHalfWidth; 
    int handleHalfHeight; 
    ofxUIRectangle *imageRect;
    
    
}; 

#endif
